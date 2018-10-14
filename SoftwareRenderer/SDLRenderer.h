#pragma once
#include "IRenderer.h"
#include "SDLWindow.h"
#include <SDL2/SDL.h>
#include "rgba16.h"
#include "FrameBuffer.h"



class SDLRenderer : public IRenderer
{
public:

	SDLRenderer(SDLWindow& window);
	~SDLRenderer();

	//IRenderer interface
	void clear() override;
	void drawPoint(const v2& pos, const v4& colour) override;
	void drawLine(const v2& pos1, const v2& pos2, const v4& colour) override;
	void drawTriangle(const v2& pos1, const v2& pos2, const v2& pos3, const v4& colour);
	void drawFillTriangle(const v2& pos1, const v2& pos2, const v2& pos3, const v4& colour);
	void drawCircle(const v2& pos, float radius, const v4& colour);
	void drawFillCircle(const v2& pos, float radius, const v4& colour);
	void drawRect(const rect& bounds, const v4& colour) override;
	void drawFillRect(const rect& bounds, const v4& colour) override;
	void present() override;

private:
	
	SDL_RWops* m_sdlRW;
	SDL_Surface* m_swSurface;
	SDL_Texture* m_swRenderTarget;
	SDL_Renderer* m_sdlRenderer;

	FrameBuffer<rgba16> m_backBuffer;
};

