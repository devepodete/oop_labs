#ifndef _ALLOCATOR_HPP_
#define _ALLOCATOR_HPP_

#include <iostream>
#include <stdexcept>
#include <memory>
#include "stack.hpp"
#include <unistd.h>

template <class T, size_t BLOCK_COUNT>
class myAllocator{
public:
	using value_type = T;
	using pointer = T*;
	using double_pointer = T**;
	using const_pointer = const T*;
	using const_double_pointer = const T**;
	using size_type = std::size_t;

	myAllocator(){
		#ifdef Debug
		std::cout << "myAllocator(): creating\n";
		#endif
		static_assert(BLOCK_COUNT > 0);
		
		//used_blocks = new T[BLOCK_COUNT];
		//free_blocks = new pointer[BLOCK_COUNT];
		used_blocks = (pointer)malloc(BLOCK_COUNT*sizeof(T));
		free_blocks = (double_pointer)malloc(BLOCK_COUNT*sizeof(pointer));

		for(size_type i = 0; i < BLOCK_COUNT; i++){
			free_blocks[i] = &used_blocks[i];
		}

		free_count = BLOCK_COUNT;
		#ifdef Debug
		std::cout << "myAllocator(): created\n";
		#endif
	}

	~myAllocator(){
		#ifdef Debug
		if(free_count < BLOCK_COUNT){
			std::cout << "~myAllocator(): memory leak\n";
		}else{
			std::cout << "~myAllocator(): no memory leak\n";
		}
		std::cout << "~myAllocator(): deleting used_blocks\n";
		#endif

		//delete[] used_blocks;
		free(used_blocks);
		#ifdef Debug
		std::cout << "~myAllocator(): deleting free_blocks\n";
		#endif

		//delete[] free_blocks;
		free(free_blocks);
		#ifdef Debug
		std::cout << "~myAllocator(): memory deleted\n";
		#endif
	}

	pointer allocate(size_type junk){
		pointer result = nullptr;
		if(free_count > 0){
			result = free_blocks[--free_count];
			#ifdef Debug
			std::cout << "allocate(): allocated\n";
			#endif
		}else{
			#ifdef Debug
			std::cout << "allocate(): not enough memory\n";
			#endif
			throw std::bad_alloc();
		}
		return result;
	}

	void deallocate(pointer p, size_type junk){
		#ifdef Debug
		std::cout << "deallocate(): deallocating\n";
		#endif
		free_blocks[free_count++] = p;
		#ifdef Debug
		std::cout << "deallocate(): deallocated\n";
		#endif
	}

	void destroy(pointer p){
		p->~T();
	}

	template <class U, class ...Args>
	void construct(U *p, Args && ...args){
		new(p) U(std::forward<Args>(args)...);
	}

	template <class U>
	struct rebind{
		using other = myAllocator<U, BLOCK_COUNT>;
	};

	struct rebind_to_node{
		using other = myAllocator<node<T>, BLOCK_COUNT>;
	};

private:
	pointer used_blocks;
	double_pointer free_blocks;
	size_type free_count;
};

#endif