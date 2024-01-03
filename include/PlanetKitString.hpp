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

namespace PlanetKit {
    class String {
    public:
        /**
         * Normal creator
         */
        String() = default;

        /**
         * Create with string
         */
        String(const char* src) {
            Copy(src);
        }

        /**
         * Create with string
         */
        String(String& src) {
            Copy(src.c_str());
        }

        /**
         * Create with string
         */
        String(const String& src) {
            Copy(src.c_str());
        }

        /**
         * Normal destructor
         */
        virtual ~String() {
            Clear();
        }

        /**
         * const char* operator
         */
        operator const char*() const {
            return m_pData;
        }

        /**
         * Get string value
         */
        const char* c_str() const {
            return m_pData;
        }

        /**
         * Get string size
         */
        size_t Size() const {
            return m_nSize;
        }

        /**
         * Append string
         */
        String& Append(const char* rhs) {
            AppendData(rhs);

            return *this;
        }

        /**
         * Compare between string
         */
        bool operator==(const char* rhs) const {
            if (m_pData == nullptr && rhs == nullptr) {
                return true;
            }
            if (rhs) {
                size_t nLen = strlen(rhs);

                if (m_nSize != nLen) {
                    return false;
                }
                else if (m_nSize == 0 && nLen == 0) {
                    return true;
                }

                if (strcmp(m_pData, rhs) == 0) {
                    return true;
                }
            }

            return false;
        }

        /**
         * Set string
         */
        String& operator=(const char* src) {
            Copy(src);

            return *this;
        }

        /**
         * Set string
         */
        String& operator=(const String& src) {
            Copy(src);

            return *this;
        }

        /**
         * Append string
         */
        String& operator+=(const char* rhs) {
            AppendData(rhs);

            return *this;
        }

        /**
         * Copy string
         */
        void Copy(const char* src) {
            Clear();

            if (src) {
                m_nSize = strlen(src);

                if (m_nSize > 0) {
                    m_pData = new char[m_nSize + 1];
                    strcpy_s(m_pData, m_nSize + 1, src);
                }
            }
        }

        /**
         * Clear string
         */
        void Clear() {
            if (m_pData && m_nSize) {
                delete[] m_pData;
                m_pData = nullptr;
                m_nSize = 0;
            }
        }

        /**
         * Append string
         */
        void AppendData(const char* rhs) {
            if (rhs != nullptr) {
                size_t nLen = strlen(rhs);

                char* pTemp = m_pData;

                m_nSize += nLen;
                m_pData = new char[m_nSize + 1];
                strcpy_s(m_pData, m_nSize + 1, pTemp);
                strcat_s(m_pData, m_nSize + 1, rhs);

                delete[] pTemp;
            }
        }

    private:
        char* m_pData = nullptr;
        size_t m_nSize = 0;
    };

    class WString {
    public:
        /**
         * Normal creator
         */
        WString() = default;

        /**
         * Create with string
         */
        WString(const wchar_t* src) {
            Copy(src);
        }

        /**
         * Create with string
         */
        WString(WString& src) {
            Copy(src.c_str());
        }

        /**
         * Create with string
         */
        WString(const WString& src) {
            Copy(src.c_str());
        }

        /**
         * Normal destructor
         */
        virtual ~WString() {
            Clear();
        }

        /**
         * const char* operator
         */
        operator const wchar_t*() const {
            return m_pData;
        }

        /**
         * Get string value
         */
        const wchar_t* c_str() const {
            return m_pData;
        }

        /**
         * Get string size
         */
        size_t Size() const {
            return m_nSize;
        }

        /**
         * Append string
         */
        WString& Append(const wchar_t* rhs) {
            AppendData(rhs);

            return *this;
        }

        /**
         * Compare between string
         */
        bool operator==(const wchar_t* rhs) const {
            if (m_pData == nullptr && rhs == nullptr) {
                return true;
            }

            if (rhs) {
                size_t nLen = wcslen(rhs);

                if (m_nSize != nLen) {
                    return false;
                }

                if (wcscmp(m_pData, rhs) == 0) {
                    return true;
                }
            }

            return false;
        }

        /**
         * Set string
         */
        WString& operator=(const wchar_t* src) {
            Copy(src);

            return *this;
        }

        /**
         * Set string
         */
        WString& operator=(const WString& src) {
            Copy(src);

            return *this;
        }

        /**
         * Append string
         */
        WString& operator+=(const wchar_t* rhs) {
            AppendData(rhs);

            return *this;
        }

        /**
         * Copy string
         */
        void Copy(const wchar_t* src) {
            Clear();

            if (src) {
                m_nSize = wcslen(src);

                if (m_nSize > 0) {
                    m_pData = new wchar_t[m_nSize + 1];
                    wcscpy_s(m_pData, m_nSize + 1, src);
                }
            }
        }

        /**
         * Clear string
         */
        void Clear() {
            if (m_pData && m_nSize) {
                delete[] m_pData;
                m_pData = nullptr;
                m_nSize = 0;
            }
        }

        /**
         * Append string
         */
        void AppendData(const wchar_t* rhs) {
            if (rhs != nullptr) {
                size_t nLen = wcslen(rhs);

                wchar_t* pTemp = m_pData;

                m_nSize += nLen;
                m_pData = new wchar_t[m_nSize + 1];
                wcscpy_s(m_pData, m_nSize + 1, pTemp);
                wcscat_s(m_pData, m_nSize + 1, rhs);

                delete[] pTemp;
            }
        }

    private:
        wchar_t* m_pData = nullptr;
        size_t m_nSize = 0;
    };
};