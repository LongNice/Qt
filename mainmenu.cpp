#include "mainmenu.h"
#include "ui_mainmenu.h"


MainMenu::MainMenu(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainMenu)
{
    ui->setupUi(this);
}

MainMenu::~MainMenu()
{
    delete ui;
}


void MainMenu::on_pushButton_clicked()
{
    MainMenu::memoryTable = new MemoryTable;
    memoryTable->show();
    hide();
}

