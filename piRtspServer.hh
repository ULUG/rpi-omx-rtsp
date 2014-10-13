#ifndef PI_RTSP_SERVER_HH
#define PI_RTSP_SERVER_HH

#include <liveMedia.hh>
#include <BasicUsageEnvironment.hh>
#include <GroupsockHelper.hh>

#include "piMemoryBufferType.hh"
#include "piMemoryBufferedSource.hh"

// this function never returns
// global image frame buffer as an arg
void* startRtspServer (void* arg);

#endif //PI_RTSP_SERVER_HH
