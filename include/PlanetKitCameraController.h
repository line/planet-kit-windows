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

#include "PlanetKitCameraInfo.h"
#include "PlanetKitVideoRender.h"

namespace PlanetKit
{
    /// The class for capturing with a camera.
    class PLANETKIT_API CameraController : virtual public Base {
    public:

        /**
         * Get a list of camera devices.
         * @param arrCameraInfo The list of available camera devices.
         */
        virtual void GetCapturerInfo(CameraInfoArray& arrCameraInfo) = 0;

        /**
         * Changes the camera that will capture the current screen.
         * @param pCameraInfo The device to capture the screen.
         * @return
         *  - The result of the process of setting up the camera device.
         * @remark
         *  - If you want to use a specific device when starting capture, you can set it first with this function and then start.
         */
        virtual EVideoControlResult SelectCamera(CameraInfoPtr pCameraInfo) = 0;

        /**
         * Get selected camera information.
         * @return
         *  - The result of selected camera information class.
         * @remark
         *  - This API may return NullOptional if no camera is selected.
         */
        virtual CameraInfoOptional GetSelectedCamera() = 0;

        /**        
         * Registers a delegate to handle device change events.
         * @param pDelegate The delegate to handle device change events.
         */
        virtual void RegisterDeviceEvent(IVideoCaptureDeviceEvent* pDelegate) = 0;

        /**
         * Deregisters a delegate to handle device change events.
         * @param pDelegate The delegate that you want to deregister.
         */
        virtual void DeregisterDeviceEvent(IVideoCaptureDeviceEvent* pDelegate) = 0;

        /**
         * Checks camera is running.
         * @return true on camera is running.
         */
        virtual bool IsRunning() = 0;

        /**
         * Starts a window handle to render a local user's preview.
         * @param hWind The window handle to render a local user's preview.
         * @return
         *  - Returns true if the local user's preview is successfully added.<br>
         *  - Returns false if the local user's preview already exists in the list of handles.<br>
         *  - Returns false if the parameter is NULL or INVALID_HANDLE_VALUE.
         * @remark
         *  - In PlanetKit 5.4 or lower, you could use StartCapture() to turn on the camera. However, StartCapture() has been removed since PlanetKit 5.5.<br>
         *  - Added in PlanetKit 5.5, StartPreview() provides a different functionality than StartCapture(). StartPreview() can be used independently of call connection status, making it possible to preview the local user's video before a call, or before switching from an audio call to a video call.<br>
         *  - From PlanetKit 5.5, if video is enabled for a call or conference, the camera will automatically turn on when the call is connected.
         */
        virtual bool StartPreview(WindowHandle hWind) = 0;

        /**
         * Starts a receiver to receive a local user's preview frame.
         * @param pReceiver The receiver to receive a local user's preview frame.
         * @return
         *  - Returns true if the local user's preview is successfully added.<br>
         *  - Returns false if the local user's preview already exists in the list of handles.<br>
         *  - Returns false if the parameter is nullptr.
         * @remark
         *  - In PlanetKit 5.4 or lower, you could use StartCapture() to turn on the camera. However, StartCapture() has been removed since PlanetKit 5.5.<br>
         *  - Added in PlanetKit 5.5, StartPreview() provides a different functionality than StartCapture(). StartPreview() can be used independently of call connection status, making it possible to preview the local user's video before a call, or before switching from an audio call to a video call.<br>
         *  - From PlanetKit 5.5, if video is enabled for a call or conference, the camera will automatically turn on when the call is connected.
         */
        virtual bool StartPreview(IVideoReceiver* pReceiver) = 0;

        /**
         * Stops the preview for the handle that was started.
         * @param hWind The window handle to render a local user's preview.
         * @return
         *  - If the preview is successfully removed, it returns true.
         */
        virtual bool StopPreview(WindowHandle hWind) = 0;

        /**
         * Stops the preview for the receiver that was started.
         * @param pReceiver The receiver to receive a local user's preview frame.
         * @return
         *  - If the preview frame receiver is successfully removed, it returns true.
         */
        virtual bool StopPreview(IVideoReceiver* pReceiver) = 0;

        /**
         * Gets the current media type.
         * @return
         *  - If successful, it returns the media type.
         */
        virtual ECapturerMediaType GetCapturerMediaType() = 0;

        /**
         * Gets camera information.
         * @return
         *  - The current selected camera information.
         */
        virtual CameraInfoPtr GetVideoCapturerInfo() = 0;

        /**
         * Gets the current capturer type.
         * @return
         *  - If successful, it returns the capturer type.
         *  - Unlike GetCapturerMediaType, GetCapturerType obtains the current capture target.
         */
        virtual EVideoCapturerType GetCapturerType() = 0;

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

    template class PLANETKIT_API AutoPtr<CameraController>;
    typedef AutoPtr<CameraController> CameraControllerPtr;
}