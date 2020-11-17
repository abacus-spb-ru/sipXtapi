# Microsoft Developer Studio Project File - Name="sipXmediaLib" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=sipXmediaLib - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "sipXmediaLib.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "sipXmediaLib.mak" CFG="sipXmediaLib - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "sipXmediaLib - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "sipXmediaLib - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName "Perforce Project"
# PROP Scc_LocalPath "."
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "sipXmediaLib - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
F90=df.exe
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GR /GX /O1 /I "include" /I "..\sipXportLib\include" /I "..\sipXsdpLib\include" /I "..\sipXtackLib\include" /I "contrib\libgsm\inc" /I "contrib\libspeex\include" /D "HAVE_SPEEX" /D "HAVE_GSM" /D "NDEBUG" /D "_LIB" /D "WIN32" /D "_MBCS" /D "SIPXTAPI_STATIC" /FD /c
# SUBTRACT CPP /YX
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ELSEIF  "$(CFG)" == "sipXmediaLib - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
F90=df.exe
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GR /GX /ZI /Od /I "include" /I "..\sipXportLib\include" /I "..\sipXsdpLib\include" /I "..\sipXtackLib\include" /I "contrib\libgsm\inc" /I "contrib\libspeex\include" /D "HAVE_SPEEX" /D "HAVE_GSM" /D "_DEBUG" /D "_LIB" /D "WIN32" /D "_MBCS" /FR /FD /GZ /c
# SUBTRACT CPP /YX
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"Debug\sipXmediaLibd.lib"

!ENDIF 

# Begin Target

# Name "sipXmediaLib - Win32 Release"
# Name "sipXmediaLib - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Group "mp Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\src\mp\dft.cpp
# End Source File
# Begin Source File

SOURCE=.\src\mp\dmaTaskWnt.cpp
# End Source File
# Begin Source File

SOURCE=.\src\mp\DSPlib.cpp
# End Source File
# Begin Source File

SOURCE=.\src\mp\dtmflib.cpp
# End Source File
# Begin Source File

SOURCE=.\src\mp\FilterBank.cpp
# End Source File
# Begin Source File

SOURCE=.\src\mp\HandsetFilterBank.cpp
# End Source File
# Begin Source File

SOURCE=.\src\mp\MicThreadWnt.cpp
# End Source File
# Begin Source File

SOURCE=.\src\mp\MpAgcBase.cpp
# End Source File
# Begin Source File

SOURCE=.\src\mp\MpAgcSimple.cpp
# End Source File
# Begin Source File

SOURCE=.\src\mp\MpArrayBuf.cpp
# End Source File
# Begin Source File

SOURCE=.\src\mp\mpau.cpp
# End Source File
# Begin Source File

SOURCE=.\src\mp\MpAudioAbstract.cpp
# End Source File
# Begin Source File

SOURCE=.\src\mp\MpAudioBuf.cpp
# End Source File
# Begin Source File

SOURCE=.\src\mp\MpAudioFileDecompress.cpp
# End Source File
# Begin Source File

SOURCE=.\src\mp\MpAudioFileOpen.cpp
# End Source File
# Begin Source File

SOURCE=.\src\mp\MpAudioFileUtils.cpp
# End Source File
# Begin Source File

SOURCE=.\src\mp\MpAudioOutputConnection.cpp
# End Source File
# Begin Source File

SOURCE=.\src\mp\MpAudioResource.cpp
# End Source File
# Begin Source File

SOURCE=.\src\mp\MpAudioUtils.cpp
# End Source File
# Begin Source File

SOURCE=.\src\mp\MpAudioWaveFileRead.cpp
# End Source File
# Begin Source File

SOURCE=.\src\mp\MpBridgeAlgLinear.cpp
# End Source File
# Begin Source File

SOURCE=.\src\mp\MpBridgeAlgSimple.cpp
# End Source File
# Begin Source File

SOURCE=.\src\mp\MpBuf.cpp
# End Source File
# Begin Source File

SOURCE=.\src\mp\MpBufferMsg.cpp
# End Source File
# Begin Source File

SOURCE=.\src\mp\MpBufPool.cpp
# End Source File
# Begin Source File

SOURCE=.\src\mp\MpCallFlowGraph.cpp
# End Source File
# Begin Source File

SOURCE=.\src\mp\MpCodec.cpp
# End Source File
# Begin Source File

SOURCE=.\src\mp\MpCodecFactory.cpp
# End Source File
# Begin Source File

SOURCE=.\src\mp\MpDataBuf.cpp
# End Source File
# Begin Source File

SOURCE=.\src\mp\MpDecoderBase.cpp
# End Source File
# Begin Source File

SOURCE=.\src\mp\MpDecoderPayloadMap.cpp
# End Source File
# Begin Source File

SOURCE=.\src\mp\MpDspUtils.cpp
# End Source File
# Begin Source File

