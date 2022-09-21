#pragma once
#include "pch.h"
#include "Singleton.h"
#include "Utilities.h"

#define LOG_INFO(...) Logger::GetInstance()->Log(std::source_location::current(), (size_t)Logger::E_LOGLEVEL::LOG_INFO, __VA_ARGS__)
#define LOG_DEBUG(...) Logger::GetInstance()->Log(std::source_location::current(), (size_t)Logger::E_LOGLEVEL::LOG_DEBUG, __VA_ARGS__)
#define LOG_WARN(...) Logger::GetInstance()->Log(std::source_location::current(), (size_t)Logger::E_LOGLEVEL::LOG_WARN, __VA_ARGS__)
#define LOG_ERROR(...) Logger::GetInstance()->Log(std::source_location::current(), (size_t)Logger::E_LOGLEVEL::LOG_ERROR, __VA_ARGS__)
#define LOG_CRASH(...) Logger::GetInstance()->Log(std::source_location::current(), (size_t)Logger::E_LOGLEVEL::LOG_CRASH, __VA_ARGS__)
#define LOG_CUSTOM(_customLogLevel, ...) Logger::GetInstance()->CustomLog(std::source_location::current(), _customLogLevel, __VA_ARGS__)
#define LOG_CUSTOM_CREATE(_newType) Logger::GetInstance()->CreateNew(_newType)
#define ASSERT(_condition, ...) Logger::GetInstance()->LogAssert(_condition, std::source_location::current(), __VA_ARGS__)

/**
*   Singleton Logger Class.
*/
class Logger : public Singleton<Logger> {
public:
    enum class E_LOGLEVEL {
        LOG_INFO = 0,
        LOG_DEBUG = 1,
        LOG_WARN = 2,
        LOG_ERROR = 3,
        LOG_ASSERT = 4,
        LOG_CRASH = 5
    };

    void CreateNew(std::string _newType);

    template <typename T, typename ...Args>
    [[noreturn]] void CustomLog(const std::source_location _logData, const std::string _customLogLevel, const T _logMessage, const Args... _logMessages)
    {
        size_t customType = -1;
        size_t index = 0;
        for (std::string type : mLogNames) {
            if (type == _customLogLevel)
                customType = index;
            ++index;
        }

        if (customType != -1) {
            if constexpr (sizeof...(_logMessages) > 0)
                return Log(_logData, customType, _logMessages...);
            else
                Log(_logData, customType, _logMessage);
        }
    }

    /**
    *   Logger function to log message according to log type.
    *   @param _logData The file location and line number the log is from.
    *   @param _logType Log type/level.
    *   @param _logMessage | _logMessages String for the message to be logged.
    */
    template <typename T, typename ...Args>
    [[noreturn]]
    void Log(const std::source_location _logData, const size_t _logType, const T _logMessage, const Args... _logMessages)
    {
        // pushing log into vector for imgui
        mLoggerStr.push_back(std::make_pair((E_LOGLEVEL)_logType, ("[" + Util::CurrentDateTime() + "]\t" + _logMessage).c_str()));

        // printing log into terminal
        printf("[%s]\t%s\t%s\n", (Util::CurrentDateTime()).c_str(), (Logger::mLogTypesVec[_logType].title).c_str(), _logMessage);

        // human readable log file
        mLogInfile << "[" << Util::CurrentDateTime() << "]\t" << std::left << std::setw(15) << Logger::mLogTypesVec[_logType].title << _logMessage;

        // full log file with file name and line number
        mFullLogInfile << "[" << Util::CurrentDateTime() << "] " << _logData.file_name() << " (LINE " << _logData.line() << ")\n\t\t\t\t" << Logger::mLogTypesVec[_logType].title << ": " << _logMessage;

        // specific log file types
        if (_logType == (size_t)Logger::E_LOGLEVEL::LOG_ASSERT || _logType == (size_t)Logger::E_LOGLEVEL::LOG_CRASH)
            mLogFilesVec[_logType] << "[" << Util::CurrentDateTime() << "] " << _logData.file_name() << " (LINE " << _logData.line() << ")\n\t\t\t\t" << _logMessage;
        else
            mLogFilesVec[_logType] << "[" << Util::CurrentDateTime() << "]\t" << _logMessage;

        if constexpr (sizeof...(_logMessages) > 0) {
            return Log(_logData, _logType, _logMessages...);
        } else {
            mLogInfile << "\n" << std::flush;
            mFullLogInfile << "\n" << std::flush;
            mLogFilesVec[_logType] << "\n" << std::flush;
        }
    }

    template <typename ...Args>
    void LogAssert(bool _condition, const std::source_location _logData, Args... _args)
    {
        if (_condition) return;
        Log(_logData, (size_t)Logger::E_LOGLEVEL::LOG_ASSERT, _args...);
        throw std::runtime_error(_args...);
    }

    std::vector<std::pair<E_LOGLEVEL, std::string>> GetLoggerStr() { return mLoggerStr; }

    /**
    *    Default constructor for the Logger class.
    */
    Logger();

    /**
    *    Destructor for the Logger class.
    */
    ~Logger();
private:
    struct LogType {
        std::string title = "";
        std::string filename = "";
        size_t level = 0;

        LogType(std::string _s1, std::string _s2, int _u1) : title(_s1), filename(_s2), level(_u1) {};
    };
    /**
    *   Log file name.
    **/
    const std::string mFilepath = "logs/";
    std::vector<std::string> mLogNames = { "INFO", "DEBUG", "WARN", "ERROR", "ASSERT", "CRASH" };
    /**
    *   Log file(s) stream object.
    **/
    std::fstream mLogInfile;
    std::fstream mFullLogInfile;
    std::vector<std::fstream> mLogFilesVec;
    /**
    *   Different log types and their file names.
    **/
    std::vector<LogType> mLogTypesVec;
    std::vector<std::pair<E_LOGLEVEL, std::string>> mLoggerStr;
};
