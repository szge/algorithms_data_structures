#pragma once
#include <string>

// circular queue implementation
// https://en.wikipedia.org/wiki/Queue_(abstract_data_type)%20
// https://en.wikipedia.org/wiki/Circular_buffer

namespace alg {
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
		
		int m_capacity;
		int m_size;	// number of items in the queue
		int m_front; // index of the front of the queue
		int m_rear;	// index of the end of the queue
		T* m_elements;
	public:
		Queue(int capacity) {
			m_capacity = capacity;
			m_size = 0;
			m_front = 0;
			m_rear = -1; // set to -1 since enqueueing first item will set it to zero
			m_elements = new T[capacity];
		}

		~Queue() {
			delete[] m_elements;
		}

		inline bool is_empty() {
			return m_size == 0;
		}

		/* Enqueue an element to the end of the queue
		@return true if queue is not full, false if the queue is full
		*/
		inline bool enqueue(T value) {
			if (m_size < m_capacity) {
					m_rear = (m_rear + 1) % m_capacity;
					m_elements[m_rear] = value;
				m_size++;
				return true;
			}

			return false;
		}

		/* Remove the element at the front of the queue and return it
		@return the element at the front of the queue
		*/
		inline T dequeue() {
			if (m_size == 0) {
				throw exception_empty;
			}
			// else:

			T& temp = m_elements[m_front]; // store the element for later

			m_size--;
			m_front = (m_front + 1) % m_capacity; // this ensures circularity

			// Note: we technically don't have to remove the object from the array just change the index
			return temp;
		}

		/* Return value by index, starting at the front of the queue
		@return the element at the specified index
		*/
		inline const T& operator [] (int index) const {
			if (index < 0 || index >= m_size) {
				throw exception_ioob;
			}
			return m_elements[(m_front + index) % m_capacity];
		}

		inline int getSize() const {
			return m_size;
		}

		inline int getCapacity() {
			return m_capacity;
		}

		// WARNING: make sure std::to_string works on type T
		std::string toString() {
			int i = m_front;
			std::string str;
			str += "Printing Queue:\n\t[";
			if (m_size > 0) {
				while (i < m_front + m_size - 1) {
					str += std::to_string(m_elements[i % m_capacity]) + ", ";
					i++;
				}
				str += std::to_string(m_elements[i % m_capacity]);
			}
			str += "]\n\tSize: " + std::to_string(m_size);
			str += " Front index: " + std::to_string(m_front);
			str += " Rear index: " + std::to_string(m_rear) + "\n";
			return str;
		}
	};
}