// Copyright 2022 LINE Plus Corporation
//
// LINE Plus Corporation licenses this file to you under the Apache License,
// version 2.0 (the "License"); you may not use this file except in compliance
// with the License. You may obtain a copy of the License at:
//
//   https://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
// WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the
// License for the specific language governing permissions and limitations
// under the License.

#pragma once

/*! \file */

#include "PlanetKitUserId.h"

namespace PlanetKit 
{
    class PLANETKIT_API VideoSource;

    typedef HWND WindowHandle;

    /**
     * Enumeration for the result of capturer APIs
     */
    enum ECapturerResult
    {
        /// Successfully started the capturer.
        ECapturerResult_Success = 0,
        /// An unknown error occurred.
        ECapturerResult_Unknown,
        /**
         * Failed to start the capturer. <br>
         *  - Another program may be using the capturer. In this case, it is a temporary phenomenon and it works normally when the program using the capturer is closed.<br>
         *  - If the phenomenon continues to occur, the program cannot run the camera due to insufficient privileges. Check the program's permissions.
         */
        ECapturerResult_AccessDenied,
        /**
         * The capturer is already running.
         */
        ECapturerResult_AlreadyRunning,
        /**
         * Failed to create a thread for the capturer.<br>
         *  - This is a temporary phenomenon and works normally when the computer is rebooted.
         */
        ECapturerResult_FailedToCreateThread,
        /// Not used.
        ECapturerResult_Max
    };

    /**
     * Enumeration for the result of capturer APIs
     */
    enum EVideoControlResult {
        /// Successfully started the capturer.
        EVideoControlResult_Success = 0,
        /// An unknown error occurred.
        EVideoControlResult_Unknown,
        /**
         * Failed to start the capturer. <br>
         *  - Another program may be using the capturer. In this case, it is a temporary phenomenon and it works normally when the program using the capturer is closed.<br>
         *  - If the phenomenon continues to occur, the program cannot run the camera due to insufficient privileges. Check the program's permissions.
         */
        EVideoControlResult_AccessDenied,
        /**
         * The capturer is already running.
         */
        EVideoControlResult_AlreadyRunning,
        /**
         * Failed to create a thread for the capturer.<br>
         *  - This is a temporary phenomenon and works normally when the computer is rebooted.
         */
        EVideoControlResult_FailedToCreateThread,
        /**
         * Failed to save images through the corresponding camera device.
         */
        EVideoControlResult_CreateVideoCapturerFail,
        /**
         * There is no available video device.
         */
        EVideoControlResult_notAvailableVideoDevice,
        /**
         * The video capture failed due to the failure of the call logic.
         */
        EVideoControlResult_CallLogicFail,
        /**
         * The video controller is not initialized yet.
         */
        EVideoControlResult_VideoControllerNotInitialized,
        /**
         * The preview already exists.
         */
        EVideoControlResult_PreviewAlreadyExist,
        /**
         * Failed to create video render.
         */
        EVideoControlResult_CreateRenderFail,
        /**
         * The camera is being used by another application.
         */
        EVideoControlResult_CameraIsAlreadyInUseByAnotherApplication,
        /**
         * The preview handle is invalid. 
         * If you want to use StartPreview, then the handle must be valid.
         */
        EVideoControlResult_PreviewHandleIsInvalid,
        /**
         * The preview receiver is invalid.
         * If you want to use StartPreview, then the receiver must be valid.
         */
        EVideoControlResult_PreviewReceiverIsInvalid,
        /**
         * Failed because no camera is currently selected. 
         * Please call CameraController::SelectCamera() to select a camera first.
         */
        EVideoControlResult_CameraIsNotSelected,
        /// Not used.
        EVideoControlResult_Max
    };

    /**
     * @brief Video resolution that PlanetKit can support.
     */
    typedef enum EVideoResolution
    {
        /// Unknown resolution
        PLNK_VIDEO_RESOLUTION_UNKNOWN = -1, 
        /// Recommended resolution
        PLNK_VIDEO_RESOLUTION_RECOMMENDED = 0, 
        /// Thumbnail resolution
        PLNK_VIDEO_RESOLUTION_THUMBNAIL, 
        /// QVGA resolution
        PLNK_VIDEO_RESOLUTION_QVGA,
        /// VGA resolution
        PLNK_VIDEO_RESOLUTION_VGA, 
        /// HD or FHD resolution
        PLNK_VIDEO_RESOLUTION_HD_FHD, 
        /// Defined as UHD but not supported yet.
        PLNK_VIDEO_RESOLUTION_UHD, 

        /// Max Value
        PLNK_VIDEO_RESOLUTION_MAX = PLNK_VIDEO_RESOLUTION_HD_FHD, 
    }EVideoResolution;

