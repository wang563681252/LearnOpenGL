#pragma once

#include <vector>
#include <Gl/glew.h>
#include "Renderer.h"

struct VertexBufferElement
{
	unsigned int type;
	unsigned int count;
	unsigned char normalized;

	static unsigned int GetSizeOfType(unsigned int type)
	{
		switch (type)
		{
		case GL_FLOAT: return 4;
		case GL_UNSIGNED_INT: return 4;
		case GL_UNSIGNED_BYTE: return 1;
		}
		ASSERT(false);
		return 0;
	}
};

class VertexBufferLayout
{
private:
	std::vector<VertexBufferElement> mElement;
	unsigned int mStride;
public:
	VertexBufferLayout()
		: mStride(0)
	{
	}

	template<typename T>
	void Push(unsigned int count)
	{
		ASSERT(false);
	}

	template<>
	void Push<float>(unsigned int count)
	{
		VertexBufferElement temp = { GL_FLOAT, count, GL_FALSE };
		mElement.push_back(temp);
		mStride += VertexBufferElement::GetSizeOfType(GL_FLOAT) * count;
	}

	template<>
	void Push<unsigned int>(unsigned int count)
	{
		VertexBufferElement temp = { GL_UNSIGNED_INT, count, GL_FALSE };
		mElement.push_back(temp);
		mStride += VertexBufferElement::GetSizeOfType(GL_UNSIGNED_INT) * count;
	}

	template<>
	void Push<unsigned char>(unsigned int count)
	{
		VertexBufferElement temp = { GL_UNSIGNED_BYTE, count, GL_TRUE };
		mElement.push_back(temp);
		mStride += VertexBufferElement::GetSizeOfType(GL_BYTE) * count;
	}
	
	inline const std::vector<VertexBufferElement>& GetElements() const { return mElement; }
	inline unsigned int GetStride() const { return mStride; };
};