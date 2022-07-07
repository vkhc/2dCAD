#pragma once

class QPainter;

struct Point {
	double x, y;
};

class Shape {
public:

protected:

private:

};

class Line {
public:

	Line(Point start, Point end);
	Line(Point start);

	void setEnd(Point x);

	void draw(QPainter* p) const;

private:
	Point start;
	Point end;

	bool done = false;
};