SOURCE=.\src\mp\MpDTMFDetector.cpp
# End Source File
# Begin Source File

SOURCE=.\src\mp\MpEncoderBase.cpp
# End Source File
# Begin Source File

SOURCE=.\src\mp\MpFlowGraphBase.cpp
# End Source File
# Begin Source File

SOURCE=.\src\mp\MpFlowGraphMsg.cpp
# End Source File
# Begin Source File

SOURCE=.\src\mp\mpG711.cpp
# End Source File
# Begin Source File

SOURCE=.\src\mp\MpidWinMM.cpp
# End Source File
# Begin Source File

SOURCE=.\src\mp\MpInputDeviceDriver.cpp
# End Source File
# Begin Source File

SOURCE=.\src\mp\MpInputDeviceManager.cpp
# End Source File
# Begin Source File

SOURCE=.\src\mp\MpJbeFixed.cpp
# End Source File
# Begin Source File

SOURCE=.\src\mp\MpJitterBuffer.cpp
# End Source File
# Begin Source File

SOURCE=.\src\mp\MpJitterBufferEstimation.cpp
# End Source File
# Begin Source File

SOURCE=.\src\mp\MpMediaTask.cpp
# End Source File
# Begin Source File

SOURCE=.\src\mp\MpMediaTaskMsg.cpp
# End Source File
# Begin Source File

SOURCE=.\src\mp\MpMisc.cpp
# End Source File
# Begin Source File

SOURCE=.\src\mp\MpMMTimer.cpp
# End Source File
# Begin Source File

SOURCE=.\src\mp\MpMMTimerWnt.cpp
# End Source File
# Begin Source File

SOURCE=.\src\mp\MpodBufferRecorder.cpp
# End Source File
# Begin Source File

SOURCE=.\src\mp\MpodWinMM.cpp
# End Source File
# Begin Source File

SOURCE=.\src\mp\MpOutputDeviceDriver.cpp
# End Source File
# Begin Source File

SOURCE=.\src\mp\MpOutputDeviceManager.cpp
# End Source File
# Begin Source File

SOURCE=.\src\mp\MpPlayer.cpp
# End Source File
# Begin Source File

SOURCE=.\src\mp\MpPlayerEvent.cpp
# End Source File
# Begin Source File

SOURCE=.\src\mp\MpPlcBase.cpp
# End Source File
# Begin Source File

SOURCE=.\src\mp\MpPlcSilence.cpp
# End Source File
# Begin Source File

SOURCE=.\src\mp\MpPlgStaffV1.cpp
# End Source File
# Begin Source File

SOURCE=.\src\mp\MprAudioFrameBuffer.cpp
# End Source File
# Begin Source File

SOURCE=.\src\mp\MpRawAudioBuffer.cpp
# End Source File
# Begin Source File

SOURCE=.\src\mp\MprBridge.cpp
# End Source File
# Begin Source File

SOURCE=.\src\mp\MprDecode.cpp
# End Source File
# Begin Source File

SOURCE=.\src\mp\MprDejitter.cpp
# End Source File
# Begin Source File

SOURCE=.\src\mp\MprDelay.cpp
# End Source File
# Begin Source File

SOURCE=.\src\mp\MprEchoSuppress.cpp
# End Source File
# Begin Source File

SOURCE=.\src\mp\MprEncode.cpp
# End Source File
# Begin Source File

SOURCE=.\src\mp\MpResampler.cpp
# End Source File
# Begin Source File

SOURCE=.\src\mp\MpResamplerSpeex.cpp
# End Source File
# Begin Source File

SOURCE=.\src\mp\MpResNotificationMsg.cpp
# End Source File
# Begin Source File

SOURCE=.\src\mp\MpResource.cpp
# End Source File
# Begin Source File

SOURCE=.\src\mp\MpResourceFactory.cpp
# End Source File
# Begin Source File

SOURCE=.\src\mp\MpResourceMsg.cpp
# End Source File
# Begin Source File

SOURCE=.\src\mp\MpResourceSortAlg.cpp
# End Source File
# Begin Source File

SOURCE=.\src\mp\MpResourceTopology.cpp
# End Source File
# Begin Source File

SOURCE=.\src\mp\MprFromFile.cpp
# End Source File
# Begin Source File

SOURCE=.\src\mp\MprFromInputDevice.cpp
# End Source File
# Begin Source File

SOURCE=.\src\mp\MprFromMic.cpp
# End Source File
# Begin Source File

SOURCE=.\src\mp\MprFromNet.cpp
# End Source File
# Begin Source File

SOURCE=.\src\mp\MprFromStream.cpp
# End Source File
# Begin Source File

SOURCE=.\src\mp\MprHook.cpp
# End Source File
# Begin Source File

SOURCE=.\src\mp\MprMixer.cpp
# End Source File
# Begin Source File

