#include "VertexBuffer.hpp"


VertexBuffer::VertexBuffer() {
	glGenBuffers(1, &this->vboID);
}

VertexBuffer::VertexBuffer(GeometryVertex* structuredVertexData, unsigned int structuredVertexDataCount, unsigned int structuredVertexDataSize) {
	glGenBuffers(1, &this->vboID);
	this->uploadData(structuredVertexData, structuredVertexDataCount, structuredVertexDataSize);
}


void VertexBuffer::uploadData(GeometryVertex* structuredVertexData, unsigned int structuredVertexDataCount, unsigned int structuredVertexDataSize) {
	unsigned int stride = sizeof(GeometryVertex);
	this->bind();
	glBufferData(GL_ARRAY_BUFFER, structuredVertexDataSize, structuredVertexData, GL_STATIC_DRAW);

	glEnableVertexAttribArray(Util::LAYOUT_LOCATION_POSITION);
	glVertexAttribPointer(Util::LAYOUT_LOCATION_POSITION, Util::DIMENSIONS_POSITION, GL_FLOAT, GL_FALSE, stride, (void*)offsetof(GeometryVertex, position));

	glEnableVertexAttribArray(Util::LAYOUT_LOCATION_COLOR);
	glVertexAttribPointer(Util::LAYOUT_LOCATION_COLOR, Util::DIMENSIONS_COLOR, GL_FLOAT, GL_FALSE, stride, (void*)offsetof(GeometryVertex, color));

	glEnableVertexAttribArray(Util::LAYOUT_LOCATION_UV);
	glVertexAttribPointer(Util::LAYOUT_LOCATION_UV, Util::DIMENSIONS_UV, GL_FLOAT, GL_FALSE, stride, (void*)offsetof(GeometryVertex, uv));

	glEnableVertexAttribArray(Util::LAYOUT_LOCATION_NORMAL);
	glVertexAttribPointer(Util::LAYOUT_LOCATION_NORMAL, Util::DIMENSIONS_NORMAL, GL_FLOAT, GL_FALSE, stride, (void*)offsetof(GeometryVertex, normal));

	glEnableVertexAttribArray(Util::LAYOUT_LOCATION_TANGENT);
	glVertexAttribPointer(Util::LAYOUT_LOCATION_TANGENT, Util::DIMENSIONS_TANGENT, GL_FLOAT, GL_FALSE, stride, (void*)offsetof(GeometryVertex, tangent));

	glEnableVertexAttribArray(Util::LAYOUT_LOCATION_BITANGENT);
	glVertexAttribPointer(Util::LAYOUT_LOCATION_BITANGENT, Util::DIMENSIONS_BITANGENT, GL_FLOAT, GL_FALSE, stride, (void*)offsetof(GeometryVertex, bitangent));

	glEnableVertexAttribArray(Util::LAYOUT_LOCATION_BONE_IDS);
	glVertexAttribPointer(Util::LAYOUT_LOCATION_BONE_IDS, Util::DIMENSIONS_BONE_IDS, GL_FLOAT, GL_FALSE, stride, (void*)offsetof(GeometryVertex, boneIds));

	glEnableVertexAttribArray(Util::LAYOUT_LOCATION_WEIGHTS);
	glVertexAttribPointer(Util::LAYOUT_LOCATION_WEIGHTS, Util::DIMENSIONS_WEIGHTS, GL_FLOAT, GL_FALSE, stride, (void*)offsetof(GeometryVertex, weights));
}


VertexBuffer::~VertexBuffer() {
	glDeleteBuffers(1, &this->vboID);
}

void VertexBuffer::bind() {
	glBindBuffer(GL_ARRAY_BUFFER, this->vboID);
}

void VertexBuffer::unbind() {
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
