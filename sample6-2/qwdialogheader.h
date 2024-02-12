#ifndef QWDIALOGHEADER_H
#define QWDIALOGHEADER_H

#include    <QDialog>
#include    <QStringListModel>
#include    <QStringList>
namespace Ui {
class QWDialogHeader;
}

class QWDialogHeader : public QDialog
{
    Q_OBJECT

public:
    explicit QWDialogHeader(QWidget *parent = nullptr);
    ~QWDialogHeader();

private:
    Ui::QWDialogHeader *ui;
    QStringListModel *listModel;
public:
    void setHeaderList(QStringList&strList);
    QStringList headersList();

};

#endif // QWDIALOGHEADER_H
