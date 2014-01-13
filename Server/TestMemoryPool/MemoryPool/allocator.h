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

		// U Ÿ���� rebind �Ҵ���
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

		// value�� ��ȯ �ּ�
		pointer address(reference value) const
		{
			return &value;
		}

		const_pointer address(const_reference value) const 
		{
			return &value;
		}

		

		// �Ҵ�������, T Ÿ���� num���� ���Ҹ� �ʱ�ȭ��Ű���� �ʴ´�.
		pointer allocate(size_type num, allocator<void>::const_pointer hint = 0)
		{
			// ���� new�� �Ҵ�
			void* p = ::operator new(num * sizeof(T));
			if (!p)
			{
				throw std::bad_alloc();
			}

			std::cout << "alloc" << std::endl;
			return static_cast<pointer>(p);
		}
		// ���ŵ� ������ p ������ �����Ѵ�.
		void deallocate(pointer p , size_type num)
		{			
			::operator delete((void*)p);
			std::cout << "dealloc" << std::endl;
		}

		// �Ҵ�� p ������ value�� �ʱ�ȭ�Ѵ�.
		void construct(pointer p, const T& value)
		{
			new(p)value_type(value);
		}

		// �ʱ�ȭ�� p ������ ���Ҹ� �����Ѵ�.
		void destroy(pointer p)
		{
			p->~T();
		}

		

		// �Ҵ�� �� �ִ� �ִ� ������ ���� ��ȯ
		size_type max_size() const throw()
		{
			return static_cast<size_type>(-1) / sizeof(T);
		}
		
	private:
		void operator=(const allocator&);
	};

	// ��� ����ȭ�� �Ҵ����� ȣȯ�� ���θ� ��ȯ�Ѵ�.
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
