#pragma once
#include <array>
#include "v4.h"

template<typename T>
class FrameBuffer
{
public:

	FrameBuffer(unsigned int bufferWidth, unsigned int bufferHeight);
	~FrameBuffer();

	unsigned int width();
	unsigned int height();
	void put(unsigned int x, unsigned int y, const T& data);
	const T& get(unsigned int x, unsigned int y);
	void fill(const T& data);
	void* getBuffer();
	unsigned int size();

private:

	unsigned int m_bufferWidth;
	unsigned int m_bufferHeight;

	T* m_buffer;
};

#include "FrameBuffer.inl"