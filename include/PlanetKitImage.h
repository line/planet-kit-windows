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
#include <wincodec.h>

namespace PlanetKit {
    class PLANETKIT_API Image;
    using ImagePtr = SharedPtr<Image>;
    using ImageOptional = Optional<ImagePtr>;
    
    class PLANETKIT_API Image {
    public:
        virtual ~Image() {}

        /**
         * Creates an instance of PlanetKit::Image from the file path.
         * @param strPath File path to an image.
         * @return
         *  - An ImagePtr is returned upon successful creation.
         * @remark
         *  - The API supports the file formats that are supported by IWICBitmapDecoder.<br>
         *  - If creating an IWICBitmapDecoder fails, the API will fail.
         * @see
         *  - For more information, see https://learn.microsoft.com/en-us/windows/win32/api/wincodec/nn-wincodec-iwicbitmapdecoder
         */
        static ImageOptional Create(const WString& strPath);

        /**
         * Creates an instance of PlanetKit::Image from the buffer.
         * @param pBuffer Buffer.
         * @param unWidth Frame width.
         * @param unHeight Frame height.
         * @param supportedFormat Select the format of the buffer from the available formats.
         * @return
         *  - An ImagePtr is returned upon successful creation.
         */
        static ImageOptional Create(BYTE* pBuffer, unsigned int unWidth, unsigned int unHeight, ESupportedVirtualBackgroundFormat supportedFormat);

        /**
         * Gets the frame width.
         * @return
         *  - Width
         */
        virtual unsigned int Width() = 0;

        /**
         * Gets the frame height.
         * @return
         *  - Height
         */
        virtual unsigned int Height() = 0;
    };
}