SOURCE=.\src\mp\MprnDTMFMsg.cpp
# End Source File
# Begin Source File

SOURCE=.\src\mp\MprnIntMsg.cpp
# End Source File
# Begin Source File

SOURCE=.\src\mp\MprnProgressMsg.cpp
# End Source File
# Begin Source File

SOURCE=.\src\mp\MprnRtpStreamActivityMsg.cpp
# End Source File
# Begin Source File

SOURCE=.\src\mp\MprNull.cpp
# End Source File
# Begin Source File

SOURCE=.\src\mp\MprNullAec.cpp
# End Source File
# Begin Source File

SOURCE=.\src\mp\MprRecorder.cpp
# End Source File
# Begin Source File

SOURCE=.\src\mp\MprRtpDispatcher.cpp
# End Source File
# Begin Source File

SOURCE=.\src\mp\MprRtpDispatcherActiveSsrcs.cpp
# End Source File
# Begin Source File

SOURCE=.\src\mp\MprRtpDispatcherIpAffinity.cpp
# End Source File
# Begin Source File

SOURCE=.\src\mp\MprSpeakerSelector.cpp
# End Source File
# Begin Source File

SOURCE=.\src\mp\MprSpeexEchoCancel.cpp
# End Source File
# Begin Source File

SOURCE=.\src\mp\MprSpeexPreProcess.cpp
# End Source File
# Begin Source File

SOURCE=.\src\mp\MprSplitter.cpp
# End Source File
# Begin Source File

SOURCE=.\src\mp\MprToneGen.cpp
# End Source File
# Begin Source File

SOURCE=.\src\mp\MprToNet.cpp
# End Source File
# Begin Source File

SOURCE=.\src\mp\MprToOutputDevice.cpp
# End Source File
# Begin Source File

SOURCE=.\src\mp\MprToSpkr.cpp
# End Source File
# Begin Source File

SOURCE=.\src\mp\MpRtpBuf.cpp
# End Source File
# Begin Source File

SOURCE=.\src\mp\MpRtpInputConnection.cpp
# End Source File
# Begin Source File

SOURCE=.\src\mp\MpRtpOutputConnection.cpp
# End Source File
# Begin Source File

SOURCE=.\src\mp\MprVad.cpp
# End Source File
# Begin Source File

SOURCE=.\src\mp\MprVoiceActivityNotifier.cpp
# End Source File
# Begin Source File

SOURCE=.\src\mp\MpSineWaveGeneratorDeviceDriver.cpp
# End Source File
# Begin Source File

SOURCE=.\src\mp\MpSpeakerSelectBase.cpp
# End Source File
# Begin Source File

SOURCE=.\src\mp\MpStaticCodecInit.cpp
# End Source File
# Begin Source File

SOURCE=.\src\mp\MpStreamFeeder.cpp
# End Source File
# Begin Source File

SOURCE=.\src\mp\MpStreamMsg.cpp
# End Source File
# Begin Source File

SOURCE=.\src\mp\MpStreamPlayer.cpp
# End Source File
# Begin Source File

SOURCE=.\src\mp\MpStreamPlaylistPlayer.cpp
# End Source File
# Begin Source File

SOURCE=.\src\mp\MpStreamQueuePlayer.cpp
# End Source File
# Begin Source File

SOURCE=.\src\mp\MpTopologyGraph.cpp
# End Source File
# Begin Source File

SOURCE=.\src\mp\MpTypes.cpp
# End Source File
# Begin Source File

SOURCE=.\src\mp\MpUdpBuf.cpp
# End Source File
# Begin Source File

SOURCE=.\src\mp\MpVadBase.cpp
# End Source File
# Begin Source File

SOURCE=.\src\mp\MpVadSimple.cpp
# End Source File
# Begin Source File

SOURCE=.\src\mp\NetInTask.cpp
# End Source File
# Begin Source File

SOURCE=.\src\mp\SpeakerThreadWnt.cpp
# End Source File
# Begin Source File

SOURCE=.\src\mp\StreamBufferDataSource.cpp
# End Source File
# Begin Source File

SOURCE=.\src\mp\StreamDataSource.cpp
# End Source File
# Begin Source File

SOURCE=.\src\mp\StreamDataSourceListener.cpp
# End Source File
# Begin Source File

SOURCE=.\src\mp\StreamDecoderListener.cpp
# End Source File
# Begin Source File

SOURCE=.\src\mp\StreamFileDataSource.cpp
# End Source File
# Begin Source File

SOURCE=.\src\mp\StreamFormatDecoder.cpp
# End Source File
# Begin Source File

SOURCE=.\src\mp\StreamHttpDataSource.cpp
# End Source File
# Begin Source File

SOURCE=.\src\mp\StreamQueueingFormatDecoder.cpp
# End Source File
# Begin Source File

SOURCE=.\src\mp\StreamQueueMsg.cpp
# End Source File
# Begin Source File

