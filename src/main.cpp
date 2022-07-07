#include <iostream>

#include <QApplication>

#include <canvasView.h>




int main(int argc, char* argv[]) {
	std::cout << "Imushave lamazo\n";

	QApplication app(argc, argv);

	CanvasView w;


	w.show();

	return app.exec();
}
