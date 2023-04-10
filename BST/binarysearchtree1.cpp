#include <iostream>
#include <limits>
#include <queue>
#include <algorithm> // for max
using namespace std;

struct Node {
	Node *parent, *left, *right;
	int depth, data;

	Node(int depth, int data) :
		parent{nullptr}, left{nullptr}, right{nullptr},
		depth{depth}, data(data) { }

	Node(Node *parent, int depth, int data) :
		parent{parent}, left{nullptr}, right{nullptr},
		depth{depth}, data{data} { }
};

// O(tree height) (and the tree height is O(n))
Node* insert_helper(Node **proot, int x, Node *parent, int depth) {
	if(*proot == nullptr) {
		return *proot = new Node(parent, depth, x);
	}
	if((*proot)->data == x) {
		return nullptr;
	}
	if(x < (*proot)->data) {
		return insert_helper(&(*proot)->left, x, *proot, depth + 1);
	} else {
		return insert_helper(&(*proot)->right, x, *proot, depth + 1);
	}
}

Node* insert(Node **proot, int x) {
	return insert_helper(proot, x, nullptr, 0);
}

// Θ(n)
void display_sideways(Node *node) {
	if(node != nullptr) {
		display_sideways(node->right);
		if(node->depth == 0) {
			cout << "-> ";
		} else {
			cout << "   ";
		}
		for(int i = 0; i < node->depth; ++i) {
			cout << "   ";
		}
		cout << node->data << endl;
		display_sideways(node->left);
	}
}

// O(tree height) (and the tree height is O(n))
Node* find(Node *root, int x) {
	if(root == nullptr) {
		return nullptr;
	}
	if(root->data == x) {
		return root;
	}
	if(x < root->data) {
		return find(root->left, x);
	} else {
		return find(root->right, x);
	}
}

// Sum all integers in the BST
// Θ(n)
int sum(Node *root) {
	if(root == nullptr) {
		return 0;
	} else {
		return root->data + sum(root->left) + sum(root->right);
	}
}

// Θ(n)
void decrement_depths(Node *root) {
	if(root) {
		root->depth--;
		decrement_depths(root->left);
		decrement_depths(root->right);
	}
}

// Deletes and returns as result the minimum node in the non-empty tree.
// Since the tree is non-empty, such minimum node must exist.
// This code is similar to findMin except that we do not have to test
// the Null case since we know that the tree is non-empty.
// O(tree height) (and the tree height is O(n))
Node *delete_min(Node **proot) {
	if((*proot)->left == nullptr) {
		// root is the minimum node, remove it from the tree and return it
		Node *min = *proot;
		decrement_depths((*proot)->right);
		*proot = (*proot)->right;
		return min;
	} else {
		// Keep moving down-left
		return delete_min(&(*proot)->left);
	}
}

// O(tree height) (and the tree height is O(n))
bool delete_node(Node **proot, int x){
	if(*proot == nullptr) {
		// Cannot find x, deletion fails
		return false;
	}
	if((*proot)->data == x) {
		// Case 1: the node is a leaf
		// Note: this case is in fact a special case of the next one (case 2-a
		// or case 2-b) so this code could be merged with the next case.
		// We keep this case separate here for clarity.
		if((*proot)->left == nullptr && (*proot)->right == nullptr) {
			delete *proot;
			*proot = nullptr;
			return true;
		}
		// Case 2-a: the node has one left child
		if((*proot)->left != nullptr && (*proot)->right == nullptr) {
			Node *tmp = *proot;
			decrement_depths((*proot)->left);
			*proot = (*proot)->left;
			delete tmp;
			return true;
		}
		// Case 2-b: the node has one right child
		if((*proot)->left == nullptr && (*proot)->right != nullptr) {
			Node *tmp = *proot;
			decrement_depths((*proot)->right);
			*proot = (*proot)->right;
			delete tmp;
			return true;
		}
		// Case 3: the node has two children
		// We replace the root with the minimum node in the right subtree
		// (The maximum node in the left subtree would work too.)
		if((*proot)->left != nullptr && (*proot)->right != nullptr) {
			Node *tmp = *proot;
			// Find the smallest node in the right subtree:
			Node *min = delete_min(&(*proot)->right);
			// Replace the root with the min:
			min->parent = (*proot)->parent;
			min->depth = (*proot)->depth;
			min->left = (*proot)->left;
			min->right = (*proot)->right;
			*proot = min;
			delete tmp;
			return true;
		}
	}
	if((*proot)->data > x) {
		return delete_node(&(*proot)->left, x);
	} else {
		return delete_node(&(*proot)->right, x);
	}
}

// Θ(n)
void delete_bst(Node *root) {
	if(root != nullptr) {
		delete_bst(root->left);
		delete_bst(root->right);
		delete root;
	}
}

// Create a balanced BST from a sorted array.
// Θ(n)
Node* create_bst_helper(int data[], int low, int high, Node *parent, int depth) {
	if(low > high) {
		return nullptr;
	}
	int mid = low + (high - low) / 2;
	Node *new_node = new Node(parent, depth, data[mid]);
	new_node->left = create_bst_helper(data, low, mid - 1, new_node, depth + 1);
	new_node->right = create_bst_helper(data, mid + 1, high, new_node, depth + 1);
	return new_node;
}

Node* create_bst(int data[], int length) {
	return create_bst_helper(data, 0, length - 1, nullptr, 0);
}

int main(int argc, const char *argv[]) {

	int data[10] = {11, 18, 19, 20, 24, 25, 67, 68, 69, 93};
	Node *bst2 = create_bst(data, 15);
	display_sideways(bst2);

	delete_bst(bst2);
	return 0;
}