SOURCE=.\src\mp\StreamRAWFormatDecoder.cpp
# End Source File
# Begin Source File

SOURCE=.\src\mp\StreamWAVFormatDecoder.cpp
# End Source File
# End Group
# Begin Group "rtcp Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\src\rtcp\BaseClass.cpp
# End Source File
# Begin Source File

SOURCE=.\src\rtcp\ByeReport.cpp
# End Source File
# Begin Source File

SOURCE=.\src\rtcp\Message.cpp
# End Source File
# Begin Source File

SOURCE=.\src\rtcp\MsgQueue.cpp
# End Source File
# Begin Source File

SOURCE=.\src\rtcp\NetworkChannel.cpp
# End Source File
# Begin Source File

SOURCE=.\src\rtcp\ReceiverReport.cpp
# End Source File
# Begin Source File

SOURCE=.\src\rtcp\RTCManager.cpp
# End Source File
# Begin Source File

SOURCE=.\src\rtcp\RTCPConnection.cpp
# End Source File
# Begin Source File

SOURCE=.\src\rtcp\RTCPHeader.cpp
# End Source File
# Begin Source File

SOURCE=.\src\rtcp\RTCPRender.cpp
# End Source File
# Begin Source File

SOURCE=.\src\rtcp\RTCPSession.cpp
# End Source File
# Begin Source File

SOURCE=.\src\rtcp\RTCPSource.cpp
# End Source File
# Begin Source File

SOURCE=.\src\rtcp\RTCPTimer.cpp
# End Source File
# Begin Source File

SOURCE=.\src\rtcp\RTPHeader.cpp
# End Source File
# Begin Source File

SOURCE=.\src\rtcp\SenderReport.cpp
# End Source File
# Begin Source File

SOURCE=.\src\rtcp\SourceDescription.cpp
# End Source File
# End Group
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Group "rtcp Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\include\rtcp\BaseClass.h
# End Source File
# Begin Source File

SOURCE=.\include\rtcp\ByeReport.h
# End Source File
# Begin Source File

SOURCE=.\include\rtcp\IBaseClass.h
# End Source File
# Begin Source File

SOURCE=.\include\rtcp\IByeReport.h
# End Source File
# Begin Source File

SOURCE=.\include\rtcp\IGetByeInfo.h
# End Source File
# Begin Source File

SOURCE=.\include\rtcp\IGetReceiverStatistics.h
# End Source File
# Begin Source File

SOURCE=.\include\rtcp\IGetSenderStatistics.h
# End Source File
# Begin Source File

SOURCE=.\include\rtcp\IGetSrcDescription.h
# End Source File
# Begin Source File

SOURCE=.\include\rtcp\INetDispatch.h
# End Source File
# Begin Source File

SOURCE=.\include\rtcp\INetworkChannel.h
# End Source File
# Begin Source File

SOURCE=.\include\rtcp\INetworkRender.h
# End Source File
# Begin Source File

SOURCE=.\include\rtcp\INetworkSource.h
# End Source File
# Begin Source File

SOURCE=.\include\rtcp\IReceiverReport.h
# End Source File
# Begin Source File

SOURCE=.\include\rtcp\IRTCPConnection.h
# End Source File
# Begin Source File

SOURCE=.\include\rtcp\IRTCPControl.h
# End Source File
# Begin Source File

SOURCE=.\include\rtcp\IRTCPHeader.h
# End Source File
# Begin Source File

SOURCE=.\include\rtcp\IRTCPNotify.h
# End Source File
# Begin Source File

SOURCE=.\include\rtcp\IRTCPRegister.h
# End Source File
# Begin Source File

SOURCE=.\include\rtcp\IRTCPRender.h
# End Source File
# Begin Source File

SOURCE=.\include\rtcp\IRTCPSession.h
# End Source File
# Begin Source File

SOURCE=.\include\rtcp\IRTCPStatistics.h
# End Source File
# Begin Source File

SOURCE=.\include\rtcp\IRTPDispatch.h
# End Source File
# Begin Source File

SOURCE=.\include\rtcp\IRTPHeader.h
# End Source File
# Begin Source File

SOURCE=.\include\rtcp\ISDESReport.h
# End Source File
# Begin Source File

SOURCE=.\include\rtcp\ISenderReport.h
# End Source File
# Begin Source File

SOURCE=.\include\rtcp\ISetReceiverStatistics.h
# End Source File
# Begin Source File

SOURCE=.\include\rtcp\ISetSenderStatistics.h
# End Source File
# Begin Source File

SOURCE=.\include\rtcp\ISetSrcDescription.h
# End Source File
# Begin Source File

SOURCE=.\include\rtcp\Message.h
# End Source File
# Begin Source File

SOURCE=.\include\rtcp\MsgQueue.h
# End Source File
# Begin Source File

