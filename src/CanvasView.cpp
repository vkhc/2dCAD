#include "CanvasView.h"


#include <QPainter>
#include <QPaintEvent>
#include <QMouseEvent>



CanvasView::CanvasView(QWidget* parent)
{
	setMouseTracking(true);
}

void CanvasView::paintEvent(QPaintEvent* e)
{
	QPainter p(this);
	QRect r = e->rect();


	p.fillRect(r, Qt::darkGray);

	for (auto& l : shapes) {
		l->draw(&p);
	}

	if (isDrawing) tempShape->draw(&p);
	
}

void CanvasView::mousePressEvent(QMouseEvent* e)
{
	if (e->button() == Qt::LeftButton) {
		if (!isDrawing) {
			isDrawing = true;
			tempShape = std::make_unique<Line>(Point{ (double)e->position().x(), (double)e->position().y() });
			
		} else {
			isDrawing = false;
			shapes.push_back(std::move(tempShape));
			qDebug() << "Number of items in vector: " << shapes.size();
		}
	}

}

void CanvasView::mouseMoveEvent(QMouseEvent* e)
{
	if (isDrawing) {
		tempShape->setNextNode(Point{ (double)e->position().x(), (double)e->position().y() });
		repaint();
	} else {

	}
}
