#include <iostream>
#include "allocator.h"

#include <vector>


using namespace std;


void* operator new(size_t sz)
{
	//cout << "operator new" << endl;
	return malloc(sz);
}

void operator delete(void* p)   // 어떤 형이 올지 모르니 void* 형
{
	//cout << "operator delete" << endl;
	free(p);
}

int main()
{
	std::vector<int, Nl::allocator<int>> vec;

	vec.push_back(1);
	cout << vec.capacity() << endl;
	vec.push_back(1);
	cout << vec.capacity() << endl;
	vec.push_back(1);
	cout << vec.capacity() << endl;
	vec.push_back(1);
	cout << vec.capacity() << endl;
	vec.push_back(1);
	cout << vec.capacity() << endl;
	vec.push_back(1);
	cout << vec.capacity() << endl;
	vec.push_back(1);
	cout << vec.capacity() << endl;


	return 0;
}