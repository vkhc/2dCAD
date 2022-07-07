#include "canvasView.h"


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

	for (auto& l : lines) {
		l.draw(&p);
	}
	
}

void CanvasView::mousePressEvent(QMouseEvent* e)
{
	if (e->button() == Qt::LeftButton) {
		if (!isDrawing) {
			isDrawing = true;
			Line l(Point{ (double)e->x(), (double)e->y() });
			lines.push_back(l);
		} else {
			isDrawing = false;
		}
	}

}

void CanvasView::mouseMoveEvent(QMouseEvent* e)
{
	if (isDrawing) {
		lines.back().setEnd(Point{ (double)e->x(), (double)e->y()} );
		repaint();
	} else {

	}
}
