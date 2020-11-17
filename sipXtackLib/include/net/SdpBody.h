//
// Copyright (C) 2005-2013 SIPez LLC.  All rights reserved.
// 
// Copyright (C) 2004 SIPfoundry Inc.
// Licensed by SIPfoundry under the LGPL license.
//
// Copyright (C) 2004-2006 Pingtel Corp.  All rights reserved.
// Licensed to SIPfoundry under a Contributor Agreement.
//
// $$
//////////////////////////////////////////////////////////////////////////////
// Author: Daniel Petrie (dpetrie AT SIPez DOT com)

#ifndef _SdpBody_h_
#define _SdpBody_h_

// SYSTEM INCLUDES
// APPLICATION INCLUDES
#include <utl/UtlDefs.h>
#include <utl/UtlSListIterator.h>
#include <os/OsSocket.h>
#include <os/OsNatConnectionSocket.h>
#include <tapi/sipXtapiEvents.h>
#include <sdp/SdpMediaLine.h>
#include <net/HttpBody.h>
#include <net/NameValuePair.h>
#include <sdp/SdpCodec.h>

// DEFINES
#define SDP_AUDIO_MEDIA_TYPE "audio"
#define SDP_VIDEO_MEDIA_TYPE "video"
#define SDP_APPLICATION_MEDIA_TYPE "application"

// Crypto suites
#define AES_CM_128_HMAC_SHA1_80   1
#define AES_CM_128_HMAC_SHA1_32   2
#define F8_128_HMAC_SHA1_80       3
// Protection level
#define SRTP_ENCRYPTION           0x0001
#define SRTP_AUTHENTICATION       0x0002
#define SRTP_SEND                 0x0004
#define SRTP_RECEIVE              0x0008
#define SRTP_OFF                  0
#define SRTP_ON                   (SRTP_ENCRYPTION|SRTP_AUTHENTICATION|SRTP_SEND|SRTP_RECEIVE)
#define SRTP_SECURITY_MASK        (SRTP_ENCRYPTION|SRTP_AUTHENTICATION)
// Key length       
#define SRTP_KEY_LENGTH          30

// MACROS
// EXTERNAL FUNCTIONS
// EXTERNAL VARIABLES
// CONSTANTS
#define SDP_CONTENT_TYPE "application/sdp"
// STRUCTS
// TYPEDEFS
typedef struct SdpSrtpParameters
{
    int cipherType;
    int securityLevel;
    unsigned char masterKey[SRTP_KEY_LENGTH+1];
} SdpSrtpParameters;


// FORWARD DECLARATIONS
class SdpCodecList;
class SdpMediaLine;

/// Container for MIME type application/sdp.
/**
 * This body type gets constructed when a HttpBody is a single
 * part MIME or multipart MIME which has a part of type
 * application/sdp.  This object has methods to manipulate,
 * iterate and construct SDP fields and media stream definitions
 *
 * In the descriptions below:
 *
 * * A 'valid field string' is any sequence of UTF-8 encoded ISO 10646 characters
 *   except 0x00 (Nul), 0x0A (LF), and 0x0D (CR).
 *   For other character sets, see RFC 2327.
 *
 * * An 'IP address' is in the canonical text format:
 *   For IP4 this is of the format:
 *   nnn.nnn.nnn.nnn where nnn is 0 to 255
 *
 * * The 'network type' and 'address type' are strings as defined
 *   in rfc 2327; should probably be "IN" and "IP4" respectively for now.
 *
 */
class SdpBody : public HttpBody
{
/* //////////////////////////// PUBLIC //////////////////////////////////// */
  public:

   typedef enum 
   {
      Unknown,
      Inactive,
      SendOnly,
      RecvOnly,
      SendRecv
   } SessionDirection;

/** 
 * @name ====================== Constructors and Destructors
 * @{
 */
   /// Construct from an existing SDP message value, or create an empty body. 
   SdpBody(const char* bytes = NULL, ///< NULL creates an empty body             
           int byteCount = -1        ///< -1 means treat bytes as null terminated
           );

