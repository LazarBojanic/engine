#include "InstanceBuffer.hpp"

InstanceBuffer::InstanceBuffer() {
	glGenBuffers(1, &this->vboID);
}

InstanceBuffer::~InstanceBuffer() {
	glDeleteBuffers(1, &this->vboID);
}

void InstanceBuffer::upload(const void* data, std::size_t sizeInBytes) {
	this->bind();
	glBufferData(GL_ARRAY_BUFFER, static_cast<GLsizeiptr>(sizeInBytes), data, GL_DYNAMIC_DRAW);
}

void InstanceBuffer::bind() {
	glBindBuffer(GL_ARRAY_BUFFER, this->vboID);
}

void InstanceBuffer::unbind() {
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
