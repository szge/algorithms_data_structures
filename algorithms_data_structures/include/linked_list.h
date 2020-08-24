#pragma once
#include <string>

// doubly linked list implementation
namespace alg {
	template <typename T>
	class LinkedList {
	private:
		class IndexOutOfBoundsException : public std::exception {
		public:
			virtual const char* what() const throw() {
				return "linked list array out of bounds";
			}
		} exception_ioob;

		class StackEmptyException : public std::exception {
		public:
			virtual const char* what() const throw() {
				return "popping from an empty linked list";
			}
		} exception_empty;

		struct Node {
			T data;
			Node* next;
			Node* previous;
		};

		Node* m_head;
		unsigned int m_size;

		void destruct(Node* node) {
			if (node == nullptr) return;

			destruct(node->next);
			delete node;
		}

		/* Return the node at the end of the list
		*/
		Node* getLast() {
			Node* current = m_head;
			Node* previous = nullptr;
			while (current != nullptr) {
				previous = current;
				current = current->next;
			}
			return previous;
		}

	public:
		LinkedList() {
			m_head = nullptr;
			m_size = 0;
		}

		~LinkedList() {
			destruct(m_head);
		}

		/* Pushes an element to the front of the linked list
		*/
		void push(T data) {
			Node* newNode = new Node;
			newNode->data = data;
			newNode->next = m_head;
			newNode->previous = nullptr;
			m_head = newNode;
			m_size++;
		}

		/* Removes the first element in the linked list
		* Make sure that the linked list is not empty before calling pop.
		* (Check with isEmpty())
		* @return the first element in the linked list
		*/
		T pop() {
			if (m_head == nullptr) throw exception_empty;

			T tempData = m_head->data;

			if (m_head->next == nullptr) {
				// linked list has only one node
				delete m_head;
				m_head = nullptr;
				return tempData;
			}

			Node* newHead = m_head->next;
			newHead->previous = nullptr;
			delete m_head;
			m_head = newHead;
			m_size--;
			return tempData;
		}

		/* Pushes an element to the back of the linked list
		*/
		void pushLast(T data) {
			Node* newNode = new Node;
			newNode->data = data;
			newNode->next = nullptr;

			if (m_head == nullptr) {
				newNode->previous = nullptr;
				m_head = newNode;
			}
			else {
				newNode->previous = getLast();
				newNode->previous->next = newNode;
			}
		}

		/* Removes the last element in the linked list
		* Make sure that the linked list is not empty before calling pop.
		* (Check with isEmpty())
		* @return the first element in the linked list
		*/
		T popLast() {
			if (m_head == nullptr) throw exception_empty;

			Node* last = getLast();
			T tempData = last->data;

			if (last == m_head) {
				m_head = nullptr;
				return tempData;
			}

			last->previous->next = nullptr;
			delete last;
			return tempData;
		}
		
		inline T peek() {
			if (m_size == 0) throw exception_empty;
			return m_head->data;
		}

		bool isEmpty() {
			return m_head == nullptr;
		}

		std::string toString() {
			std::string str;
			if (m_head == nullptr) {
				str += "linked list is empty\n";
			}
			else {
				Node* current = m_head;
				Node* previous = nullptr;
				while (current != nullptr) {
					if (previous != nullptr) {
						str += "[" + std::to_string(previous->data) + "]->";
					}
					previous = current;
					current = current->next;
				}
				str += "[" + std::to_string(previous->data) + "]\n";
			}
			return str;
		}
	};
}