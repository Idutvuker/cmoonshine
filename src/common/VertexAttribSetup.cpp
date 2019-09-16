#include "VertexAttribSetup.h"
#include "../util/Logger.h"

VertexAttribSetup::VertexAttribSetup(const std::vector<VertexDataType> &dataTypes, bool batched) :
		setup(dataTypes.size()),
		batched(batched)
{
	int offset = 0;
	
	for (int i = 0; i < dataTypes.size(); i++) {
		const VertexDataType &type = dataTypes[i];
		
		setup[i].index = i;
		setup[i].size = type.getSize();
		setup[i].type = type.getGLType();
		setup[i].offset = offset;
		
		offset += type.getSize() * type.getGLTypeSize();
	}
	
	for (auto &attrib : setup)
		attrib.stride = offset;
}

int VertexAttribSetup::getVertexSize() const
{
	int size = 0;
	for (auto &attrib : setup)
		size += attrib.size;
	return size;
}
