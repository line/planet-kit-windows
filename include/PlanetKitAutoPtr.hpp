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

namespace PlanetKit
{
    /**
     * PlanetKit reference automation pointer class.
     */
    template <class T>
    class AutoPtr {
    public:

#if __cplusplus >= 201103L || (defined(_MSC_VER) && _MSC_VER >= 1800)
        explicit AutoPtr() = default;
#else
        AutoPtr() :
            m_pData(NULL)
        {
        }
#endif

#if __cplusplus >= 201103L || (defined(_MSC_VER) && _MSC_VER >= 1800)
        explicit AutoPtr(T* pSrc) {
#else
        AutoPtr(T* pSrc) {
#endif
            m_pData = pSrc;
            if (m_pData) {
                m_pData->AddRef();
            }
        }

        AutoPtr(const AutoPtr<T>& src) {
            this->m_pData = src.m_pData;

            if (this->m_pData) {
                this->m_pData->AddRef();
            }
        }

        virtual ~AutoPtr() {
            Release();
        }

        /**
         * Checks for equality between this and rhs.
         */
        bool operator==(const AutoPtr<T>& rhs) {
            return (this->m_pData == rhs.m_pData);
        }

        /**
         * Checks for inequality between this and rhs.
         */
        bool operator!=(const AutoPtr<T>& rhs) {
            return (this->m_pData != rhs.m_pData);
        }

        /**
         * Sets a value.
         */
        AutoPtr<T>& operator=(const AutoPtr<T>& src) {
            if (this == &src) {
                return *this;
            }
            else {
                Release();

                this->m_pData = src.m_pData;
                if (this->m_pData) {
                    this->m_pData->AddRef();
                }
            }

            return *this;
        }

        /**
         * Sets a value.
         */
        AutoPtr<T>& operator=(T* src) {
            if (this->m_pData == src) {
                // do nothing
            }
            else {
                Release();

                this->m_pData = src;
                if (this->m_pData) {
                    this->m_pData->AddRef();
                }
            }

            return *this;
        }

        /**
         * Gets a value.
         */
        T* operator*() {
            return m_pData;
        }

        /**
         * Gets a value.
         */
        T* operator->() {
            return m_pData;
        }

    private:
        void Release() {
            if (m_pData) {
                m_pData->Release();
            }
        }

    private:
#if __cplusplus >= 201103L || (defined(_MSC_VER) && _MSC_VER >= 1800)
        T* m_pData = nullptr;
#else
        T* m_pData;
#endif
    };
};
