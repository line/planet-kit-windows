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

#include "PlanetKitPredefine.h"
#include "PlanetKitMemory.h"

namespace PlanetKit {
    template <typename T>
    class PLANETKIT_API ControlBlock {
    public:
        explicit ControlBlock(T* ptr) : ptr_(ptr), ref_count_(1) {}

        virtual ~ControlBlock() {}

        void addRef() {
            InterlockedIncrement(&ref_count_);
        }

        void release() {
            if (InterlockedDecrement(&ref_count_) == 0) {
                ptr_->~T();
                PlanetKitMemory::FreeMemory(ptr_);
                ptr_ = nullptr;

                this->~ControlBlock();
                PlanetKitMemory::FreeMemory(this);
            }
        }

        T* getPtr() const {
            return ptr_;
        }

    private:
        T* ptr_;
        LONG ref_count_;
    };
};