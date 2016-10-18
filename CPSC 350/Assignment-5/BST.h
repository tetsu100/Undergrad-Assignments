#ifndef BST_H
#define BST_H

#include "TreeNode.h"
#include "Faculty.h"
#include "Student.h"
#include <iomanip>
using namespace std;

template <class T>
class BST
{
	public:
		BST();
		virtual ~BST(); // WHY WHY WHY
		void insert(T value);
		bool contains(T value);
		T* find(T value);
		bool isEmpty();
		T* getMax();
		T* getMin();
		TreeNode<T>* getSuccessor(TreeNode<T>* d);
		void recPrint(TreeNode<T>* node);
		void printTree();
		bool deleteNode(T k);
		TreeNode<T>* getRoot();
		void copyf(BST<Faculty> &ftree, TreeNode<T>* p);
		void copys(BST<Student> &stree, TreeNode<T>* p);
		void postorder(TreeNode<T>* p, int indent=0);

		TreeNode<T>* root;
};

template <class T>
T* BST<T>::find(T value)
{
	if(root == NULL)
	{
		cout << "root is null" << endl;
		return NULL;
	}
	TreeNode<T>* current = root;


	while(value != current->key)
	{	
		if(value < current->key)
			current = current->left;
		else
			current = current->right;

	if (current == NULL)
		return NULL;
	}

	cout << "returning something" << endl;

	return &current->key;
}


template <class T>
TreeNode<T>* BST<T>::getRoot()
{
	return root;
}

template <class T>
BST<T>::BST()
{
	root = NULL;
}

template <class T>
BST<T>::~BST()
{
	// iterate and delete 
	// will be linear
}

template <class T>
void BST<T>::printTree()
{
	recPrint(root);
}

template <class T>
void BST<T>::recPrint(TreeNode<T>* node)
{
	if(node == NULL)
		return;
	
	recPrint(node->left);
	node->key.printDetails();
	recPrint(node->right);
	cout << endl;
}

template <class T>
void BST<T>::copyf(BST<Faculty> &ftree, TreeNode<T>* p){
	if(p != NULL) {
        if(p->right) {
            copyf(ftree,p->right);
        }

		ftree.insert(p->key);
		
        if(p->left) {
            copyf(ftree,p->left);
        }
    }
}

template <class T>
void BST<T>::copys(BST<Student> &stree, TreeNode<T>* p){
	if(p != NULL) {
        if(p->right) {
            copys(stree,p->right);
        }

		stree.insert(p->key);
		
        if(p->left) {
            copys(stree,p->left);
        }
    }
}

template <class T>
void BST<T>::postorder(TreeNode<T>* p, int indent)
{
    if(p != NULL) {
        if(p->right) {
            postorder(p->right, indent+4);
        }
        if (indent) {
            std::cout << std::setw(indent) << ' ';
        }
        if (p->right) std::cout<<" /\n" << std::setw(indent) << ' ';
			p->key.printDetails();
        if(p->left) {
            std::cout << std::setw(indent) << ' ' <<" \\\n";
            postorder(p->left, indent+4);
        }
    }
}

template <class T>
T* BST<T>::getMax()
{
	TreeNode<T>* current = root;

	if(root == NULL)
		return NULL;

	while(current->right != NULL)
	{
		current = current->right; 
	}

	return current->key;
}


template <class T>
T* BST<T>::getMin()
{
	TreeNode<T>* current = root;

	if(root == NULL)
		return NULL;

	while(current->left != NULL)
	{
		current = current->left; 
	}

	return &(current->key);
}


template <class T>
void BST<T>::insert(T value)
{
	TreeNode<T>* node = new TreeNode<T>(value);
	if(root == NULL)
	{
		root = node;
	}
	else
	{
		TreeNode<T>* current = root;
		TreeNode<T>* parent; // empty

		while(true)
		{
			parent = current;
			if (value < current->key)
			{
				current = current->left;

				if(current == NULL)
				{
					parent->left = node;
					break;
				}
			}

			else
			{
				current = current->right;
				if (current == NULL)
				{
					parent->right = node;
					break;
				}
			}
		}
	}
}


template <class T>
bool BST<T>::contains(T value)
{
	
	if(root == NULL)
		return false;
	else
	{
		TreeNode<T>* current = root;
		while(value != current->key)
		{
			if(value < current->key)
				current = current->left;
			else
				current = current->right;

		if (current == NULL)
			return false;
		}
	}

	return true;
}




// the left most of the right, or the right

template <class T>
TreeNode<T>* BST<T>::getSuccessor(TreeNode<T>* d)
{
	TreeNode<T>* sp = d; // successor ka parent
	TreeNode<T>* successor = d;
	TreeNode<T>* current = d->right;

	while(current != NULL)
	{
		sp = successor;
		successor = current;
		current = current->left;
	}

	if(successor != d->right)
	{
		sp->left = successor->right;
		successor-> right = d->right;
		
	}

	return successor;
}


template <class T>
bool BST<T>::deleteNode(T k)
{
	if(root == NULL) // empty tree
		return false;

	TreeNode<T> *current = root;
	TreeNode<T> *parent = root;
	bool isLeft = true;

	while(current->key != k)
	{
		parent = current;
		if(k < current->key)
		{
			isLeft = true;
			current = current->left;
		}
		else
		{
			isLeft = false;
			current = current->right;
		}

		if(current == NULL)
			return false;
	}


	// if leaf node, no children

	if(current->left == NULL && current->right == NULL)
	{
		if(current == root)
			root = NULL;
		else if(isLeft)
			parent->left = NULL;
		else
			parent->right = NULL;
	}

	// has left child, but no right child
	if(current->right == NULL)
	{
		if(current == root)
			root = current->left;
		else if(isLeft)
			parent->left = current->left;
		else
			parent->right = current->left;

		
		return true;
	}

	// has right child, but no left child
	if(current->left == NULL)
	{
		if(current == root)
			root = current->right;
		else if(isLeft)
			parent->left = current->right;
		else
			parent->right = current->right;


		return true;
	}
	else // 2 children
	{
		TreeNode<T> *successor = getSuccessor(current);
		// connect or link, parent of current to successor
		// check is left
		// check is right
		// then link successor to current's left child

		parent->left = successor;
		successor->left = current->left;

		return true;
	}

}
#endif