// ======================================================================
// \title  GpsComponent.hpp
// \author apujara22
// \brief  hpp file for GpsComponent component implementation class
// ======================================================================

#ifndef GpsModule_GpsComponent_HPP
#define GpsModule_GpsComponent_HPP

#include "GpsModule/Components/GpsComponent/GpsComponentComponentAc.hpp"

namespace GpsModule {

class GpsComponent final : public GpsComponentComponentBase {
  public:
    // ----------------------------------------------------------------------
    // Component construction and destruction
    // ----------------------------------------------------------------------

    //! Construct GpsComponent object
    GpsComponent(const char* const compName  //!< The component name
    );

    //! Destroy GpsComponent object
    ~GpsComponent();

  private:
    // ----------------------------------------------------------------------
    // Handler implementations for typed input ports
    // ----------------------------------------------------------------------

    //! Handler implementation for drvConnected
    //!
    //! Ready signal when driver is connected
    void drvConnected_handler(FwIndexType portNum  //!< The port number
                              ) override;

    //! Handler implementation for drvReceiveIn
    //!
    //! Receive (read) data from driver.
    void drvReceiveIn_handler(FwIndexType portNum,  //!< The port number
                              Fw::Buffer& buffer,
                              const Drv::ByteStreamStatus& status) override;

  private:
    // ----------------------------------------------------------------------
    // Handler implementations for commands
    // ----------------------------------------------------------------------

    //! Handler implementation for command REPORT_UTCTIME
    //!
    //! Command that triggers an event which returns UTC time
    void REPORT_UTCTIME_cmdHandler(FwOpcodeType opCode,  //!< The opcode
                                   U32 cmdSeq            //!< The command sequence number
                                   ) override;

    // ADDED:
        // Accumulates bytes until a complete NMEA sentence is received
        char m_nmeaBuffer[128];
        U32 m_nmeaIndex;

        // Most recently received valid GPS UTC time, in seconds since midnight
        F64 m_utcTime;
        bool m_hasValidUtcTime;

};

}  // namespace GpsModule

#endif
