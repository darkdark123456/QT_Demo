#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

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
    void on_count_clicked();

    void on_size_clicked();

    void on_upper_clicked();

    void on_lower_clicked();

    void on_is_empty_clicked();

    void on_is_null_clicked();

    void on_append_clicked();

    void on_prepend_clicked();

    void on_indexof_clicked();

    void on_lastindexof_clicked();

    void on_right_clicked();

    void on_left_clicked();

    void on_trimm_clicked();

    void on_section_clicked();

    void on_contains_clicked();

    void on_endwith_clicked();

    void on_stratswith_clicked();

private:
    Ui::Widget *ui;
};
#endif // WIDGET_H
