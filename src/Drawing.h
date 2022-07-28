#pragma once

#include "Shapes.h"
#include "CanvasView.h"

#include <vector>
#include <memory>

class Drawing {
public:

	void add(std::unique_ptr<Shape>& shape) { shapes.push_back(std::move(shape)); }

	void draw(QPainter& p) { for (const auto& s : shapes) s->draw(&p); }
public:
	std::vector<std::unique_ptr<Shape>> shapes;
};