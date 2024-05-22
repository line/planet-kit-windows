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

#ifndef CONSTEXPR
    #if __cplusplus >= 201103L || (defined(_MSVC_LANG) && _MSVC_LANG >= 201103L)
        #define CONSTEXPR constexpr
    #else
        #define CONSTEXPR
    #endif
#endif

namespace PlanetKit
{
    struct Nullopt {
        struct _NullTag {};

#if __cplusplus >= 201103L || (defined(_MSC_VER) && _MSC_VER >= 1800)
        CONSTEXPR explicit Nullopt(_NullTag) {}
#else
        CONSTEXPR Nullopt(_NullTag) {}
#endif
    };

    /**
     * This value means nullptr in Optional class.
     */
    CONSTEXPR Nullopt NullOptional(Nullopt::_NullTag{});

    /**
     * PlanetKit Optional class.
     * @remark Use like std::optional in C++17
     */
    template <typename T>
    class Optional {
    public:
        Optional(const T& src) {
            m_value = src;
            m_bHasValue = true;
        };

        Optional(const Nullopt&) {
            m_bHasValue = false;
        };

        Optional() {
            m_bHasValue = false;
        };

#if __cplusplus >= 201103L || (defined(_MSC_VER) && _MSC_VER >= 1800)
        CONSTEXPR explicit operator bool() const {
#else
        CONSTEXPR operator bool() const {
#endif
            return m_bHasValue;
        };

        /**
         * Checks has value.
         * @return true as having value.
         */
        bool HasValue() const {
            return m_bHasValue;
        }

        /**
         * Gets optional value if it has value.
         * @remark
         *   You should call HasValue() or operator bool() before using this method.<br>
         *   This method returns NullOptional if HasValue() or operator bool() returns false.
         */
        const T* operator->() const {
            return &m_value;
        }

        /**
         * Gets optional value if it has value.
         * @remark
         *   You should call HasValue() or operator bool() before using this method.<br>
         *   This method returns NullOptional if HasValue() or operator bool() returns false.
         */
        T* operator->() {
            return &m_value;
        }

        /**
         * Gets optional value if it has value.
         * @remark
         *   You should call HasValue() or operator bool() before using this method.<br>
         *   This method returns NullOptional if HasValue() or operator bool() returns false.
         */
        const T& operator*() const {
            return m_value;
        }

        /**
         * Gets optional value if it has value.
         * @remark
         *   You should call HasValue() or operator bool() before using this method.<br>
         *   This method returns NullOptional if HasValue() or operator bool() returns false.
         */
        T& operator*() {
            return m_value;
        }

        /**
         * Copy optional value if it has value.
         */
        Optional<T>& operator=(const Optional<T>& src) {
            m_bHasValue = src.m_bHasValue;
            if (m_bHasValue) {
                m_value = src.m_value;
            }
            return *this;
        }

        /**
         * Sets optional value.
         */
        Optional<T>& operator=(const T& src) {
            m_bHasValue = true;
            m_value = src;

            return *this;
        }

        /**
         * Gets optional value if it has value.
         * @remark
         *   You should call HasValue() or operator bool() before using this method.<br>
         *   This method returns NullOptional if HasValue() or operator bool() returns false.
         */
        T& Value() {
            return m_value;
        }

        /**
         * Gets optional value if it has value.
         * @remark
         *   You should call HasValue() or operator bool() before using this method.<br>
         *   This method returns NullOptional if HasValue() or operator bool() returns false.
         */
        const T& Value() const {
            return m_value;
        }

    private:
#if __cplusplus >= 201103L || (defined(_MSC_VER) && _MSC_VER >= 1800)
        bool m_bHasValue = false;
#else
        bool m_bHasValue;
#endif

        T m_value;

    };
};

