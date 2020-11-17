//  
// Copyright (C) 2007-2017 SIPez LLC.  All rights reserved.
//
// $$
///////////////////////////////////////////////////////////////////////////////

// Author: Sergey Kostanbaev <Sergey DOT Kostanbaev AT sipez DOT com>

// SYSTEM INCLUDES
// APPLICATION INCLUDES
// CODEC LIBRARY INCLUDES
#include "plgspeex.h"

// EXTERNAL VARIABLES
// CONSTANTS
// TYPEDEFS
// LOCAL DATA TYPES
// EXTERNAL FUNCTIONS
// DEFINES
// STATIC VARIABLES INITIALIZATON
static const char* defaultFmtps[] =
{
   "",
   "mode=2",
   "mode=3",
   "mode=4",
   "mode=5",
   "mode=6",
   "mode=7",
   "mode=8"
};

/// Exported codec information.
static const struct MppCodecInfoV1_1 sgCodecInfo = 
{
///////////// Implementation and codec info /////////////
   "Jean-Marc Valin/Xiph.Org Foundation", // codecManufacturer
   "Speex",                     // codecName
   "1.2beta2",                  // codecVersion
   CODEC_TYPE_FRAME_BASED,      // codecType

/////////////////////// SDP info ///////////////////////
   "speex",                     // mimeSubtype
   sizeof(defaultFmtps)/sizeof(defaultFmtps[0]), // fmtpsNum
   defaultFmtps,                // fmtps
   8000,                        // sampleRate
   1,                           // numChannels
   CODEC_FRAME_PACKING_SPECIAL  // framePacking
};

DECLARE_FUNCS_V1(speex)

/* ============================== FUNCTIONS =============================== */

CODEC_API int PLG_GET_INFO_V1_1(speex)(const struct MppCodecInfoV1_1 **codecInfo)
{
   if (codecInfo)
   {
      *codecInfo = &sgCodecInfo;
   }
   return RPLG_SUCCESS;
}

CODEC_API void *PLG_INIT_V1_2(speex)(const char* fmtp, int isDecoder,
                                     struct MppCodecFmtpInfoV1_2* pCodecInfo)
{
   return universal_speex_init(fmtp, isDecoder, 8000, pCodecInfo);
}


CODEC_API int PLG_FREE_V1(speex)(void* handle, int isDecoder)
{
   return universal_speex_free(handle, isDecoder);
}

CODEC_API int PLG_GET_PACKET_SAMPLES_V1_2(speex)(void          *handle,
                                                 const uint8_t *pPacketData,
                                                 unsigned       packetSize,
                                                 unsigned      *pNumSamples,
                                                 const struct RtpHeader* pRtpHeader)
{
   return universal_speex_get_packet_samples(handle, pPacketData, packetSize,
      pNumSamples, pRtpHeader);
}

CODEC_API  int PLG_DECODE_V1(speex)(void* handle, const void* pCodedData, 
                                    unsigned cbCodedPacketSize, void* pAudioBuffer, 
                                    unsigned cbBufferSize, unsigned *pcbDecodedSize, 
                                    const struct RtpHeader* pRtpHeader)
{
   return universal_speex_decode(handle, pCodedData, cbCodedPacketSize,
      pAudioBuffer, cbBufferSize, pcbDecodedSize, pRtpHeader);
}

CODEC_API int PLG_ENCODE_V1(speex)(void* handle, const void* pAudioBuffer, 
                                   unsigned cbAudioSamples, int* rSamplesConsumed, 
                                   void* pCodedData, unsigned cbMaxCodedData, 
                                   int* pcbCodedSize, unsigned* pbSendNow)
{
   return universal_speex_encode(handle, pAudioBuffer, cbAudioSamples, 
      rSamplesConsumed, pCodedData, cbMaxCodedData, pcbCodedSize, pbSendNow);
}
