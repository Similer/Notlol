#include "MemoryPool.h"

using namespace Nl;

namespace Nl
{
	LPTSTR lpNxtPage = nullptr;
	DWORD dwPages = 0;
	DWORD dwPageSize = 0;
	MemoryPool* GMemoryPool = nullptr;

}



MemoryPool::MemoryPool(void)
{
}


MemoryPool::~MemoryPool(void)
{
}
