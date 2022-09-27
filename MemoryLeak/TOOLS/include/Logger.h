/*!*****************************************************************************
\file Logger.h
\author Chen Jia Wen
\par DP email: c.jiawen\@digipen.edu
\par Course: GAM200
\par Group: Memory Leak Studios
\date 26-09-2022
\brief
This file contains the class Logger and it's functions declaration.
The Logger class logs messages and errors of different levels and
also handles the assertion.
*******************************************************************************/

#pragma once
//#pragma warning ( disable : 4840 4477)
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
#define THROW(_type, ...) Logger::GetInstance()->LogThrow((size_t)_type, std::source_location::current(), __VA_ARGS__)

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

    enum class E_EXCEPTION {
        RANGE_ERR = 0,
        OVERFLOW_ERR = 1,
        LOGIC_ERR = 2,
        RUNTIME_ERR = 3
    };

    /*!*****************************************************************************
    \brief
    Creates a new log type.

    \param std::string _newType
    The name of the new log type.
    *******************************************************************************/
    void CreateNew(std::string _newType);

    /*!*****************************************************************************
    \brief
    Logs a message of a custom log type.

    \param const std::source_location _logData
    The log data consisting of the filename and the code line of when the log is
    being called.

    \param std::string _customLogLevel
    The name of the custom log type.

    \param const T _logMessage
    The message to be logged.
    *******************************************************************************/
    template <typename T, typename ...Args>
    void CustomLog(const std::source_location _logData, const std::string _customLogLevel, const T _logMessage, const Args... _logMessages)
    {
        size_t customType = 0;
        size_t index = 0;
        for (std::string type : mLogNames) {
            if (type == _customLogLevel)
                customType = index;
            ++index;
        }

        if (customType > 0) {
            if constexpr (sizeof...(_logMessages) > 0)
                return Log(_logData, customType, _logMessages...);
            else
                Log(_logData, customType, _logMessage);
        }
    }

    /*!*****************************************************************************
    \brief
    Logs a message according to the log type and prints the log into their
    respective log files.

    \param const std::source_location _logData
    The log data containing of the file location and the code line number of
    when the log is being called.

    \param const size_t _logType
    The log type/level.

    \param const T _logMessage
    The message to be logged.
    *******************************************************************************/
    template <typename T, typename ...Args>
    void Log(const std::source_location _logData, const size_t _logType, const T _logMessage, const Args... _logMessages)
    {
        // pushing log into vector for imgui
        mLoggerStr.push_back(std::make_pair((E_LOGLEVEL)_logType, ("[" + Util::CurrentDateTime() + "]\t" + _logMessage).c_str()));

        // printing log into terminal
        std::cout << "[" << Util::CurrentDateTime().c_str() << "]\t" << Logger::mLogTypesVec[_logType].title.c_str() << "\t" << _logMessage << "\n";

        // human readable log file
        mLogInfile << "[" << Util::CurrentDateTime() << "]\t" << std::left << std::setw(15) << Logger::mLogTypesVec[_logType].title << _logMessage;

        // full log file with file name and line number
        mFullLogInfile << "[" << Util::CurrentDateTime() << "] " << _logData.file_name() << " (LINE " << _logData.line() << ")\n\t\t\t\t" << Logger::mLogTypesVec[_logType].title << ": " << _logMessage;

        // specific log file types
        if (_logType == (size_t)Logger::E_LOGLEVEL::LOG_ASSERT)
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

    /*!*****************************************************************************
    \brief
    Asserts base on a condition and prints the assert into a file.

    \param bool _condition
    The condition to check against.

    \param const std::source_location _logData
    The log data containing of the file location and the code line number of
    when the assert is being called.
    *******************************************************************************/
    template <typename ...Args>
    void LogAssert(bool _condition, const std::source_location _logData, Args... _args)
    {
        if (!_condition) return;
        Log(_logData, (size_t)Logger::E_LOGLEVEL::LOG_ASSERT, _args...);
        throw std::runtime_error(_args...);
    }
    
    /*!*****************************************************************************
    \brief
    Asserts base on a condition and prints the assert in a file.

    \param bool _condition
    The condition to check against.

    \param const std::source_location _logData
    The log data containing of the file location and the code line number of
    when the assert is being called.
    *******************************************************************************/
    template <typename Args>
    void LogThrow(const size_t _type, const std::source_location _logData, Args _args)
    {
        std::string filename = _logData.file_name();
        std::string line = std::to_string(_logData.line());
        std::string data = "\n\t\t\t\tThrown at " + filename + " (LINE " + line + ")\n";
        switch (_type) {
        case (size_t)E_EXCEPTION::RUNTIME_ERR:
            throw std::runtime_error(_args + data);
            break;
        case (size_t)E_EXCEPTION::RANGE_ERR:
            throw std::range_error(_args + data);
            break;
        case (size_t)E_EXCEPTION::OVERFLOW_ERR:
            throw std::overflow_error(_args + data);
            break;
        case (size_t)E_EXCEPTION::LOGIC_ERR:
            throw std::logic_error(_args + data);
            break;
        }
    }

    /*!*****************************************************************************
    \brief
    Retrieves a vector of all the logs to be displayed in the editor.
    *******************************************************************************/
    std::vector<std::pair<E_LOGLEVEL, std::string>> GetLoggerStr() { return mLoggerStr; }

    /*!*****************************************************************************
    \brief
    Default constructor for the Logger class.
    *******************************************************************************/
    Logger();

    /*!*****************************************************************************
    \brief
    Destructor for the Logger class.
    *******************************************************************************/
    ~Logger();
private:
    struct LogType {
        std::string title = "";
        std::string filename = "";
        size_t level = 0;

        LogType(std::string _s1, std::string _s2, int _u1) : title(_s1), filename(_s2), level(_u1) {};
    };

    const std::string mFilepath = "../logs/";
    std::vector<std::string> mLogNames = { "INFO", "DEBUG", "WARN", "ERROR", "ASSERT", "CRASH" };

    std::fstream mLogInfile;
    std::fstream mFullLogInfile;
    std::vector<std::fstream> mLogFilesVec;

    std::vector<LogType> mLogTypesVec;
    std::vector<std::pair<E_LOGLEVEL, std::string>> mLoggerStr;
};