    /**
     * Camera resolution that PlanetKit can support.
     */
    typedef enum ECameraResolution
    {
        /// VGA resolution (640:480)
        PLNK_CAMERA_RESOLUTION_VGA, 
        /// VGA 16:9 resolution (640:360)
        PLNK_CAMERA_RESOLUTION_VGA_16_9, 
        /// HD resolution (1280:720)
        PLNK_CAMERA_RESOLUTION_HD, 
        /// VGA resolution (1920:1080)
        PLNK_CAMERA_RESOLUTION_FHD 
    }ECameraResolution;

#if __cplusplus >= 201103L || (defined(_MSC_VER) && _MSC_VER >= 1800)
    constexpr ECameraResolution ECameraResolutionDefault = PLNK_CAMERA_RESOLUTION_HD;
#else
#define ECameraResolutionDefault (PlanetKit::ECameraResolution::PLNK_CAMERA_RESOLUTION_HD)
#endif
    

    /**
     * Camera FPS that PlanetKit can support.
     */
    typedef enum EVideoCaptureFps
    {
        /// Default
        PLNK_VIDEO_CAPTURE_FPS_DEFAULT = 0, 
        /// 5 fps
        PLNK_VIDEO_CAPTURE_FPS_5 = 5,
        /// 10 fps
        PLNK_VIDEO_CAPTURE_FPS_10 = 10,
        /// 15 fps
        PLNK_VIDEO_CAPTURE_FPS_15 = 15,
        /// 24 fps
        PLNK_VIDEO_CAPTURE_FPS_24 = 24,
        /// 30 fps
        PLNK_VIDEO_CAPTURE_FPS_30 = 30,
        /// Max, which means 30 fps
        PLNK_VIDEO_CAPTURE_FPS_MAX = PLNK_VIDEO_CAPTURE_FPS_30,
    } EVideoCaptureFps;

    /**
     * Video FPS that PlanetKit can support.
     */
    typedef enum EVideoFps 
    {
        /// Undefined
        PLNK_VIDEO_FPS_UNDEFINED = 0,
        /// 5 fps
        PLNK_VIDEO_FPS_5,
        /// 10 fps
        PLNK_VIDEO_FPS_10,
        /// 15 fps
        PLNK_VIDEO_FPS_15,
        /// 24 fps
        PLNK_VIDEO_FPS_24,
        /// 30 fps
        PLNK_VIDEO_FPS_30,
        /// Max, which means 30 fps
        PLNK_VIDEO_FPS_MAX = PLNK_VIDEO_FPS_30,
    }EVideoFps;


#if __cplusplus >= 201103L || (defined(_MSC_VER) && _MSC_VER >= 1800)
    constexpr EVideoFps EVideoFpsDefault = PLNK_VIDEO_FPS_15;
#else
#define EVideoFpsDefault (PlanetKit::EVideoFps::PLNK_VIDEO_FPS_15)
#endif

