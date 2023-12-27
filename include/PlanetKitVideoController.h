// Copyright 2023 LINE Plus Corporation
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

#include "PlanetKit.h"
#include "PlanetKitVideoCommon.h"
#include "PlanetKitCameraInfo.h"
#include "PlanetKitScreenShareInfo.h"
#include "PlanetKitVideoRender.h"
#include "PlanetKitUserId.h"

namespace PlanetKit
{
    class VideoSource;
    class PLANETKIT_API VideoRender;
    typedef AutoPtr<VideoRender> VideoRenderPtr;

    typedef AutoPtr<VideoController> VideoControllerPtr;

    typedef HWND WindowHandle;

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

    /// The interface for receiving a callback when frame processing is finished.
    class PLANETKIT_API IVideoCapturerEvent {
    public:
        // A callback for VideoCaptureType::VIDEO_CAPTURE_WINDOW
        virtual void OnCaptureWindowStateChanged(const SWindowStateChangeParam *pParam) = 0;
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
        virtual bool RegisterDelegate(IVideoInterceptorDelegate *pDelegate) = 0;

        /**
         * Deregisters the frame processing completion callback.
         * @return
         *  - Returns true if successful.
         */
        virtual bool DeregisterDelegate() = 0;
    };

    /// The interface for receiving a callback when there are changes to the capture device.
    class PLANETKIT_API IVideoCaptureDeviceEvent  {
    public:
        PLANETKIT_DEPRECATED("This will not be supported in 5.1.19 or later. Use void OnDeviceAdded(CameraInfoPtr pInfo)")
            /**
             * @deprecated This will not be supported in 5.1.19 or later.
             * @see void OnDeviceAdded(CameraInfoPtr pInfo)
             */
            void onDeviceAdded(const SCameraInfo* pInfo);

        PLANETKIT_DEPRECATED("This will not be supported in 5.1.19 or later. Use void OnDeviceRemoved(CameraInfoPtr pInfo)")
            /**
             * @deprecated This will not be supported in 5.1.19 or later.
             * @see void OnDeviceRemoved(CameraInfoPtr pInfo)
             */
            void onDeviceRemoved(const SCameraInfo* pInfo);

        /**
         * This callback method is called when a camera device is added.
         * @param pInfo Information of the added camera device.
         */
        virtual void OnDeviceAdded(CameraInfoPtr pInfo) = 0;

        /**
         * This callback method is called when a camera device is removed.
         * @param pInfo Information of the removed camera device.
         */
        virtual void OnDeviceRemoved(CameraInfoPtr pInfo) = 0;
    };
    
    /// The class for managing the video of screen share and camera.
    class PLANETKIT_API VideoController : virtual public Base {
    public:
        /**
         * Adds a Windows Handle to render the local user's view.
         * @param hWind The Windows Handle to render the local user's view.
         * @return
         *  - Returns true if the local user's view is successfully added. 
         *  - Returns false if the local user's view is already added or if it fails to add the view.
         * @remark
         *  - For screen share, it adds a view to render the local user's shared screen.
         *  - For the camera, it adds a view to render the local user's screen captured by the camera.
         */
        virtual bool AddMyView(WindowHandle hWind) = 0;

        /**
         * Clears all of the local user's views that are currently stored.
         */
        virtual void ClearMyView() = 0;

        /**
         * Removes a Windows Handle to render the local user's view.
         * @param hWind The Windows Handle to render the local user's view.
         * @return
         *  - If the local user's view is successfully removed, it returns true.
         *  - Returns false if the local user's view does not exist or if it fails to remove the view.
         * @remark
         *  - For screen share, it removes a view to render the shared screen.
         *  - For the camera, it removes a view to render the local user's screen captured by the camera.
         */
        virtual bool RemoveMyView(WindowHandle hWind) = 0;

        /**
         * Adds a Windows Handle to render a peer view.
         * @param hWind The Windows Handle to render a peer view.
         * @return
         *  - Returns true if the peer view is successfully added.
         *  - Returns false if the peer view is already added or if it fails to add the view.
         * @remark
         *  - For screen share, it adds a view to render the peer's shared screen.
         *  - For the camera, it adds a view to render the peer's screen captured by the camera.
         *  - This API is intended for calls and does not require peer information.
         */
        virtual bool AddPeerView(WindowHandle hWind) = 0;

        /**
         * Adds a Windows Handle to render a peer view.
         * @param hWind The Windows Handle to render a peer view.
         * @param pUserPtr Information on the Peer to be rendered.
         * @return
         *  - Returns true if the peer view is successfully added.
         *  - Returns false if the peer view is already added or if it fails to add the view.
         * @remark
         *  - For screen share, it adds a view to render the peer's shared screen.
         *  - For the camera, it adds a view to render the peer's screen captured by the camera.
         *  - This API is intended for conferences.
         */
        virtual bool AddPeerView(WindowHandle hWind, UserIdPtr pUserPtr) = 0;

        /**
         * Clears all of peer views that are currently stored.
         */
        virtual void ClearPeerView() = 0;

