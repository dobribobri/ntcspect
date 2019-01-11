#include "formlog.h"
#include "ui_formlog.h"

FormLog::FormLog(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormLog)
{
    ui->setupUi(this);
    this->textEdit = ui->textEdit;
}

FormLog::~FormLog()
{
    delete ui;
}
