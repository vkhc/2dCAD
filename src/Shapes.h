#pragma once

#include <iostream>

class QPainter;

enum class Shape_t {
	line,
	circle
};

struct Node {

};

struct Point {

	double x, y;
	int z = 0;
};

class Shape {
public:
	virtual void setNextNode(Point x) = 0;
	virtual void draw(QPainter* p) const = 0;
	virtual void showInfo() const = 0;

	virtual Shape_t type() const = 0;
protected:
	//QPoint toScreen(const Point& point);
private:

};

class Line : public Shape {
public:

	Line(Point start, Point end);
	Line(Point start);

	void setNextNode(Point x) override;

	void draw(QPainter* p) const override;

	void showInfo() const { std::cout << "Start: x=" << start.x << " y=" << start.y << '\n'; }

	Shape_t type() const { return Shape_t::line; }

private:
	Point start;
	Point end;

	bool done = false;
};

class Circle : public Shape {
public:
	Circle(Point center) : center(center) {}

	void setNextNode(Point x) override;
	void draw(QPainter* p) const override;

	void showInfo() const { std::cout << "Center: x=" << center.x << " y=" << center.y << '\n'; }

	Shape_t type() const { return Shape_t::circle; }

public:
	Point center;
	double radius = 0;
};