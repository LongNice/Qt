#ifndef MAINMENU_H
#define MAINMENU_H

#include <QMainWindow>
#include "memorytable.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainMenu; }
QT_END_NAMESPACE

class MainMenu : public QMainWindow
{
    Q_OBJECT

public:
    MainMenu(QWidget *parent = nullptr);
    ~MainMenu();

private slots:
    void on_pushButton_clicked();

private:
    Ui::MainMenu *ui;
    MemoryTable *memoryTable;
};
#endif // MAINMENU_H
