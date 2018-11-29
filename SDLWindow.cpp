#include "SDLWindow.h"
#include <stdio.h>

SDLWindow::SDLWindow(unsigned int width, unsigned int height)
	: m_width(width), m_height(height), m_initialised(false), IWindow(width, height)
{}

SDLWindow::~SDLWindow()
{
	destroy();
}

SDL_Window* SDLWindow::getContext()
{
	return m_window;
}

void SDLWindow::init()
{
	//no multiple initialisation
	if (m_initialised) return;
	m_initialised = true;

	m_msf = 0;

	m_lastTime = SDL_GetTicks();

	//Creates a mew SDL2 window
	m_window = SDL_CreateWindow("", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, m_width, m_height, SDL_WINDOW_SHOWN);
}

void SDLWindow::update()
{
	SDL_PollEvent(&m_event);

	switch (m_event.type)
	{
	case SDL_QUIT:
		destroy();
		break;
	}

	unsigned int timeNow = SDL_GetTicks();
	unsigned int deltaTime = timeNow - m_lastTime;
	m_lastTime = SDL_GetTicks();
	m_msf = (float)deltaTime / 1000.0f;

	sprintf(m_title, "Software Renderer - %d ms/frame", deltaTime);
	SDL_SetWindowTitle(m_window, m_title);

}

void SDLWindow::destroy()
{
	if (!m_initialised) return;
	m_initialised = false;

	SDL_DestroyWindow(m_window);
}

bool SDLWindow::running()
{
	return m_initialised;
}

float SDLWindow::getFrameTime()
{
	return m_msf;
}