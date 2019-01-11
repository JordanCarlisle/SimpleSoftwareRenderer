#include "GraphicsDevice.h"
#include "maths.h"
#include <cmath>
#include <iostream>
#include <array>
#include <algorithm>

GraphicsDevice::GraphicsDevice(SDLWindow& window) 
	: m_backBuffer(1024, 768, 0)
	, m_depthBuffer(1024, 768, kFrameBufferFlag_Allocate)
{
	m_GraphicsDevice = SDL_CreateRenderer(window.getContext(), -1, SDL_RENDERER_ACCELERATED);
	m_swRenderTarget = SDL_CreateTexture(m_GraphicsDevice, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, m_backBuffer.width(), m_backBuffer.height());
	SDL_SetRenderTarget(m_GraphicsDevice, m_swRenderTarget);
}


GraphicsDevice::~GraphicsDevice()
{
	SDL_DestroyRenderer(m_GraphicsDevice);
}

void GraphicsDevice::clear()
{
	SDL_Rect texRect = { 0, 0, m_backBuffer.width(), m_backBuffer.height() };

	void* pixels;
	int pitch;

	SDL_LockTexture(m_swRenderTarget, &texRect, &pixels, &pitch);

	m_backBuffer.setPixelBuffer(pixels);

	rgba32 colour(
		(char)255,
		(char)255,
		(char)255,
		(char)255
	);
	m_backBuffer.fill(colour);
	m_depthBuffer.fill(-std::numeric_limits<float>::max());
}

void GraphicsDevice::drawPoint(const v2& pos, const v4& colour)
{
	rgba32 rgba(
		(char)(colour.x * 255.0f),
		(char)(colour.y * 255.0f),
		(char)(colour.z * 255.0f),
		(char)(colour.w * 255.0f)
	);

	m_backBuffer.put((unsigned int)pos.x, (unsigned int)pos.y, rgba);
}

void GraphicsDevice::drawLine(const v2& pos1, const v2& pos2, const v4& colour)
{
	rgba32 rgba(
		(char)(colour.x * 255.0f),
		(char)(colour.y * 255.0f),
		(char)(colour.z * 255.0f),
		(char)(colour.w * 255.0f)
	);

	int x1 = (int)pos1.x;
	int x2 = (int)pos2.x;
	int y1 = (int)pos1.y;
	int y2 = (int)pos2.y;

	if (x1 == x2 && y1 == y2)
	{
		m_backBuffer.put(x1, y1, rgba);
		return;
	}

	bool invert = false;
	int err = 0;

	if (std::abs(x1 - x2) < std::abs(y1 - y2))
	{
		invert = true;
		int temp = x1;
		x1 = y1;
		y1 = temp;
		temp = x2;
		x2 = y2;
		y2 = temp;
	}

	if (x1 > x2)
	{
		int temp = x1;
		x1 = x2;
		x2 = temp;
		temp = y1;
		y1 = y2;
		y2 = temp;
	}

	int dx = x2 - x1;
	int dy = y2 - y1;
	
	int err2 = std::abs(dy) * 2;
	int x, y = y1;

	for (x = x1; x <= x2; x++)
	{
		if (!invert)
			m_backBuffer.put(x, y, rgba);
		else
			m_backBuffer.put(y, x, rgba);
		err += err2;
		if (err > dx)
		{
			if (y2 > y1)
				y += 1;
			else
				y -= 1;
			err -= dx * 2;
		}
	}
}

void GraphicsDevice::drawTriangle(const v2& pos1, const v2& pos2, const v2& pos3, const v4& colour)
{
	drawLine(pos1, pos2, colour);
	drawLine(pos2, pos3, colour);
	drawLine(pos3, pos1, colour);
}

