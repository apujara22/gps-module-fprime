// ======================================================================
// \title  GpsComponent.cpp
// \author apujara22
// \brief  cpp file for GpsComponent component implementation class
// ======================================================================

#include "GpsModule/Components/GpsComponent/GpsComponent.hpp"
// #include "Drv/ByteStreamDriverModel/ByteStreamDriverModel.hpp"

#include <string>

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>

namespace {

bool parseGgaSentence(
    char* sentence,
    F64& utcTime,
    F64& latitude,
    F64& longitude,
    F32& altitude,
    F32& groundSpeed,
    bool& hasFix
) {
    char* fields[16] = {};
    U32 count = 0;
    char* p = sentence;

    // Split while preserving empty fields between consecutive commas.
    while (count < 16) {
        fields[count++] = p;
        char* comma = std::strchr(p, ',');
        if (comma == nullptr) {
            break;
        }
        *comma = '\0';
        p = comma + 1;
    }

    if (count < 10 ||
        (std::strcmp(fields[0], "$GPGGA") != 0 &&
         std::strcmp(fields[0], "$GNGGA") != 0)) {
        return false;
    }

    // UTC field must contain hhmmss.
    if (std::strlen(fields[1]) < 6) {
        return false;
    }

    const F64 hours = std::atof(std::string(fields[1], 2).c_str());
    const F64 minutes = std::atof(std::string(fields[1] + 2, 2).c_str());
    const F64 seconds = std::atof(fields[1] + 4);

    utcTime = hours * 3600.0 + minutes * 60.0 + seconds;

    const int fixQuality = std::atoi(fields[6]);
    hasFix = fixQuality > 0;

    // A valid GGA sentence can report no fix and empty coordinates.
    if (!hasFix) {
        return true;
    }

    if (fields[2][0] == '\0' || fields[3][0] == '\0' ||
        fields[4][0] == '\0' || fields[5][0] == '\0' ||
        fields[9][0] == '\0') {
        return false;
    }

    const F64 latRaw = std::atof(fields[2]);
    const F64 lonRaw = std::atof(fields[4]);

    latitude = std::floor(latRaw / 100.0) +
        (latRaw - std::floor(latRaw / 100.0) * 100.0) / 60.0;

    longitude = std::floor(lonRaw / 100.0) +
        (lonRaw - std::floor(lonRaw / 100.0) * 100.0) / 60.0;

    if (fields[3][0] == 'S') {
        latitude = -latitude;
    }
    if (fields[5][0] == 'W') {
        longitude = -longitude;
    }

    altitude = static_cast<F32>(std::atof(fields[9]));
    groundSpeed = 0.0F;

    return true;
}

}  // namespace

namespace GpsModule {

// ----------------------------------------------------------------------
// Component construction and destruction
// ----------------------------------------------------------------------

GpsComponent ::GpsComponent(const char* const compName)
    : GpsComponentComponentBase(compName),
      m_nmeaIndex(0),
      m_utcTime(0.0),
      m_hasValidUtcTime(false) {
    std::memset(m_nmeaBuffer, 0, sizeof(m_nmeaBuffer));
}

GpsComponent ::~GpsComponent() {}

// ----------------------------------------------------------------------
// Handler implementations for typed input ports
// ----------------------------------------------------------------------

void GpsComponent ::drvConnected_handler(FwIndexType portNum) {
    // The UART driver is connected and ready to communicate.
}

void GpsComponent ::drvReceiveIn_handler(
    FwIndexType portNum,
    Fw::Buffer& buffer,
    const Drv::ByteStreamStatus& status
) {
    if (status == Drv::ByteStreamStatus::OP_OK) {
        const U8* data = buffer.getData();
        const U32 size = buffer.getSize();

        for (U32 i = 0; i < size; ++i) {
            const char c = static_cast<char>(data[i]);

            if (c == '\r') {
                continue;
            }

            if (c == '\n') {
                if (m_nmeaIndex > 0) {
                    m_nmeaBuffer[m_nmeaIndex] = '\0';

                    // Parse only GGA sentences.
                    if (std::strncmp(m_nmeaBuffer, "$GPGGA,", 7) == 0 ||
                        std::strncmp(m_nmeaBuffer, "$GNGGA,", 7) == 0) {

                        // Parsing modifies its input, so use a copy.
                        char sentence[128];
                        std::strncpy(
                            sentence,
                            m_nmeaBuffer,
                            sizeof(sentence) - 1
                        );
                        sentence[sizeof(sentence) - 1] = '\0';

                        F64 utcTime = 0.0;
                        F64 latitude = 0.0;
                        F64 longitude = 0.0;
                        F32 altitude = 0.0F;
                        F32 groundSpeed = 0.0F;
                        bool hasFix = false;

                        if (parseGgaSentence(
                                sentence,
                                utcTime,
                                latitude,
                                longitude,
                                altitude,
                                groundSpeed,
                                hasFix)) {

                            m_utcTime = utcTime;
                            m_hasValidUtcTime = true;

                            if (hasFix) {
                                
                                this->tlmWrite_UTCTime(utcTime);
                                this->tlmWrite_Latitude(latitude);
                                this->tlmWrite_Longitude(longitude);
                                this->tlmWrite_Altitude(altitude);

                                this->log_ACTIVITY_LO_GpsReading(
                                    latitude,
                                    longitude,
                                    altitude
                                );
                            } else {
                                this->log_WARNING_HI_NoLock();
                            }
                        } else {
                            this->log_ACTIVITY_HI_ParseError();
                        }
                    }

                    m_nmeaIndex = 0;
                }
            } else if (m_nmeaIndex < sizeof(m_nmeaBuffer) - 1) {
                m_nmeaBuffer[m_nmeaIndex++] = c;
            } else {
                // Sentence exceeded the buffer capacity; reset and resync.
                m_nmeaIndex = 0;
                this->log_ACTIVITY_HI_ParseError();
            }
        }
    }

    // Return the received buffer to the UART driver.
    this->drvReceiveReturnOut_out(0, buffer);
}

// ----------------------------------------------------------------------
// Handler implementations for commands
// ----------------------------------------------------------------------

void GpsComponent ::REPORT_UTCTIME_cmdHandler(
    FwOpcodeType opCode,
    U32 cmdSeq
) {
    if (m_hasValidUtcTime) {
        const U32 totalSeconds = static_cast<U32>(m_utcTime);
        const U32 hours = totalSeconds / 3600;
        const U32 minutes = (totalSeconds % 3600) / 60;
        const U32 seconds = totalSeconds % 60;

        this->log_ACTIVITY_HI_ReportUtcTime(hours, minutes, seconds);
        this->cmdResponse_out(opCode, cmdSeq, Fw::CmdResponse::OK);
    } else {
        this->log_ACTIVITY_HI_ParseError();
        this->cmdResponse_out(
            opCode,
            cmdSeq,
            Fw::CmdResponse::EXECUTION_ERROR
        );
    }
}

}  // namespace GpsModule
