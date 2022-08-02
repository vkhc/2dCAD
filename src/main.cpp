#include <iostream>
#include <exception>

#include <QApplication>

#include <CanvasView.h>



int main(int argc, char* argv[]) {

	std::set_terminate([] { std::cerr << "Unhandled exception occured\n"; abort(); });


	QApplication app(argc, argv);

	CanvasView w;


	w.show();

	return app.exec();
}
