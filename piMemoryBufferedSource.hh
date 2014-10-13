#ifndef PI_MEMORY_BUFFERED_SOURCE_HH
#define PI_MEMORY_BUFFERED_SOURCE_HH


#ifndef _FRAMED_SOURCE_HH
#include "FramedSource.hh"
#endif

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <interface/vcos/vcos.h>
#include <interface/vcos/vcos_mutex.h>

#include "piMemoryBufferType.hh"

// read from buffer sps_pps -> frames -> sps_pps
#define PARAMETER_SET_DISTANCE 5

class piMemoryBufferedSource : public FramedSource
{
public:
	static piMemoryBufferedSource* createNew (UsageEnvironment& env,
		PI_MEMORY_BUFFER* input_buffer, Boolean deleteBufferOnClose = True);

protected:
	// called only by createNew ()
	piMemoryBufferedSource (UsageEnvironment& env,
        PI_MEMORY_BUFFER* input_buffer, Boolean deleteBufferOnClose);
	
	virtual ~piMemoryBufferedSource (void);

private:
	// redefined virtual functions
	virtual void doGetNextFrame (void);

	// buffer data
    PI_MEMORY_BUFFER* fBuffer;
    u_int32_t nFrameIdx;
    
	Boolean fDeleteBufferOnClose;
 	unsigned fPlayTimePerFrame;
	unsigned fLastPlayTime;
};


#endif
