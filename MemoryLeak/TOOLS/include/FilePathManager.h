#pragma once
#include "pch.h"


class FilePathManager {
public:
	static void Init(std::string const&);
	
	static std::string GetFilePath(std::string const&);

	//static std::shared_ptr<FilePathManager> GetInstance();

private:
	//static std::shared_ptr<FilePathManager> mInstance;

	// Key: in-code name | Value: actual file path
	static std::map<std::string, std::string> mFilePaths;

};


































































