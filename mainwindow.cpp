#include "mainwindow.h"
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QSplitter>
#include <QTableWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QTabWidget>
#include <QTabWidget>
#include <QLabel>
#include <QComboBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    // DB and Controller
    dbm = new DataBaseManager();
    controller = new Controller(dbm);

    // Menu Bar
    QMenuBar *menuBar = new QMenuBar(this);
    setMenuBar(menuBar);

    QMenu *menuMenu = new QMenu("Menu", this);
    menuBar->addMenu(menuMenu);
    QMenu *adminMenu = new QMenu("Administration", this);
    menuBar->addMenu(adminMenu);
    QMenu *helpMenu = new QMenu("Help", this);
    menuBar->addMenu(helpMenu);

    QAction *closeAction = new QAction("Close", this);
    menuMenu->addAction(closeAction);

    connect(closeAction, &QAction::triggered, this, &MainWindow::onClose);

    QSplitter *mainSplitter = new QSplitter(Qt::Horizontal, this);

    // Left Pane
    QWidget *leftPane = new QWidget();
    QVBoxLayout *leftLayout = new QVBoxLayout(leftPane);

    // Filter Box
    QWidget *filterBox = new QWidget();
    QHBoxLayout *filterBoxLayout = new QHBoxLayout(filterBox);
    QPushButton *filterBtn = new QPushButton("Filter:");

    artistsComboBox =  new QComboBox();
    populateArtistsComboBox();

    QPushButton *allProjectsBtn = new QPushButton("all projects");
    QPushButton *refreshBtn = new QPushButton("Refresh");
    filterBoxLayout->addWidget(filterBtn);
    filterBoxLayout->addWidget(artistsComboBox);
    filterBoxLayout->addWidget(allProjectsBtn);
    filterBoxLayout->addWidget(refreshBtn);

    QComboBox *projectsComboBox = new QComboBox();

    QTabWidget *leftTabBar = new QTabWidget();
    QTableWidget *shotsTable = new QTableWidget();
    QTableWidget *assetsTable = new QTableWidget();
    leftTabBar->addTab(shotsTable, "shots");
    leftTabBar->addTab(assetsTable, "assets");

    QWidget *bottomLeftBtnBox = new QWidget();
    QHBoxLayout *bottomLeftBtnBoxLayout = new QHBoxLayout(bottomLeftBtnBox);
    QPushButton *createBtn = new QPushButton("Create Shot");
    QPushButton *manageBtn = new QPushButton("Manage Shows");
    QPushButton *deleteBtn = new QPushButton("Delete Shot");

    bottomLeftBtnBoxLayout->addWidget(createBtn);
    bottomLeftBtnBoxLayout->addWidget(manageBtn);
    bottomLeftBtnBoxLayout->addWidget(deleteBtn);

    leftLayout->addWidget(filterBox);
    leftLayout->addWidget(projectsComboBox);
    leftLayout->addWidget(leftTabBar);
    leftLayout->addWidget(bottomLeftBtnBox);

    mainSplitter->addWidget(leftPane);
    mainSplitter->addWidget(new QLabel("Placeholder for the right part."));

    setCentralWidget(mainSplitter);
}

MainWindow::~MainWindow() {}

void MainWindow::populateArtistsComboBox(){
    artistsComboBox->addItems(controller->loadArtists());
}

void MainWindow::onClose() {
    close();
}
