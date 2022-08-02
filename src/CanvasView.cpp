#include "CanvasView.h"

#include "Drawing.h"
#include "Shapes.h"

#include <QPainter>
#include <QPaintEvent>
#include <QMouseEvent>

int findStepSize(double zoomRatio)
{
	int minSize = 50;
	int maxSize = 300;


	double unitSize = 1;
	//int v = std::log10(unitSize);
	//unitSize = std::pow(10, v);


	//if (unitSize > 60) unitSize /= 10;
	//if (unitSize < 10)  unitSize *= 10;
	double stepUnscaled = unitSize * 100;
	int stepSize = stepUnscaled * zoomRatio;
	
	if (stepSize > maxSize)
		while (stepUnscaled > maxSize / zoomRatio)
			stepUnscaled /= 10;
	else if (stepSize < minSize)
		while (stepUnscaled < minSize / zoomRatio)
			stepUnscaled *= 10;

	stepSize = stepUnscaled * zoomRatio;




	return stepSize;
}

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

	int mainStep = findStepSize(zoomRatio);
	int fineStep = mainStep / 5;
	
	auto origin = fromDrawing({ 0, 0 });



	static std::vector<QLine> fineGrid;
	static std::vector<QLine> mainGrid;
	//static std::vector<QLine> originAxes;

	fineGrid.clear();
	mainGrid.clear();

	int vertInitPoint = origin.x() % mainStep;
	int horInitPoint = origin.y() % mainStep;
	
	for (int i = vertInitPoint; i < width() ; i += fineStep) {
		fineGrid.emplace_back(i, 0, i, height());
	}
	for (int i = horInitPoint; i < height() ; i += fineStep) {
		fineGrid.emplace_back(0, i, width(), i);
	}

	for (int i = vertInitPoint; i < width() ; i += mainStep) {
		mainGrid.emplace_back(i, 0, i, height());
	}
	for (int i = horInitPoint; i < height() ; i += mainStep) {
		mainGrid.emplace_back(0, i, width(), i);
	}
	
	p.setPen(fineGridLines);
	p.drawLines(&fineGrid[0], fineGrid.size());

	p.setPen(mainGridLines);
	p.drawLines(&mainGrid[0], mainGrid.size());


	p.setPen(originAxes);
	p.drawLine(origin.x(), 0, origin.x(), height());
	p.drawLine(0, origin.y(), width(), origin.y());

}


CanvasView::CanvasView(QWidget* parent) : QWidget(parent)
{
	setMouseTracking(true);

	drawing = std::make_unique<Drawing>();
		std::unique_ptr<Shape> circle = std::make_unique<Circle>(Point{ 0, 0 });
		circle->setNextNode({ 0, 100 });
		drawing->add(circle);
	
	offset.setX(width() / 2);
	offset.setY(height() / 2);

	zoomRatio = 1;
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

	Point coords = toDrawing(lastPos);
	QString c = "X: " + QString::number(coords.x) + "\tY: " + QString::number(coords.y) + "\tOffset " + 
				QString::number(offset.x()) + ", " + QString::number(offset.y()) + "\tZoom: " + QString::number(zoomRatio);
	QString s = "Screen coordinates (actual): " + QString::number(lastPos.x()) + ", " + QString::number(lastPos.y()) +
				"\tconverted: " + QString::number(fromDrawing(coords).x()) + ", " + QString::number(fromDrawing(coords).y());
	p.drawText(QPoint(5,15), c);
	p.drawText(QPoint(5, 30), s);
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
	return Point{ -offset.x() / zoomRatio + 1. * pointOnScreen.x() / zoomRatio,
				  offset.y() / zoomRatio - 1. * pointOnScreen.y() / zoomRatio };
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
