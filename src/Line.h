#pragma once

class QPainter;

struct Node {

};

struct Point {

	double x, y;
};

class Shape {
public:
	virtual void setNextNode(Point x) = 0;
	virtual void draw(QPainter* p) const = 0;
protected:

private:

};

class Line : public Shape {
public:

	Line(Point start, Point end);
	Line(Point start);

	void setNextNode(Point x) override;

	void draw(QPainter* p) const override;

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

private:
	Point center;
	double radius;
};