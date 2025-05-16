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

#include "PlanetKitControlBlock.hpp"
#include <windows.h>

namespace PlanetKit {
    template <typename T>
    class PLANETKIT_API SharedPtr {
    public:
        SharedPtr() : control_block_(nullptr) {}
        SharedPtr(std::nullptr_t) : control_block_(nullptr) {}

        explicit SharedPtr(T* ptr) : control_block_(new ControlBlock<T>(ptr)) {}

        SharedPtr(const SharedPtr& other) {
            copy(other);
        }

        template <typename U>
        SharedPtr(const SharedPtr<U>& other) : control_block_(reinterpret_cast<ControlBlock<T>*>(other.control_block_)) {
            if (control_block_) {
                control_block_->addRef();
            }
        }

        SharedPtr& operator=(const SharedPtr& other) {
            if (this != &other) {
                release();
                copy(other);
            }
            return *this;
        }

        SharedPtr& operator=(std::nullptr_t) {
            release();
            control_block_ = nullptr;
            return *this;
        }

        ~SharedPtr() {
            release();
        }

        bool hasValue() const {
            return get() ? true : false;
        }

        T& operator*() const {
            return *get();
        }

        T* operator->() const {
            return get();
        }

        bool operator==(const SharedPtr& other) const {
            return get() == other.get();
        }

        bool operator!=(const SharedPtr& other) const {
            return !(*this == other);
        }

        bool operator==(std::nullptr_t) const {
            return get() == nullptr;
        }

        bool operator!=(std::nullptr_t) const {
            return get() != nullptr;
        }

        bool operator<(const SharedPtr& other) const {
            return control_block_ < other.control_block_;
        }

        template <typename U>
        SharedPtr<U> as() const {
            U* castedPtr = dynamic_cast<U*>(get());
            if (castedPtr) {
                return SharedPtr<U>(*this);
            }
            return SharedPtr<U>();
        }

    private:
        ControlBlock<T>* control_block_;

        void release() {
            if (control_block_) {
                control_block_->release();
            }
        }

        void copy(const SharedPtr& other) {
            control_block_ = other.control_block_;
            if (control_block_) {
                control_block_->addRef();
            }
        }

        T* get() const {
            return control_block_ ? control_block_->getPtr() : nullptr;
        }

        template <typename U>
        friend class SharedPtr;
    };

    template <typename T, typename... Args>
    SharedPtr<T> MakeAutoPtr(Args&&... args) {
        return SharedPtr<T>(new T(args...));
    }
};