   /// Copy constructor
   SdpBody(const SdpBody& rSdpBody);

   /// Destructor
   virtual
      ~SdpBody();

///@}
   
/**
 * @name ====================== Message Serialization Interfaces
 *
 * @{
 */

   /// Get the string length this body would be if serialized
   virtual int getLength() const;

   /// Get the serialized string representation of this SDP message.
   virtual void getBytes(const char** bytes, ///< buffer space where SDP is written, null terminated
                         int* length         ///< number of bytes written (not including the null terminator)
                         ) const;

   /// Get the serialized string representation of this SDP message.
   virtual void getBytes(UtlString* bytes, ///< message output
                         int* length       ///< number of bytes in message
                         ) const;

///@}

/**
 * @name ====================== Header Setting Interfaces

 * These methods set the standard header fields (the ones not in a media set)
 *
 * @{
 */

   void setStandardHeaderFields(const char* sessionName,  ///< any valid field string
                                const char* emailAddress, ///< email address per rfc 2327
                                const char* phoneNumber,  ///< phone number address per rfc 2327
                                const char* originatorAddress ///< IP address
                                );


   void setSessionNameField(const char* sessionName);

   void setOriginator(const char* userId,/**< user id of caller or "-" if host does not support
                                          *   the idea of user logon */
                      int sessionId,     ///< unique id for this call session
                      int sessionVersion,/**< number to get incremented each time
                                          *   the SDP data gets modified for this call session */
                      const char* address///< IP address
                      );

   void setEmailAddressField(const char* emailAddress);

   void setPhoneNumberField(const char* phoneNumber);

   // Append a 't' field after any existing times, converting from epoch->ntp time.
   void addEpochTime(unsigned long epochStartTime,
                     unsigned long epochEndTime = 0
                     );

   // Append a 't' field after any existing times.
   void addNtpTime(unsigned long ntpStartTime,
                   unsigned long ntpEndTime = 0
                   );

   // Get the stream direction or activity state (i.e. sendrecv, sendonly, recvonly, inactive)
   UtlBoolean getMediaStreamDirection(int mediaIndex, ///< which media description set to read
                                      SessionDirection& direction) const;

   // set all media attributes to either a=setup:actpass, a=setup:active, or a=setup:passive
   void setRtpTcpRole(RtpTcpRoles role);                   
   UtlString getRtpTcpRole() const;

///@}

/**
 * @name ====================== Media Setting Interfaces
 *
 * These interfaces are used to build up media descriptions
 *
 * @{
 */

   /// Create a set of media codec and address entries
   void addCodecsOffer(int iNumAddresses,
                       const UtlString mediaAddresses[],
                       int rtpAudioPorts[],
                       int rtcpAudioPorts[],
                       int rtpVideoPorts[],
                       int rtcpVideoPorts[],
                       RTP_TRANSPORT transportTypes[],
                       int numRtpCodecs,
                       SdpCodec* rtpCodecs[],
                       SdpSrtpParameters& srtpParams,
                       int videoBandwidth,
                       int videoFramerate,
                       RTP_TRANSPORT transportOffering
                       );

   /**<
    * This method is for building a SdpBody which is in response
    * to a SdpBody send from the other side
    */

   // Build a MediaLine (for local capabilities for using in addMediaLinesAnswer)
   static void buildMediaLine(SdpMediaLine::SdpMediaType mediaType,
                              int totalBandwidth,
                              int iNumAddresses,
                              UtlString hostAddresses[],
                              int rtpPorts[],
                              int rtcpPorts[],
                              int numRtpCodecs,
                              SdpCodec* rtpCodecs[],
                              SdpMediaLine& mediaLine);

