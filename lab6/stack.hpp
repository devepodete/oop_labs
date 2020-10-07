#ifndef __STACK_HPP__
#define __STACK_HPP__

#include <memory>
#include <exception>
#include "pentagon.hpp"
#include "allocator.hpp"
#include <unistd.h>

template <class T>
struct node{
	using type = T;
	node(){};
	node(const T &key): value(key){};
	std::shared_ptr<node<T>> next;
	std::weak_ptr<node<T>> prev;
	T value;
};


template <class T>
class iterator{
protected:
	iterator(){};
public:
	typedef std::bidirectional_iterator_tag iterator_category;
	typedef T value_type;
	typedef int difference_type;
	typedef T* pointer;
	typedef T& reference;

	iterator(std::shared_ptr<T> pointer): ptr(pointer){};

	iterator operator++(){
		ptr = (ptr.lock())->next;
		return *this;
	}

	iterator operator++(int junk){
		iterator i = *this;
		ptr = (ptr.lock())->next;
		return i;
	}

	iterator operator--(){
		ptr = (ptr.lock())->prev;
		return *this;
	}

	iterator operator--(int junk){
		iterator i = *this;
		ptr = (ptr.lock())->prev;
		return i;
	}

	typename T::type &operator*(){
		return (ptr.lock())->value;
	}

	std::shared_ptr<T> operator->(){
		return ptr.lock();
	}

	bool operator==(const iterator &rhs){
		return ptr.lock() == rhs.ptr.lock();
	}

	bool operator!=(const iterator &rhs){
		return ptr.lock() != rhs.ptr.lock();
	}

private:
	std::weak_ptr<T> ptr;
};


template <class T, class Allocator = std::allocator<T>>
class stack: public iterator<node<T>>{
public:
	stack(){
		//fake = std::make_shared<node<T>>();
		fake = nodeAllocate();
		
		fake->next = fake;
		fake->prev = fake;
		size_ = 0;
	}

	~stack(){
		#ifdef Debug
		std::cout << "~stack(): destroying\n";
		#endif
		
		while(fake->next != fake){
			pop();
		}
		fake->next = nullptr;
		
		#ifdef Debug
		std::cout << "~stack(): destroyed\n";
		#endif
	}

	void push(const T &item){
		//auto temp = std::make_shared<node<T>>(item);
		auto temp = nodeAllocate(item);

		if(fake->next == fake){
			fake->next = temp;
			fake->prev = temp;
			temp->next = fake;
			temp->prev = fake;
		}else{
			auto first = fake->next;
			temp->next = first;
			temp->prev = fake;
			first->prev = temp;
			fake->next = temp;
		}
		size_++;
	}

	void pop(){
		if(is_empty()){
			throw std::logic_error("Empty stack pop");
		}
		if(fake->next == (fake->prev).lock()){
			fake->next = fake;
		}else{
			fake->next = fake->next->next;
			fake->next->prev = fake;
		}
		size_--;
	}

	T top() const{
		if(is_empty()){
			throw std::logic_error("Empty stack top");
		}
		return fake->next->value;
	}

	void insert(iterator<node<T>> it, const T &key){
		if(is_empty()){
			push(key);
		}else{
			auto temp = std::make_shared<node<T>>(key);
			//auto temp = nodeAllocate(key);
			temp->next = (it->next->prev).lock();
			temp->prev = it->prev;
			((it->prev).lock())->next = temp;
			it->prev = temp;
		}
	}

	void erase(iterator<node<T>> it){
		if(is_empty()){
			throw std::logic_error("Empty stack erase");
		}
		if(it == end()){
			throw std::logic_error("Removing fake item is permitted");
		}
		it->next->prev = it->prev;		
		((it->prev).lock())->next = it->next;
	}

	bool is_empty() const{
		return size_ == 0;
	}

	size_t size() const{
		return size_;
	}

	iterator<node<T>> begin(){
		return iterator<node<T>>(fake->next);
	}

	iterator<node<T>> end(){
		return iterator<node<T>>(fake);
	}

	iterator<node<T>> at(int pos){
		if(pos >= size_ || pos < 0){
			throw std::logic_error("Wrong position iterator");
		}
		if(is_empty()){
			throw std::logic_error("Can not get iterator from empty stack");
		}
		int k = 0;
		if(pos < size_/2){
			iterator<node<T>> temp(begin());
			while(k < pos){
				temp++;
				k++;
			}
			return temp;
		}else{
			iterator<node<T>> temp(--end());
			while(size_-k-1 > pos){
				temp--;
				k++;
			}
			return temp;
		}
	}

	void print(){
		std::cout << "stack: ";
		for(auto i = begin(); i != end(); i++){
			std::cout << *i << " ";
		}
		std::cout << "\n";
	}
private:
	
	using node_allocator = typename Allocator::rebind_to_node::other;
	
	node_allocator all;
	std::shared_ptr<node<T>> fake;
	size_t size_;
	
	std::shared_ptr<node<T>> nodeAllocate(){
		node<T> *temp = all.allocate(1);
		all.construct(temp);
		#ifdef Debug
		std::cout << "nodeAllocate() 1: ptr\n"; 
		#endif
		std::shared_ptr<node<T>> ptr(temp, [this](node<T> *a){
			#ifdef Debug
			std::cout << "----------------------\n";
			std::cout << "pointer destructor 1: destroy\n";
			#endif
			this->all.destroy(a);
			#ifdef Debug
			std::cout << "pointer destructor 1: deallocate\n";
			#endif
			this->all.deallocate(a, 1);
			#ifdef Debug
			std::cout << "pointer destructor 1: complete\n";
			std::cout << "----------------------\n";
			#endif
		});
		return ptr;
	}

	std::shared_ptr<node<T>> nodeAllocate(const T &item){
		node<T> *temp = all.allocate(1);
		all.construct(temp, item);
		#ifdef Debug
		std::cout << "nodeAllocate() 2: ptr\n";
		#endif
		std::shared_ptr<node<T>> ptr(temp, [this](node<T>* a){
			#ifdef Debug
			std::cout << "----------------------\n";
			std::cout << "pointer destructor 2: destroy\n";
			#endif
			this->all.destroy(a);
			#ifdef Debug
			std::cout << "pointer destructor 2: deallocate\n";
			#endif
			this->all.deallocate(a, 1);
			#ifdef Debug
			std::cout << "pointer destructor 2: complete\n";
			std::cout << "----------------------\n";
			#endif
		});
		return ptr;
	}
};

#endif