SOURCE=.\include\rtcp\NetworkChannel.h
# End Source File
# Begin Source File

SOURCE=.\include\rtcp\ReceiverReport.h
# End Source File
# Begin Source File

SOURCE=.\include\rtcp\RTCManager.h
# End Source File
# Begin Source File

SOURCE=.\include\rtcp\RtcpConfig.h
# End Source File
# Begin Source File

SOURCE=.\include\rtcp\RTCPConnection.h
# End Source File
# Begin Source File

SOURCE=.\include\rtcp\RTCPHeader.h
# End Source File
# Begin Source File

SOURCE=.\include\rtcp\RTCPRender.h
# End Source File
# Begin Source File

SOURCE=.\include\rtcp\RTCPSession.h
# End Source File
# Begin Source File

SOURCE=.\include\rtcp\RTCPSource.h
# End Source File
# Begin Source File

SOURCE=.\include\rtcp\RTCPTimer.h
# End Source File
# Begin Source File

SOURCE=.\include\rtcp\RTPHeader.h
# End Source File
# Begin Source File

SOURCE=.\include\rtcp\SenderReport.h
# End Source File
# Begin Source File

SOURCE=.\include\rtcp\SourceDescription.h
# End Source File
# Begin Source File

SOURCE=.\include\rtcp\TLink.h
# End Source File
# Begin Source File

SOURCE=.\include\rtcp\TLinkedList.h
# End Source File
# End Group
# Begin Group "mp Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\include\mp\dmaTask.h
# End Source File
# Begin Source File

SOURCE=.\include\mp\dsplib.h
# End Source File
# Begin Source File

SOURCE=.\include\mp\dtmflib.h
# End Source File
# Begin Source File

SOURCE=.\include\mp\FilterBank.h
# End Source File
# Begin Source File

SOURCE=.\include\mp\HandsetFilterBank.h
# End Source File
# Begin Source File

SOURCE=.\include\mp\HandsetFilterbankWindows.h
# End Source File
# Begin Source File

SOURCE=.\include\mp\MpAgcBase.h
# End Source File
# Begin Source File

SOURCE=.\include\mp\MpAgcSimple.h
# End Source File
# Begin Source File

SOURCE=.\include\mp\MpArrayBuf.h
# End Source File
# Begin Source File

SOURCE=.\include\mp\mpau.h
# End Source File
# Begin Source File

SOURCE=.\include\mp\MpAudioAbstract.h
# End Source File
# Begin Source File

SOURCE=.\include\mp\MpAudioBuf.h
# End Source File
# Begin Source File

SOURCE=.\include\mp\MpAudioFileDecompress.h
# End Source File
# Begin Source File

SOURCE=.\include\mp\MpAudioFileOpen.h
# End Source File
# Begin Source File

SOURCE=.\include\mp\MpAudioFileUtils.h
# End Source File
# Begin Source File

SOURCE=.\include\mp\MpAudioOutputConnection.h
# End Source File
# Begin Source File

SOURCE=.\include\mp\MpAudioResource.h
# End Source File
# Begin Source File

SOURCE=.\include\mp\MpAudioResourceConstructor.h
# End Source File
# Begin Source File

SOURCE=.\include\mp\MpAudioUtils.h
# End Source File
# Begin Source File

SOURCE=.\include\mp\MpAudioWaveFileRead.h
# End Source File
# Begin Source File

SOURCE=.\include\mp\MpBridgeAlgBase.h
# End Source File
# Begin Source File

SOURCE=.\include\mp\MpBridgeAlgLinear.h
# End Source File
# Begin Source File

SOURCE=.\include\mp\MpBridgeAlgSimple.h
# End Source File
# Begin Source File

SOURCE=.\include\mp\MpBuf.h
# End Source File
# Begin Source File

SOURCE=.\include\mp\MpBufferMsg.h
# End Source File
# Begin Source File

SOURCE=.\include\mp\MpBufPool.h
# End Source File
# Begin Source File

SOURCE=.\include\mp\MpCallFlowGraph.h
# End Source File
# Begin Source File

SOURCE=.\include\mp\MpCodec.h
# End Source File
# Begin Source File

SOURCE=.\include\mp\MpCodecFactory.h
# End Source File
# Begin Source File

SOURCE=.\include\mp\MpCodecInfo.h
# End Source File
# Begin Source File

SOURCE=.\include\mp\MpDataBuf.h
# End Source File
# Begin Source File

SOURCE=.\include\mp\MpDecoderBase.h
# End Source File
# Begin Source File

SOURCE=.\include\mp\MpDecoderPayloadMap.h
# End Source File
# Begin Source File

SOURCE=.\include\mp\MpDefs.h
# End Source File
# Begin Source File

SOURCE=.\include\mp\MpdPtAVT.h
# End Source File
# Begin Source File

SOURCE=.\include\mp\MpdSipxGSM.h
# End Source File
# Begin Source File

