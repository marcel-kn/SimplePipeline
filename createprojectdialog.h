#ifndef CREATEPROJECTDIALOG_H
#define CREATEPROJECTDIALOG_H

#include "models/projectmodel.h"
#include <QDialog>
#include <QLineEdit>
#include <QTextEdit>
#include <QPushButton>
#include <QString>

class CreateProjectDialog : public QDialog
{
    Q_OBJECT

public:
    CreateProjectDialog(QWidget *parent = nullptr);
    ProjectModel project() const;

private:
    QLineEdit *nameEdit;
    QTextEdit *descriptionEdit;
    QLineEdit *pathEdit;
    QLineEdit *frameRateEdit;
    QLineEdit *resolutionWEdit;
    QLineEdit *resolutionHEdit;
    QPushButton *btnBrowse;
    QPushButton *btnOk;
    QPushButton *btnCancel;

    ProjectModel m_project;

private slots:
    void validateInput();
    void browse();
};



#endif // CREATEPROJECTDIALOG_H
