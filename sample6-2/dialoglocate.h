#ifndef DIALOGLOCATE_H
#define DIALOGLOCATE_H

#include <QDialog>

namespace Ui {
class DialogLocate;
}

class DialogLocate : public QDialog
{
    Q_OBJECT

public:
    explicit DialogLocate(QWidget *parent = nullptr);
    ~DialogLocate();
private:
    Ui::DialogLocate *ui;
public:
    void setSpinRange(int row,int column);
    void setSpinValue(int row,int column);
private slots:
    void on_btnSetText_clicked();
signals:
    void changeCellText(int row,int column,QString &text);
};

#endif // DIALOGLOCATE_H
