#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

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
    void on_txtN_textChanged();
    void on_txtN_editingFinished();
    void on_txtT_textChanged();
    void on_txtP_textChanged();
    void on_btnOpen_clicked();
    void on_btnSave_clicked();
    void on_btnTest_clicked();

private:
    bool isConditionChanged;
    QStringList listN;
    QStringList listT;
    QStringList listP;
    QVector<QStringList> rules;
    Ui::Widget *ui;
};

#endif // WIDGET_H
