#pragma once
#include "v2.h"
#include "v4.h"
#include "rect.h"

//Renderer interface class
class IRenderer
{
public:

	IRenderer() {};
	virtual ~IRenderer() {};

	virtual void clear() = 0;
	virtual void drawPoint(const v2& pos, const v4& colour) = 0;
	virtual void drawLine(const v2& pos1, const v2& pos2, const v4& colour) = 0;
	virtual void drawRect(const rect& bounds, const v4& colour) = 0;
	virtual void drawFillRect(const rect& bounds, const v4& colour) = 0;
	virtual void present() = 0;
};