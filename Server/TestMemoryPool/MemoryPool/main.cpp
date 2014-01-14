#include <iostream>
#include "allocator.h"
#include "MemoryPool.h"
#include <vector>


using namespace std;


void* operator new(size_t sz)
{
	//cout << "operator new" << endl;
	return malloc(sz);
}

void operator delete(void* p)   // � ���� ���� �𸣴� void* ��
{
	//cout << "operator delete" << endl;
	free(p);
}

using namespace Nl;

int main()
{
	GMemoryPool = new MemoryPool;

	GMemoryPool->Initialize();

	GMemoryPool->Terminate();

	delete GMemoryPool;

	return 0;
}