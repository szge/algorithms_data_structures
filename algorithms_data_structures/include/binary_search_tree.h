#pragma once
#include <iostream>
#include <string>
#include <typeinfo>

namespace alg {
	template <typename KeyT, typename ValueT>
	class BST {
	private:
		class BSTKeyNotFoundException : public std::exception {
		public:
			virtual const char* what() const throw() {
				return "key not found";
			}
		} exception_key_not_found;

		struct treeNode {
			KeyT key;
			ValueT value;
			treeNode* left;
			treeNode* right;
		};

	// member variables
	private:
		treeNode* m_root;

	// methods
	private:
		void destruct(treeNode* node) {
			if (node == nullptr) return;

			// post order traversal
			destruct(node->left);
			destruct(node->right);
			delete node;
		}

		std::string toString(const treeNode* node, const int indent) {
			if (node == nullptr) return "";

			std::string str;
			for (int i = 0; i < indent; i++) str += " ";
			str += std::to_string(node->key) + ", " + std::to_string(node->value) + "\n";
			if (node->left != nullptr) {
				for (int i = 0; i <= indent; i++) str += " ";
				str += toString(node->left, indent + 1);
			}
			if (node->right != nullptr) {
				for (int i = 0; i <= indent; i++) str += " ";
				str += toString(node->right, indent + 1);
			}
			return str;
		}

		/* Returns the value corresponding to the given key
		* @return the corresponding value
		*/
		treeNode* find(const KeyT& key) {
			treeNode* node = m_root;
			while (node != nullptr && key != node->key) {
				if (key < node->value) {
					node = node->left;
				}
				else {
					node = node->right;
				}
			}

			return node;
		}

		/* Finds the minimum node belonging to the tree starting at <node>
		*/
		treeNode* minimum(treeNode* node) {
			while (node->left != nullptr) {
				node = node->left;
			}

			return node;
		}

		/* Finds the parent node of a given node. <node> should be a valid node in the tree
		* @return the parent node of <node>, nullptr if <node> is m_root
		*/
		treeNode* getParent(treeNode* node) {
			treeNode* current = m_root;
			treeNode* previous = nullptr;
			while (current != nullptr && current != node) {
				previous = current;
				if (node->key < current->key) {
					current = current->left;
				}
				else {
					current = current->right;
				}
			}

			return previous;
		}

	public:
		BST() {
			m_root = nullptr;
		}

		~BST() {
			destruct(m_root);
		}

		void insert(const KeyT& key, const ValueT& value) {
			// make a new node
			treeNode* newNode = new treeNode;
			newNode->key = key;
			newNode->value = value;
			newNode->left = nullptr;
			newNode->right = nullptr;

			// traverse through the tree keeping track of the current and previous nodes
			treeNode* current = m_root;
			treeNode* previous = nullptr;
			while (current != nullptr) {
				previous = current;
				if (key < current->key) {
					current = current->left;
				}
				else {
					current = current->right;
				}
			}
			
			// insert the new node
			if (previous == nullptr) {
				// tree is empty so make a new root
				m_root = newNode;
			}
			else if (key < previous->key) {
				previous->left = newNode;
			}
			else {
				previous->right = newNode;
			}
		}

		/* Return the value corresponding to a given key
		* Note: throws an error if the key is not found
		*/
		ValueT getValue(const KeyT& key) {
			treeNode* node = find(key);

			if (node == nullptr) {
				throw exception_key_not_found;
			}

			return node->value;
		}

		bool deleteKey(const KeyT& key) {
			treeNode* node = find(key);
			
			if (node == nullptr) return false;

			treeNode* parent = getParent(node);

			if (node->left == nullptr) {
				// case: there are no children or there is only a right child
				if (node == m_root) {
					m_root = node->right;
				}
				else if (node == parent->left) {
					parent->left = node->right;
				}
				else {
					parent->right = node->right;
				}

				delete node;
			}
			else if (node->right == nullptr) {
				// case: there is only a left child
				if (node == m_root) {
					m_root = node->left;
				}
				else if (node == parent->left) {
					parent->left = node->left;
				}
				else {
					parent->right = node->left;
				}

				delete node;
			}
			else {
				// case: there are two children
				// RE: https://en.wikipedia.org/wiki/Binary_search_tree#Deletion

				// new base = minimum from right subtree
				treeNode* newRoot = minimum(node->right);

				// copy values from newRoot to the root node
				node->key = newRoot->key;
				node->value = newRoot->value;

				// find newRoot's parent and replace newRoot with newRoot's right child
				// (it can only have right children)
				treeNode* parent = getParent(newRoot);

				if (newRoot->key < parent->key) {
					// newRoot used to be a left child so replace itself with its children
					parent->left = newRoot->right;
				}
				else {
					parent->right = newRoot->right;
				}

				delete newRoot;
			}
			return true;
		}

		std::string toString() {
			return toString(m_root, 0);
		}
	};
}