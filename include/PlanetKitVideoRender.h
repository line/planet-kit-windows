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

#include <Windows.h>

#include "PlanetKit.h"
#include "PlanetKitVideoCommon.h"

namespace PlanetKit 
{
    class IVideoRenderEvent;

    class PLANETKIT_API VideoRender : public Base {
    public:

        /**
        * Pushes a video frame to render.
        * @param pVideoFrame Video frame to be rendered.
        * @return true on success.
        */
        virtual bool RenderVideoFrame(const SVideoFrame *pVideoFrame) = 0;


        /**
        * Registers a video render event delegate to the render instance.
        * @param pDelegate 
        * @return true on successful registration.
        */
        virtual bool RegisterRenderEvent(IVideoRenderEvent *pDelegate) = 0;


        /**
        * Deregisters the video render event delegate from the render instance.
        * @return true on successful deregistration.
        */
        virtual bool DeregisterRenderEvent() = 0;


        /**
        * Resets the video render start event. 
        * After ResetRenderStartEvent() has been called, IVideoRenderEvent::OnRenderStart will be called on the next video frame received.
        * @return true on successful deregistration.
        */
        virtual void ResetRenderStartEvent() = 0;


        /**
        * Sets the video aspect ratio mode. 
        * @param eMode Video aspect ratio mode. 
        * @return true on success.
        */
        virtual bool SetVideoAspectRatioMode(EVideoAspectRatioMode eMode) = 0;
        

        /**
        * Gets the render's video aspect ratio mode.
        * @return Current render's EVideoAspectRatioMode.
        */
        virtual EVideoAspectRatioMode GetVideoAspectRatioMode() = 0;


        /**
         * Sets the mirroring type of the view.
         * @param eMirrorType Mirroring type.
         * @remark
         *  - The default value is `PLNK_MIRROR_TYPE_AUTO`.
         */
        virtual void SetMirrorType(EVideoMirrorType eMirrorType) = 0;

        /**
         * Gets the mirroring type of the view.
         */
        virtual EVideoMirrorType GetMirrorType() = 0;

        /**
         * Sets the rotation state of the view.
         * @param eRotation Rotation state.
         * @remark
         *  - The default value is `PLNK_VIDEO_ROTATION_0`.
         */
        virtual void SetRotation(EVideoRotation eRotation) = 0;

        /**
         * Gets the rotation state of the view.
         */
        virtual EVideoRotation GetRotation() = 0;

        /**
         * Sets the background color of the video.
         */
        virtual void SetBackgroundColor(COLORREF rgbClr) = 0;

    protected:
        virtual ~VideoRender() {}
    };

    template class PLANETKIT_API AutoPtr<VideoRender>;
    typedef AutoPtr<VideoRender> VideoRenderPtr;

    template class PLANETKIT_API Optional<VideoRenderPtr>;
    typedef Optional<VideoRenderPtr> VideoRenderOptional;

    class PLANETKIT_API IVideoRenderEvent {
    public:
        /// Called when the rendering starts.
        virtual void OnRenderStart(HWND hWnd) = 0;

        /**
         * Called when the rendering fails.
         * @remark
         *  - Raised when the rendering fails.
         */
        virtual void OnRenderFailure(HWND hWnd) = 0;
    };
}