SOURCE=.\include\mp\MpdSipxILBC.h
# End Source File
# Begin Source File

SOURCE=.\include\mp\MpdSipxPcma.h
# End Source File
# Begin Source File

SOURCE=.\include\mp\MpdSipxPcmu.h
# End Source File
# Begin Source File

SOURCE=.\include\mp\MpdSipxSpeex.h
# End Source File
# Begin Source File

SOURCE=.\include\mp\MpDspUtils.h
# End Source File
# Begin Source File

SOURCE=.\include\mp\MpDspUtilsConvertVect.h
# End Source File
# Begin Source File

SOURCE=.\include\mp\MpDspUtilsIntSqrt.h
# End Source File
# Begin Source File

SOURCE=.\include\mp\MpDspUtilsSerials.h
# End Source File
# Begin Source File

SOURCE=.\include\mp\MpDspUtilsShift.h
# End Source File
# Begin Source File

SOURCE=.\include\mp\MpDspUtilsSum.h
# End Source File
# Begin Source File

SOURCE=.\include\mp\MpDspUtilsSumVect.h
# End Source File
# Begin Source File

SOURCE=.\include\mp\MpDTMFDetector.h
# End Source File
# Begin Source File

SOURCE=.\include\mp\MpEncoderBase.h
# End Source File
# Begin Source File

SOURCE=.\include\mp\MpePtAVT.h
# End Source File
# Begin Source File

SOURCE=.\include\mp\MpeSipxGSM.h
# End Source File
# Begin Source File

SOURCE=.\include\mp\MpeSipxILBC.h
# End Source File
# Begin Source File

SOURCE=.\include\mp\MpeSipxPcma.h
# End Source File
# Begin Source File

SOURCE=.\include\mp\MpeSipxPcmu.h
# End Source File
# Begin Source File

SOURCE=.\include\mp\MpeSipxSpeex.h
# End Source File
# Begin Source File

SOURCE=.\include\mp\MpFlowGraphBase.h
# End Source File
# Begin Source File

SOURCE=.\include\mp\MpFlowGraphMsg.h
# End Source File
# Begin Source File

SOURCE=.\include\mp\MpidWinMM.h
# End Source File
# Begin Source File

SOURCE=.\include\mp\MpInputDeviceDriver.h
# End Source File
# Begin Source File

SOURCE=.\include\mp\MpInputDeviceManager.h
# End Source File
# Begin Source File

SOURCE=.\include\mp\MpIntResourceMsg.h
# End Source File
# Begin Source File

SOURCE=.\include\mp\MpJbeFixed.h
# End Source File
# Begin Source File

SOURCE=.\include\mp\MpJitterBuffer.h
# End Source File
# Begin Source File

SOURCE=.\include\mp\MpJitterBufferEstimation.h
# End Source File
# Begin Source File

SOURCE=.\include\mp\MpMediaTask.h
# End Source File
# Begin Source File

SOURCE=.\include\mp\MpMediaTaskMsg.h
# End Source File
# Begin Source File

SOURCE=.\include\mp\MpMisc.h
# End Source File
# Begin Source File

SOURCE=.\include\mp\MpMMTimer.h
# End Source File
# Begin Source File

SOURCE=.\include\mp\MpMMTimerWnt.h
# End Source File
# Begin Source File

SOURCE=.\include\mp\MpodBufferRecorder.h
# End Source File
# Begin Source File

SOURCE=.\include\mp\MpodWinMM.h
# End Source File
# Begin Source File

SOURCE=.\include\mp\MpOutputDeviceDriver.h
# End Source File
# Begin Source File

SOURCE=.\include\mp\MpOutputDeviceManager.h
# End Source File
# Begin Source File

SOURCE=.\include\mp\MpPackedResourceMsg.h
# End Source File
# Begin Source File

SOURCE=.\include\mp\MpPlayer.h
# End Source File
# Begin Source File

SOURCE=.\include\mp\MpPlayerEvent.h
# End Source File
# Begin Source File

SOURCE=.\include\mp\MpPlayerListener.h
# End Source File
# Begin Source File

SOURCE=.\include\mp\MpPlcBase.h
# End Source File
# Begin Source File

SOURCE=.\include\mp\MpPlcSilence.h
# End Source File
# Begin Source File

SOURCE=.\include\mp\MpPlgStaffV1.h
# End Source File
# Begin Source File

SOURCE=.\include\mp\MpQueuePlayerListener.h
# End Source File
# Begin Source File

SOURCE=.\include\mp\MprAudioFrameBuffer.h
# End Source File
# Begin Source File

SOURCE=.\include\mp\MpRawAudioBuffer.h
# End Source File
# Begin Source File

SOURCE=.\include\mp\MprBridge.h
# End Source File
# Begin Source File

SOURCE=.\include\mp\MprBridgeConstructor.h
# End Source File
# Begin Source File

