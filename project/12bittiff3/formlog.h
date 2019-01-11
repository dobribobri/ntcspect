#ifndef FORMLOG_H
#define FORMLOG_H

#include <QWidget>
#include <QTextEdit>

namespace Ui {
class FormLog;
}

class FormLog : public QWidget
{
    Q_OBJECT

public:
    explicit FormLog(QWidget *parent = 0);
    ~FormLog();

    QTextEdit* textEdit;

private:
    Ui::FormLog *ui;
};

#endif // FORMLOG_H
