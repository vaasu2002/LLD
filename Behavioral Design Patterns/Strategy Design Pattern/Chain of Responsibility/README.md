```cpp
#include <iostream>
#include <memory>
#include <string>

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
            case LogLevel::DEBUG: return "[DEBUG]";
            case LogLevel::ERROR: return "[ERROR]";
            case LogLevel::WARN:  return "[WARN]";
            default:              return "[UNDEFINED]";
        }
    }
};

class LogProcessor {
protected:
    std::unique_ptr<LogProcessor> next_;

public:
    virtual ~LogProcessor() = default;

    void setNext(std::unique_ptr<LogProcessor> next) {
        next_ = std::move(next);
    }

    virtual void processLog(LogLevel level, const std::string& message) = 0;
};

// Info Logger
class InfoLogProcessor : public LogProcessor {
public:
    void processLog(LogLevel level, const std::string& message) override {
        if (level == LogLevel::INFO) {
            std::cout << LogProcessHelper::enumToString(level) << " " << message << std::endl;
        } else if (next_) {
            next_->processLog(level, message);
        }
    }
};

// Warn Logger
class WarnLogProcessor : public LogProcessor {
public:
    void processLog(LogLevel level, const std::string& message) override {
        if (level == LogLevel::WARN) {
            std::cout << LogProcessHelper::enumToString(level) << " " << message << std::endl;
        } else if (next_) {
            next_->processLog(level, message);
        }
    }
};

int main() {
    // Chain: Info -> Warn
    auto loggerChain = std::make_unique<InfoLogProcessor>();
    auto warnLogger = std::make_unique<WarnLogProcessor>();

    // as this is unique pointer, we need to transfer ownership as we cannot
    // copy constrcutor would have called if we didn't else
    loggerChain->setNext(std::move(warnLogger));

    // Use chain
    loggerChain->processLog(LogLevel::INFO, "App started");
    loggerChain->processLog(LogLevel::WARN, "Low disk space");
    loggerChain->processLog(LogLevel::ERROR, "Unhandled exception");

    // No need to delete — unique_ptr handles cleanup automatically

    return 0;
}

```
