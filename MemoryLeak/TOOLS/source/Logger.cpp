/*!*****************************************************************************
\file Logger.cpp
\author Chen Jia Wen
\par DP email: c.jiawen\@digipen.edu
\par Course: GAM200
\par Group: Memory Leak Studios
\date 26-09-2022
\brief
This file contains the function definitions of the class Logger.
The Logger class logs messages and errors of different levels and
also handles the assertion.
*******************************************************************************/

#pragma once
#include "Logger.h"

/*!*****************************************************************************
\brief
Creates a new log type.

\param std::string _newType
The name of the new log type.
*******************************************************************************/
void Logger::CreateNew(std::string _newType) {
    std::string newType = Util::UpperString(_newType);
    mLogNames.push_back(newType);

    mLogTypesVec.push_back({ newType, Util::LowerString(newType) + ".log", (int)mLogNames.size() });
    mLogFilesVec.resize(mLogTypesVec.size());
    mLogFilesVec[mLogTypesVec.size() - 1].open(mFilepath + mLogTypesVec[mLogTypesVec.size() - 1].filename.c_str(), std::ios_base::out | std::ios_base::app);
}

/*!*****************************************************************************
\brief
Default constructor for the Logger class.
*******************************************************************************/
Logger::Logger() {
    if (!std::filesystem::exists(mFilepath))
        std::filesystem::create_directory(mFilepath);

    // CREATE VECTOR WITH LOG TYPE DETAILS
    for (size_t i = 0; i < mLogNames.size(); ++i)
        mLogTypesVec.push_back({ Util::UpperString(mLogNames[i]), Util::LowerString(mLogNames[i]) + ".log", (int)i });

    // opening specific log file types
    mLogFilesVec.resize(mLogTypesVec.size());
    for (size_t i = 0; i < mLogNames.size(); ++i) {
        mLogFilesVec[i].open(mFilepath + mLogTypesVec[i].filename.c_str(), std::ios_base::out | std::ios_base::app);
        mLogFilesVec[i] << "----- NEW RUN -----\n";
    }

    // opening human readable log file
    const std::string logFilename = "log.log";
    mLogInfile.open(mFilepath + logFilename, std::ios_base::out | std::ios_base::app);
    mLogInfile << "----- NEW RUN -----\n";

    // opening full log file with file name and line number
    const std::string fullLogFilename = "fulllog.log";
    mFullLogInfile.open(mFilepath + fullLogFilename, std::ios_base::out | std::ios_base::app);
    mFullLogInfile << "----- NEW RUN -----\n";
}

/*!*****************************************************************************
\brief
Destructor for the Logger class.
*******************************************************************************/
Logger::~Logger() {
    mLogInfile << "----- END RUN -----\n";
    mFullLogInfile << "----- END RUN -----\n";
    mLogInfile.close();
    mFullLogInfile.close();
    for (size_t i = 0; i < mLogNames.size(); ++i) {
        mLogFilesVec[i] << "----- END RUN -----\n";
        mLogFilesVec[i].close();
    }
}
