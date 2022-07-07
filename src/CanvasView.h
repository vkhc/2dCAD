#pragma once

#include "Line.h"

#include <QWidget>

#include <vector>

class CanvasView : public QWidget {
public:
	CanvasView(QWidget* parent = nullptr);

protected:
	void paintEvent(QPaintEvent* e) override;
	void mousePressEvent(QMouseEvent* e) override;
	void mouseMoveEvent(QMouseEvent* e) override;

private:
	std::vector<Line> lines;

	bool isDrawing = false;
};