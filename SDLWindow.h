#pragma once
#include "IWindow.h"
#include <SDL2/SDL.h>

class SDLWindow : public IWindow
{
public:

	SDLWindow(unsigned int width, unsigned int height);
	~SDLWindow();

	SDL_Window* getContext();

	//IWindow Interface
	void init() override;
	void update() override;
	void destroy() override;
	bool running() override;
	float getFrameTime();

private:

	//window dimensions
	unsigned int m_width;
	unsigned int m_height;

	//title
	char m_title[128];
	float m_msf;
	unsigned int m_lastTime;

	//SDL objects and pointers
	SDL_Window* m_window;
	SDL_Event m_event;

	//initialisation
	bool m_initialised;

};

