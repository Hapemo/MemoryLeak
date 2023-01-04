#include "FilePathManager.h"
#include "Logger.h"

//std::shared_ptr<FilePathManager> FilePathManager::mInstance = nullptr;

std::map<std::string, std::string> FilePathManager::mFilePaths;

void FilePathManager::Init(std::string const& path) {
  LOG_CUSTOM_CREATE("FILEPATHMANAGER");

  // Opening file
  std::fstream file;
  file.open(path, std::ios_base::in);
  if (!file.is_open()) {
    LOG_WARN("File " + path + " not found.\n");
    return;
  }

  mFilePaths = Util::TextFileToMap(file);
}

//std::shared_ptr<FilePathManager> FilePathManager::GetInstance() {
//  if (!mInstance) {
//    LOG_CUSTOM_CREATE("FILEPATHMANAGER");
//    mInstance = std::make_shared<FilePathManager>();
//  }
//  return mInstance;
//}

std::string FilePathManager::GetFilePath(std::string const& pathName) {
  std::string filePath;
  try {
     filePath = mFilePaths.at(pathName);
  } catch (std::out_of_range const& err) {
    (void)err;
    LOG_CUSTOM("FILEPATHMANAGER", "Unable to get filepath of: " + pathName);
  }

  return filePath;
}
























































