#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "controller.h"
#include "databasemanager.h"
#include <QMainWindow>
#include <QComboBox>
#include <QTableWidget>
#include <QTabWidget>
#include <QPushButton>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void populateArtistsComboBox();
    void populateProjectsComboBox();
    void populateElemTable();

    /**
     * @brief Queries the selected Tab in the Elements Tab Widget
     * @return Index of the tab:
     * 0 - Shots, 1 - Assets
     */
    int queryActiveTab();

    /**
     * @brief Sets the names for the left buttons Shot or Asset specific
     */
    void setElemBtnNames();

private:
    QComboBox *artistsComboBox;
    QComboBox *projectsComboBox;
    QTableWidget *shotsTable;
    Controller* controller;
    DataBaseManager* dbm;
    QTabWidget *leftTabBar;
    QPushButton *createBtn;
    QPushButton *manageBtn;
    QPushButton *deleteBtn;

private slots:
    void onClose();
    void onCreateProject();
    void onElemTabChanged();
};
#endif // MAINWINDOW_H
