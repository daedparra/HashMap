// HashMap.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <list>
#include <string>
#include <functional>
#include <assert.h>
typedef unsigned int Hash;
std::hash<std::string> s_hash;

//
// a hash map
//
// 1. only stores pointers
// 2. can assume T *always* has the element "mHash" that contains the hash
//
template<class T, int SIZE>
class HashMap{
public:
	HashMap()
	{
		// TODO: assert if SIZE isn't actually a power of two
		assert((SIZE & (SIZE - 1)) == 0);
		mMask = SIZE - 1;
	}

	// TODO: insert data, return if succeeded
	bool Insert(T& data)
	{
		if (data != nullptr) {
			int index = Translate(data->mHash);
			mBuckets[index].push_back(data);
			return true;
		}
		return false;
	}

	// TODO: insert data, don't check to see if it already exists
	void InsertNoCheck(T& data)
	{
		int index = Translate(data->mHash);
		mBuckets[index].push_back(data);
	}

	// TODO: find the data from the hash
	T Find(Hash hash)
	{
		int index = Translate(hash);
		bool isEmpty = mBuckets[index].empty();
		if (!isEmpty) 
		{
			for (T entry : mBuckets[index])
			{
				if (hash == entry->mHash) {
					return entry;
				}
			}
		}
		return nullptr;
	}

	// TODO: find the data from the hash (but as const)
	const T Find(Hash hash) const
	{
		int index = Translate(hash);
		bool isEmpty = mBuckets[index].empty();
		if (!isEmpty)
		{
			for (T entry : mBuckets[index])
			{
				if (hash == entry->mHash) 
				{
					return entry;
				}
			}
		}
		return nullptr;
	}


	// TODO: delete the data from the hash
	void Delete(T data)
	{
		int index = Translate(data->mHash);
		T deletedObject = Find(data->mHash);
		if (deletedObject != nullptr) 
		{
			mBuckets[index].remove(deletedObject);
		}
		
	}

private:

	// TODO: explain why this works
	int Translate(Hash hash) const
	{
		return (hash & mMask);
	}

private:

	Hash mMask;

	// TODO: you should use your own linked list class
	std::list<T> mBuckets[SIZE];
};

//
// TEST CODE
//

class MyObject
{
public:
	Hash mHash;
};

int main()
{
	Hash HELLO_hash = s_hash("HELLO");
	Hash BYE_hash = s_hash("BYE");
	Hash CONST_hash = s_hash("CONST");


	MyObject* myObject = new MyObject();
	myObject->mHash = HELLO_hash;

	MyObject* mySecondObject = new MyObject();
	mySecondObject->mHash = BYE_hash;

	MyObject* myThirdObject = new MyObject();
	myThirdObject->mHash = CONST_hash;

	HashMap<MyObject*, 256> myHashMap;
	myHashMap.InsertNoCheck(myObject);

	if (myHashMap.Insert(mySecondObject)) {
		printf("You Inserted");
	}

	MyObject* searchObject = myHashMap.Find(myObject->mHash);
	myHashMap.Delete(myObject);
	MyObject* searchObjectDElete = myHashMap.Find(myObject->mHash);

	//const find
	myHashMap.InsertNoCheck(myThirdObject);
	const MyObject* searchObjectConst = myHashMap.Find(myThirdObject->mHash);

	delete myObject;
	return 0;
}


