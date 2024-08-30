#pragma once
namespace utils {
    class ILogHandler {
        public:
            virtual void onDebug(const char* msg);
            virtual void onInfo(const char* msg);
            virtual void onWarn(const char* msg);
            virtual void onError(const char* msg);
    };
};