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
#include "PlanetKitVideoDefine.h"

namespace PlanetKit {
    /// Video frame class
    class PLANETKIT_API VideoFrame {
    public:
        virtual ~VideoFrame() { }

        /// Gets the frame buffer. (I420 buffer)
        virtual const unsigned char* GetBuffer() = 0;
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

    typedef SharedPtr<VideoFrame> VideoFramePtr;
};