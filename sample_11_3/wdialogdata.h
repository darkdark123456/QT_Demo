#ifndef WDIALOGDATA_H
#define WDIALOGDATA_H

#include <QDialog>
#include    <QSql>
#include    <QSqlRecord>
namespace Ui {
class WDialogData;
}

class WDialogData : public QDialog
{
    Q_OBJECT

public:
    explicit WDialogData(QWidget *parent = nullptr);
    ~WDialogData();

private:
    Ui::WDialogData *ui;
    QSqlRecord mRecord;
};

#endif // WDIALOGDATA_H
