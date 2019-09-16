#include "NodeType.h"


NodeType::bitset NodeType::CLASSID = 0;

bool NodeType::instanceOf(NodeType *other) const {
	return ((1u << other->id) & genes) != 0;
}

NodeType::NodeType(unsigned int _id, unsigned int _genes, const std::string &_name) : name(_name), id(_id), genes(_genes) {++CLASSID;}

NodeType::NodeType(bitset _genes, const std::string &_name) :
		NodeType(CLASSID, _genes | (1u << CLASSID), _name)
{};


