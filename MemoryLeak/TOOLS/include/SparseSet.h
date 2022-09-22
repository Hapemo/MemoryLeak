#pragma once
#include "pch.h"
#include "logger.h"

template<typename T>
class SparseSet {
private:
	using DataType = T; // Container's data
	using IndexType = short; // Index unit for pairing
	
	// Data's ID must be convertable to int.
	
public:
	SparseSet() = delete;
	SparseSet(SparseSet const&) = delete;

	SparseSet(int);
	//std::vector<int> GetShallow() { return mShallow; }
	//std::vector<DataType> GetDense() { return mDense; }

	DataType& operator[](IndexType const&);
	void AddData(DataType const&, IndexType const&);
	void RemoveData(IndexType const&);
	bool CheckData(IndexType const&);
	
	void PrintSet();

private:
	std::vector<int> mShallow; // Interface container
	std::vector<DataType> mDense; // Storage container
	int mCapacity;
	const int mSize;
	const int emptyID;
};


//std::ostream& operator<<(std::ostream& out, SparseSet);

template<typename T>
SparseSet<T>::SparseSet(int _size) : mSize(_size), emptyID(INT_MAX), mCapacity(0) {
	mShallow.resize(mSize);
	mDense.resize(mSize);
	std::fill(mShallow.begin(), mShallow.end(), emptyID);
}

template<typename T>
SparseSet<T>::DataType& SparseSet<T>::operator[](IndexType const& _index) {
	int deepID{ mShallow[static_cast<int>(_index)] };
	ASSERT(deepID != emptyID, "SparseSet cannot find ID: " + std::to_string(deepID));
	return mDense[deepID];
}



template<typename T>
void SparseSet<T>::RemoveData(IndexType const& _index) {
	int& deepID{ mShallow[static_cast<int>(_index)] };
	ASSERT(deepID != emptyID, "SparseSet cannot find ID: " + std::to_string(deepID));

	--mCapacity;
	mDense[deepID] = mDense[mCapacity];
	for (int i = 0; i < mSize; ++i) {
		if (mShallow[i] == mCapacity) {
			mShallow[i] = deepID;
			break;
		}
	}
	deepID = emptyID;
}


template<typename T>
void SparseSet<T>::AddData(DataType const& _data, IndexType const& _index) {
	int& deepID{ mShallow[static_cast<int>(_index)] };
	std::string errorMessage{ "ID: " + std::to_string(deepID) + " is already added, you can try operator[] to adjust the data instead" };
	//ASSERT(deepID == emptyID, errorMessage);
	if (deepID != emptyID) {
		std::cout << "Error in AddData\n";
	}
	deepID = mCapacity;
	mDense[mCapacity] = _data;
	++mCapacity;
}

template<typename T>
bool SparseSet<T>::CheckData(IndexType const& _index) {
	return mShallow[static_cast<int>(_index)] != emptyID;
}

template<typename T>
void SparseSet<T>::PrintSet() {
	std::cout << "Size: " << mSize << "\nCapacity: " << mCapacity;
	std::cout << "\nShallow:\n";
	int shallowCount{};
	for (int const& pairingID : mShallow) {
		std::cout << "Index " << shallowCount++ << " | PairingID " << pairingID << "\n";
	}

	int denseCount{};
	std::cout << "Dense:\n";
	for (auto const& data : mDense) {
		std::cout << "PairingID " << denseCount++ << " | Data " << data << "\n";
	}
	std::cout << "\n\n";
}
