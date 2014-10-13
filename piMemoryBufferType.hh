#ifndef PI_MEMORY_BUFFER_TYPE_HH
#define PI_MEMORY_BUFFER_TYPE_HH

#include <stdio.h>
#include <stdlib.h>
#include <queue>

#include <interface/vcos/vcos.h>
#include <interface/vcos/vcos_mutex.h>


#define PARAMETER_SET_MAX 64
#define RTSP_INPUT_BUFFER_MAX 300000

class PI_MEMORY_BUFFER
{
public:
    PI_MEMORY_BUFFER (u_int32_t duration);
    ~PI_MEMORY_BUFFER (void);
    
    u_int32_t get_duration (void) { return frameduration; }
    
    // flush temp storage to current frame storage
    void flush_frame_data (void);

    // save
    void save_sps_data (void* in_data, u_int32_t data_len);
    void save_pps_data (void* in_data, u_int32_t data_len);
    void push_frame_data (void* in_data, u_int32_t data_len);
    
    // read
    int read_frame_data (void* fTo, u_int32_t* readlen);
    void read_frame_sps (void* fTo, u_int32_t* readlen);
    void read_frame_pps (void* fTo, u_int32_t* readlen);
    
private:
    // lock for frame_data
    VCOS_MUTEX_T buffer_lock;
    VCOS_MUTEX_T spspps_lock;
    
    u_int32_t sps_len;
    char sps[PARAMETER_SET_MAX];
    u_int32_t pps_len;
    char pps[PARAMETER_SET_MAX];

    u_int32_t temp_data_len;
    char* temp_data;
    
    u_int32_t frame_data_len;
	u_int8_t is_new_frame;
    char* frame_data;

	u_int32_t frameduration;
};

#endif	
