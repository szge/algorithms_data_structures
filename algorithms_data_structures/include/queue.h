#pragma once
#include <string>

namespace alg {
	// circular queue implementation

	template<typename T>
	class Queue {
	private:
		class QueueEmptyException : public std::exception {
		public:
			virtual const char* what() const throw() {
				return "queue is empty";
			}
		} exception_empty;

		class QueueIndexOutOfBoundsException : public std::exception {
		public:
			virtual const char* what() const throw() {
				return "queue index out of bounds";
			}
		} exception_ioob;
		
		int _capacity;
		int _size;	// number of items in the queue
		int _front; // index of the front of the queue
		int _rear;	// index of the end of the queue
		T* _elements;
	public:
		Queue(int capacity) {
			_capacity = capacity;
			_size = 0;
			_front = 0;
			_rear = -1; // set to -1 since enqueueing first item will set it to zero
			_elements = new T[capacity];
		}

		~Queue() {
			delete[] _elements;
		}

		inline bool is_empty() {
			return _size == 0;
		}

		/* Enqueue an element to the end of the queue
		@return true if queue is not full, false if the queue is full
		*/
		inline bool enqueue(T value) {
			if (_size < _capacity) {
					_rear = (_rear + 1) % _capacity;
					_elements[_rear] = value;
				_size++;
				return true;
			}

			return false;
		}

		/* Remove the element at the front of the queue and return it
		@return the element at the front of the queue
		*/
		inline T dequeue() {
			if (_size == 0) {
				throw exception_empty;
			}
			// else:

			T& temp = _elements[_front]; // store the element for later

			_size--;
			_front = (_front + 1) % _capacity; // this ensures circularity

			// Note: we technically don't have to remove the object from the array just change the index
			return temp;
		}

		/* Return value by index, starting at the front of the queue
		@return the element at the specified index
		*/
		inline const T& operator [] (int index) const {
			if (index < _capacity) {
				return _elements[(_front + index) % _capacity];
			}
			else {
				throw exception_ioob;
			}
		}

		inline int getCapacity() {
			return _capacity;
		}

		// WARNING: make sure std::to_string works on type T
		std::string toString() {
			int i = _front;
			std::string str;
			str += "Printing Queue:\n\t[";
			if (_size > 0) {
				while (i < _front + _size - 1) {
					str += std::to_string(_elements[i % _capacity]) + ", ";
					i++;
				}
				str += std::to_string(_elements[i % _capacity]);
			}
			str += "]\n\tSize: " + std::to_string(_size);
			str += " Front index: " + std::to_string(_front);
			str += " Rear index: " + std::to_string(_rear) + "\n";
			return str;
		}
	};
}