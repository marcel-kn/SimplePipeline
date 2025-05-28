#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "controller.h"
#include "databasemanager.h"
#include <QMainWindow>
#include <QComboBox>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void populateArtistsComboBox();

private:
    QComboBox *artistsComboBox;
    Controller* controller;
    DataBaseManager* dbm;

private slots:
    void onClose();
};
#endif // MAINWINDOW_H
