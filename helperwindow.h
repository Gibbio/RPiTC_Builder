#ifndef HELPERWINDOW_H
#define HELPERWINDOW_H

#include <QDialog>

namespace Ui {
class HelperWindow;
}

class HelperWindow : public QDialog
{
    Q_OBJECT

public:
    explicit HelperWindow(QWidget *parent = 0);
    ~HelperWindow();

private slots:

    void on_terminalopen_pushButton_clicked();

    void on_savebashmesh_pushButton_clicked();

    void on_backtobuilder_pushButton_clicked();

private:
    Ui::HelperWindow *hui;
};

#endif // HELPERWINDOW_H