   /// Create a response to a set of media codec and address entries.
   void addCodecsAnswer(int iNumAddresses,
                       UtlString mediaAddresses[],
                       int rtpAudioPorts[],
                       int rtcpAudioPorts[],
                       int rtpVideoPorts[],
                       int rtcpVideoPorts[],
                       RTP_TRANSPORT transportTypes[],
                       int numRtpCodecs, 
                       SdpCodec* rtpCodecs[],
                       SdpSrtpParameters& srtpParams,
                       int videoBandwidth,
                       int videoFramerate,
                       const SdpBody* sdpRequest  ///< Sdp we are responding to
                       ); 
   /**<
    * This method is for building a SdpBody which is in response
    * to a SdpBody send from the other side
    */

   // Create an answer SDP in this for the given media streams and SDP offer
   void addMediaLinesAnswer(int numMediaLines, const SdpMediaLine* mediaLines[], const SdpBody& offer);

   /// Create a new media set for SDP message.
   void addMediaData(const char* mediaType, ///< "audio", "video", "application", "data", "control"
                     int portNumber,        ///< TCP or UDP port number for the media stream
                     int portPairCount,     ///< the number of PAIRS of ports to be used for the media stream.
                     const char* mediaTransportType, ///< i.e. "RTP/AVP"
                     int numPayloadTypes,   ///< entries in the payloadType parameter 
                     int payloadType[]      /**< format specifier specific to context
                                             * of mediaTransportType.
                                             * (i.e. for TRP/AVP u-law this is 0, a-law is 14).
                                             * see RFC 1890 for the Payload Type numbers
                                             */
                     );

   void addCodecParameters(int numRtpCodecs,
                           SdpCodec* rtpCodecs[],
                           const char* szMimeType = "audio"
                           );

   /// Set address.
   void addConnectionAddress(const char* ipAddress /**< for IP4 this is of the format:
                                              * nnn.nnn.nnn.nnn where nnn is 0 to 255 */
                       );
    /**<
     * Set address for SDP message header or specific media set if called
     * after addAddressData.
     */

   void addConnectionAddress(const char* networkType, ///< network type - should be "IN"
                       const char* addressType, ///< address type - should be "IP4"
                       const char* ipAddress    ///< IP address
                       );

   /// Set address.
   void setConnectionAddress(const char* ipAddress /**< for IP4 this is of the format:
                                              * nnn.nnn.nnn.nnn where nnn is 0 to 255 */
                       );
    /**<
     * Set address for SDP message header or specific media set if called
     * after addAddressData.
     */
   void setConnectionAddress(const char* networkType, ///< network type - should be "IN"
                       const char* addressType, ///< address type - should be "IP4"
                       const char* ipAddress    ///< IP address
                       );

   void addRtpmap(int payloadType,
                  const char* mimeSubtype,
                  int sampleRate,
                  int numChannels
                  );

   void addSrtpCryptoField(SdpSrtpParameters& params);

   void addFormatParameters(int payloadType,
                            const char* formatParameters
                            );

   /// Add a "a" field for the given ptime value in milliseconds
   void addPtime(int pTime);

    /**
     * Set the candidate attribute per draft-ietf-mmusic-ice-05
     */
    void addCandidateAttribute(int         candidateId, 
                               const char* transportId, 
                               const char* transportType,
                               uint64_t    qValue, 
                               const char* candidateIp, 
                               int         candidatePort) ;

///@}
   
/**
 * @name ====================== Field Reading Interfaces
 *
 * Use these interfaces to get field values rather than the generic interfaces below.
 *
 * @{
 */

   //! Get the number of media description sets
   int getMediaSetCount() const;

   /// Get the index to the next media set of the given type.
   int findMediaType(const char* mediaType,  ///< the media type to search for
                     int startMediaIndex = 0 ///< start searching from here
                     ) const;
   /**<
    * The default is to start from the begining.  The resulting
    * index may be the start index if it is of the given type.
    *
    * @return the media index if it exists, -1 if it does not exist.
    */

