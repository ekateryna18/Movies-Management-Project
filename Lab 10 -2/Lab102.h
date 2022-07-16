#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Lab102.h"

class Lab102 : public QMainWindow
{
    Q_OBJECT

public:
    Lab102(QWidget *parent = Q_NULLPTR);

private:
    Ui::Lab102Class ui;
};
