#include <iostream>

enum class LogLevel {
    INFO,
    DEBUG,
    ERROR,
    WARN
};

class LogProcessHelper {
public:
    static std::string enumToString(LogLevel level) {
        switch (level) {
            case LogLevel::INFO:  return "[INFO]";
            case LogLevel::WARN:  return "[WARN]";
            case LogLevel::DEBUG: return "[DEBUG]";
            case LogLevel::ERROR: return "[ERROR]";
            default:              return "[UNDEFINED]";
        }
    }
};

class LogProcessor {
public:
    LogProcessor* nextLogProcessor = nullptr;

    virtual ~LogProcessor() = default;

    LogProcessor() = default;
    LogProcessor(LogProcessor* nextLogProcessor) {
        this->nextLogProcessor = nextLogProcessor;
    }

    virtual void processLog(LogLevel level, std::string message) = 0;
};

class InfoLogProcessor : public LogProcessor {
public:
    using LogProcessor::LogProcessor; // It inherits the constructors of the base class into derived class
    void processLog(LogLevel level, std::string message) override {
        if (level == LogLevel::INFO) {
            std::cout << LogProcessHelper::enumToString(level) << " " << message << std::endl;
        } else if (nextLogProcessor) {
            nextLogProcessor->processLog(level, message);
        }
    }
};

class WarnLogProcessor : public LogProcessor {
public:
    using LogProcessor::LogProcessor;
    void processLog(LogLevel level, std::string message) override {
        if (level == LogLevel::WARN) {
            std::cout << LogProcessHelper::enumToString(level) << " " << message << std::endl;
        } else if (nextLogProcessor) {
            nextLogProcessor->processLog(level, message);
        }
    }
};

// You can add DebugLogProcessor, ErrorLogProcessor similarly

int main() {
    // Set up the chain: INFO -> WARN
    LogProcessor* infoLogger = new InfoLogProcessor(new WarnLogProcessor());

    // Test logs
    infoLogger->processLog(LogLevel::INFO, "This is an info log.");
    infoLogger->processLog(LogLevel::WARN, "This is a warning log.");
    infoLogger->processLog(LogLevel::DEBUG, "This debug won't be handled."); // No handler

    // Clean up
    delete infoLogger;
    // delete warnLogger;

    return 0;
}