   /// Read a full media line.
   UtlBoolean getMediaData(int mediaIndex, ///< the index of the media to read (the nth m line)
                           UtlString* mediaType,
                           int* mediaPort,
                           int* mediaPortPairs,
                           UtlString* mediaTransportType,
                           int maxPayloadTypes,
                           int* numPayloadTypes,
                           int payloadTypes[]) const;

   /// Inspects whether the given transport type and media type combination is specified 
   /// as an m-line in the sdp
   const bool isTransportAvailable(const OsSocket::IpProtocolSocketType protocol,
                                   const SIPX_MEDIA_TYPE mediaType) const;
                                   
   /// Read whether the media network type is IP4 or IP6.
   UtlBoolean getMediaNetworkType(int mediaIndex, ///< which media description set to read
                                  UtlString* networkType) const;

   /// Get IP address for the indicated media stream.
   UtlBoolean getMediaAddress(int mediaIndex, ///< which media description set to read
                              UtlString* address) const;

   /// Get the media type for the indicated  media stream.
   UtlBoolean getMediaType(int mediaIndex, ///< which media description set to read
                           UtlString* mediaType ///< audio, video, application, etc.
                           ) const;

   /// Get the port number for the indicated media stream.
   UtlBoolean getMediaPort(int mediaIndex, ///< which media description set to read
                           int* port) const;

   // Get the rtcp port number of the indicated media stream.
   UtlBoolean getMediaRtcpPort(int mediaIndex, ///< which media description set to read
                               int* port) const ;

   /// Get the number of port pairs in media stream.
   UtlBoolean getMediaPortCount(int mediaIndex, ///< which media description set to read
                                int* numPorts) const;
   /**<
    * Stream pairs start with the port number given by getMediaPort
    * and are incremented from there to derive the additional
    * port numbers
    */

   /// Get the transport protocol for the indicated media stream.
   UtlBoolean getMediaProtocol(int mediaIndex, ///< which media description set to read
                               UtlString* transportProtocol
                               ) const;

   /// Get the payload types for the indicated media stream.
   UtlBoolean getMediaPayloadType(int mediaIndex, ///< which media description set to read
                                  int maxTypes,   ///< size of the payloadTypes array
                                  int* numTypes,  ///< number of entries returned in payloadTypes
                                  int payloadTypes[] ///< array of integer payload types
                                  ) const;

   /// Get the ptime field for the given media set
   UtlBoolean getPtime(int mediaIndex, int& ptime) const;

   /// Media field accessor utility.
   UtlBoolean getMediaSubfield(int mediaIndex,
                               int subfieldIndex,
                               UtlString* subField
                               ) const;

   /// Get the subfields of the rtpmap field.
   UtlBoolean getPayloadRtpMap(int mediaIndex,         ///< index to which m line contains rtpmap
                               int payloadType,        ///< which rtp map to read
                               UtlString& mimeSubtype, ///< the codec name (mime subtype)
                               int& sampleRate,        ///< the number of samples/sec. (-1 if not set)
                               int& numChannels        ///< the number of channels (-1 if not set)
                               ) const;

   // Get the fmtp parameter
   UtlBoolean getPayloadFormat(int mediaIndex,         ///< index to which m line contains rtpmap
                               int payloadType,
                               UtlString& fmtp) const;
   /**
    * See SdpCodec for utilities to parse the fmtp field (e.g. getFmtpParameter and getVideoSizes)
    */

   // Get the crypto field for SRTP
   UtlBoolean getSrtpCryptoField(int mediaIndex,                  ///< mediaIndex of crypto field
                                 int index,                       ///< Index inside of media type
                                 SdpSrtpParameters& params) const;

   // Get the a=control;trackId= value
   UtlBoolean getControlTrackId(int mediaLineIndex, UtlString& trackId) const;

   // Get the framerate field if there
   UtlBoolean getFramerateField(int mediaIndex,
                                int& videoFramerate) const;

   UtlBoolean getBandwidthField(int& bandwidth) const;

