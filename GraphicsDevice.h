#pragma once
#include "SDLWindow.h"
#include <SDL2/SDL.h>
#include "v2.h"
#include "v3.h"
#include "rect.h"
#include "rgba32.h"
#include "FrameBuffer.h"
#include "texture.h"


class GraphicsDevice 
{
public:

	GraphicsDevice(SDLWindow& window);
	~GraphicsDevice();

	void clear();
	void drawPoint(const v2& pos, const v4& colour);
	void drawLine(const v2& pos1, const v2& pos2, const v4& colour);
	void drawTriangle(const v2& pos1, const v2& pos2, const v2& pos3, const v4& colour);
	void drawFillTriangle(const v3& pos1, const v3& pos2, const v3& pos3, const v4& colour, const v4& colour2, const v4& colour3, const texture& tex, const v2& texcoord1, const v2& texcoord2, const v2& texcoord3);
	void drawCircle(const v2& pos, float radius, const v4& colour);
	void drawFillCircle(const v2& pos, float radius, const v4& colour);
	void drawRect(const rect& bounds, const v4& colour);
	void drawFillRect(const rect& bounds, const v4& colour);
	void blitTexture(const texture& tex, const v2& pos);
	void present();

	void stall();

private:
	
	SDL_RWops* m_sdlRW;
	SDL_Surface* m_swSurface;
	SDL_Texture* m_swRenderTarget;
	SDL_Renderer* m_GraphicsDevice;

	FrameBuffer<rgba32> m_backBuffer;
	FrameBuffer<float> m_depthBuffer;
};

