#pragma once
#include <utils/String.h>
#include <exception>

namespace utils {
    class Exception : public std::exception {
        public:
            Exception(const String& msg);
            Exception(const char* msgFmt, ...);
        
            const String& message() const;
            virtual char const* what() const;
            
        protected:
            String m_msg;
    };
};