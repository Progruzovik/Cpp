#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "grammar.h"

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget();
    ~Widget();

private slots:
    void on_txtN_editingFinished();
    void on_btnOpen_clicked();
    void on_btnSave_clicked();
    void on_btnTest_clicked();

private:
    Grammar grammar;
    Ui::Widget *ui;
};

#endif // WIDGET_H
