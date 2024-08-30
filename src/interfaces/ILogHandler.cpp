#include <utils/interfaces/ILogHandler.h>

namespace utils {
    void ILogHandler::onDebug(const char* msg) { }
    void ILogHandler::onInfo(const char* msg) { }
    void ILogHandler::onWarn(const char* msg) { }
    void ILogHandler::onError(const char* msg) { }
};