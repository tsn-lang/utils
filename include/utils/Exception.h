#pragma once
#include <utils/String.h>

namespace utils {
    class Exception {
        public:
            Exception(const String& msg);
            Exception(const char* msgFmt, ...);
        
            const String& message() const;
            
        protected:
            String m_msg;
    };
};