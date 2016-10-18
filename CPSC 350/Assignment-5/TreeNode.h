#ifndef TREENODE_H
#define TREENODE_H

#include <iostream>

using namespace std;

template<class T>
class TreeNode
{
	public:
	TreeNode();
	TreeNode(T k);
	virtual ~TreeNode(); //W HYYYYYYY
	T key;
	T value;
	TreeNode<T>* left;
	TreeNode<T>* right;
};


template <class T>
TreeNode<T>::TreeNode()
{
	left = NULL;
	right = NULL;
}


template <class T>
TreeNode<T>::TreeNode(T k)
{
	left = NULL;
	right = NULL;
	key = k;
}


template <class T>
TreeNode<T>::~TreeNode()
{
	// add anything here????
}
#endif