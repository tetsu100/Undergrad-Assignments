#ifndef GENSTACK_H
#define GENSTACK_H

template <class genType>
class GenStack
{
private:
		int sizeStack;
		int top;
		genType *genStackPtr;

public:
	GenStack(const int);
	~GenStack(){ delete genStackPtr; }
	genType peek();
	bool push(const genType&);
	bool pop(genType&);
	bool empty();
	int getSize();
	void resize();
};

#endif