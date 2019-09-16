#include "Node.h"

#include <iomanip>

void Node::addChild(Node *node)
{
	if (node->parent != nullptr)
		return Log::e(name, "Can't attach node with existent parent");
	
	if (node == this)
		return Log::e(name, "Can't attach node to itself");

	
	children.push_back(node);
	node->parent = this;
	
}

void Node::recursivePrint(int depth) const
{
	for (int i = 0; i < depth; i++)
		Log::d_ost << "    ";
	Log::d_ost << '[' << name << "]\n";
	
	for (Node * child : children)
		child->recursivePrint(depth + 1);
}


Node::~Node()
{
	for (Node * child : children)
		delete child;
}

void Node::autoName()
{
	NodeType *type = this->getType();
	name = getType()->name + std::to_string(type->count++);
}