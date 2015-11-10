#include "helperwindow.h"
#include "ui_helperwindow.h"
#include <QTextStream>
#include <QFile>

HelperWindow::HelperWindow(QWidget *parent) :
    QDialog(parent),
    hui(new Ui::HelperWindow)
{
    hui->setupUi(this);
    QFile file("/opt/bashme.sh");
    file.open(QFile::ReadWrite | QFile::Text);
    QTextStream ReadFile(&file);
    hui->bashmesh_plainTextEdit->setPlainText(ReadFile.readAll());
}

HelperWindow::~HelperWindow()
{
    delete hui;
}

void HelperWindow::on_backtobuilder_pushButton_clicked()
{
    close();
}

void HelperWindow::on_terminalopen_pushButton_clicked()
{
    system(qPrintable("xterm -title RPiTC_BASHME! -geometry 180x40 -e 'cd /opt && echo \"# Now you can run ./bashme.sh\" && bash' &"));
}

void HelperWindow::on_savebashmesh_pushButton_clicked()
{
    //updating bashme.sh script...
    QFile file("/opt/bashme.sh");
    file.open(QIODevice::Truncate | QIODevice::Text | QIODevice::ReadWrite);
    QTextStream SaveFile(&file);
    SaveFile << hui->bashmesh_plainTextEdit->toPlainText();
    file.flush();
    file.close();
}
