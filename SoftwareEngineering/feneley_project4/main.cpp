#include <QApplication>
#include "Window.h"

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	Window *window = new Window();
    return app.exec();
	return 0;
}