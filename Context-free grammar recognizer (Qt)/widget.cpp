#include "widget.h"
#include "ui_widget.h"

#include <QDebug>
#include <QFileDialog>
#include <QTextStream>

Widget::Widget() : QWidget(), ui(new Ui::Widget)
{
    ui->setupUi(this);
    ui->txtResult->setText("The output window");
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_txtN_editingFinished()
{
    QStringList listN = ui->txtN->text().split(QRegExp(","));
    grammar.setListN(listN);
    ui->boxS->clear();
    ui->boxS->insertItems(0, listN);
}

void Widget::on_btnOpen_clicked()
{
    QFile file(QFileDialog::getOpenFileName(this, tr("Load grammar"), qApp->applicationDirPath(), "*.txt"));
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream stream(&file);
        ui->txtN->setText(stream.readLine());
        on_txtN_editingFinished();
        ui->txtT->setText(stream.readLine());
        ui->txtP->setPlainText(stream.readAll());
        file.close();
    }
}

void Widget::on_btnSave_clicked()
{
    QFile file(QFileDialog::getSaveFileName(this, tr("Save grammar"), qApp->applicationDirPath(), "*.txt"));
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream stream(&file);
        stream << ui->txtN->text();
        endl(stream);
        stream << ui->txtT->text();
        endl(stream);
        stream << ui->txtP->toPlainText();
        file.close();
    }
}

void Widget::on_btnTest_clicked()
{
    grammar.setListT(ui->txtT->text().split(QRegExp(",")));
    grammar.setListP(ui->txtP->toPlainText().split(QRegExp("\n")));
    grammar.setStart(ui->boxS->currentIndex());
    if (grammar.isDefinitionIncomplete()) {
        ui->txtResult->setText("Incomplete definition!");
    } else {
        grammar.setRules();
        ui->txtResult->setText(grammar.getRandomWord());
    }
}
