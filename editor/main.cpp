#include "editor.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[]) {
	QApplication a(argc, argv);
	editor w;
	w.show();
	return a.exec();
}
