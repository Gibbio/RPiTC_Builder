#ifndef RPITC_H
#define RPITC_H

#include <QMainWindow>
#include "helperwindow.h"

namespace Ui {
class RPiTC;
}

class RPiTC : public QMainWindow
{
    Q_OBJECT

public:
    explicit RPiTC(QWidget *parent = 0);
    ~RPiTC();

private slots:
    void on_pushButton_clicked();

    void on_rescan_pushButton_clicked();

    void on_searchfile_pushButton_clicked();

    void on_ica_checkBox_toggled(bool checked);

public:
    Ui::RPiTC *ui;
};

#endif // RPITC_H