   /**<
    * Find the "a" record containing an rtpmap for the given
    * payload type id, parse it and return the parameters for it.
    */


#if 0
   /// Find the send and receive codecs from the rtpCodecs array which are compatible with this SdpBody..
   void getBestAudioCodecs(int numRtpCodecs,
                           SdpCodec rtpCodecs[],
                           UtlString* rtpAddress,
                           int* rtpPort,
                           int* sendCodecIndex,
                           int* receiveCodecIndex) const;
   ///< It is assumed that the best matches are first in the body
#endif


   /// Find the send and receive codecs from the rtpCodecs array which are compatible with this SdpBody.
   void getBestAudioCodecs(SdpCodecList& localRtpCodecs,
                           int& numCodecsInCommon,
                           SdpCodec**& commonCodecsForEncoder,
                           //SdpCodec**& commonCodecsForDecoder,
                           UtlString& rtpAddress, 
                           int& rtpPort,
                           int& rtcpPort,
                           int& videoRtpPort,
                           int& videoRtcpPort,
                           SdpSrtpParameters& localSrtpParams,
                           SdpSrtpParameters& matchingSrtpParams,
                           int localBandwidth,
                           int& matchingBandwidth,
                           int localVideoFramerate,
                           int& matchingVideoFramerate) const;
             
   ///< It is assumed that the best are matches are first in the body.
   // TODO: This interface is total broken and needs to be eliminated
   // It munges the codecs and payload types accross all of the m lines
   void getCodecsInCommon(int audioMediaSetIndex,
                          int videoMediaSetIndex,
                          int audioPayloadIdCount,
                          int videoPayloadIdCount,
                          int audioPayloadTypes[],
                          int videoPayloadTypes[],
                          int videoRtpPort,
                          SdpCodecList& localRtpCodecs,
                          int& numCodecsInCommon,
                          SdpCodec* commonCodecsForEncoder[],
                          SdpCodec* commonCodecsForDecoder[]) const;

   ///< For local capabilities, get remote media line and supported local codecs
   int getCodecsInCommon(const SdpMediaLine& localMediaLine,
                         int remoteMediaLineIndex,
                         SdpMediaLine& remoteMediaLine,
                         SdpCodecList& localDecodeCodecs) const;
   /**
    *  Assumes this SDP is the SDP offer and the localMediaLine is the capabilities for
    *  the offer.
    *
    *  @param localMediaLine - local capabilities (codecs, ports, addresses, etc.)
    *  @param remoteMediaLineIndex - index to m line in this SDP offer to which the local
    *                                capabilities are to be matched.
    *  @param remoteMediaLine - gets filled in with remote capabilities per indexed m line
    *  @param localDecodeCodecs - codecs that this side should offer with payload IDs matched
    *                             where possible.
    *
    * @returns number of matched codecs.
    */

   // Reads the indexed m line from this SDP into the given SdpMediaLine container.
   UtlBoolean getMediaLine(int remoteMediaLineIndex, SdpMediaLine& mediaLine, const SdpCodecList* codecFactory) const;

   // Add a SdpMediaLine object to this SdpBody
   void addMediaLine(const SdpMediaLine& mediaLine, SdpBody& sdpBody);

   // Find common encryption suites
   void getEncryptionInCommon(SdpSrtpParameters& audioParams,
                              SdpSrtpParameters& remoteParams,
                              SdpSrtpParameters& commonAudioParms) const;

   // Find common bandwidth
   void getBandwidthInCommon(int localBandwidth,
                             int remoteBandwidth,
                             int& commonBandwidth) const;

   // Find a common video framerate
   void getVideoFramerateInCommon(int localVideoFramerate,
                                  int remoteVideoFramerate,
                                  int& commonVideoFramerate) const;

    /**
     * Get the candidate attribute per draft-ietf-mmusic-ice-05
     */
    UtlBoolean getCandidateAttribute(int mediaIndex,
                                     int candidateIndex,
                                     int& rCandidateId,
                                     UtlString& rTransportId,
                                     UtlString& rTransportType,
                                     uint64_t& rQvalue, 
                                     UtlString& rCandidateIp, 
                                     int& rCandidatePort) const ;


