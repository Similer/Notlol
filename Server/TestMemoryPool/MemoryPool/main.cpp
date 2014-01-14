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

void operator delete(void* p)   // 어떤 형이 올지 모르니 void* 형
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