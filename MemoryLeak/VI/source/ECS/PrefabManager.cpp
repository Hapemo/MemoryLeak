#include "PrefabManager.h"
#include "ECS_items.h"


void PrefabManager::LoadPrefab(std::filesystem::path const& _path) {
	// Call serialisation manager's function to convert the json file data into prefab
	// void DeserialisePrefab(PrefabPtr _prefab, std::ifstream const& _in);

	std::ifstream inFile{ _path };
	if (!inFile.is_open()) {
		LOG_WARN("Unable to open prefab file: " + _path.string());
		return;
	}

	PrefabPtr prefab = CreatePrefab();

	//DeserialisePrefab(prefab, inFile); // Load json file into prefab and store in prefab manager.
}

// Create a new empty prefab and append it to PrefabManager's container
typename PrefabManager::PrefabPtr PrefabManager::CreatePrefab() {
	PrefabPtr prefab = std::make_shared<Prefab>();
	mPrefabs.push_back(prefab);
	return prefab;
}

// Seralise the prefab and store in into a json file.
void PrefabManager::SavePrefab(std::string const& _prefabName) {
	// Get the prefab to save
	PrefabPtr prefab{ GetPrefab(_prefabName) };
	if (prefab->Name() == "Error") {
		LOG_ERROR("Unable to save prefab, prefab is error");
		return;
	}

	// Open file to save prefab in
	std::filesystem::path folderPath = ResourceManager::GetInstance()->FileTypePath(ResourceManager::E_RESOURCETYPE::prefab);
	const std::string filePath = folderPath.string() + _prefabName + ".json";
	std::ofstream outFile{ filePath };
	if (!outFile.is_open()) {
		LOG_ERROR("Unable to open outfile when attempting to save prefab");
		return;
	}

	// Serialise the file with serialisation manager's function
	// void SerialisePrefab(PrefabPtr _prefab, std::ofstream const& _out);
	//SerialisePrefab(prefab, outFile);
	
}
//
//// Should we include this? To delete prefab files and their meta file.
//void PrefabManager::DeletePrefab(ResourceManager::GUID const&) {
//
//}

typename PrefabManager::PrefabPtr PrefabManager::GetPrefab(std::string const& _name) {
	for (PrefabPtr prefab : mPrefabs)
		if (prefab->Name() == _name) return prefab;

	LOG_WARN("Prefab: " + _name + " not found when attempting to GetPrefab");
	
	static PrefabPtr errPrefab = std::make_shared<Prefab>("Error"); // This is error prefab, should never be used.
	return errPrefab;
}





















