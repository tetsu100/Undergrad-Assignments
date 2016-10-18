#include "StudentNode.h"

//StudentNode::StudentNode(){}

StudentNode::StudentNode() // parameters for student object
{
	next = NULL;
	prev = NULL;
}

StudentNode::~StudentNode() // desctructor
{
	next = NULL;
	prev = NULL;
}
