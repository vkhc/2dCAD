#pragma once

#include "Line.h"

#include <QWidget>

#include <vector>
#include <memory>

class CanvasView : public QWidget {
public:
	CanvasView(QWidget* parent = nullptr);

protected:
	void paintEvent(QPaintEvent* e) override;
	void mousePressEvent(QMouseEvent* e) override;
	void mouseMoveEvent(QMouseEvent* e) override;

private:
	std::vector<std::unique_ptr<Shape>> shapes;

	std::unique_ptr<Shape> tempShape;

	bool isDrawing = false;
};