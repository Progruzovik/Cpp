#include "widget.h"
#include "ui_widget.h"

#include <QDebug>
#include <QFileDialog>
#include <QTextStream>

Widget::Widget() : QWidget(), isConditionChanged(true), ui(new Ui::Widget)
{
    ui->setupUi(this);
    ui->txtResult->setText("The output window");
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_txtN_textChanged()
{
    isConditionChanged = true;
}

void Widget::on_txtN_editingFinished()
{
   listN = ui->txtN->text().split(QRegExp(","));
   ui->boxS->clear();
   ui->boxS->insertItems(0, listN);
}

void Widget::on_txtT_textChanged()
{
    isConditionChanged = true;
}

void Widget::on_txtP_textChanged()
{
    isConditionChanged = true;
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
    listT = ui->txtT->text().split(QRegExp(","));
    listP = ui->txtP->toPlainText().split(QRegExp("\n"));
    if (listN.isEmpty() || QString(listN[0]).isEmpty() || QString(listT[0]).isEmpty() || QString(listP[0]).isEmpty()) {
        ui->txtResult->setText("Incomplete definition!");
    } else {
        if (isConditionChanged) {
            rules.clear();
            for (int i = 0, l = listN.size(); i < l; i++) {
                QStringList list;
                rules << list;
            }
            foreach (QString s, listP) {
                QStringList list = s.split(QRegExp("->"));
                int index = listN.indexOf(list[0]);
                if (list.size() > 1 && index != -1) {
                    list = list[1].split(QRegExp("[|]"));
                    foreach (QString r, list) {
                        rules[index] << r;
                    }
                }
            }
        }
        QString result, word = listN[ui->boxS->currentIndex()];
        QStringList symbolsN;
        symbolsN << word;
        while (!symbolsN.isEmpty()) {
            result += word + " -> ";
            QString wordNew, symbol = symbolsN.takeFirst();
            int index = listN.indexOf(symbol);
            QStringList transformation = QString(rules[index][qrand() % rules[index].size()]).split("&");
            foreach (QString s, transformation) {
                if (listN.contains(s)) {
                    symbolsN << s;
                    wordNew += s + ' ';
                } else if (listT.contains(s)) {
                    wordNew += s + ' ';
                }
            }
            wordNew.chop(1);
            int symbolIndex = word.indexOf(symbol);
            wordNew = word.left(symbolIndex) + wordNew + word.right(word.size() - symbolIndex - symbol.size());
            result += wordNew + '\n';
            word = wordNew;
            if (result.size() > 100000) {
                result += "==========\nThe output length is too high!\n";
                symbolsN.clear();
            }
        }
        result.chop(1);
        ui->txtResult->setText(result);
    }
}
