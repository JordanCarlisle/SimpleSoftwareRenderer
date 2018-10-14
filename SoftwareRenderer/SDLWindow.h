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

private:

	//window dimensions
	unsigned int m_width;
	unsigned int m_height;

	//SDL objects and pointers
	SDL_Window* m_window;
	SDL_Event m_event;

	//initialisation private member
	bool m_initialised;

};

