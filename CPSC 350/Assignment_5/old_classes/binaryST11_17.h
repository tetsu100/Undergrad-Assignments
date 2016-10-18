#ifndef BINARYST_H
#define BINARYST_H
#include <iostream>
#include <string>

using namespace std;

template <typename T>
class treeNode
{
public:
	treeNode<T>* left;
	treeNode<T>* right;
	T data;
	treeNode(T d)
	{
		left = NULL;
		right = NULL;
		data = d;
	}
	~treeNode()
	{

	}
};

template <typename T>
class binaryST
{
public:
	treeNode<T>* root;
	int size;
	string serialBST;
	bool search(T d);
	T searchData(T d);
	bool remove(T _data);
	treeNode<T>* getSuccessor(treeNode<T>* d);
	T getMin();
	T getMax();
	void printTree();
	void printTreeHelper(treeNode<T>* r);
	void insert(T d);
	void insertHelper(T d, treeNode<T>*& current);
	void serialize();
	void serializeHelper(treeNode<T>* r);
	binaryST()
	{
		serialBST = "UNSERIALIZED";
		root = NULL;
	}
	~binaryST()
	{
		//deallocate memory??
	}
};

template <typename T>
void binaryST<T>::serialize()
{
	if(root != NULL)
	{
		serialBST = "";
		serializeHelper(root);
	}
}

template <typename T>
void binaryST<T>::serializeHelper(treeNode<T>* r)
{
	if(r->left != NULL)
	{
		serializeHelper(r->left);
	}
	if(r != NULL)
	{
		serialBST += r->data.toSerial();
	}
	if(r->right != NULL)
	{
		serializeHelper(r->right);
	}
}

template <typename T>
bool binaryST<T>::search(T d)
{
	bool exists = false;
	treeNode<T>* current = root;
	while(current != NULL)
	{
		if(d > current->data)
		{
			current = current->right;
		}
		else if(d < current->data)
		{
			current = current->left;
		}
		else
		{
			exists = true;
			break;
		}
	}
	return exists;
}

template <typename T>
T binaryST<T>::searchData(T d)
{
	treeNode<T>* current = root;
	T dReturn = d;
	while(current != NULL)
	{
		if(d > current->data)
		{
			current = current->right;
		}
		else if(d < current->data)
		{
			current = current->left;
		}
		else
		{
			dReturn = current->data;
			break;
		}
	}
	return dReturn;
}

template <typename T>
T binaryST<T>::getMin()
{
	treeNode<T>* current = root;
	while(current != NULL)
	{
		current = current->left;
	}
	return current->data;
}

template <typename T>
T binaryST<T>::getMax()
{
	treeNode<T>* current = root;
	while(current != NULL)
	{
		current = current->right;
	}
	return current->data;
}

template <typename T>
void binaryST<T>::printTree()
{
	if(root != NULL)
	{
		printTreeHelper(root);
	}
}

template <typename T>
void binaryST<T>::printTreeHelper(treeNode<T>* r)
{
	if(r->left != NULL)
	{
		printTreeHelper(r->left);
	}
	if(r != NULL)
	{
		cout << r->data << endl;
	}
	if(r->right != NULL)
	{
		printTreeHelper(r->right);
	}
}

template <typename T>
void binaryST<T>::insert(T d)
{
	++size;

	insertHelper(d, root);
}

template <typename T>
void binaryST<T>::insertHelper(T d, treeNode<T>*& current)
{
	if(current == NULL)
	{
		current = new treeNode<T>(d);
	}
	else if (d < current->data)
	{
		insertHelper(d, current->left);
			
	}
	else
	{
		insertHelper(d, current->right);
	}
}

template <typename T>
bool binaryST<T>::remove(T _data)
{
	if (root == NULL) 
        return false;
                            
    treeNode<T>* current = root;
    treeNode<T>* parent = root;
    bool isLeft = true;

    while(current->data != _data)
    {    
        parent = current;
        if(_data < current->data)
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

    //no children – this would be nice
    if(current->left==NULL && current->right==NULL)
    {
        if(current == root)
            root = NULL;                 
        else if(isLeft)
            parent->left = NULL;
        else                            
            parent->right = NULL;
    }
     
    //one child – still not too bad
    // no right child, replace with left subtree
    else if(current->right==NULL)
    {
        if(current == root) 
            root = current->left;
        else if(isLeft)
            parent->left = current->left;
        else
            parent->right = current->left;
    }
    // no left child, replace with right subtree
    else if(current->left==NULL)
    {
        if(current == root)
            root = current->right;
        else if(isLeft)
            parent->left = current->right;
        else
            parent->right = current->right;
    }
    else
    {
        treeNode<T>* successor = getSuccessor(current);

        // connect parent of current to successor
        if(current == root)
            root = successor;
        else if(isLeft)
            parent->left = successor;
        else
            parent->right = successor;

        // connect successor to current's left child
        successor->left = current->left;
    }
   	size--;
   	return true;  
}

template <typename T>
treeNode<T>* binaryST<T>::getSuccessor(treeNode<T>* d)
{
   treeNode<T>* sp = d;
   treeNode<T>* successor = d;
   treeNode<T>* current = d->right;
   while(current != NULL)
   {                             
      sp = successor;
      successor = current;
      current = current->left;
   }
                                        
   if(successor != d->right)
   {
      sp->left = successor->right;
      successor->right = d->right;
   }
   return successor;
}

#endif