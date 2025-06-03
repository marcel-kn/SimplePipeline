#include "createprojectdialog.h"

#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QIntValidator>
#include <QFileDialog>

CreateProjectDialog::CreateProjectDialog(QWidget *parent) {

    this->setWindowTitle("Create Project");
    QVBoxLayout *layout = new QVBoxLayout(this);

    nameEdit = new QLineEdit;
    descriptionEdit = new QTextEdit;
    pathEdit = new QLineEdit;
    frameRateEdit = new QLineEdit("25");
    resolutionWEdit = new QLineEdit("1920");
    resolutionHEdit = new QLineEdit("1080");

    frameRateEdit->setValidator(new QIntValidator(1, 999, this));
    resolutionWEdit->setValidator(new QIntValidator(1, 100000, this));
    resolutionHEdit->setValidator(new QIntValidator(1, 100000, this));

    layout->addWidget(new QLabel("Project Name: "));
    layout->addWidget(nameEdit);

    QHBoxLayout *pathLayout = new QHBoxLayout();
    layout->addLayout(pathLayout);
    pathLayout->addWidget(new QLabel("Path: "));
    pathLayout->addWidget(pathEdit);
    btnBrowse = new QPushButton("Browse");
    connect(btnBrowse, &QPushButton::clicked, this, &CreateProjectDialog::browse);

    pathLayout->addWidget(btnBrowse);

    layout->addWidget(new QLabel("Description: "));
    layout->addWidget(descriptionEdit);

    QHBoxLayout *frameRateLayout = new QHBoxLayout();
    layout->addLayout(frameRateLayout);
    frameRateLayout->addWidget(new QLabel("Frame Rate: "));
    frameRateLayout->addWidget(frameRateEdit);

    QHBoxLayout *resolutionLayout = new QHBoxLayout();
    layout->addLayout(resolutionLayout);
    resolutionLayout->addWidget(new QLabel("Resolution: "));
    resolutionLayout->addWidget(resolutionWEdit);
    resolutionLayout->addWidget(new QLabel("x"));
    resolutionLayout->addWidget(resolutionHEdit);

    btnOk = new QPushButton("OK");
    btnCancel = new QPushButton("Cancel");
    connect(btnOk, &QPushButton::clicked, this, &CreateProjectDialog::validateInput);
    connect(btnCancel, &QPushButton::clicked, this, &QDialog::reject);

    QHBoxLayout *btnsLayout = new QHBoxLayout();
    layout->addLayout(btnsLayout);
    btnsLayout->addWidget(btnOk);
    btnsLayout->addWidget(btnCancel);

}

void CreateProjectDialog::validateInput() {
    if (!nameEdit->text().isEmpty()) {
        m_project = ProjectModel(0, nameEdit->text(), pathEdit->text(),
                                 descriptionEdit->toPlainText(), true, frameRateEdit->text().toInt(),
                                 resolutionWEdit->text().toInt(), resolutionHEdit->text().toInt()
                                 );
        accept();
    };
}

void CreateProjectDialog::browse() {
    QString dir = QFileDialog::getExistingDirectory(
        this,
        "Choose a project directory",
        QDir::homePath(),
        QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks
        );
    if (!dir.isEmpty()) {
        pathEdit->setText(dir);
    }
}

ProjectModel CreateProjectDialog::project() const {
    return m_project;
}
