telemetry packets GpsDeployPackets {

  packet CDH id 1 group 1 {
    CdhCore.cmdDisp.CommandsDispatched
    CdhCore.cmdDisp.CommandsDropped
    #CdhCore.tlmSend.SendLevel # uncomment when using TlmPacketizer

    FileHandling.fileUplink.FilesReceived
    FileHandling.fileUplink.PacketsReceived
    FileHandling.fileDownlink.FilesSent
    FileHandling.fileDownlink.PacketsSent
    FileHandling.fileManager.CommandsExecuted

    GpsModule.cmdSeq.CS_LoadCommands
    GpsModule.cmdSeq.CS_CancelCommands
    GpsModule.cmdSeq.CS_CommandsExecuted
    GpsModule.cmdSeq.CS_SequencesCompleted
    ComCcsds.comQueue.comQueueDepth
    ComCcsds.comQueue.buffQueueDepth
    ComCcsds.commsBufferManager.TotalBuffs
    ComCcsds.commsBufferManager.CurrBuffs
    ComCcsds.commsBufferManager.HiBuffs

    GpsModule.rateGroup_1Hz.RgMaxTime
    GpsModule.rateGroup_0_5Hz.RgMaxTime
    GpsModule.rateGroup_0_25Hz.RgMaxTime
  }

  packet CDHErrors id 2 group 1 {
    CdhCore.$health.PingLateWarnings

    FileHandling.fileUplink.Warnings
    FileHandling.fileDownlink.Warnings
    FileHandling.fileManager.Errors

    GpsModule.cmdSeq.CS_Errors
    ComCcsds.commsBufferManager.NoBuffs
    ComCcsds.commsBufferManager.EmptyBuffs

    GpsModule.rateGroup_1Hz.RgCycleSlips
    GpsModule.rateGroup_0_5Hz.RgCycleSlips
    GpsModule.rateGroup_0_25Hz.RgCycleSlips
  }

  packet SystemRes1 id 5 group 2 {
    GpsModule.systemResources.MEMORY_TOTAL
    GpsModule.systemResources.MEMORY_USED
    GpsModule.systemResources.NON_VOLATILE_TOTAL
    GpsModule.systemResources.NON_VOLATILE_FREE
  }

  packet SystemRes3 id 6 group 2 {
    GpsModule.systemResources.CPU
    GpsModule.systemResources.CPU_00
    GpsModule.systemResources.CPU_01
    GpsModule.systemResources.CPU_02
    GpsModule.systemResources.CPU_03
    GpsModule.systemResources.CPU_04
    GpsModule.systemResources.CPU_05
    GpsModule.systemResources.CPU_06
    GpsModule.systemResources.CPU_07
    GpsModule.systemResources.CPU_08
    GpsModule.systemResources.CPU_09
    GpsModule.systemResources.CPU_10
    GpsModule.systemResources.CPU_11
    GpsModule.systemResources.CPU_12
    GpsModule.systemResources.CPU_13
    GpsModule.systemResources.CPU_14
    GpsModule.systemResources.CPU_15
  }

  packet DataProducts id 21 group 3 {
    DataProducts.dpCat.CatalogDps
    DataProducts.dpCat.DpsSent

    DataProducts.dpMgr.NumSuccessfulAllocations
    DataProducts.dpMgr.NumFailedAllocations
    DataProducts.dpMgr.NumDataProducts
    DataProducts.dpMgr.NumBytes

    DataProducts.dpWriter.NumBuffersReceived
    DataProducts.dpWriter.NumBytesWritten
    DataProducts.dpWriter.NumSuccessfulWrites
    DataProducts.dpWriter.NumFailedWrites
    DataProducts.dpWriter.NumErrors

    DataProducts.dpBufferManager.TotalBuffs
    DataProducts.dpBufferManager.CurrBuffs
    DataProducts.dpBufferManager.HiBuffs
    DataProducts.dpBufferManager.NoBuffs
    DataProducts.dpBufferManager.EmptyBuffs
  }

  packet Version1 id 22 group 2 {
    CdhCore.version.FrameworkVersion
    CdhCore.version.ProjectVersion
  }

  packet Version_Library1 id 23 group 2 {
    CdhCore.version.LibraryVersion01
    CdhCore.version.LibraryVersion02
  }

  packet Version_Library2 id 24 group 2 {
    CdhCore.version.LibraryVersion03
    CdhCore.version.LibraryVersion04
  }

  packet Version_Library3 id 25 group 2 {
    CdhCore.version.LibraryVersion05
    CdhCore.version.LibraryVersion06
  }

  packet Version_Library4 id 26 group 2 {
    CdhCore.version.LibraryVersion07
    CdhCore.version.LibraryVersion08
  }

  packet Version_Library5 id 27 group 2 {
    CdhCore.version.LibraryVersion09
    CdhCore.version.LibraryVersion10
  }

  packet Version_Custom1 id 28 group 2 {
    CdhCore.version.CustomVersion01
  }

  packet Version_Custom2 id 29 group 2 {
    CdhCore.version.CustomVersion02
  }

  packet Version_Custom3 id 30 group 2 {
    CdhCore.version.CustomVersion03
  }

  packet Version_Custom4 id 31 group 2 {
    CdhCore.version.CustomVersion04
  }

  packet Version_Custom5 id 32 group 2 {
    CdhCore.version.CustomVersion05
  }

  packet Version_Custom6 id 33 group 2 {
    CdhCore.version.CustomVersion06
  }

  packet Version_Custom7 id 34 group 2 {
    CdhCore.version.CustomVersion07
  }

  packet Version_Custom8 id 35 group 2 {
    CdhCore.version.CustomVersion08
  }

  packet Version_Custom9 id 36 group 2 {
    CdhCore.version.CustomVersion09
  }

  packet Version_Custom10 id 37 group 2 {
    CdhCore.version.CustomVersion10
  }

  packet GpsInfo id 8 group 2 {
    gps.UTCTime
    gps.Latitude
    gps.Longitude
    gps.Altitude
  }

} omit {
  CdhCore.cmdDisp.CommandErrors

  bufferManager.TotalBuffs
  bufferManager.CurrBuffs
  bufferManager.HiBuffs
  bufferManager.NoBuffs
  bufferManager.EmptyBuffs
  serialDriver.BytesSent
  serialDriver.BytesRecv
}