    /**
     * Capture media type
     */
    typedef enum ECapturerMediaType
    {
        /// Unknown
        PLNK_CAPTURER_TYPE_Unknown = 0,
        /// I420
        PLNK_CAPTURER_TYPE_I420,
        /// IYUV
        PLNK_CAPTURER_TYPE_IYUV,
        /// RGB24
        PLNK_CAPTURER_TYPE_RGB24,
        /// ARGB
        PLNK_CAPTURER_TYPE_ARGB,
        /// RGB565
        PLNK_CAPTURER_TYPE_RGB565,
        /// YUY2
        PLNK_CAPTURER_TYPE_YUY2,
        /// YV12
        PLNK_CAPTURER_TYPE_YV12,
        /// UYVY
        PLNK_CAPTURER_TYPE_UYVY,
        /// MJPEG
        PLNK_CAPTURER_TYPE_MJPEG,
        /// BGRA
        PLNK_CAPTURER_TYPE_BGRA,
        /// RGB32
        PLNK_CAPTURER_TYPE_RGB32,
        /// RGB555
        PLNK_CAPTURER_TYPE_RGB555,
        /// RGB8
        PLNK_CAPTURER_TYPE_RGB8,
        /// L8
        PLNK_CAPTURER_TYPE_L8,
        /// L16
        PLNK_CAPTURER_TYPE_L16,
        /// D16
        PLNK_CAPTURER_TYPE_D16,
        /// AI44
        PLNK_CAPTURER_TYPE_AI44,
        /// AYUV
        PLNK_CAPTURER_TYPE_AYUV,
        /// YVYU
        PLNK_CAPTURER_TYPE_YVYU,
        /// YVU9
        PLNK_CAPTURER_TYPE_YVU9,
        /// NV11
        PLNK_CAPTURER_TYPE_NV11,
        /// NV12
        PLNK_CAPTURER_TYPE_NV12,
        /// Y210
        PLNK_CAPTURER_TYPE_Y210,
        /// Y216
        PLNK_CAPTURER_TYPE_Y216,
        /// Y410
        PLNK_CAPTURER_TYPE_Y410,
        /// Y416
        PLNK_CAPTURER_TYPE_Y416,
        /// Y41P
        PLNK_CAPTURER_TYPE_Y41P,
        /// Y41T
        PLNK_CAPTURER_TYPE_Y41T,
        /// Y42T
        PLNK_CAPTURER_TYPE_Y42T,
        /// P210
        PLNK_CAPTURER_TYPE_P210,
        /// P216
        PLNK_CAPTURER_TYPE_P216,
        /// P010
        PLNK_CAPTURER_TYPE_P010,
        /// P016
        PLNK_CAPTURER_TYPE_P016,
        /// v210
        PLNK_CAPTURER_TYPE_v210,
        /// v216
        PLNK_CAPTURER_TYPE_v216,
        /// v410
        PLNK_CAPTURER_TYPE_v410,
        /// MP43
        PLNK_CAPTURER_TYPE_MP43,
        /// MP4S
        PLNK_CAPTURER_TYPE_MP4S,
        /// M4S2
        PLNK_CAPTURER_TYPE_M4S2,
        /// MP4V
        PLNK_CAPTURER_TYPE_MP4V,
        /// WMV1
        PLNK_CAPTURER_TYPE_WMV1,
        /// WMV2
        PLNK_CAPTURER_TYPE_WMV2,
        /// WMV3
        PLNK_CAPTURER_TYPE_WMV3,
        /// WVC1
        PLNK_CAPTURER_TYPE_WVC1,
        /// MSS1
        PLNK_CAPTURER_TYPE_MSS1,
        /// MSS2
        PLNK_CAPTURER_TYPE_MSS2,
        /// MPG1
        PLNK_CAPTURER_TYPE_MPG1,
        /// DVSL
        PLNK_CAPTURER_TYPE_DVSL,
        /// DVSD
        PLNK_CAPTURER_TYPE_DVSD,
        /// DVHD
        PLNK_CAPTURER_TYPE_DVHD,
        /// DV25
        PLNK_CAPTURER_TYPE_DV25,
        /// DV50
        PLNK_CAPTURER_TYPE_DV50,
        /// DVH1
        PLNK_CAPTURER_TYPE_DVH1,
        /// DVC
        PLNK_CAPTURER_TYPE_DVC,
        /// H264
        PLNK_CAPTURER_TYPE_H264,
        /// H265
        PLNK_CAPTURER_TYPE_H265,
        /// 420O
        PLNK_CAPTURER_TYPE_420O,
        /// HEVC
        PLNK_CAPTURER_TYPE_HEVC,
        /// HEVC_ES
        PLNK_CAPTURER_TYPE_HEVC_ES,
        /// VP80
        PLNK_CAPTURER_TYPE_VP80,
        /// VP90
        PLNK_CAPTURER_TYPE_VP90,
        /// ORAW
        PLNK_CAPTURER_TYPE_ORAW,
        /// H263
        PLNK_CAPTURER_TYPE_H263,
        /// A2R10G10B10
        PLNK_CAPTURER_TYPE_A2R10G10B10,
        /// A16B16G16R16F
        PLNK_CAPTURER_TYPE_A16B16G16R16F,
        /// H264_ES
        PLNK_CAPTURER_TYPE_H264_ES,
        /// MPEG2
        PLNK_CAPTURER_TYPE_MPEG2,
        /// H264_HDCP
        PLNK_CAPTURER_TYPE_H264_HDCP,
        /// HEVC_HDCP
        PLNK_CAPTURER_TYPE_HEVC_HDCP,
        /// Base_HDCP
        PLNK_CAPTURER_TYPE_Base_HDCP,
    }ECapturerMediaType;

