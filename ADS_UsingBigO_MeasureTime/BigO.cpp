/*****************************************************************//**
 * \file   BigO.cpp
 * \brief  Provides timing function used to measure performance of a function.
 * This file also contains some common algorithm (search, sort, factorial)
 * implementations which you can use the measureTime function with.
 *
 * \author DF
 * \date   October 2020
 *********************************************************************/
#include <iostream>
#include <list>
#include <chrono>
using namespace std;

template <typename FuncType>
double measureTime(FuncType func);

int binarySearch(int* list, int size, int target);
int linearSearch(int* list, int size, int value);
void printFirstItem(int arrayOfItems[]);
void bubbleSort(int arr[], int size);
void factorial(int i);

/// What is a functor in c++? https://www.geeksforgeeks.org/functors-in-cpp/
//create a class to hold the values that we want to pass to measureTime and provide a functor
class BinarySearchFunctor { //step 1 - create class/struct to represent the functor
private:
	//step 2 - add member variables which are the params that we pass to the function that we call
	int* pArr;
	int length;
	int target;

public:

	//step 3 - if class then create constructor to take and store the params
	BinarySearchFunctor(int* pArr, int length, int target) : pArr(pArr), length(length), target(target) {};

	//step 4 - overload the function call operator AND then call the target function
	void operator()() {
		binarySearch(this->pArr, this->length, this->target);
	}
};

/********************************* Other Functor Example *********************************/
//we can also simply create a struct instead of a class and provide a functor
struct BinarySearchFunctorAsStruct {
	int* pArr;
	int length;
	int target;
};

//another example of a functor using a struct
struct Line {
	//y = m*x + c => slope * x  + yIntercept 
	float slope;
	float yIntercept;

	//function call operator - returns float
	float operator()(int x) {
		float y = slope * x + yIntercept;
		return y;
	}
};

//another example of a functor using a struct
struct EncryptedString {
	string encryptionKey;
	string encryptionAlgo;

	string operator()(string data) {
		return "Encrypted with " + encryptionAlgo + " and key " + encryptionKey + "[" + data + "]";
	}
};

/********************************* Main *********************************/

int main()
{
	std::cout << "Code to use BigO functions...." << endl;

	int target = 0;
	int length = 20;
	int maxValue = 1000;
	int* pNums = new int[length];

	/******************************************************************************/

	cout << "Populate array..." << endl << endl;
	srand(time(NULL));
	for (auto i = 0; i < length; i++)
	{
		//rand() returns number in range 0 -> RAND_MAX generally 0 -> 32,527
		pNums[i] = std::rand() % maxValue + 1; //1 -> maxValue 
	}

	/******************************************************************************/

	cout << "Printing contents..." << endl << endl;

	for (auto i = 0; i < length; i++)
		cout << pNums[i] << endl;

	/******************************************************************************/

	cout << "Linear search..." << endl << endl;
	cout << "Enter number to search for: " << endl;
	cin >> target;
	cout << target << " found at: " << linearSearch(pNums, length, target) << endl;

	/******************************************************************************/

	cout << "Binary search..." << endl << endl;
	bubbleSort(pNums, length);
	for (auto i = 0; i < length; i++)
		cout << pNums[i] << endl;

	cout << "Enter number to search for: " << endl;
	cin >> target;
	cout << target << " found at: " << binarySearch(pNums, length, target) << endl;

	/******************************************************************************/

	cout << "Timing the Binary search..." << endl << endl;
	//now lets measure how long the binarySearch function takes to execute with same target value
	BinarySearchFunctor bFunc(pNums, length, target);
	cout << "Binary Search took " << measureTime(bFunc) << "ns";

}

template <typename FuncType>
double measureTime(FuncType func)
{
	std::chrono::time_point<std::chrono::high_resolution_clock> st = std::chrono::high_resolution_clock::now();
	func();
	std::chrono::time_point<std::chrono::high_resolution_clock> end = std::chrono::high_resolution_clock::now();
	return (end - st) / std::chrono::nanoseconds(1);
}

int binarySearch(int* pArray, int length, int target)
{
	int min = 0, max = length - 1, mid = 0;
	bool found = false;
	while (!found && min <= max)
	{
		mid = (min + max) / 2;
		if (pArray[mid] == target)
			found = true;
		else if (target < pArray[mid])
			max = mid - 1;
		else
			min = mid + 1;
	}

	if (found)
		return mid;
	else
		return -1;
}

//same as...
//int linearSearch(int array[], int length, int target)
int linearSearch(int* pArray, int length, int target)
{
	for (int x = 0; x < length; x++)
		if (pArray[x] == target) return x;

	return -1;
}

void printFirstItem(int arrayOfItems[])
{
	cout << arrayOfItems[0] << endl;
}

//same as...
//void bubbleSort(int* pArray, int length)
void bubbleSort(int arr[], int length)
{
	int tmp = 0;

	for (int i = 0; i < length; i++) {
		for (int j = 0; j < (length - i - 1); j++) {
			if (arr[j] > arr[j + 1]) {
				tmp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = tmp;
			}
		}
	}
}

void factorial(int i)
{
	int sum = 0;
	for (int x = i; x > 0; x--)
	{
		sum += x;
	}
	cout << sum << endl;

	if (i > 0)
		factorial(i - 1);
	else
		return;
}