   UtlBoolean getCandidateAttributes(const char* szMimeType,
                                     int         nMaxAddresses,                                     
                                     int         candidateIds[],
                                     UtlString   transportIds[],
                                     UtlString   transportTypes[],
                                     uint64_t    qvalues[], 
                                     UtlString   candidateIps[], 
                                     int         candidatePorts[],
                                     int&        nActualAddresses) const ;

   UtlBoolean getCandidateAttributes(int         mediaIndex,
                                     int         nMaxAddresses,                                     
                                     int         candidateIds[],
                                     UtlString   transportIds[],
                                     UtlString   transportTypes[],
                                     uint64_t    qvalues[], 
                                     UtlString   candidateIps[], 
                                     int         candidatePorts[],
                                     int&        nActualAddresses) const ;

   /**
     * Locates a specific value for an attribute field
     * Used to locate sendonly and recvonly in case if hold and unhold INVITE messages
     */
   UtlBoolean findValueInField(const char* pField, const char* pvalue) const;


///@}

/* //////////////////////////// PROTECTED ///////////////////////////////// */
  protected:
   friend class SdpBodyTest;
   
   /**
    * @name ====================== Generic SDP field accessors
    *
    * It is better to use the more specific accessor methods above for the field type you need
    * than to use these generic interfaces.  These may be deprecated in the future.
    *
    * @{
    */

   /// Return the number of fields in the body.
   int getFieldCount() const;

   /// Return the name and value of the nth field in the body.
   UtlBoolean getValue(int fieldIndex,
                       UtlString* name,
                       UtlString* value) const;
   /**<
    * It is better to use a more specific accessor method for the field type you need
    * than to iterate over all fields using this interface.
    *
    * @return FALSE if there are not enough fields
    */

   /// Set a specific field.
   void setValue(const char* name,       ///< field name to set
                 const char* value       ///< value for the named field
                 );

///@}

   /// Parse an existing string into the internal representation.
   void parseBody(const char* bytes = NULL, ///< NULL creates an empty body             
                  int byteCount = -1        ///< -1 means treat bytes as null terminated
                  );


/* //////////////////////////// PRIVATE /////////////////////////////////// */
  private:

   /// Get the position of the first of a set of headers, checking in order.
   size_t findFirstOf( const char* headers /**< null terminated set of single-character header names */);
   /**<
    * @returns The index of the first of the headers found, or UTL_NOT_FOUND if none are present.
    *
    * Example:
    * @code
    * 
    *    size_t timeLocation = findFirstOf("zkam");
    *    addValue("t", value.data(), timeLocation);
    * 
    * @endcode
    */
   
   /// Is the named field optional according to RFC 2327? true==optional.
   bool isOptionalField(const char* name) const;

   /// Add the given name/value pair to the body at the specified position.
   void addValue(const char* name, 
                 const char* value = NULL, 
                 int fieldIndex = -1       ///< -1 means append to the end.
                 );
   
   UtlSList* sdpFields;

   /// Position to the field instance.
   static NameValuePair* positionFieldInstance(int fieldInstanceIndex, ///< field instance of interest starting a zero
                                               UtlSListIterator* iter, /**< an iterator on sipFields. The search will
                                                                        *  start at the begining.*/
                                               const char* fieldName
                                               );
   /**<
    * Positions the given iterator to the to the nth instance of fieldName.
    * @return the field name value pair if it exists leaving the iterator positioned there.
    */

   static NameValuePair* findFieldNameBefore(UtlSListIterator* iter,
                                             const char* targetFieldName,
                                             const char* beforeFieldName);

   //! Disabled assignment operator
   SdpBody& operator=(const SdpBody& rhs);

};

/* ============================ INLINE METHODS ============================ */

#endif  // _SdpBody_h_