    /**
     * An enumeration representing the mirroring types of a view.
     */
    typedef enum EVideoMirrorType {
        /// For the local user's video, the mirroring mode is determined based on the currently used camera.
        PLNK_MIRROR_TYPE_AUTO = 0,
        /// Activates mirroring for the view, displaying the original video flipped horizontally.
        PLNK_MIRROR_TYPE_MIRRORED = 1,
        /// Deactivates mirroring for the view, displaying the original video as it is.
        PLNK_MIRROR_TYPE_UNMIRRORED = 2
    } EVideoMirrorType;

    /**
     * Rotation of video
     */
    typedef enum EVideoRotation {
        /// No rotation
        PLNK_VIDEO_ROTATION_0 = 0,
        /// Rotation by 90 degrees
        PLNK_VIDEO_ROTATION_90 = 1,
        /// Rotation by 180 degrees
        PLNK_VIDEO_ROTATION_180 = 2,
        /// Rotation by 270 degrees
        PLNK_VIDEO_ROTATION_270 = 3
    }EVideoRotation;

    /**
     * Rendered video ratio mode
     */
    typedef enum EVideoAspectRatioMode
    {
        /// Fills the window and ignores the aspect ratio.
        PLNK_VIDEO_FILL_WINDOW,
        /// Keeps the aspect ratio and fits the window.
        PLNK_VIDEO_ASPECT_FIT, 
        /// Crops to fill the window with aspect ratio.
        PLNK_VIDEO_ASPECT_FILL, 
        /// Indicates an error type.
        PLNK_VIDEO_ASPECT_MODE_UNDEFINED 
    }EVideoAspectRatioMode;

    /// Type to use when opening the camera.
    typedef enum ECameraInfoType
    {
        /// Indicates the normal type. When opening the camera, it uses the optimal specification that can be supported.
        PLNK_CAMERA_INFO_NORMAL = 0,
        /// Indicates a type that uses only the MJPEG type. Opening the camera fails if the device does not support MJPEG.
        PLNK_CAMERA_INFO_ONLY_MJPEG,
        /// This type excludes the MJPEG type when opening the camera.
        PLNK_CAMERA_INFO_NOT_USE_MJPEG
    }ECameraInfoType;

#if __cplusplus >= 201103L || (defined(_MSC_VER) && _MSC_VER >= 1800)
    constexpr ECameraInfoType ECameraInfoTypeDefault = PLNK_CAMERA_INFO_NORMAL;
#else
#define ECameraInfoTypeDefault (PlanetKit::ECameraInfoType::PLNK_CAMERA_INFO_NORMAL)
#endif

    /**
     * Video capability
     */
    typedef struct SVideoCapability
    {
        /// Video max resolution
        EVideoResolution eMaxResolution;
        /// Video max FPS
        EVideoFps eMaxFps;
        /// Preferred HW codec
        bool bPreferHWCodec;
    } SVideoCapability;

    /**
     * Capturer type
     */
    typedef enum EVideoCapturerType
    {
        /// Camera
        PLNK_VID_CAPTURER_CAMERA,
        /// Screen selected for screen share
        PLNK_VID_CAPTURER_SCREEN,
        /// Window selected for screen share
        PLNK_VID_CAPTURER_WINDOW,
        /// Capturer is not found.
        PLNK_VID_CAPTURER_NO_CAPTURER,
    } EVideoCapturerType;

    typedef enum EInitialMyVideoState
    {
        PLNK_INITIAL_MY_VIDEO_STATE_RESUME = 0,
        PLNK_INITIAL_MY_VIDEO_STATE_PAUSE,
    }EInitialMyVideoState;

    /**
     * Result for PlanetKitConference::StopPeerVideo and PlanetKitConference::RequestPeerVideo, which is delivered by the callback API.
     */
    typedef struct SRequestMediaResultParam
    {
        /// Result of PlanetKitConference::StopPeerVideo or PlanetKitConference::RequestPeerVideo APIs
        bool bIsSuccess;
        /// Error code
        EMediaRequestError eError;
        /// Failure reason when API fails.
        const char* szFailReason;
    } SRequestMediaResultParam;

    /**
     * Result for PlanetKitConference::RequestPeerVideo, which is delivered by the callback API.
     */
    typedef struct SRequestVideoResolutionResultParam
    {
        /// Result of PlanetKitConference::RequestPeerVideo APIs
        bool                bIsSuccess;
        /// Error code
        EMediaRequestError  eError;
        /// Resolution that you requested
        EVideoResolution    eRequestRes;
        /// Resolution that is received
        EVideoResolution    eReceiveRes;
        /// Failure reason when API fails.
        const char*         szFailReason;
    } SRequestVideoResolutionResultParam;