SOURCE=.\include\mp\MprBridgeSetGainsMsg.h
# End Source File
# Begin Source File

SOURCE=.\include\mp\MprDecode.h
# End Source File
# Begin Source File

SOURCE=.\include\mp\MprDecodeConstructor.h
# End Source File
# Begin Source File

SOURCE=.\include\mp\MprDecodeSelectCodecsMsg.h
# End Source File
# Begin Source File

SOURCE=.\include\mp\MprDejitter.h
# End Source File
# Begin Source File

SOURCE=.\include\mp\MprDelay.h
# End Source File
# Begin Source File

SOURCE=.\include\mp\MprDelayConstructor.h
# End Source File
# Begin Source File

SOURCE=.\include\mp\MprEchoSuppress.h
# End Source File
# Begin Source File

SOURCE=.\include\mp\MprEncode.h
# End Source File
# Begin Source File

SOURCE=.\include\mp\MprEncodeConstructor.h
# End Source File
# Begin Source File

SOURCE=.\include\mp\MpResampler.h
# End Source File
# Begin Source File

SOURCE=.\include\mp\MpResamplerSpeex.h
# End Source File
# Begin Source File

SOURCE=.\include\mp\MpResNotificationMsg.h
# End Source File
# Begin Source File

SOURCE=.\include\mp\MpResource.h
# End Source File
# Begin Source File

SOURCE=.\include\mp\MpResourceConstructor.h
# End Source File
# Begin Source File

SOURCE=.\include\mp\MpResourceFactory.h
# End Source File
# Begin Source File

SOURCE=.\include\mp\MpResourceMsg.h
# End Source File
# Begin Source File

SOURCE=.\include\mp\MpResourceSortAlg.h
# End Source File
# Begin Source File

SOURCE=.\include\mp\MpResourceTopology.h
# End Source File
# Begin Source File

SOURCE=.\include\mp\MprFromFile.h
# End Source File
# Begin Source File

SOURCE=.\include\mp\MprFromFileConstructor.h
# End Source File
# Begin Source File

SOURCE=.\include\mp\MprFromInputDevice.h
# End Source File
# Begin Source File

SOURCE=.\include\mp\MprFromInputDeviceConstructor.h
# End Source File
# Begin Source File

SOURCE=.\include\mp\MprFromMic.h
# End Source File
# Begin Source File

SOURCE=.\include\mp\MprFromNet.h
# End Source File
# Begin Source File

SOURCE=.\include\mp\MprFromStream.h
# End Source File
# Begin Source File

SOURCE=.\include\mp\MprHook.h
# End Source File
# Begin Source File

SOURCE=.\include\mp\MprHookConstructor.h
# End Source File
# Begin Source File

SOURCE=.\include\mp\MprMixer.h
# End Source File
# Begin Source File

SOURCE=.\include\mp\MprnDTMFMsg.h
# End Source File
# Begin Source File

SOURCE=.\include\mp\MprnIntMsg.h
# End Source File
# Begin Source File

SOURCE=.\include\mp\MprnProgressMsg.h
# End Source File
# Begin Source File

SOURCE=.\include\mp\MprnRtpStreamActivityMsg.h
# End Source File
# Begin Source File

SOURCE=.\include\mp\MprNull.h
# End Source File
# Begin Source File

SOURCE=.\include\mp\MprNullAec.h
# End Source File
# Begin Source File

SOURCE=.\include\mp\MprNullAecConstructor.h
# End Source File
# Begin Source File

SOURCE=.\include\mp\MprNullConstructor.h
# End Source File
# Begin Source File

SOURCE=.\include\mp\MprRecorder.h
# End Source File
# Begin Source File

SOURCE=.\include\mp\MprRecorderConstructor.h
# End Source File
# Begin Source File

SOURCE=.\include\mp\MprRtpDispatcher.h
# End Source File
# Begin Source File

SOURCE=.\include\mp\MprRtpDispatcherActiveSsrcs.h
# End Source File
# Begin Source File

SOURCE=.\include\mp\MprRtpDispatcherIpAffinity.h
# End Source File
# Begin Source File

SOURCE=.\include\mp\MprRtpInputConnectionConstructor.h
# End Source File
# Begin Source File

SOURCE=.\include\mp\MprRtpOutputConnectionConstructor.h
# End Source File
# Begin Source File

SOURCE=.\include\mp\MprRtpStartReceiveMsg.h
# End Source File
# Begin Source File

SOURCE=.\include\mp\MprRtpStartReceiveMsg.h
# End Source File
# Begin Source File

SOURCE=.\include\mp\MprSpeakerSelector.h
# End Source File
# Begin Source File

SOURCE=.\include\mp\MprSpeakerSelectorConstructor.h
# End Source File
# Begin Source File

SOURCE=.\include\mp\MprSpeexEchoCancel.h
# End Source File
# Begin Source File

