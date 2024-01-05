#include <bits/stdc++.h>
using namespace std;

// An AVL tree node
class node {
	public:
		int key;
		node* left, *right;
};

node* newNode(int key) {
	node* Node = new node();
	Node->key = key;
	Node->left = Node->right = NULL;
	return Node;
}

node* rightRotate(node* x) {
	node* y = x->left;
	x->left = y->right;
	y->right = x;
	return y;
}

node* leftRotate(node* x) {
	node* y = x->right;
	x->right = y->left;
	y->left = x;
	return y;
}

node* splay(node* root, int key) {
	
	// Base Case
	if(root == NULL || root->key  == key) {
		return root;
	}
	
	// Key lies in left subtree
	if(root->key > key) {
		
		if(root->left == NULL) return root;
		
		// Zig-Zig
		if(root->left->key > key) {
			root->left->left = splay(root->left->left, key);
			
			root = rightRotate(root);
		}
		
		// Zig-Zag
		else if(root->left->key < key) {
			
			root->left->right = splay(root->left->right, key);
			
			if(root->left->right != NULL) {
				root->left = leftRotate(root->left);
			}
		}
		
		return (root->left == NULL) ? root : rightRotate(root);
	} else {
		// Key lies in right subtree
		
		if(root->right == NULL) return root;
		
		// Zag-Zig (Right Left Case)
		if (root->right->key > key) {
			root->right->left = splay(root->right->left, key);
			
			if(root->right->left != NULL) {
				root->right = rightRotate(root->right);
			}
		} 
		
		// Zag Zag Case
		else if(root->right->key < key) {
			root->right->right = splay(root->right->right, key);
			
			root = leftRotate(root);
		}
		
		return (root->right == NULL) ? root : leftRotate(root);
	}
}

node* search(node* root, int key) {
	return splay(root, key);
}

node* insert(node* root, int k) {
	// Simple Case : If tree is empty
	if(root == NULL) return newNode(k);
	
	root = splay(root, k);
	
	// If key is already present, then return
	if (root->key == k) return root;
	
	node* newnode = newNode(k);
	
	// If root's key is greater, make
	// root as right child of newnode
	// and copy the left child of root to newnode
	if (root->key > k) {
		newnode->right = root;
		newnode->left = root->left;
		root->left = NULL;
	}
	
	//If root's key is smaller, make
	// root as left child of newnode
	// and copy the right child of root to newnode
	if (root->key < k) {
		newnode->left = root;
		newnode->right = root->right;
		root->right = NULL;
	}
	
	return newnode;
}


// Time Complexity - O(logn) on average, O(n) on worst
// Space Complexity - O(nlogn) on average

//Applications
/*
Used in Windows NT (in virtual memory, networking, and file system code).
the gcc compiler, and gnu c++ library




*/