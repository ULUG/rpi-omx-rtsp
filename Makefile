.SUFFIXES : .cpp .o

CC = g++
CXX = g++
PROGRAM  = picam_rtsp.bin

CFLAGS = -DSTANDALONE -D__STDC_CONSTANT_MACROS -D__STDC_LIMIT_MACROS \
        -DTARGET_POSIX -D_LINUX -DPIC -D_REENTRANT -D_LARGEFILE64_SOURCE \
        -D_FILE_OFFSET_BITS=64 -U_FORTIFY_SOURCE -DHAVE_LIBOPENMAX=2 -DOMX \
        -DOMX_SKIP64BIT -ftree-vectorize -pipe -DUSE_EXTERNAL_OMX \
        -DHAVE_LIBBCM_HOST -DUSE_EXTERNAL_LIBBCM_HOST -DUSE_VCHIQ_ARM -fPIC \
        -ftree-vectorize -pipe -g -Wall -fpermissive

# general, openmax flags
LDFLAGS = -L/opt/vc/lib -lopenmaxil -lbcm_host -lvcos -lvchiq_arm -lpthread -lstdc++
INCLUDES = -I/opt/vc/include -I/opt/vc/include/interface/vcos/pthreads \
        -I/opt/vc/include/interface/vmcs_host/linux

# live555 flags
LDFLAGS += /usr/local/lib/libliveMedia.a /usr/local/lib/libgroupsock.a /usr/local/lib/libBasicUsageEnvironment.a /usr/local/lib/libUsageEnvironment.a
INCLUDES += -I/usr/local/include/liveMedia -I/usr/local/include/groupsock -I/usr/local/include/BasicUsageEnvironment -I/usr/local/include/UsageEnvironment


SRCS = picam_rtsp.cpp \
		omx_utils.cpp \
		omx_dump.cpp \
		piRtspServer.cpp \
		piMemoryBufferType.cpp \
		piMemoryBufferedSource.cpp

OBJS = picam_rtsp.o \
		omx_utils.o \
		omx_dump.o \
		piRtspServer.o \
		piMemoryBufferType.o \
		piMemoryBufferedSource.o


all: $(PROGRAM)

picam_rtsp.bin: $(OBJS) $(SRCS) Makefile
	$(CC) -o $(PROGRAM) $(OBJS) $(LDFLAGS) -rdynamic
 
#$(CC) -o $(PROGRAM) -Wl,--whole-archive $(OBJS) $(LDFLAGS) -Wl,--no-whole-archive -rdynamic

%.o: %.cpp
	$(CC) $(CFLAGS) $(INCLUDES) -c ${*F}.cpp -o ${*F}.o -Wno-deprecated-declarations


clean:
	rm -f $(PROGRAM) *.o
