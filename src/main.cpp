#include <iostream>

#include <QApplication>

#include <CanvasView.h>




int main(int argc, char* argv[]) {
	std::cout << "Imushave lamazo\n";

	QApplication app(argc, argv);

	CanvasView w;


	w.show();

	return app.exec();
}
