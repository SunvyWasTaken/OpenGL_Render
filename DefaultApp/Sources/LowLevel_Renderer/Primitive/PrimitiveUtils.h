#pragma once

#define LOAD_VERTEX_ARRAYS(vao) \
	glGenVertexArrays(1, &vao); \
	glBindVertexArray(vao);

#define LOAD_ARRAY_BUFFER(vbo, vertices, vertex_type) \
	glGenBuffers(1, &vbo); \
	glBindBuffer(GL_ARRAY_BUFFER, vbo); \
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(vertex_type), vertices.data(), GL_STATIC_DRAW);

#define LOAD_ELEMENT_ARRAY_BUFFER(ebo, indices) \
	glGenBuffers(1, &ebo); \
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo); \
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), indices.data(), GL_STATIC_DRAW);

#define LOAD_BASIC_VERTEX_ATTRIB_POINTER() \
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertex_type), 0); \
	glEnableVertexAttribArray(0); \
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(vertex_type), reinterpret_cast<char*>(nullptr) + sizeof(vertex_type::m_point)); \
	glEnableVertexAttribArray(1); \
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(vertex_type), reinterpret_cast<char*>(nullptr) + sizeof(vertex_type::m_point) + sizeof(vertex_type::m_color)); \
	glEnableVertexAttribArray(2);