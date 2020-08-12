#pragma once
#include <iostream>
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
			_rear = -1;
			_elements = new T[capacity];
		}

		~Queue() {
			delete[] _elements;
		}

		inline bool is_empty() {
			return _size == 0 ? true : false;
		}

		/* Enqueue an element to the end of the queue
		@return true if queue is not full, false if the queue is full
		*/
		inline bool enqueue(T value) {
			if (_size < _capacity) {
				_size++;
				_rear = (_rear + 1) % _capacity;
				_elements[_rear] = value;
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
			if (_front != _rear) _front = (_front + 1) % _capacity; // this ensures circularity

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

		// WARNING: make sure std::to_string works on type T
		std::string toString() {
			std::string str;
			str += "==Printing Queue==\nArray: [";
			for (int i = 0; i < _capacity; i++) {
				str += "[";
				// TODO: fix print idiot

				// note: the reason I substitute (i <= _rear) with (i < _front + _size) is because of
				// the case where the size is 0 and _front == _rear
				if (_front <= i && i < _front + _size) {
					str += std::to_string(_elements[i]);
				}
				str += "]";
			}
			str += "]\nSize: " + std::to_string(_size);
			str += " Front index: " + std::to_string(_front);
			str += " Rear index: " + std::to_string(_rear);
			str += "\n==================\n";
			return str;
		}

		static void test() {
			alg::Queue<float> q = Queue(4);
			std::cout << "new queue!\n";
			std::cout << "enqueueing value 0.1\n";
			q.enqueue((float) 0.1);
			std::cout << "enqueueing value 0.2\n";
			q.enqueue((float) 0.2);
			std::cout << "enqueueing value 0.3\n";
			q.enqueue((float) 0.3);

			std::cout << "pushing value 0.4, return value when not full: " << q.enqueue((float) 0.4) << "\n";
			// shouldn't do anything
			std::cout << "pushing value 0.5, return value when full: " << q.enqueue((float) 0.5) << "\n";
			
			std::cout << q.toString();

			while (!q.is_empty()) {
				std::cout << "dequeueing value: " << q.dequeue() << "\n";
			}

			std::cout << q.toString();

			std::cout << "enqueueing value 0.1\n";
			q.enqueue((float)0.1);
			std::cout << q.toString();
			std::cout << "enqueueing value 0.2\n";
			q.enqueue((float)0.2);
			std::cout << q.toString();
			std::cout << "enqueueing value 0.3\n";
			q.enqueue((float)0.3);
			std::cout << q.toString();
		}
	};
}