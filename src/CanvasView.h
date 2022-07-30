#pragma once

#include <QWidget>

#include <vector>
#include <memory>

#include "Shapes.h"
#include "Drawing.h"

class Drawing;

class CanvasView;

class ShapeCreator {
public:
	ShapeCreator(CanvasView* canvas) : canvas(canvas) {}
	virtual void setNextNode(QPoint point) = 0;
	virtual void draw(QPainter* p) const = 0;
	virtual std::unique_ptr<Shape> create() = 0;
protected:
	std::vector<QPoint> nodes;
private:
	CanvasView* canvas = nullptr;
};

class LineCreator : public ShapeCreator {
public:
	LineCreator(CanvasView* canvas) : ShapeCreator(canvas) { nodes.reserve(2); }
	std::unique_ptr<Shape> create() override;

	void setNextNode(QPoint point) override;
	void draw(QPainter* p) const override;

private:
	int nMaxNodes = 2;

};


class CanvasView : public QWidget {
public:
	CanvasView(QWidget* parent = nullptr);
	Point toDrawing(const QPoint& pointOnScreen);
	QPoint fromDrawing(const Point& drawingPoint);
	int fromDrawing(const double& l);
	void drw(Shape* s, QPainter& p);

protected:
	void paintEvent(QPaintEvent* e) override;
	void mousePressEvent(QMouseEvent* e) override;
	void mouseReleaseEvent(QMouseEvent* e) override;
	void mouseMoveEvent(QMouseEvent* e) override;
	void wheelEvent(QWheelEvent* e) override;
	void resizeEvent(QResizeEvent* e) override;



private:
	std::unique_ptr<Drawing> drawing;
	std::unique_ptr<ShapeCreator> tempShape;

	bool isDrawing = false;

	int viewLen = 100;
	QPoint offset;
	double zoomRatio;

	QPoint lastPos;
	bool mouseLeftDown = false;

};

