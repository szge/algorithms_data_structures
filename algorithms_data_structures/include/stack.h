#pragma once
#include <exception>

// stack implementation with pushing and popping from the end of the array
// indexing is O(1) operation so it's faster than moving all the elements by
// pushing the front

namespace alg {

	// template stuff:
	// https://stackoverflow.com/questions/495021/why-can-templates-only-be-implemented-in-the-header-file

	template<typename T>
	
	class Stack {
	private:
		class StackEmptyException: public std::exception {
		public:
			virtual const char* what() const throw() {
				return "stack is empty";
			}
		} exception_empty;

		class StackIndexOutOfBoundsException : public std::exception {
		public:
			virtual const char* what() const throw() {
				return "stack index out of bounds";
			}
		} exception_ioob;

		int _capacity;
		int _size;
		T* _elements;

	public:
		Stack(int capacity) {
			_capacity = capacity;
			_size = 0;
			_elements = new T[capacity];
		}

		// called when the Stack is deleted
		~Stack() {
			// elements are deleted since they are in an array and not deleted by default;
			// the other attributes like capacity and size are deleted by default with the Stack.
			delete [] _elements;
		}

		// the "inline" keyword is an optimization technique for the program to store the memory
		// addresses of instructions. This is used for simple functions.
		inline bool is_empty() {
			return (_size == 0);
		}

		/* Remove the element at the top of the stack and return it
		@return the element at the top of the stack
		*/
		inline T pop() {
			if (_size > 0) {
				_size--;
				return _elements[_size];
			}
			throw exception_empty;
		}

		/* Push an element to the top of the stack
		@return true if stack is not full, false if the stack is full
		*/
		inline bool push(const T& value) {
			if (_size < _capacity) {
				_elements[_size++] = value;
				return true;
			}
			return false;
		}

		inline int size() const {
			return _size;
		}

		/* Return value by index, starting at the top of the stack
		@return the element at the specified index
		*/
		inline const T& operator [] (int index) const {
			if (index < _capacity) {
				return _elements[_size - 1 - index];
			}
			else {
				throw exception_ioob;
			}
		}
	};
}