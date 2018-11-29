#pragma once

template <typename T>
FrameBuffer<T>::FrameBuffer(unsigned int bufferWidth, unsigned int bufferHeight, unsigned int flags)
	: m_bufferWidth(bufferWidth), m_bufferHeight(bufferHeight)
{
	m_flags = flags;
	if (m_flags & kFrameBufferFlag_Allocate)
	{
		m_buffer = new T[bufferWidth * bufferHeight];
	}
}

template <typename T>
FrameBuffer<T>::~FrameBuffer()
{
	if (m_flags & kFrameBufferFlag_Allocate)
	{
		delete[] m_buffer;
	}
}

template <typename T>
void FrameBuffer<T>::setPixelBuffer(void* pixelBuffer)
{
	m_buffer = (T*)pixelBuffer;
}


template <typename T>
inline unsigned int FrameBuffer<T>::width()
{
	return m_bufferWidth;
}

template <typename T>
inline unsigned int FrameBuffer<T>::height()
{
	return m_bufferHeight;
}

template <typename T>
inline void FrameBuffer<T>::put(unsigned int x, unsigned int y, const T& data)
{
	if (x < m_bufferWidth && y < m_bufferHeight)
	{
		m_buffer[y*m_bufferWidth + x] = data;
	}
}

template <typename T>
inline const T& FrameBuffer<T>::get(unsigned int x, unsigned int y)
{
	if (x < m_bufferWidth && y < m_bufferHeight)
	{
		return m_buffer[y*m_bufferWidth + x];
	}
	return std::move(T());
}

template <typename T>
inline void FrameBuffer<T>::fill(const T& data)
{
	for (unsigned int i = 0; i < m_bufferWidth * m_bufferHeight; i++)
	{
		m_buffer[i] = data;
	}
}

template <typename T>
void* FrameBuffer<T>::getBuffer()
{
	return (void*)m_buffer;
}

template <typename T>
inline unsigned int FrameBuffer<T>::size()
{
	return m_bufferWidth * m_bufferHeight * 4 * sizeof(T);
}