    /**
     * Video frame information
     */
    typedef struct SVideoFrame
    {
        /// Pointer to the frame buffer
        unsigned char *pbuffer;
        /// Allocated buffer size
        unsigned int unBufferSize;
        /// Length (in bytes) of buffer
        unsigned int unDataLength;
        /// Width
        unsigned int unWidth;
        /// Height
        unsigned int unHeight;
        /// Tick
        long long llTick;
        /// Time stamp
        long long llTimeStamp;
        /// Duration
        long long llDuration;
        /// Rotation
        EVideoRotation eRotation;

        /// You can use this flag to check whether the frame belongs to the main room.
        bool bSubgroupMain;
        /// Subgroup name that can be used if bSubgroupMain flag is false
        wchar_t szSubgroupName[PLNK_BUFFER_SIZE_512];
    }SVideoFrame;

    /// Video frame class
    class VideoFrame : public Base
    {
    public :
        /// Gets the frame buffer. (I420 buffer)
        virtual unsigned char* GetBuffer() = 0;
        /// Gets the allocated buffer size.
        virtual unsigned int GetBufferSize() = 0;
        /// Gets the length (in bytes) of the buffer.
        virtual unsigned int GetDataLength() = 0;
        /// Gets the frame width.
        virtual int GetWidth() = 0;
        /// Gets the frame height.
        virtual int GetHeight() = 0;
        /// Gets the frame stride.
        virtual int GetStride() = 0;
    };

    template class PLANETKIT_API AutoPtr<VideoFrame>;
    typedef AutoPtr<VideoFrame> VideoFramePtr;
    
    typedef  void * ScreenId;
    typedef  void * WindowId; //HWND
    typedef  void * ScreenShareID; //HWND

    /**
     * This class is provided to receive peer's video data and render it directly.
     * @remark
     *   You should create a custom class that inherits from this class.
     * @see
     *   - PlanetKitConference::RegisterMyVideoReceiver
     *   - PlanetKitConference::RegisterPeersVideoReceiver
     *   - PlanetKitConference::RegisterMyScreenShareReceiver
     *   - PlanetKitConference::RegisterPeerScreenShareReceiver
     *   - PlanetKitConference::DeregisterMyVideoReceiver
     *   - PlanetKitConference::DeregisterPeersVideoReceiver
     *   - PeerControl::SetReceiver
     */

    class PLANETKIT_API IVideoReceiver {
    public:
        /**
         * Called when the peer's video data is activated.
         * @param pVideoFrame Peer's video data. You can render the peer's video with this parameter.
         * @param szPeerId Peer's ID.
         * @param szPeerServiceId Peer's service ID.
         * @remark
         * - In the case of the local user's own frame, the ID and ServiceID will be nullptr.
         */
        virtual void OnVideo(const SVideoFrame *pVideoFrame, UserIdPtr pUserID) = 0;
    };

    template<typename T>
    inline T GET_VIDEO_DATA_LENGTH(const T& witdh, const T& height)
    {
        return (T)(witdh * height * 1.5);
    }

    /// The interface for receiving a callback when frame processing is finished.
    class PLANETKIT_API IVideoInterceptorDelegate {
    public:
        /**
         * A callback that occurs when a capture is finished.
         * @param pVideoFrame The frame being captured.
         * @return
         *  - Returns true if successful.
         */
        virtual bool onProcessFinished(SVideoFrame* pVideoFrame) = 0;
    };

    /// The interface for receiving a callback when the status of the window in screen share changes.
    class PLANETKIT_API IVideoInterceptor {
    public:
        /**
        * Returns SVideoFrame* if a video frame is processed synchronously
        */
        virtual SVideoFrame* ProcessVideoFrame(SVideoFrame* pVideoFrame) = 0;

        /**
         * Registers the frame processing completion callback.
         * @param pDelegate A callback that occurs when a capture is finished.
         * @return
         *  - Returns true if successful.
         */
        virtual bool RegisterDelegate(IVideoInterceptorDelegate* pDelegate) = 0;

        /**
         * Deregisters the frame processing completion callback.
         * @return
         *  - Returns true if successful.
         */
        virtual bool DeregisterDelegate() = 0;
    };

}