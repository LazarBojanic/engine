#pragma once

#include "Util.hpp"

class IndexBuffer {
private:
	unsigned int iboID;

public:
	IndexBuffer();
	IndexBuffer(unsigned int* rawIndexData, unsigned int rawIndexDataCount, unsigned int rawIndexDataSize);
	~IndexBuffer();
	void uploadData(unsigned int* rawIndexData, unsigned int rawIndexDataCount, unsigned int rawIndexDataSize);
	void bind();

	void unbind();


	unsigned int getIboID() {
		return this->iboID;
	}
};
