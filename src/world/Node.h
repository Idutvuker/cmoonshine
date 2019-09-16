#pragma once

#include <list>

#include "NodeType.h"
#include "../util/Logger.h"


class Node
{
	MACRO_NODE_DECL()
	
private:
	Node * parent = nullptr;

public:
	std::list<Node *> children = std::list<Node *>();

	std::string name;
	
	template<typename Base>
	Base * instanceOf()
	{
		if (getType()->instanceOf(&Base::TYPE))
			return static_cast<Base *>(this);
		return nullptr;
	}

	void addChild(Node * node);
	
	void recursivePrint(int depth = 0) const;

	virtual ~Node();
	
	void autoName();
};



