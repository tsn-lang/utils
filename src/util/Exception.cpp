#include <utils/Exception.h>

namespace utils {
    Exception::Exception(const String& msg) : m_msg(msg) {}

    const String& Exception::message() const {
        return m_msg;
    }
};