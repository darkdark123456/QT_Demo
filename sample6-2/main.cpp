#include "mainwindow.h"

#include <QApplication>
#include    <qdialoglogin.h>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QDialogLogin *dlgLogin=new QDialogLogin();
    if(dlgLogin->exec()==QDialog::Accepted){
        MainWindow w;
        w.show();
        return a.exec();
    }
    else{
        return 0;
    }

}