void GraphicsDevice::drawFillTriangle(const v3& pos1, const v3& pos2, const v3& pos3, const v4& colour, const v4& colour2, const v4& colour3, const v2& texcoord1, const v2& texcoord2, const v2& texcoord3, texture* tex)
{
	rect bb;
	bb.x = std::fmin(pos1.x, std::fmin(pos2.x, pos3.x));
	bb.y = std::fmin(pos1.y, std::fmin(pos2.y, pos3.y));
	bb.width = std::fmax(pos1.x, std::fmax(pos2.x, pos3.x));
	bb.height = std::fmax(pos1.y, std::fmax(pos2.y, pos3.y));

	v4 finalColour;
	finalColour.w = 1.0f;

	rgba32 rgba;

	for (int x = bb.x; x < bb.width; x++)
	{
		for (int y = bb.y; y < bb.height; y++)
		{
			v3 p(x, y, 0.0f);
			v3 uvw = maths::barycentricCoords(p, pos1, pos2, pos3);

			//point is within triangle
			if (uvw.x > 0.0f && uvw.y > 0.0f && uvw.z > 0.0f)
			{
				p.z = (pos1.z * uvw.x) + (pos2.z * uvw.y) + (pos3.z * uvw.z);

				//depth check
				//pixel depth value greater than depth buffer value
				if (p.z > m_depthBuffer.get((unsigned int)p.x, (unsigned int)p.y))
				{
					//update depth buffer
					m_depthBuffer.put((unsigned int)p.x, (unsigned int)p.y, p.z);

					//interpolate between 3 colours
					finalColour.x = (colour.x * uvw.x) + (colour2.x * uvw.y) + (colour3.x * uvw.z);
					finalColour.y = (colour.y * uvw.x) + (colour2.y * uvw.y) + (colour3.y * uvw.z);
					finalColour.z = (colour.z * uvw.x) + (colour2.z * uvw.y) + (colour3.z * uvw.z);
					
					if (tex != nullptr)
					{
						v2 uv = texcoord1 * uvw.x + texcoord2 * uvw.y + texcoord3 * uvw.z;

						// wrap uv coordinates
						if (uv.x < 0.0f) uv.x = 1.0f - uv.x;
						if (uv.x > 1.0f) uv.x -= -1.0f;
						if (uv.y < 0.0f) uv.y = 1.0f - uv.y;
						if (uv.y > 1.0f) uv.y -= 1.0f;

						//sample the texture
						unsigned int w = uv.x * tex->width;
						unsigned int h = uv.y * tex->height;

						rgba32 pixelCol = tex->pixels[h * tex->width + w];

						finalColour.x *= (float)pixelCol.r / 255.0f;
						finalColour.y *= (float)pixelCol.g / 255.0f;
						finalColour.z *= (float)pixelCol.b / 255.0f;
					}
					
					rgba.r = (unsigned char)(finalColour.x * 255.0f);
					rgba.g = (unsigned char)(finalColour.y * 255.0f);
					rgba.b = (unsigned char)(finalColour.z * 255.0f);

					//update back buffer
					m_backBuffer.put((unsigned int)p.x, (unsigned int)p.y, rgba);
				}
			}
		}
	}
}

void GraphicsDevice::drawCircle(const v2& pos, float radius, const v4& colour)
{
	if (radius < 1.0f)
		return;

	rgba32 rgba( 
		(char)(colour.x * 255.0f),
		(char)(colour.y * 255.0f),
		(char)(colour.z * 255.0f),
		(char)(colour.w * 255.0f)
	);

	int x1 = pos.x;
	int y1 = pos.y;

	int x = radius;
	int y = 0;
	int err = 0;

	for (; x >= y;)
	{
		m_backBuffer.put(x1 + x, y1 - y, rgba);
		m_backBuffer.put(x1 + y, y1 - x, rgba);
		m_backBuffer.put(x1 - y, y1 - x, rgba);
		m_backBuffer.put(x1 - x, y1 - y, rgba);
		m_backBuffer.put(x1 + x, y1 + y, rgba);
		m_backBuffer.put(x1 + y, y1 + x, rgba);
		m_backBuffer.put(x1 - y, y1 + x, rgba);
		m_backBuffer.put(x1 - x, y1 + y, rgba);

		if (err <= 0)
		{
			y += 1;
			err += 2 * y + 1;
		}

		if (err > 0)
		{
			x -= 1;
			err -= 2 * x + 1;
		}
	}
}

void GraphicsDevice::drawFillCircle(const v2& pos, float radius, const v4& colour)
{
	if (radius < 1.0f)
		return;

	rgba32 rgba(
		(char)(colour.x * 255.0f),
		(char)(colour.y * 255.0f),
		(char)(colour.z * 255.0f),
		(char)(colour.w * 255.0f)
	);

	int x1 = pos.x;
	int y1 = pos.y;

	int x = radius;
	int y = 0;
	int err = 0;

	for (; x >= y;)
	{
		drawLine(v2(x1 - x, y1 + y), v2(x1 + x, y1 + y), colour);
		drawLine(v2(x1 - x, y1 - y), v2(x1 + x, y1 - y), colour);
		drawLine(v2(x1 - y, y1 - x), v2(x1 + y, y1 - x), colour);
		drawLine(v2(x1 + y, y1 + x), v2(x1 - y, y1 + x), colour);
		

		if (err <= 0)
		{
			y += 1;
			err += 2 * y + 1;
		}

		if (err > 0)
		{
			x -= 1;
			err -= 2 * x + 1;
		}
	}
}

void GraphicsDevice::blitTexture(const texture& tex, const v2& pos)
{
	int max = (int)pos.x + tex.width;
	max = (max < m_backBuffer.width()) ? max : m_backBuffer.width();
	int maxy = (int)pos.y + tex.height;
	maxy = (maxy < m_backBuffer.height()) ? maxy : m_backBuffer.height();

	int minx = (int)pos.x;
	minx = (minx >= 0) ? minx : 0;
	int miny = (int)pos.y;
	miny = (miny >= 0) ? miny : 0;

	for(int i = 0; i < tex.width; i++)
		for (int j = 0; j < tex.height; j++)
		{
			m_backBuffer.put(i, j, tex.pixels[j*tex.width + i]);
		}
}

void GraphicsDevice::present()
{
	SDL_UnlockTexture(m_swRenderTarget);

	SDL_RenderCopy(m_GraphicsDevice, m_swRenderTarget, NULL, NULL);
	SDL_RenderPresent(m_GraphicsDevice);
}