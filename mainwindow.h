#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QGridLayout>
#include <QPoint>
#include <QComboBox>
#include <QGroupBox>
#include <QPushButton>
#include <QListWidget>

#include "graphui.h"

#if DEV
#include <QSound>
#endif

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QGridLayout* layout;
    GraphUi* paintWidget;
    QListWidget* list;
    QWidget* widget;

};

#endif // MAINWINDOW_H
