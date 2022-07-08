#include "Line.h"

#include <QPainter>

#include <cmath>

Line::Line(Point start, Point end) : start(start), end(end)
{

}

Line::Line(Point start) : start(start), end(start)
{
}

void Line::setNextNode(Point x)
{
	end = x;
}

void Line::draw(QPainter* p) const
{
	p->drawLine(start.x, start.y, end.x, end.y);
}

void Circle::setNextNode(Point x)
{
	radius = std::sqrt(std::pow(center.x - x.x, 2) + std::pow(center.y - x.y, 2));
}

void Circle::draw(QPainter* p) const
{
	p->drawEllipse({ center.x, center.y }, radius, radius);
}
