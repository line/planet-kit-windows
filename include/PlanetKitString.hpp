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
#include <assert.h>

#include "PlanetKitPredefine.h"
#include "PlanetKitMemory.h"

#pragma warning(push)

// Disable warning: multiple copy constructors specified
#pragma warning(disable: 4521)


namespace PlanetKit {
    class PLANETKIT_API String {
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
                    m_pData = static_cast<char*>(PlanetKitMemory::AllocateArrayMemory(m_nSize + 1));
                    strcpy_s(m_pData, m_nSize + 1, src);
                }
            }
        }

        /**
         * Clear string
         */
        void Clear() {
            if (m_pData && m_nSize) {
                PlanetKitMemory::FreeArrayMemory(m_pData);
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
                m_pData = static_cast<char*>(PlanetKitMemory::AllocateArrayMemory(m_nSize + 1));
                strcpy_s(m_pData, m_nSize + 1, pTemp);
                strcat_s(m_pData, m_nSize + 1, rhs);

                PlanetKitMemory::FreeArrayMemory(pTemp);
            }
        }

    private:
        char* m_pData = nullptr;
        size_t m_nSize = 0;
    };

    class PLANETKIT_API WString {
    public:
        /**
         * Normal creator
         */
        WString() {
            Initialize();
        }

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
            if (m_nSize == 0 && rhs == nullptr) {
                return true;
            }

            if (rhs) {
                size_t nLen = wcslen(rhs);

                if (m_nSize != nLen) {
                    return false;
                }

                if (m_nSize == 0 && nLen == 0) {
                    return true;
                }
                else  if (wcscmp(m_pData, rhs) == 0) {
                    return true;
                }
            }

            return false;
        }

        bool operator==(const WString& rhs) const {
            if (m_nSize == 0 && rhs.Size() == 0) {
                return true;
            }

            if (this->Size() != rhs.Size()) {
                return false;
            }

            if (wcscmp(m_pData, rhs.c_str()) == 0) {
                return true;
            }

            return false;
        }

        bool operator!=(const WString& rhs) const {
            if (m_nSize == 0 && rhs.Size() == 0) {
                return false;
            }

            if (this->Size() != rhs.Size()) {
                return true;
            }

            if (wcscmp(m_pData, rhs.c_str()) == 0) {
                return false;
            }

            return true;
        }


        const wchar_t operator[] (int idx) {
            assert(!(idx > (int)m_nSize));
            assert(!(idx < 0));

            if (idx >= (int)m_nSize) {
                return L'\0';
            }
            else {
                return m_pData[idx];
            }
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
         * Append string
         */
        WString& operator+=(const WString& rhs) {
            AppendData(rhs.c_str());

            return *this;
        }

        /**
         * Substring
         */
        WString Substring(const unsigned int unStart, const unsigned unLength = 0) const{
            WString strTemp;
            wchar_t* pstrChar = m_pData + unStart;
            if (unLength == 0) {
                strTemp = pstrChar;
                return strTemp;
            }
            else {
                if (unStart + unLength > m_nSize) {
                    return strTemp;
                }
                else {
                    wchar_t charTemp = m_pData[unStart + unLength];
                    m_pData[unStart + unLength] = L'\0';

                    strTemp = pstrChar;
                    m_pData[unStart + unLength] = charTemp;

                    return strTemp;
                }
            }
        }

        private :
            WString(int) {} // Disable creation with NULL
            WString(void*) {} // Disable creation with std::nullptr

            WString& operator=(int) { return *this; }
            WString& operator=(void*) { return *this; }

            bool operator==(int) { return false; }
            bool operator==(void*) { return false; }

            bool operator!=(int) { return false; }
            bool operator!=(void*) { return false; }

            WString& operator+=(int) { return *this; }
            WString& operator+=(void*) { return *this; }

            WString& Append(int) { return *this; }
            WString& Append(void*) { return *this; }

            /**
             * Copy string
             */
            void Copy(const wchar_t* src) {
                if (*this == src) {
                    return;
                }

                Clear();

                assert(!(src == nullptr));

                if (src && wcslen(src) > 0) {
                    m_nSize = wcslen(src);

                    if (m_nSize > 0) {
                        m_pData = static_cast<wchar_t*>(PlanetKitMemory::AllocateArrayMemory((m_nSize + 1) * sizeof(wchar_t)));
                        wcscpy_s(m_pData, m_nSize + 1, src);
                    }
                    else {
                        Initialize();
                    }
                }
                else {
                    Initialize();
                }
            }

            /**
             * Append string
             */
            void AppendData(const wchar_t* rhs) {
                assert(!(rhs == nullptr));

                if (rhs != nullptr) {
                    size_t nLen = wcslen(rhs);

                    if (nLen > 0) {
                        if (m_nSize > 0) {
                            wchar_t* pTemp = m_pData;

                            m_nSize += nLen;
                            m_pData = static_cast<wchar_t*>(PlanetKitMemory::AllocateArrayMemory((m_nSize + 1) * sizeof(wchar_t)));
                            wcscpy_s(m_pData, m_nSize + 1, pTemp);
                            wcscat_s(m_pData, m_nSize + 1, rhs);

                            PlanetKitMemory::FreeArrayMemory(pTemp);
                        }
                        else {
                            Copy(rhs);
                        }
                    }
                }
            }

            void Clear() {
                if (m_pData) {
                    PlanetKitMemory::FreeArrayMemory(m_pData);
                    m_pData = nullptr;
                    m_nSize = 0;
                }
            }

            void Initialize() {
                m_pData = static_cast<wchar_t*>(PlanetKitMemory::AllocateArrayMemory(1 * sizeof(wchar_t)));
                m_pData[0] = L'\0';
                m_nSize = 0;
            }

    private:
        wchar_t* m_pData = nullptr;
        size_t m_nSize = 0;
    };
};


#pragma warning(pop)
