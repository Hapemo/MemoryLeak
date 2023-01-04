#pragma once
#include "pch.h"


class FilePathManager {
public:
	static void Init(std::string const&);
	
	static std::string GetFilePath(std::string const&);

private:
	// Key: in-code name | Value: actual file path
	static std::map<std::string, std::string> mFilePaths;

};


































































