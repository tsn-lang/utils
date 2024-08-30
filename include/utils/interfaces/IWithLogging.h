#pragma once
namespace utils {
    class ILogHandler;

    class IWithLogging {
        public:
            IWithLogging();

            void setLogHandler(ILogHandler* handler);
            ILogHandler* getLogHandler() const;

            void logDebug(const char* msg, ...);
            void logInfo(const char* msg, ...);
            void logWarn(const char* msg, ...);
            void logError(const char* msg, ...);

            bool didError() const;
        
        private:
            ILogHandler* m_logger;
            bool m_hasErrors;
    };
};