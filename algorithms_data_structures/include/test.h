#pragma once
#include "bubble_sort.h"
#include "stack.h"
#include "queue.h"
#include "binary_search_tree.h"
#include "linked_list.h"
#include "elo.h"
#include <iostream>
#include <vector>
#include <array>
#include <algorithm>
#include <random>

using namespace std;

namespace alg {
	class Test {
	public:
		static void test_bubble_sort() {
			cout << "Bubble sort test!\n";
			int arr[8] = { 8, 7, 6, 5, 4, 3, 2, 1 };
			cout << "Array before sorting: \n[";
			int len = size(arr) - 1;
			for (int i = 0; i < len; i++) {
				cout << arr[i] << ", ";
			}
			cout << arr[len] << "]\n";

			alg::BubbleSort(arr, 0, len);

			cout << "Array after sorting: \n[";
			for (int i = 0; i < len; i++) {
				cout << arr[i] << ", ";
			}
			cout << arr[len] << "]\n";
		}

		static void test_stack() {
			alg::Stack<float> s(4);
			cout << "new stack!\n";
			cout << "pushing value 10.5\n";
			s.push(10.5);
			cout << "pushing value 5\n";
			s.push(5);
			cout << "pushing value -3.14159\n";
			s.push((float)-3.14159);

			cout << "pushing 1, return value when not full: " << s.push(1) << "\n";
			cout << "pushing 1, return value when full: " << s.push(1) << "\n";

			while (!s.is_empty()) {
				cout << "popping value: " << s.pop() << "\n";
			}
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
			cout << "new queue!\n";
			cout << "enqueueing value 1\n";
			q.enqueue(1);
			cout << "enqueueing value 2\n";
			q.enqueue(2);
			cout << "enqueueing value 3\n";
			q.enqueue(3);

			cout << "enqueueing value 4, return value when not full: " << q.enqueue(4) << "\n";
			// shouldn't do anything
			cout << "enqueueing value 5, return value when full: " << q.enqueue(5) << "\n";

			cout << q.toString();

			while (!q.is_empty()) {
				cout << "dequeueing value: " << q.dequeue() << "\n";
			}

			cout << q.toString();

			cout << "enqueueing value 1\n";
			q.enqueue(1);
			cout << q.toString();
			cout << "enqueueing value 2\n";
			q.enqueue(2);
			cout << q.toString();
			cout << "enqueueing value 3\n";
			q.enqueue(3);
			cout << q.toString();

			cout << "indexing element at position 0: " << q[0] << "\n";
			cout << "indexing element at position 1: " << q[1] << "\n";
			cout << "indexing element at position 2: " << q[2] << "\n";

			while (!q.is_empty()) {
				cout << "dequeueing value: " << q.dequeue() << "\n";
			}
		}

		static void test_bst() {
			cout << "Binary search tree test!\n";
			alg::BST<int, double> bst;

			// create a binary tree with keys from 0 to len - 1 and insert them in a random order
			cout << "Creating a bst (key: int, value: double) from [0, 9] randomly shuffled:\n";
			array<int, 10> numbers;
			for (unsigned int i = 0; i < numbers.size(); i++) {
				numbers[i] = i;
			}
			shuffle(numbers.begin(), numbers.end(), default_random_engine(1));

			for (int i : numbers) {
				bst.insert(i, i);
			}

			cout << bst.toString();

			cout << "Inserting key, value 7, 7 \n";
			bst.insert(7, 7);
			cout << bst.toString();

			cout << "Finding value for key \"5\": " << to_string(bst.getValue(5)) << "\n";

			cout << "Deleting value 4 (leaf/no children):\n";
			bst.deleteKey(4);
			cout << bst.toString();

			cout << "Deleting value 0 (one child):\n";
			bst.deleteKey(0);
			cout << bst.toString();

			cout << "Deleting value 3 (root plus two children):\n";
			bst.deleteKey(3);
			cout << bst.toString();
		}

		static void test_linked_list() {
			LinkedList<int> linkedList;
			cout << "Linked list test!\n";
			cout << linkedList.toString();

			cout << "Pushing value 3 to the front:\n";
			linkedList.push(3);
			cout << linkedList.toString();

			cout << "Pushing value 1 to the back:\n";
			linkedList.pushLast(1);
			cout << linkedList.toString();

			cout << "Popping from the front: " << linkedList.pop() << "\n";
			cout << linkedList.toString();

			cout << "Popping from the front: " << linkedList.pop() << "\n";
			cout << linkedList.toString();

			cout << "Pushing value 1 to the back:\n";
			linkedList.pushLast(1);
			cout << linkedList.toString();

			cout << "Popping from the back: " << linkedList.popLast() << "\n";
			cout << linkedList.toString();
		}

		static void test_elo() {
			cout << "Elo test!\n";

			int playerA = 1613;
			cout << "Player A's elo is 1613\n";

			playerA = (int)round(get<0>(EloEvaluate(playerA, 1609, 0)));
			cout << "Player A loses to a player rated 1609. Their new elo is " << playerA << "\n";

			playerA = (int)round(get<0>(EloEvaluate(playerA, 1477, 0.5)));
			cout << "Player A draws with a player rated 1477. Their new elo is " << playerA << "\n";

			playerA = (int)round(get<0>(EloEvaluate(playerA, 1388, 1)));
			cout << "Player A wins against a player rated 1388. Their new elo is " << playerA << "\n";

			playerA = (int)round(get<0>(EloEvaluate(playerA, 1586, 1)));
			cout << "Player A wins against a player rated 1586. Their new elo is " << playerA << "\n";

			playerA = (int)round(get<0>(EloEvaluate(playerA, 1720, 0)));
			cout << "Player A loses to a player rated 1720. Their new elo is " << playerA << "\n";

		}
	};
}
