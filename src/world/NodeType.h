#pragma once

#include "../util/Logger.h"
#include <vector>

	
class NodeType
{
	typedef unsigned int bitset;

	static bitset CLASSID;
	
	bitset count = 0;
	
	NodeType(unsigned int _id, unsigned int _genes, const std::string &name);

public:
	const bitset id;
	const bitset genes;
	const std::string name;
	
	NodeType(const NodeType &) = delete;
	NodeType &operator=(const NodeType &) = delete;
	
	NodeType(bitset _genes, const std::string &name);
	
	bool instanceOf(NodeType *other) const;
	
	friend class Node;
};



#define MACRO_NODE_DECL() \
public: \
	static NodeType TYPE; \
	virtual NodeType* getType();


#define MACRO_FIRST_NODE_IMPL(Derived) \
	NodeType Derived::TYPE{0, #Derived}; \
	NodeType* Derived::getType() { \
		return &Derived::TYPE; \
	}
	
#define MACRO_NODE_IMPL(Derived, Base) \
	NodeType Derived::TYPE{Base::TYPE.genes, #Derived}; \
	NodeType* Derived::getType() { \
		return &Derived::TYPE; \
	}