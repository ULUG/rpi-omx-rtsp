
#include "piMemoryBufferedSource.hh"
#include "GroupsockHelper.hh"


piMemoryBufferedSource* piMemoryBufferedSource::createNew (
    UsageEnvironment& env, PI_MEMORY_BUFFER* input_buffer,
	Boolean deleteBufferOnClose)
{
	if (input_buffer == NULL) {
		return NULL;
	}

	return new piMemoryBufferedSource (env, input_buffer, deleteBufferOnClose);
}

piMemoryBufferedSource::piMemoryBufferedSource (UsageEnvironment& env,
	PI_MEMORY_BUFFER* input_buffer, Boolean deleteBufferOnClose)
    : FramedSource (env), fBuffer (input_buffer), nFrameIdx (0),
	fDeleteBufferOnClose (deleteBufferOnClose), fPlayTimePerFrame (0),
	fLastPlayTime (0)
{
	// constructor
    fMaxSize = RTSP_INPUT_BUFFER_MAX;
}

piMemoryBufferedSource::~piMemoryBufferedSource (void)
{
	if (fDeleteBufferOnClose) {
		delete fBuffer;
	}
}

void piMemoryBufferedSource::doGetNextFrame (void)
{
    if (nFrameIdx < PARAMETER_SET_DISTANCE) {
        // read frame
        while (fBuffer->read_frame_data (fTo, &fFrameSize) == 0) {
            // wait for frame data
            // busy loop for simplicity
            usleep (1000);
        }
    } else if (nFrameIdx == PARAMETER_SET_DISTANCE) {
        // read sps, pps will be delivered by next call
        fBuffer->read_frame_sps (fTo, &fFrameSize);
    } else {
        // read pps, reset frame index
        fBuffer->read_frame_pps (fTo, &fFrameSize);
        nFrameIdx = 0;
    }
	//printf ("read frame %d\n", fFrameSize);
    
    // increase frame index
    nFrameIdx++;

	// set the presentation time
    // so just record the current time as being the presentation time
    gettimeofday(&fPresentationTime, NULL);

	// inform the downstream object that it has data:
	FramedSource::afterGetting(this);
}

