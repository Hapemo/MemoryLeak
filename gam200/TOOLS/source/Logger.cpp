#pragma once
#include "Logger.h"

void Logger::CreateNew(std::string _newType) {
    std::string newType = Util::UpperString(_newType);
    mLogNames.push_back(newType);

    mLogTypesVec.push_back({ newType, Util::LowerString(newType) + ".log", (int)mLogNames.size() });
    mLogFilesVec.resize(mLogTypesVec.size());
    mLogFilesVec[mLogTypesVec.size() - 1].open(mFilepath + mLogTypesVec[mLogTypesVec.size() - 1].filename.c_str(), std::ios_base::out | std::ios_base::app);
}

/**
*    Default constructor for the Logger class.
*/
Logger::Logger() {
    // CREATE VECTOR WITH LOG TYPE DETAILS
    for (size_t i = 0; i < mLogNames.size(); ++i)
        mLogTypesVec.push_back({ Util::UpperString(mLogNames[i]), Util::LowerString(mLogNames[i]) + ".log", (int)i });

    // opening specific log file types
    mLogFilesVec.resize(mLogTypesVec.size());
    for (size_t i = 0; i < mLogNames.size(); ++i)
        mLogFilesVec[i].open(mFilepath + mLogTypesVec[i].filename.c_str(), std::ios_base::out | std::ios_base::app);

    // opening human readable log file
    const std::string logFilename = "log.log";
    mLogInfile.open(mFilepath + logFilename, std::ios_base::out | std::ios_base::app);

    // opening full log file with file name and line number
    const std::string fullLogFilename = "fulllog.log";
    mFullLogInfile.open(mFilepath + fullLogFilename, std::ios_base::out | std::ios_base::app);
}

/**
*    Destructor for the Logger class.
*/
Logger::~Logger() {
    mLogInfile.close();
    mFullLogInfile.close();

    for (size_t i = 0; i < mLogNames.size(); ++i)
        mLogFilesVec[i].close();
}
