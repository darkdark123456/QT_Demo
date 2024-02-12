#ifndef TREEWIDGET_H
#define TREEWIDGET_H

#include <QMainWindow>
#include    <QFileDialog>
#include    <QTreeWidgetItem>
QT_BEGIN_NAMESPACE
namespace Ui { class treeWidget; }
QT_END_NAMESPACE

class treeWidget : public QMainWindow
{
    Q_OBJECT

public:
    treeWidget(QWidget *parent = nullptr);
    ~treeWidget();
public:
    void addDirectoryItem(QTreeWidgetItem *item,QString dir);
    QString getFinalDirectoryName(const QString &fullPathName);

private slots:
    void on_actAddDirectory_triggered();

    void on_actAddFile_triggered();

    void on_actDeleteItem_triggered();

   void on_actDisplay_triggered();

private:
    Ui::treeWidget *ui;
};
#endif // TREEWIDGET_H
