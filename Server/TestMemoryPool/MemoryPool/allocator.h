#pragma once

#include <windows.h>

namespace Nl
{

	template <class T>
	class allocator
	{
	public:

		typedef T value_type;
		typedef value_type* pointer;
		typedef const value_type* const_pointer;
		typedef value_type& reference;
		typedef const value_type& const_reference;

		typedef size_t size_type;
		typedef ptrdiff_t difference_type;

		// U 타입의 rebind 할당자
		template <class U>
		struct rebind
		{
			typedef allocator<U> other;
		};

		// constructor & destructor
		allocator() throw()
		{
		}
		allocator(const allocator&) throw()
		{
		}
		template <class U>
		allocator(const allocator<U>&) throw()
		{
		}
		~allocator() throw()
		{
		}

		// value의 반환 주소
		pointer address(reference value) const
		{
			return &value;
		}

		const_pointer address(const_reference value) const 
		{
			return &value;
		}

		

		// 할당하지만, T 타입의 num개의 원소를 초기화시키지는 않는다.
		pointer allocate(size_type num, allocator<void>::const_pointer hint = 0)
		{
			// 전역 new로 할당
			void* p = ::operator new(num * sizeof(T));
			if (!p)
			{
				throw std::bad_alloc();
			}

			std::cout << "alloc" << std::endl;
			return static_cast<pointer>(p);
		}
		// 제거된 원소의 p 공간을 해제한다.
		void deallocate(pointer p , size_type num)
		{			
			::operator delete((void*)p);
			std::cout << "dealloc" << std::endl;
		}

		// 할당된 p 공간을 value로 초기화한다.
		void construct(pointer p, const T& value)
		{
			new(p)value_type(value);
		}

		// 초기화된 p 공간의 원소를 제거한다.
		void destroy(pointer p)
		{
			p->~T();
		}

		

		// 할당될 수 있는 최대 원소의 개수 반환
		size_type max_size() const throw()
		{
			return static_cast<size_type>(-1) / sizeof(T);
		}
		
	private:
		void operator=(const allocator&);
	};

	// 모든 전문화된 할당자의 호환성 여부를 반환한다.
	template <class T>
	bool operator==(const allocator<T>&, const allocator<T>&) throw()
	{
		return true;
	}
	template <class T>
	bool operator!=(const allocator<T>&, const allocator<T>&) throw()
	{
		return false;
	}

	template<> class allocator<void>
	{
	public:
		typedef void        value_type;
		typedef void*       pointer;
		typedef const void* const_pointer;

		template <class U> 
		struct rebind { typedef allocator<U> other; };
	};

}
