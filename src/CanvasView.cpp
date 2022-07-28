#include "CanvasView.h"

#include "Drawing.h"
#include "Shapes.h"

#include <QPainter>
#include <QPaintEvent>
#include <QMouseEvent>

void CanvasView::drw(Shape* s, QPainter& p)
{
	if (s->type() == Shape_t::circle) {
		auto circle = static_cast<Circle*>(s);
		qDebug() << "center [on Drawing] x: " << circle->center.x << "; y: " << circle->center.y
			<< " [on Screen] : " << fromDrawing(circle->center)
			<< "\n radius: " << circle->radius << fromDrawing(circle->radius);
		p.drawEllipse(fromDrawing(circle->center), fromDrawing(circle->radius), fromDrawing(circle->radius));
	}
}


CanvasView::CanvasView(QWidget* parent)
{
	setMouseTracking(true);

	drawing = std::make_unique<Drawing>();
		std::unique_ptr<Shape> circle = std::make_unique<Circle>(Point{ 0, 0 });
		circle->setNextNode({ 15, 20 });
		drawing->add(circle);
	
	offsetH = width() / 2;
	offsetV = height() / 2;

}

void CanvasView::paintEvent(QPaintEvent* e)
{
	QPainter p(this);
	QRect r = e->rect();

	p.fillRect(r, Qt::darkGray);

	//drawing->draw(p);

	//if (isDrawing) {
	//	tempShape->draw(&p);
	//}

	for (const auto& s : drawing->shapes) {
		drw(s.get(), p);
	}
}

void CanvasView::mousePressEvent(QMouseEvent* e)
{
	auto pScreen = e->pos();
	auto pReal = toDrawing(pScreen);
	if (e->button() == Qt::LeftButton) {
		if (!isDrawing) {
			isDrawing = true;
			tempShape = std::make_unique<LineCreator>(this);
			tempShape->setNextNode(pScreen);

		} else {
			isDrawing = false;
//			drawing->add(tempShape);
		}
	}
	
}

void CanvasView::mouseMoveEvent(QMouseEvent* e)
{
	if (isDrawing) {
		tempShape->setNextNode(e->pos());
		repaint();
	} else {

	}

}

void CanvasView::resizeEvent(QResizeEvent* e)
{
	zoomRatio = 2;
}

#define mN

Point CanvasView::toDrawing(const QPoint& pointOnScreen)
{

	int scrX = pointOnScreen.x();
	int scrY = pointOnScreen.y();

	int widgetWidth = width();
	int widgetHeight = height();

	double viewWidth = 100;
	double viewHeight = 100;

#ifdef N
	double x = -viewWidth / 2 + (1.0 * scrX / widgetWidth) * viewWidth;
	double y = viewHeight / 2 - (1.0 * scrY / widgetHeight) * viewHeight;
#else
	double x = -offsetH + 1.0 * scrX / zoomRatio;
	double y = offsetV / 2 - 1.0 * scrY / zoomRatio;
#endif
	
	return Point{ x, y };
}

QPoint CanvasView::fromDrawing(const Point& drawingPoint)
{
	int widgetWidth = width();
	int widgetHeight = height();

	double viewWidth = 100;
	double viewHeight = 100;


#ifdef N
	int x = (drawingPoint.x + 1. * viewWidth / 2) / viewWidth * widgetWidth;
	int y = - (drawingPoint.y - 1. * viewHeight / 2) / viewHeight * widgetHeight;
#else
	int sub = (drawingPoint.x + 1. * width() / 2);
	int x = drawingPoint.x * zoomRatio + offsetH;
	int y = -drawingPoint.y * zoomRatio + offsetV;
#endif

	return QPoint(x, y);
}

int CanvasView::fromDrawing(const double& l)
{
	int widgetWidth = width();
	int widgetHeight = height();

	double viewWidth = 100;
	double viewHeight = 100;

	int x = l * zoomRatio;

	return x;
}

void LineCreator::draw(QPainter* p) const
{
	//p->drawLine(start, end);
}



std::unique_ptr<Shape> LineCreator::create()
{
	return std::unique_ptr<Shape>();
}

void LineCreator::setNextNode(QPoint point)
{
//	end = point;
}
