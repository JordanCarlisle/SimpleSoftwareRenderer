#pragma once
#include <array>
#include "v4.h"

enum kFrameBufferFlag
{
	kFrameBufferFlag_Allocate = 1
};

template<typename T>
class FrameBuffer
{
public:

	FrameBuffer(unsigned int bufferWidth, unsigned int bufferHeight, unsigned int flags);
	~FrameBuffer();

	void setPixelBuffer(void* pixelBuffer);
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
	unsigned int m_flags;

	T* m_buffer;
};

#include "FrameBuffer.inl"