#pragma once

class IWindow
{
public:

	IWindow(unsigned int width, unsigned int height) {};
	virtual ~IWindow() {};

	virtual void init() = 0;
	virtual void update() = 0;
	virtual void destroy() = 0;
	virtual bool running() = 0;


};

