#include "editor.h"
#include <QProcess>
#include <QWindow>
#include <QFormLayout>

editor::editor(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	QProcess *calcProc = new QProcess;
	calcProc->start("SceneEditor");
	if (calcProc->waitForStarted()) {
		calcProc->waitForReadyRead(100); // just for timeout
		QProcess proc;
		//proc.start("xwininfo", QStringList() << "-int" << "-name" << "Calculator");
		proc.start("SceneEditor");
		proc.waitForReadyRead();
		QByteArray in = proc.readAllStandardOutput();
		//qDebug() << in;
		proc.close();

		int beg = in.indexOf("id: ") + 4;
		int end = in.indexOf(" \"SceneEditor");
		QByteArray wId = in.mid(beg, end - beg);

		QWindow *win = QWindow::fromWinId(WId(wId.toInt()));
		QWidget *cont = QWidget::createWindowContainer(win, NULL);
		QFormLayout *layout = new QFormLayout;
		layout->addWidget(cont);
	}
}