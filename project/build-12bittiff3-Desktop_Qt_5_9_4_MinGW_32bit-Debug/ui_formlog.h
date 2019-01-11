/********************************************************************************
** Form generated from reading UI file 'formlog.ui'
**
** Created by: Qt User Interface Compiler version 5.9.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FORMLOG_H
#define UI_FORMLOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_FormLog
{
public:
    QTextEdit *textEdit;

    void setupUi(QWidget *FormLog)
    {
        if (FormLog->objectName().isEmpty())
            FormLog->setObjectName(QStringLiteral("FormLog"));
        FormLog->resize(400, 300);
        FormLog->setMinimumSize(QSize(400, 300));
        FormLog->setMaximumSize(QSize(400, 300));
        textEdit = new QTextEdit(FormLog);
        textEdit->setObjectName(QStringLiteral("textEdit"));
        textEdit->setGeometry(QRect(0, 0, 401, 301));

        retranslateUi(FormLog);

        QMetaObject::connectSlotsByName(FormLog);
    } // setupUi

    void retranslateUi(QWidget *FormLog)
    {
        FormLog->setWindowTitle(QApplication::translate("FormLog", "Log", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class FormLog: public Ui_FormLog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FORMLOG_H
