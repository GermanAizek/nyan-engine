#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_editor.h"

class editor : public QMainWindow
{
	Q_OBJECT

public:
	editor(QWidget *parent = Q_NULLPTR);

private:
	Ui::editorClass ui;
};
