#pragma once

#include <QWidget>

class CanvasView : public QWidget {
public:
	CanvasView(QWidget* parent = nullptr);

protected:
	void paintEvent(QPaintEvent* e) override;

};