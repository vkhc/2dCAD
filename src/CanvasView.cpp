#include "canvasView.h"


#include <QPainter>
#include <QPaintEvent>

CanvasView::CanvasView(QWidget* parent) {

}

void CanvasView::paintEvent(QPaintEvent* e)
{
	QPainter p(this);
	QRect r = e->rect();


	p.fillRect(r, Qt::darkGray);

	p.drawLine(0, 0, 100, 100);
	
}