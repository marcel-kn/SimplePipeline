#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "controller.h"
#include "databasemanager.h"
#include <QMainWindow>
#include <QComboBox>
#include <QTableWidget>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void populateArtistsComboBox();
    void populateProjectsComboBox();
    void populateShotsTable();

private:
    QComboBox *artistsComboBox;
    QComboBox *projectsComboBox;
    QTableWidget *shotsTable;
    Controller* controller;
    DataBaseManager* dbm;

private slots:
    void onClose();
    void onCreateProject();
};
#endif // MAINWINDOW_H
