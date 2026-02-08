#include "pch.h"

#include "Rect.h"

Rect::Rect(float x, float y, float w, float h)
{
	SetPosition(x, y);
	SetSize(w, h);
}

Rect::Rect(int x, int y, int w, int h)
{
	SetPosition(x, y);
	SetSize(w, h);
}

void Rect::SetPosition(float x, float y)
{
	rectangle.x = x;
	rectangle.y = y;

	intRectangle.x = (int)x;
	intRectangle.y = (int)y;
}


void Rect::SetSize(float w, float h)
{
	rectangle.w = w;
	rectangle.h = h;

	intRectangle.w = (int)w;
	intRectangle.h = (int)h;
}
