#include <utils/String.h>
#include <utils/Exception.h>
#include <type_traits>

#include <string.h>
#include <stdarg.h>

namespace utils {
    String::String() : m_isReadOnly(false), m_str(nullptr), m_len(0), m_capacity(0) {
    }

    String::String(const char* cstr) {
        m_isReadOnly = false;

        if (!cstr || cstr[0] == 0) {
            m_len = 0;
            m_capacity = 0;
            m_str = nullptr;
            return;
        }
        
        m_len = (u32)strlen(cstr);
        m_capacity = m_len;
        m_str = new char[m_len + 1];
        
        for (u32 i = 0;i < m_len;i++) m_str[i] = cstr[i];
        m_str[m_len] = 0;
    }

    String::String(const std::string& str) {
        m_isReadOnly = false;
        m_len = (u32)str.length();
        m_capacity = m_len;
        m_str = new char[m_len + 1];

        const char* cstr = str.c_str();
        for (u32 i = 0;i < m_len;i++) m_str[i] = cstr[i];
        m_str[m_len] = 0;
    }

    String::String(const String& str) {
        m_isReadOnly = str.m_isReadOnly;
        m_len = str.m_len;
        m_capacity = m_len;

        if (m_isReadOnly) {
            m_str = str.m_str;
            return;
        }

        m_str = new char[m_len + 1];

        for (u32 i = 0;i < m_len;i++) m_str[i] = str.m_str[i];
        m_str[m_len] = 0;
    }

    String::~String() {
        if (!m_isReadOnly && m_str) delete [] m_str;
        m_str = nullptr;
        m_len = m_capacity = 0;
    }

    u32 String::size() const {
        return m_len;
    }

    const char* String::c_str() const {
        return m_str;
    }

    size_t String::hash() const {
        return std::_Hash_array_representation(m_str, m_len);
    }

    String& String::operator =(const String& rhs) {
        if (m_isReadOnly) throw Exception("Attempted to write to read-only string");

        copy(rhs.m_str, rhs.m_len);
        return *this;
    }

    String& String::operator =(const char* rhs) {
        if (m_isReadOnly) throw Exception("Attempted to write to read-only string");
        
        copy(rhs, (u32)strlen(rhs));
        return *this;
    }

    String& String::operator =(const std::string& rhs) {
        if (m_isReadOnly) throw Exception("Attempted to write to read-only string");
        
        copy(rhs.c_str(), (u32)rhs.length());
        return *this;
    }

    String& String::operator +=(char rhs) {
        if (m_isReadOnly) throw Exception("Attempted to write to read-only string");
        
        append(&rhs, 1);
        return *this;
    }

    String& String::operator +=(const String& rhs) {
        if (m_isReadOnly) throw Exception("Attempted to write to read-only string");
        
        append(rhs.m_str, rhs.m_len);
        return *this;
    }

    String& String::operator +=(const char* rhs) {
        if (m_isReadOnly) throw Exception("Attempted to write to read-only string");
        
        append(rhs, (u32)strlen(rhs));
        return *this;
    }

    String& String::operator +=(const std::string& rhs) {
        if (m_isReadOnly) throw Exception("Attempted to write to read-only string");
        
        append(rhs.c_str(), (u32)rhs.length());
        return *this;
    }

    String String::operator +(const char rhs) const {
        String ret;
        ret.m_len = m_len + 1;
        ret.m_capacity = ret.m_len;
        ret.m_str = new char[ret.m_len + 1];

        for (u32 i = 0;i < m_len;i++) ret.m_str[i] = m_str[i];
        ret.m_str[m_len] = rhs;
        ret.m_str[m_len + 1] = 0;

        return ret;
    }

    String String::operator +(const String& rhs) const {
        String ret;
        ret.m_len = m_len + rhs.m_len;
        ret.m_capacity = ret.m_len;
        ret.m_str = new char[ret.m_len + 1];

        for (u32 i = 0;i < m_len;i++) ret.m_str[i] = m_str[i];
        for (u32 i = 0;i < rhs.m_len;i++) ret.m_str[m_len + i] = rhs.m_str[i];
        ret.m_str[ret.m_len] = 0;

        return ret;
    }

    String String::operator +(const char* rhs) const {
        u32 len = (u32)strlen(rhs);

        String ret;
        ret.m_len = m_len + len;
        ret.m_capacity = ret.m_len;
        ret.m_str = new char[ret.m_len + 1];

        for (u32 i = 0;i < m_len;i++) ret.m_str[i] = m_str[i];
        for (u32 i = 0;i < len;i++) ret.m_str[m_len + i] = rhs[i];
        ret.m_str[ret.m_len] = 0;
        
        return ret;
    }

