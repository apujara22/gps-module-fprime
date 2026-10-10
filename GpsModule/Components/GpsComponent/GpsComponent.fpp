module GpsModule {
    @ GPS component for F Prime Project 0
    active component GpsComponent {

        import Drv.ByteStreamDriverClient

        # One async command/port is required for active components
        # This should be overridden by the developers with a useful command/port

        @ Command that triggers an event which returns UTC time
        async command REPORT_UTCTIME()

        @ Trigger event if GPS does not have a lock
        event NoLock \
            severity warning high \
            format "No GPS lock"

        @ Log to the console if there's an error parsing a string
        event ParseError \
            severity activity high \
            format "There was an error parsing the string"

        @ Event that reports UTC time
        event ReportUtcTime(UtcTime: F64) \
            severity activity high \
            format "Current UTC time is {}"

        @ Event that outputs GPS reading
        event GpsReading(lat: F64, lon: F64, alt: F32) \
            severity activity low \
            format "GPS reading: lat={f}, lon={f}, alt={f} m"
        
        telemetry UTCTime: F64
        telemetry Latitude: F64
        telemetry Longitude: F64
        telemetry Altitude: F32

        # @ other port
        # output port deallocate: Fw.BufferSend

        # @ Port for receiving data
        # async input port UartRead: Drv.ByteStreamManager

        


        ##############################################################################
        #### Uncomment the following examples to start customizing your component ####
        ##############################################################################

        # @ Example async command
        # async command COMMAND_NAME(param_name: U32)

        # @ Example telemetry counter
        # telemetry ExampleCounter: U64

        # @ Example event
        # event ExampleStateEvent(example_state: Fw.On) severity activity high id 0 format "State set to {}"

        # @ Example port: receiving calls from the rate group
        # sync input port run: Svc.Sched

        # @ Example parameter
        # param PARAMETER_NAME: U32

        ###############################################################################
        # Standard AC Ports: Required for Channels, Events, Commands, and Parameters  #
        ###############################################################################
        @ Port for requesting the current time
        time get port timeCaller

        @ Enables command handling
        import Fw.Command

        @ Enables event handling
        import Fw.Event

        @ Enables telemetry channels handling
        import Fw.Channel

        

    }
}


