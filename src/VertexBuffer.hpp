#pragma once
#include "GeometryVertex.hpp"

class VertexBuffer {
private:
	unsigned int vboID;

public:
	VertexBuffer();
	VertexBuffer(GeometryVertex* structuredVertexData, unsigned int structuredVertexDataCount, unsigned int structuredVertexDataSize);
	~VertexBuffer();
	void uploadData(GeometryVertex* structuredVertexData, unsigned int structuredVertexDataCount, unsigned int structuredVertexDataSize);
	void bind();
	void unbind();

	unsigned int getVboID() {
		return this->vboID;
	}
};
