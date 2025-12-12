#include "VertexArray.hpp"

VertexArray::VertexArray() {
	glGenVertexArrays(1, &this->vaoID);
}

VertexArray::~VertexArray() {
	glDeleteVertexArrays(1, &this->vaoID);
}

void VertexArray::bind() {
	glBindVertexArray(this->vaoID);
}

void VertexArray::unbind() {
	glBindVertexArray(0);
}
