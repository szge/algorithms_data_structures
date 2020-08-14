#pragma once
#include "stack.h"
#include "queue.h"
#include "bubble_sort.h"
#include <iostream>

namespace alg {
	class Test {
	public:
		static void test_bubble_sort() {
			std::cout << "Bubble sort test!\n";
			int arr[8] = { 8, 7, 6, 5, 4, 3, 2, 1 };
			std::cout << "Array before sorting: \n[";
			int len = std::size(arr) - 1;
			for (int i = 0; i < len; i++) {
				std::cout << arr[i] << ", ";
			}
			std::cout << arr[len] << "]\n";

			alg::BubbleSort(arr, 0, len);

			std::cout << "Array after sorting: \n[";
			for (int i = 0; i < len; i++) {
				std::cout << arr[i] << ", ";
			}
			std::cout << arr[len] << "]\n";
		}

		static void test_queue() {
			// IMPORTANT NOTE: if used improperly it will result in a seg fault or something
			// this is because the dequeue does not call delete on the object in memory in case
			// you'd want to use the object somewhere else

			// correct usage:
			/*Queue<MyClass> q = Queue(10);

			if (int i = 0; i < q.getCapacity(); i++) {
				MyClass* c = new MyClass();
				q.add(c);
			}

			print(q.dequeue());

			delete c;*/
			alg::Queue<int> q(4);
			std::cout << "new queue!\n";
			std::cout << "enqueueing value 1\n";
			q.enqueue(1);
			std::cout << "enqueueing value 2\n";
			q.enqueue(2);
			std::cout << "enqueueing value 3\n";
			q.enqueue(3);

			std::cout << "enqueueing value 4, return value when not full: " << q.enqueue(4) << "\n";
			// shouldn't do anything
			std::cout << "enqueueing value 5, return value when full: " << q.enqueue(5) << "\n";

			std::cout << q.toString();

			while (!q.is_empty()) {
				std::cout << "dequeueing value: " << q.dequeue() << "\n";
			}

			std::cout << q.toString();

			std::cout << "enqueueing value 1\n";
			q.enqueue(1);
			std::cout << q.toString();
			std::cout << "enqueueing value 2\n";
			q.enqueue(2);
			std::cout << q.toString();
			std::cout << "enqueueing value 3\n";
			q.enqueue(3);
			std::cout << q.toString();

			while (!q.is_empty()) {
				std::cout << "dequeueing value: " << q.dequeue() << "\n";
			}


		}

		static void test_stack() {
			alg::Stack<float> s(4);
			std::cout << "new stack!\n";
			std::cout << "pushing value 10.5\n";
			s.push(10.5);
			std::cout << "pushing value 5\n";
			s.push(5);
			std::cout << "pushing value -3.14159\n";
			s.push((float)-3.14159);

			std::cout << "pushing 1, return value when not full: " << s.push(1) << "\n";
			std::cout << "pushing 1, return value when full: " << s.push(1) << "\n";

			while (!s.is_empty()) {
				std::cout << "popping value: " << s.pop() << "\n";
			}
		}
	};
}
