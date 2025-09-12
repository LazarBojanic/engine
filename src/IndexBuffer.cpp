#include "IndexBuffer.hpp"

IndexBuffer::IndexBuffer() {
	glGenBuffers(1, &this->iboID);
}
IndexBuffer::IndexBuffer(unsigned int* rawIndexData, unsigned int rawIndexDataCount, unsigned int rawIndexDataSize) {
	glGenBuffers(1, &this->iboID);
	this->uploadData(rawIndexData, rawIndexDataCount, rawIndexDataSize);
}
IndexBuffer::~IndexBuffer() {
	glDeleteBuffers(1, &this->iboID);
}
void IndexBuffer::uploadData(unsigned int* rawIndexData, unsigned int rawIndexDataCount, unsigned int rawIndexDataSize) {
	this->bind();
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, rawIndexDataSize, rawIndexData, GL_STATIC_DRAW);
}

void IndexBuffer::bind() {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->iboID);
}

void IndexBuffer::unbind() {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
