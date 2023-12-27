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

#include <string.h>

namespace PlanetKit
{
    /**
     * Array class.
     */
    template <class T>
    class Array {
    public:
#if __cplusplus >= 201103L || (defined(_MSC_VER) && _MSC_VER >= 1800)
        Array() = default;
#else
        Array() :
            m_pData(nullptr),
            m_nSize(0)
        {
        }
#endif

#if __cplusplus >= 201103L || (defined(_MSC_VER) && _MSC_VER >= 1800)
        /**
         * Do not support copy constructor.
         */
        Array(const Array<T>& src) = delete;
#else
        Array(const Array<T>& src) {
            // do nothing but error
            ASSERT(FALSE);
        }
#endif
        virtual ~Array() {
            Clear();
        }

        /**
         * Clears all elements in the array.
         */
        void Clear() {
            if (m_pData) {
                delete[] m_pData;
                m_pData = nullptr;
            }

            m_nSize = 0;
        }

        /**
         * Sets the number of array elements and allocates memory.
         * @param size Size of the array
         * @remark This API internally calls Clear() before resizing.
         */
        void Resize(size_t size) {
            Clear();

            if (size > 0) {
                m_pData = new T[size];
                m_nSize = size;
            }
        }

        /**
         * Sets the element value at idx.
         * @param idx Element index
         * @param rhs Element value to be set.
         */
        void SetAt(int idx, const T& rhs) {
            m_pData[idx] = rhs;
        }

        /**
         * Gets the number of array elements.
         */
        size_t Size() const {
            return m_nSize;
        }

        /**
         * Gets the element at idx.
         * @param idx Index of the array
         * @return Element item
         */
        T& At(int idx) const {
            return m_pData[idx];
        }

        /**
         * Gets the element at idx.
         * @param idx Index of the array
         * @return Element item
         */
        T& operator[](int idx) const {
            return m_pData[idx];
        }

        Array<T>& operator=(const Array<T>& src) = delete;

    private:

#if __cplusplus >= 201103L || (defined(_MSC_VER) && _MSC_VER >= 1800)
        T* m_pData = nullptr;
#else
        T* m_pData;
#endif

#if __cplusplus >= 201103L || (defined(_MSC_VER) && _MSC_VER >= 1800)
        size_t m_nSize = 0;
#else
        size_t m_nSize;
#endif
    };
};