        /**
         * Removes a Windows Handle to render a peer view.
         * @param hWind The Windows Handle to render a peer view.
         * @return
         *  - If the peer view is successfully removed, it returns true.
         *  - Returns false if the peer view does not exist or if it fails to remove the view.
         * @remark
         *  - For screen share, it removes a view to render the peer's shared screen.
         *  - For the camera, it removes a view to render the peer's screen captured by the camera.
         */
        virtual bool RemovePeerView(WindowHandle hWind) = 0;

        /**
         * Sets the video mirror attribute to the video capturer.
         * @param bMirror
         * @return
         *  - If it successfully set the mirror mode, it returns true.
         */
        virtual bool SetMirrorMode(bool bMirror) = 0;

        /**
         * Gets the video mirror attribute of the video capturer.
         * @return
         *  - Returns true if mirrored
         */
        virtual bool IsVideoMirrored() = 0;

        /**
         * Gets the current media type.
         * @return
         *  - If successful, it returns the media type.
         */
        virtual ECapturerMediaType GetCapturerMediaType() = 0;

        /**
         * Gets the current capturer type.
         * @return
         *  - If successful, it returns the capturer type.
         *  - Unlike GetCapturerMediaType, GetCapturerType obtains the current capture target.
         */
        virtual EVideoCapturerType GetCapturerType() = 0;

        /**
         * Gets the rotation state.
         * @return
         *  - Rotation state
         * @see EVideoRotation
         */
        virtual EVideoRotation GetRotation() = 0;

        /**
         * Sets the rotation state.
         * @param eRotation  Rotation state
         * @see EVideoRotation
         */
        virtual void SetRotation(EVideoRotation eRotation) = 0;

        /**
         * Gets camera information.
         * @return
         *  - The current selected camera information.
         */
        virtual CameraInfoPtr GetVideoCapturerInfo() = 0;

        /**
         * Registers the video interceptor.
         * @param pInterceptor The video interceptor to register.
         * @return
         *  - Returns true if successful.
         * @remark
         *  - This intercepts the frame captured through the camera before delivering it to the counterpart.
         *  - If necessary, you can change the frame to be delivered to the counterpart.
         */
        virtual bool RegisterVideoInterceptor(IVideoInterceptor* pInterceptor) = 0;

        /**
         * Deregisters the video interceptor.
         * @return
         *  - Returns true if successful.
         */
        virtual bool DeregisterVideoInterceptor() = 0;

        /**
         * Pauses the video capturer. Currently supports EVideoCapturerType::PLNK_VID_CAPTURER_CAMERA
         * @return true on success
         */
        virtual bool Pause() = 0;
        
        /**
         * Resumes the video capturer. Currently supports EVideoCapturerType::PLNK_VID_CAPTURER_CAMERA
         * @return true on success
         */
        virtual bool Resume() = 0;

        /**
         * Registers a receiver to receive the screen sent to the counterpart.
         * @param pReceiver
         * @return true on success
         */
        virtual bool RegisterMyVideoReceiver(IVideoReceiver *pReceiver) = 0;   
        
        /**
          * Registers a receiver to receive the screen coming from the counterpart.
          * @param pReceiver
          * @return true on success
          */
        virtual bool RegisterPeersVideoReceiver(IVideoReceiver *pReceiver) = 0;        
        
        /**
         * Deregisters a receiver to receive the screen sent to the counterpart.
         * @param pReceiver
         * @return true on success
         */
        virtual bool DeregisterMyVideoReceiver(IVideoReceiver *pReceiver) = 0;

        /**
         * Deregisters a receiver to receive the screen coming from the counterpart.
         * @param pReceiver
         * @return true on success
         */
        virtual bool DeregisterPeersVideoReceiver(IVideoReceiver *pReceiver) = 0;        
        
        /**
         * Initializes rendering resources. If it fails, rendering is not supported.
         * @return true if PlanetKitVideoRender is supported.
         */
        virtual bool InitializeRender() = 0;

        /**
         * Frees rendering resources. FinalizeRender must be called when all render objects are released.
         * @return true on success
         * @remark
         *  - To clear all render objects, call ClearPeerView and ClearMyView.
         */
        virtual bool FinalizeRender() = 0;

        /**
         * Obtains the renderer currently rendering the Window.
         * @param hWnd The window for which you want to obtain the currently rendering renderer.
         * @return 
         *  - The renderer that is currently rendering.
         * @remark
         *  - You can change options of the window currently being rendered by calling this API.
         */
        virtual VideoRenderPtr GetRender(WindowHandle hWnd) = 0;
       
        /**
         * Sends frame data to the counterpart.
         * @param sVideoFrame The frame to send to the counterpart.
         * @return
         *  - Returns true if successful.
         */
        virtual bool WriteFrameData(SVideoFrame& sVideoFrame) = 0;

        /**
         * Checks whether it is currently possible to deliver frames to the counterpart.
         * @param ull64tick The tick count of the current frame.
         * @return
         *  - Returns true if it is possible to send frames to the counterpart.
         * @remark
         *  - In case there is a current FPS limit, you need to check the speed of the current frame through the tick count value .
         *  - You verify whether the current frame can be delivered at an appropriate FPS by checking the speed of this frame.
         */
        virtual bool IsPostingFrameAvailable(UINT64 ull64tick) = 0;
    };
}