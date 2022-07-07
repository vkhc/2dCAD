#include "Line.h"

#include <QPainter>

Line::Line(Point start, Point end) : start(start), end(end)
{

}

Line::Line(Point start) : start(start), end(start)
{
}

void Line::setEnd(Point x)
{
	end = x;
}

void Line::draw(QPainter* p) const
{
	p->drawLine(start.x, start.y, end.x, end.y);
}
