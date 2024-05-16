#pragma once

#include "PrimitiveUtils.h"
#include "Vertex.h"
#include "Math/Transform.h"

#include <glad/glad.h>
#include <array>

#include "PrimitiveMesh.h"


template <typename Type>
class Cube : public PrimitiveMesh<Type>
{
	using vertex_type = Vertex<Type>;
	using Transform = Math::Transform<Type>;
	using parent = PrimitiveMesh<Type>;

public:
	Cube();
	~Cube();

	void load() override;
	void render(ContextRenderer& contextRenderer) override;
};

template <typename Type>
Cube<Type>::Cube()
	: parent()
{
}

template <typename Type>
Cube<Type>::~Cube()
{
}

template <typename Type>
void Cube<Type>::load()
{
	std::array<vertex_type, 24> vertices = {
		//Front
		vertex_type({ -1.f,	1.f,	 1.f }, { 1.0f,	1.0f,	1.0f }, {  0.0f,		0.0f }, { 0.f, 0.f, 1.f} ),
		vertex_type({ -1.f,	-1.f,	 1.f }, { 1.0f,	1.0f,	1.0f }, {  0.0f,		1.0f }, { 0.f, 0.f, 1.f} ),
		vertex_type({  1.f,	-1.f,	 1.f }, { 1.0f,	1.0f,	1.0f }, {  1.0f,		1.0f }, { 0.f, 0.f, 1.f} ),
		vertex_type({  1.f,	1.f,	 1.f }, { 1.0f,	1.0f,	1.0f }, {  1.0f,		0.0f }, { 0.f, 0.f, 1.f} ),

		//Right
		vertex_type({ 1.f,		1.f,	 1.f }, { 1.0f,	1.0f,	1.0f }, {  0.0f,		0.0f }, { 1.f, 0.f, 0.f} ),
		vertex_type({ 1.f,		-1.f,	 1.f }, { 1.0f,	1.0f,	1.0f }, {  0.0f,		1.0f }, { 1.f, 0.f, 0.f} ),
		vertex_type({ 1.f,		-1.f,	-1.f }, { 1.0f,	1.0f,	1.0f }, {  1.0f,		1.0f }, { 1.f, 0.f, 0.f} ),
		vertex_type({ 1.f,		1.f,	-1.f }, { 1.0f,	1.0f,	1.0f }, {  1.0f,		0.0f }, { 1.f, 0.f, 0.f} ),

		//Back
		vertex_type({ -1.f,	-1.f,	-1.f }, { 1.0f,	1.0f,	1.0f }, {  0.0f,		0.0f }, { 0.f, 0.f, -1.f} ),
		vertex_type({ -1.f,	1.f,	-1.f }, { 1.0f,	1.0f,	1.0f }, {  0.0f,		1.0f }, { 0.f, 0.f, -1.f} ),
		vertex_type({  1.f,	1.f,	-1.f }, { 1.0f,	1.0f,	1.0f }, {  1.0f,		1.0f }, { 0.f, 0.f, -1.f} ),
		vertex_type({  1.f,	-1.f,	-1.f }, { 1.0f,	1.0f,	1.0f }, {  1.0f,		0.0f }, { 0.f, 0.f, -1.f} ),

		//Left
		vertex_type({ -1.f,	1.f,	-1.f }, { 1.0f,	1.0f,	1.0f }, {  0.0f,		0.0f }, { -1.f, 0.f, 0.f} ),
		vertex_type({ -1.f,	-1.f,	-1.f }, { 1.0f,	1.0f,	1.0f }, {  0.0f,		1.0f }, { -1.f, 0.f, 0.f} ),
		vertex_type({ -1.f,	-1.f,	 1.f }, { 1.0f,	1.0f,	1.0f }, {  1.0f,		1.0f }, { -1.f, 0.f, 0.f} ),
		vertex_type({ -1.f,	1.f,	 1.f }, { 1.0f,	1.0f,	1.0f }, {  1.0f,		0.0f }, { -1.f, 0.f, 0.f} ),

		//Top
		vertex_type({ -1.f,	1.f,	-1.f }, { 1.0f,	1.0f,	1.0f }, {  0.0f,		0.0f }, { 0.f, 1.f, 0.f} ),
		vertex_type({ -1.f,	1.f,	 1.f }, { 1.0f,	1.0f,	1.0f }, {  0.0f,		1.0f }, { 0.f, 1.f, 0.f} ),
		vertex_type({  1.f,	1.f,	 1.f }, { 1.0f,	1.0f,	1.0f }, {  1.0f,		1.0f }, { 0.f, 1.f, 0.f} ),
		vertex_type({  1.f,	1.f,	-1.f }, { 1.0f,	1.0f,	1.0f }, {  1.0f,		0.0f }, { 0.f, 1.f, 0.f} ),
																	
		vertex_type({ -1.f,	-1.f,	1.f },	{ 1.0f,	1.0f,	1.0f }, {  0.0f,		0.0f }, { 0.f, -1.f, 0.f} ),
		vertex_type({ -1.f,	-1.f,	-1.f }, { 1.0f,	1.0f,	1.0f }, {  0.0f,		1.0f }, { 0.f, -1.f, 0.f} ),
		vertex_type({  1.f,	-1.f,	-1.f }, { 1.0f,	1.0f,	1.0f }, {  1.0f,		1.0f }, { 0.f, -1.f, 0.f} ),
		vertex_type({  1.f,	-1.f,	 1.f }, { 1.0f,	1.0f,	1.0f }, {  1.0f,		0.0f }, { 0.f, -1.f, 0.f} )
	};

	std::array<GLuint, 36> indices = {
		0, 1, 2, //Front
		2, 3, 0,

		4, 5, 6, //Right
		6, 7, 4,

		8, 9, 10, //Back
		10, 11, 8,

		12, 13, 14, //Left
		14, 15, 12,

		16, 17, 18, //Top
		18, 19, 16,

		20, 21, 22, //Bottom
		22, 23, 20
	};

	LOAD_ARRAY_BUFFER(this->m_vbo, vertices)
	LOAD_ELEMENT_ARRAY_BUFFER(this->m_ebo, indices)

	parent::load();
}

template <typename Type>
void Cube<Type>::render(ContextRenderer& contextRenderer)
{
	parent::render(contextRenderer);

	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
}
