#ifndef OMX_UTILS_HH
#define OMX_UTILS_HH

#include <interface/vcos/vcos.h>
#include <IL/OMX_Broadcom.h>

#include "omx_dump.hh"



#define OMX_INIT_STRUCTURE(x) \
memset (&(x), 0, sizeof (x)); \
(x).nSize = sizeof (x); \
(x).nVersion.nVersion = OMX_VERSION; \
(x).nVersion.s.nVersionMajor = OMX_VERSION_MAJOR; \
(x).nVersion.s.nVersionMinor = OMX_VERSION_MINOR; \
(x).nVersion.s.nRevision = OMX_VERSION_REVISION; \
(x).nVersion.s.nStep = OMX_VERSION_STEP

#define VIDEO_FRAMERATE 30
#define VIDEO_BITRATE 3000000
#define VIDEO_IDR_PERIOD 5 //Disabled
#define VIDEO_SEI OMX_FALSE
#define VIDEO_EEDE OMX_FALSE
#define VIDEO_EEDE_LOSS_RATE 0
#define VIDEO_QP OMX_FALSE
#define VIDEO_QP_I 0 //1 .. 51, 0 means off
#define VIDEO_QP_P 0 //1 .. 51, 0 means off
#define VIDEO_PROFILE OMX_VIDEO_AVCProfileBaseline //OMX_VIDEO_AVCProfileHigh
#define VIDEO_INLINE_HEADERS OMX_FALSE

//Some settings doesn't work well
#define CAM_WIDTH 1280
#define CAM_HEIGHT 720
#define CAM_SHARPNESS 0 //-100 .. 100
#define CAM_CONTRAST 0 //-100 .. 100
#define CAM_BRIGHTNESS 50 //0 .. 100
#define CAM_SATURATION 0 //-100 .. 100
#define CAM_SHUTTER_SPEED_AUTO OMX_TRUE
#define CAM_SHUTTER_SPEED 1.0/8.0
#define CAM_ISO_AUTO OMX_TRUE
#define CAM_ISO 100 //100 .. 800
#define CAM_EXPOSURE OMX_ExposureControlAuto
#define CAM_EXPOSURE_COMPENSATION 0 //-24 .. 24
#define CAM_MIRROR OMX_MirrorNone
#define CAM_ROTATION 0 //0 90 180 270
#define CAM_COLOR_ENABLE OMX_FALSE
#define CAM_COLOR_U 128 //0 .. 255
#define CAM_COLOR_V 128 //0 .. 255
#define CAM_NOISE_REDUCTION OMX_TRUE
#define CAM_FRAME_STABILIZATION OMX_FALSE
#define CAM_METERING OMX_MeteringModeAverage
#define CAM_WHITE_BALANCE OMX_WhiteBalControlAuto
// The gains are used if the white balance is set to off
#define CAM_WHITE_BALANCE_RED_GAIN 1000 //0 ..
#define CAM_WHITE_BALANCE_BLUE_GAIN 1000 //0 ..
#define CAM_IMAGE_FILTER OMX_ImageFilterNone
#define CAM_ROI_TOP 0 //0 .. 100
#define CAM_ROI_LEFT 0 //0 .. 100
#define CAM_ROI_WIDTH 100 //0 .. 100
#define CAM_ROI_HEIGHT 100 //0 .. 100
#define CAM_DRC OMX_DynRangeExpOff


// Component data
typedef struct {
    OMX_HANDLETYPE handle;
    VCOS_EVENT_FLAGS_T flags;
    OMX_STRING name;
} component_t;


// Events used with vcos_event_flags_get() and vcos_event_flags_set()
typedef enum {
    EVENT_ERROR = 0x1,
    EVENT_PORT_ENABLE = 0x2,
    EVENT_PORT_DISABLE = 0x4,
    EVENT_STATE_SET = 0x8,
    EVENT_FLUSH = 0x10,
    EVENT_MARK_BUFFER = 0x20,
    EVENT_MARK = 0x40,
    EVENT_PORT_SETTINGS_CHANGED = 0x80,
    EVENT_PARAM_OR_CONFIG_CHANGED = 0x100,
    EVENT_BUFFER_FLAG = 0x200,
    EVENT_RESOURCES_ACQUIRED = 0x400,
    EVENT_DYNAMIC_RESOURCES_AVAILABLE = 0x800,
    EVENT_FILL_BUFFER_DONE = 0x1000,
    EVENT_EMPTY_BUFFER_DONE = 0x2000,
} component_event;


// Event handler functions
OMX_ERRORTYPE event_handler (OMX_IN OMX_HANDLETYPE comp,
    OMX_IN OMX_PTR app_data, OMX_IN OMX_EVENTTYPE event, OMX_IN OMX_U32 data1,
    OMX_IN OMX_U32 data2, OMX_IN OMX_PTR event_data);
OMX_ERRORTYPE fill_buffer_done_handler ( OMX_IN OMX_HANDLETYPE comp,
    OMX_IN OMX_PTR app_data, OMX_IN OMX_BUFFERHEADERTYPE* buffer);

// Synchronize functions
void wake (component_t* component, VCOS_UNSIGNED event);
void wait (component_t* component, VCOS_UNSIGNED events,
           VCOS_UNSIGNED* retrieved_events);

// Component init functions
void init_component (component_t* component);
void load_camera_drivers (component_t* component);
void deinit_component (component_t* component);

//
void change_state (component_t* component, OMX_STATETYPE state);

void enable_port (component_t* component, OMX_U32 port);
void disable_port (component_t* component, OMX_U32 port);

// Encoder buffer setting functions
void enable_encoder_output_port (component_t* encoder,
    OMX_BUFFERHEADERTYPE** encoder_output_buffer);
void disable_encoder_output_port (component_t* encoder,
    OMX_BUFFERHEADERTYPE* encoder_output_buffer);

// Component settings
void camera_settings (component_t* camera);
void encoder_settings (component_t* encoder);

#endif // OMX_UTILS_HH
