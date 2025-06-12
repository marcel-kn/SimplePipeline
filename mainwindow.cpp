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
#include <QStandardItemModel>

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

    leftTabBar = new QTabWidget();
    shotsTable = new QTreeView();
    populateElemTable();

    assetsTable = new QTableWidget();
    leftTabBar->addTab(shotsTable, "shots");
    leftTabBar->addTab(assetsTable, "assets");

    QWidget *bottomLeftBtnBox = new QWidget();
    QHBoxLayout *bottomLeftBtnBoxLayout = new QHBoxLayout(bottomLeftBtnBox);
    createBtn = new QPushButton(this);
    manageBtn = new QPushButton(this);
    deleteBtn = new QPushButton(this);

    connect(leftTabBar, &QTabWidget::currentChanged, this, &MainWindow::onElemTabChanged);

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

    setElemBtnNames();
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

int MainWindow::queryActiveTab() {
    return leftTabBar->currentIndex();
}

void MainWindow::setElemBtnNames() {
    int tab = queryActiveTab();
    if (tab == 0) {
        createBtn->setText("Create Shot");
        manageBtn->setText("Manage Shows");
        deleteBtn->setText("Delete Shot");
    }
    else if (tab == 1) {
        createBtn->setText("Create Asset");
        manageBtn->setText("Manage Types");
        deleteBtn->setText("Delete Asset");
    }
}

void MainWindow::populateElemTable() {

    QList<QPair<int, QString>> catNamesIds = controller->loadShows();

    QStandardItemModel *model = new QStandardItemModel();

    // insert category
    for (int i = 0; i < catNamesIds.size(); i++) {
        QStandardItem *item = new QStandardItem(catNamesIds.at(i).second);
        item->setEnabled(false);
        item->setSelectable(false);
        model->appendRow(item);

        // insert elements
        QList<QPair<int, QString>> elemNamesIds = controller->loadShots(catNamesIds.at(i).first);
        for (int e = 0; e < elemNamesIds.size(); e++) {
            QStandardItem *eItem = new QStandardItem(elemNamesIds.at(e).second);
            // Store id in first role
            eItem->setData(elemNamesIds.at(e).first, Qt::UserRole);
            eItem->setEnabled(false);
            item->appendRow(eItem);
        }
    }

    shotsTable->setModel(model);
    shotsTable->sortByColumn(0, Qt::AscendingOrder);

    shotsTable->expandAll();
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

void MainWindow::onElemTabChanged() {
    setElemBtnNames();
}
