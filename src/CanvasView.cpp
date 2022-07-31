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
		//qDebug() << "center [on Drawing] x: " << circle->center.x << "; y: " << circle->center.y
		//	<< " [on Screen] : " << fromDrawing(circle->center)
		//	<< "\n radius: " << circle->radius << fromDrawing(circle->radius);
		p.setPen(Qt::lightGray);
		p.drawEllipse(fromDrawing(circle->center), fromDrawing(circle->radius), fromDrawing(circle->radius));
	}
}

void CanvasView::drawGrid(QPainter& p)
{
	auto originAxes = QColor(103, 92, 108);
	auto mainGridLines = QColor(63, 72, 88);
	auto fineGridLines = QColor(33, 42, 58);

	int mainStep = 100;
	int fineStep = mainStep / 5;
	
	auto origin = fromDrawing({ 0, 0 });

	int vertInitPoint = origin.x() % mainStep;
	int horInitPoint = origin.y() % mainStep;
	
	p.setPen(fineGridLines);
	for (int i = vertInitPoint; i < width() ; i += fineStep) {
		p.drawLine(i, 0, i, height());
	}
	for (int i = horInitPoint; i < height() ; i += fineStep) {
		p.drawLine(0, i, width(), i);
	}

	p.setPen(mainGridLines);
	for (int i = vertInitPoint; i < width() ; i += mainStep) {
		p.drawLine(i, 0, i, height());
	}
	for (int i = horInitPoint; i < height() ; i += mainStep) {
		p.drawLine(0, i, width(), i);
	}

	p.setPen(originAxes);
	p.drawLine(origin.x(), 0, origin.x(), height());
	p.drawLine(0, origin.y(), width(), origin.y());

}


CanvasView::CanvasView(QWidget* parent)
{
	setMouseTracking(true);

	drawing = std::make_unique<Drawing>();
		std::unique_ptr<Shape> circle = std::make_unique<Circle>(Point{ 0, 0 });
		circle->setNextNode({ 0, 30 });
		drawing->add(circle);
	
	offset.setX(width() / 2);
	offset.setY(height() / 2);

}

void CanvasView::paintEvent(QPaintEvent* e)
{
	QPainter p(this);
	QRect r = e->rect();

	p.fillRect(r, QColor{23, 32, 48});

	drawGrid(p);

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
	lastPos = e->pos();
	auto pScreen = e->pos();
	auto pReal = toDrawing(pScreen);
	if (e->button() == Qt::LeftButton) {
		if (!isDrawing) {
			isDrawing = true;
			tempShape = std::make_unique<LineCreator>(this);
			tempShape->setNextNode(pScreen);
			mouseLeftDown = true;
		} else {
			isDrawing = false;
//			drawing->add(tempShape);
		}
	}
	
}

void CanvasView::mouseReleaseEvent(QMouseEvent* e)
{
	mouseLeftDown = false;
}

void CanvasView::mouseMoveEvent(QMouseEvent* e)
{
	

	if (isDrawing) {
		tempShape->setNextNode(e->pos());
		repaint();
	//} else {

	}

	if (e->buttons() & Qt::LeftButton) {
		offset += e->pos() - lastPos;


		repaint();
	}

	lastPos = e->pos();

}

void CanvasView::resizeEvent(QResizeEvent* e)
{
	zoomRatio = 2;
}

void CanvasView::wheelEvent(QWheelEvent* e)
{
    double factor = 1.2; // Magnification factor

	QPoint numDegrees = e->angleDelta() / 8;
    if (numDegrees.y() < 0) factor = 1 / factor;

	zoomRatio *= factor;

    QPoint d = offset - e->position().toPoint();
	offset +=  d * (factor -1);
	
	repaint();
}

Point CanvasView::toDrawing(const QPoint& pointOnScreen)
{	
	return Point{ -offset.x() + 1. * pointOnScreen.x() / zoomRatio,
				  offset.y() / 2 - 1. * pointOnScreen.y() / zoomRatio };
}

QPoint CanvasView::fromDrawing(const Point& drawingPoint)
{
	return QPoint{ int(drawingPoint.x * zoomRatio + offset.x()),
				   int(-drawingPoint.y * zoomRatio + offset.y()) };
}

int CanvasView::fromDrawing(const double& l)
{
	return l * zoomRatio;
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
