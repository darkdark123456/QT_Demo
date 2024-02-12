#ifndef WIDGET_H
#define WIDGET_H

#include    <QWidget>
#include    <QDateTime>
QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void on_toolButton_clicked();

    void on_calendarWidget_selectionChanged();

    void on_toolButton_7_clicked();

    void on_toolButton_5_clicked();

    void on_toolButton_9_clicked();

private:
    Ui::Widget *ui;
};
#endif // WIDGET_H
