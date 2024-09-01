#include <utils/Exception.h>
#include <varargs.h>

namespace utils {
    Exception::Exception(const String& msg) : m_msg(msg) {}
    Exception::Exception(const char* msgFmt, ...) {
        char buf[1024] = { 0 };

        va_list l;
        va_start(l, msgFmt);
        vsnprintf(buf, 1024, msgFmt, l);
        va_end(l);

        m_msg = buf;
    }

    const String& Exception::message() const {
        return m_msg;
    }
};