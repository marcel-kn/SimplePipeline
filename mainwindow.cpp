#include "mainwindow.h"
#include "createprojectdialog.h"
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
#include <QDebug>

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

    QAction *openCreateProjectAction = new QAction("Create Project", this);
    menuMenu->addAction(openCreateProjectAction);
    connect(openCreateProjectAction, &QAction::triggered, this, &MainWindow::onCreateProject);

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

    projectsComboBox = new QComboBox();
    populateProjectsComboBox();

    QTabWidget *leftTabBar = new QTabWidget();
    shotsTable = new QTableWidget();
    populateShotsTable();

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

void MainWindow::populateProjectsComboBox(){
    for (const auto& project : controller->loadProjects()){
        projectsComboBox->addItem(project.second, project.first);
    }
}

void MainWindow::populateShotsTable() {
    QList<QPair<int, QString>> shotNamesIds = controller->loadShots();
    shotsTable->setRowCount(shotNamesIds.size());
    shotsTable->setColumnCount(1);

    for (int i = 0; i < shotNamesIds.size(); i++) {
        QTableWidgetItem *item = new QTableWidgetItem(shotNamesIds.at(i).second);
        // Store Id in first role
        item->setData(Qt::UserRole, shotNamesIds.at(i).first);
        shotsTable->setItem(i, 0, item);
    }
}

void MainWindow::onClose() {
    close();
}

void MainWindow::onCreateProject() {
    CreateProjectDialog dialog(this);
    if (dialog.exec() == QDialog::Accepted) {
        ProjectModel p = dialog.project();
        controller->storeProject(p);
    }
}
