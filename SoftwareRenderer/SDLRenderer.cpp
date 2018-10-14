#include "SDLRenderer.h"
#include <cmath>
#include <iostream>

SDLRenderer::SDLRenderer(SDLWindow& window) : m_backBuffer(1024, 768)
{
	
	m_sdlRenderer = SDL_CreateRenderer(window.getContext(), -1, SDL_RENDERER_ACCELERATED);
	m_swRenderTarget = SDL_CreateTexture(m_sdlRenderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, m_backBuffer.width(), m_backBuffer.height());
	SDL_SetRenderTarget(m_sdlRenderer, m_swRenderTarget);
}


SDLRenderer::~SDLRenderer()
{
	SDL_DestroyRenderer(m_sdlRenderer);
}

void SDLRenderer::clear()
{
//	SDL_SetRenderDrawColor(m_sdlRenderer, 0x00, 0x00, 0x00, 0xff);
//	SDL_RenderClear(m_sdlRenderer);
	rgba16 colour(
		(char)0,
		(char)0,
		(char)0,
		(char)255
	);
	m_backBuffer.fill(colour);
}

void SDLRenderer::drawPoint(const v2& pos, const v4& colour)
{
	rgba16 rgba(
		(char)(colour.x * 255.0f),
		(char)(colour.y * 255.0f),
		(char)(colour.z * 255.0f),
		(char)(colour.w * 255.0f)
	);
	m_backBuffer.put((unsigned int)pos.x, (unsigned int)pos.y, rgba);
}

void SDLRenderer::drawLine(const v2& pos1, const v2& pos2, const v4& colour)
{

	rgba16 rgba(
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

void SDLRenderer::drawTriangle(const v2& pos1, const v2& pos2, const v2& pos3, const v4& colour)
{
	drawLine(pos1, pos2, colour);
	drawLine(pos2, pos3, colour);
	drawLine(pos3, pos1, colour);
}

void SDLRenderer::drawFillTriangle(const v2& pos1, const v2& pos2, const v2& pos3, const v4& colour)
{
	rect bb;
	bb.x = std::fmin(pos1.x, std::fmin(pos2.x, pos3.x));
	bb.y = std::fmin(pos1.y, std::fmin(pos2.y, pos3.y));
	bb.width = std::fmax(pos1.x, std::fmax(pos2.x, pos3.x));
	bb.height = std::fmax(pos1.y, std::fmax(pos2.y, pos3.y));

	for (int x = bb.x; x < bb.width; x++)
	{
		for (int y = bb.y; x < bb.height; y++)
		{

		}
	}
}

void SDLRenderer::drawCircle(const v2& pos, float radius, const v4& colour)
{
	if (radius < 1.0f)
		return;

	rgba16 rgba(
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

void SDLRenderer::drawFillCircle(const v2& pos, float radius, const v4& colour)
{
	if (radius < 1.0f)
		return;

	rgba16 rgba(
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

void SDLRenderer::drawRect(const rect& bounds, const v4& colour)
{

}

void SDLRenderer::drawFillRect(const rect& bounds, const v4& colour)
{

}

void SDLRenderer::present()
{
	SDL_Rect texRect = { 0, 0, m_backBuffer.width(), m_backBuffer.height() };

	void* pixels;
	int pitch;

	SDL_LockTexture(m_swRenderTarget, &texRect, &pixels, &pitch);
	memcpy(pixels, m_backBuffer.getBuffer(), pitch * m_backBuffer.height());
	SDL_UnlockTexture(m_swRenderTarget);

/*	
	for (unsigned int i = 0; i < m_backBuffer.width(); i++)
	{
		for (unsigned int j = 0; j < m_backBuffer.height(); j++)
		{
			rgba16 colour = m_backBuffer.get(i, j);

			SDL_SetRenderDrawColor(m_sdlRenderer, colour.r, colour.g, colour.b, colour.a);
			SDL_RenderDrawPoint(m_sdlRenderer, i, j);
		}
	}
	*/

	SDL_RenderCopy(m_sdlRenderer, m_swRenderTarget, NULL, NULL);
	SDL_RenderPresent(m_sdlRenderer);
}