    String String::operator +(const std::string& rhs) const {
        u32 len = (u32)rhs.length();
        const char* cstr = rhs.c_str();

        String ret;
        ret.m_len = m_len + len;
        ret.m_capacity = ret.m_len;
        ret.m_str = new char[ret.m_len + 1];

        for (u32 i = 0;i < m_len;i++) ret.m_str[i] = m_str[i];
        for (u32 i = 0;i < len;i++) ret.m_str[m_len + i] = cstr[i];
        ret.m_str[ret.m_len] = 0;
        
        return ret;
    }
    
    bool String::operator ==(const String& rhs) const {
        if (m_len != rhs.m_len) return false;
        if (m_len == 0) return true;
        return strncmp(m_str, rhs.m_str, m_len) == 0;
    }

    bool String::operator ==(const char* rhs) const {
        if (!m_str != !rhs) return false;
        if (!m_str) return true;

        u32 len = u32(strlen(rhs));
        
        if (m_len != len) return false;
        if (m_len == 0) return true;
        return strncmp(m_str, rhs, m_len) == 0;
    }

    bool String::operator ==(const std::string& rhs) const {
        if (m_len != rhs.length()) return false;
        if (m_len == 0) return true;
        return strncmp(m_str, rhs.c_str(), m_len) == 0;
    }
    
    bool String::operator !=(const String& rhs) const {
        if (m_len != rhs.m_len) return true;
        if (m_len == 0) return false;
        return strncmp(m_str, rhs.m_str, m_len) != 0;
    }

    bool String::operator !=(const char* rhs) const {
        if (!m_str != !rhs) return true;
        if (!m_str) return false;

        u32 len = u32(strlen(rhs));
        
        if (m_len != len) return true;
        if (m_len == 0) return false;
        return strncmp(m_str, rhs, m_len) != 0;
    }

    bool String::operator !=(const std::string& rhs) const {
        if (m_len != rhs.length()) return true;
        if (m_len == 0) return false;
        return strncmp(m_str, rhs.c_str(), m_len) != 0;
    }

    char String::operator [](u32 index) const {
        return m_str[index];
    }

    char& String::operator [](u32 index) {
        return m_str[index];
    }

    String::operator std::string() const {
        return std::string(m_str, m_len);
    }
    
    void String::copy(const char* src, u32 len) {
        if (m_isReadOnly) throw Exception("Attempted to write to read-only string");
        
        if (len == 0) {
            if (m_capacity > 0) m_str[0] = 0;
            m_len = 0;
            return;
        }
        
        if (len > m_capacity) {
            if (m_str) delete [] m_str;
            m_capacity = len;
            m_str = new char[len + 1];
        }

        m_len = len;
        for (u32 i = 0;i < m_len;i++) m_str[i] = src[i];
        m_str[m_len] = 0;
    }

    String String::Format(const char* fmt, ...) {
        String ret;

        u32 fmtLen = (u32)strlen(fmt);
        ret.m_capacity = fmtLen + 256;
        ret.m_str = new char[ret.m_capacity + 1];

        va_list l;
        va_start(l, fmt);
        ret.m_len = (u32)vsnprintf(ret.m_str, fmtLen + 256, fmt, l);
        va_end(l);

        return ret;
    }

    String String::View(const char* str, u32 length) {
        String ret;

        ret.m_isReadOnly = true;
        ret.m_str = const_cast<char*>(str);
        ret.m_len = length;
        ret.m_capacity = 0;

        return ret;
    }
    
    void String::append(const char* src, u32 len) {
        if (m_isReadOnly) throw Exception("Attempted to write to read-only string");
        
        if (len + m_len >= m_capacity) extend(len + m_len + 64);

        for (u32 i = 0;i < len;i++) m_str[m_len + i] = src[i];

        m_len += len;
        m_str[m_len] = 0;
    }

    void String::extend(u32 newCapacity) {
        if (m_isReadOnly) throw Exception("Attempted to write to read-only string");
        
        char* newData = new char[newCapacity + 1];

        if (m_str) {
            for (u32 i = 0;i < m_len;i++) newData[i] = m_str[i];
            newData[m_len] = 0;
            delete [] m_str;
        } else {
            memset(newData, 0, newCapacity);
        }

        m_str = newData;
        m_capacity = newCapacity;
    }
};

std::size_t std::hash<utils::String>::operator()(const utils::String& k) const {
    return std::_Hash_array_representation(k.c_str(), k.size());
}