SOURCE=.\include\mp\MprSpeexPreProcess.h
# End Source File
# Begin Source File

SOURCE=.\include\mp\MprSpeexPreProcessConstructor.h
# End Source File
# Begin Source File

SOURCE=.\include\mp\MprSplitter.h
# End Source File
# Begin Source File

SOURCE=.\include\mp\MprSplitterConstructor.h
# End Source File
# Begin Source File

SOURCE=.\include\mp\MprToneGen.h
# End Source File
# Begin Source File

SOURCE=.\include\mp\MprToneGenConstructor.h
# End Source File
# Begin Source File

SOURCE=.\include\mp\MprToNet.h
# End Source File
# Begin Source File

SOURCE=.\include\mp\MprToOutputDevice.h
# End Source File
# Begin Source File

SOURCE=.\include\mp\MprToOutputDeviceConstructor.h
# End Source File
# Begin Source File

SOURCE=.\include\mp\MprToOutputDeviceWithAecConstructor.h
# End Source File
# Begin Source File

SOURCE=.\include\mp\MprToSpkr.h
# End Source File
# Begin Source File

SOURCE=.\include\mp\MpRtpBuf.h
# End Source File
# Begin Source File

SOURCE=.\include\mp\MpRtpInputConnection.h
# End Source File
# Begin Source File

SOURCE=.\include\mp\MpRtpOutputConnection.h
# End Source File
# Begin Source File

SOURCE=.\include\mp\MprVad.h
# End Source File
# Begin Source File

SOURCE=.\include\mp\MprVadConstructor.h
# End Source File
# Begin Source File

SOURCE=.\include\mp\MprVoiceActivityNotifier.h
# End Source File
# Begin Source File

SOURCE=.\include\mp\MprVoiceActivityNotifierConstructor.h
# End Source File
# Begin Source File

SOURCE=.\include\mp\MpSineWaveGeneratorDeviceDriver.h
# End Source File
# Begin Source File

SOURCE=.\include\mp\MpSpeakerSelectBase.h
# End Source File
# Begin Source File

SOURCE=.\include\mp\MpStaticCodecInit.h
# End Source File
# Begin Source File

SOURCE=.\include\mp\MpStreamFeeder.h
# End Source File
# Begin Source File

SOURCE=.\include\mp\MpStreamMsg.h
# End Source File
# Begin Source File

SOURCE=.\include\mp\MpStreamPlayer.h
# End Source File
# Begin Source File

SOURCE=.\include\mp\MpStreamPlaylistPlayer.h
# End Source File
# Begin Source File

SOURCE=.\include\mp\MpStreamQueuePlayer.h
# End Source File
# Begin Source File

SOURCE=.\include\mp\MpStringResourceMsg.h
# End Source File
# Begin Source File

SOURCE=.\include\mp\MpSyncFlowgraphMsg.h
# End Source File
# Begin Source File

SOURCE=.\include\mp\MpToneResourceMsg.h
# End Source File
# Begin Source File

SOURCE=.\include\mp\MpTopologyGraph.h
# End Source File
# Begin Source File

SOURCE=.\include\mp\MpTypes.h
# End Source File
# Begin Source File

SOURCE=.\include\mp\MpUdpBuf.h
# End Source File
# Begin Source File

SOURCE=.\include\mp\MpVadBase.h
# End Source File
# Begin Source File

SOURCE=.\include\mp\MpVadSimple.h
# End Source File
# Begin Source File

SOURCE=.\include\mp\NetInTask.h
# End Source File
# Begin Source File

SOURCE=.\include\mp\RtpHeader.h
# End Source File
# Begin Source File

SOURCE=.\include\mp\StreamBufferDataSource.h
# End Source File
# Begin Source File

SOURCE=.\include\mp\StreamDataSource.h
# End Source File
# Begin Source File

SOURCE=.\include\mp\StreamDataSourceListener.h
# End Source File
# Begin Source File

SOURCE=.\include\mp\StreamDecoderListener.h
# End Source File
# Begin Source File

SOURCE=.\include\mp\StreamDefs.h
# End Source File
# Begin Source File

SOURCE=.\include\mp\StreamFileDataSource.h
# End Source File
# Begin Source File

SOURCE=.\include\mp\StreamFormatDecoder.h
# End Source File
# Begin Source File

SOURCE=.\include\mp\StreamHttpDataSource.h
# End Source File
# Begin Source File

SOURCE=.\include\mp\StreamQueueingFormatDecoder.h
# End Source File
# Begin Source File

SOURCE=.\include\mp\StreamQueueMsg.h
# End Source File
# Begin Source File

SOURCE=.\include\mp\StreamRAWFormatDecoder.h
# End Source File
# Begin Source File

SOURCE=.\include\mp\StreamWAVFormatDecoder.h
# End Source File
# End Group
# End Group
# End Target
# End Project
