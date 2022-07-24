#include "memorytable.h"
#include "ui_memorytable.h"

MemoryTable::MemoryTable(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MemoryTable)
{
    ui->setupUi(this);
    MemoryTable::MemoryTypeCBIndex = 0;
    MemoryTable::VTCBIndex = 0;
    MemoryTable::BisrCBIndex = 0;
    MemoryTable::SortCBIndex = 0;
    addConfTablePage();
}

MemoryTable::~MemoryTable()
{
    delete ui;
}

/*
 * Because widget's index will modified after deleting other widget,
 * So need to update ConfTableMap.
*/
void MemoryTable::updateConfTableMap(int widgetIndex)
{
    int index = widgetIndex;
    for ( ; index < MemoryTable::ConfTableMap.size()-1 ; index++)
        MemoryTable::ConfTableMap[index] = MemoryTable::ConfTableMap.value(index+1);

    auto found = ConfTableMap.find(index+1);
    MemoryTable::ConfTableMap.erase(found);
}

void MemoryTable::updateComboBoxMap()
{


}

void MemoryTable::addComboBox(QTableWidget *tableWidget, int row)
{
    QComboBox *memoryType = new QComboBox;
    QComboBox *bisr = new QComboBox;
    QComboBox *vt = new QComboBox;
    QComboBox *sort = new QComboBox;
    QStringList memTypeOption = {"1P", "2P", "P2P", "DP"};
    QStringList bisrOption = {"True", "False"};
    QStringList vtOption = {" ","Low", "Standard", "High"};
    QStringList sortOption = {"Area", "Taa", "Freq.", "Dc", "Ac"};
    memoryType->addItems(memTypeOption);
    bisr->addItems(bisrOption);
    vt->addItems(vtOption);
    sort->addItems(sortOption);

    tableWidget->setCellWidget(row, 0, memoryType);
    tableWidget->setCellWidget(row, 4, bisr);
    tableWidget->setCellWidget(row, 5, vt);
    tableWidget->setCellWidget(row, 7, sort);

    MemoryTable::MemoryTypeComboBoxMap[MemoryTable::MemoryTypeCBIndex++] = memoryType;
    MemoryTable::MemoryTypeComboBoxMap[MemoryTable::BisrCBIndex++] = bisr;
    MemoryTable::MemoryTypeComboBoxMap[MemoryTable::VTCBIndex++] = vt;
    MemoryTable::MemoryTypeComboBoxMap[MemoryTable::SortCBIndex++] = memoryType;
}

void MemoryTable::addConfTablePage()
{
    QWidget *newPage = new QWidget(this);
    QTableWidget *newTable = new QTableWidget(newPage);
    QStringList confOption = {"Memory Type", "Word", "Bit", "Byte", "Bisr", "Vt", "Frequency", "Sort"};
    newTable->setColumnCount(confOption.size());
    newTable->setRowCount(1);
    newTable->setHorizontalHeaderLabels(confOption);
    newTable->resize(ui->tabWidget->size());

    addComboBox(newTable, 0);

    int widgetIndex = ui->tabWidget->addTab(newPage, "Tab");
    MemoryTable::ConfTableMap[widgetIndex] = newTable;
}

void MemoryTable::on_AddTable_clicked()
{
    addConfTablePage();
}

void MemoryTable::on_AddConf_clicked()
{
    int widgetIndex = ui->tabWidget->currentIndex();
    auto found = MemoryTable::ConfTableMap.find(widgetIndex);
    if (found == MemoryTable::ConfTableMap.end()) {
        qDebug() << "Widget id: " << widgetIndex << " ConfTableMap Failed!" ;
        QApplication::quit();
    }

    QTableWidget *tableWidget = found.value();
    int row = tableWidget->rowCount();
    tableWidget->setRowCount(row+1);

    addComboBox(tableWidget, row);

}

void MemoryTable::on_DeleteLastConf_clicked()
{
    int widgetIndex = ui->tabWidget->currentIndex();
    auto found = MemoryTable::ConfTableMap.find(widgetIndex);
    if (found == MemoryTable::ConfTableMap.end()) {
        qDebug() << "Widget id: " << widgetIndex << " ConfTableMap Failed!" ;
        QApplication::quit();
    }

    QTableWidget *tableWidget = found.value();
    int row = tableWidget->rowCount();
    tableWidget->setRowCount(row-1);
}

void MemoryTable::on_DeleteTable_clicked()
{
    int widgetIndex = ui->tabWidget->currentIndex();
    ui->tabWidget->removeTab(widgetIndex);
    auto found = MemoryTable::ConfTableMap.find(widgetIndex);
    if (found == MemoryTable::ConfTableMap.end()) {
        qDebug() << "Widget id: " << widgetIndex << " ConfTableMap Failed!" ;
        QApplication::quit();
    }

    MemoryTable::ConfTableMap.erase(found);
    updateConfTableMap(widgetIndex);
}

void MemoryTable::on_Cancel_clicked()
{
    QApplication::quit();
}

void MemoryTable::openFile(QFile *file)
{
    if(!file->open(QIODevice::ReadWrite)) {
        qDebug() << "Open File Failed!";
        QApplication::quit();
    }
}

void MemoryTable::outputFile(QFile *file)
{
    qDebug() << "1";
    QTextStream stream(file);
    qDebug() << "2";
    for (int tableIndex = 0 ; MemoryTable::ConfTableMap.size() ; tableIndex++) {
        auto table = MemoryTable::ConfTableMap.value(tableIndex);
        qDebug() << "3";
        for (int row = 1 ; table->rowCount() ; row++) {
            for (int col = 0 ; table->columnCount() ; col++) {
                switch(col) {
                    case 0 :
                        qDebug() << "5";
                        stream << "-type " << table->item(row, col)->data(Qt::DisplayRole).toString() << Qt::endl;
                        qDebug() << table->item(row, col)->data(Qt::DisplayRole).toString();
                        break;
                    case 1:
                        stream << "-word " << table->item(row, col)->data(Qt::DisplayRole).toString() << Qt::endl;
                        break;
                    case 2:
                        stream << "-bit " << table->item(row, col)->data(Qt::DisplayRole).toString() << Qt::endl;
                        break;
                    case 3:
                        stream << "-byte " << table->item(row, col)->data(Qt::DisplayRole).toString() << Qt::endl;
                        break;
                    case 4:
                        stream << "-bisr " << table->item(row, col)->data(Qt::DisplayRole).toString() << Qt::endl;
                        break;
                    case 5:
                        if (table->item(row, col)->data(Qt::DisplayRole).toString() != " ") {
                            stream << "-vt " << table->item(row, col)->data(Qt::DisplayRole).toString() << Qt::endl;
                        }
                        break;
                    case 6:
                        stream << "-freq " << table->item(row, col)->data(Qt::DisplayRole).toString() << Qt::endl;
                        break;
                    case 7:
                        stream << "-sort " << table->item(row, col)->data(Qt::DisplayRole).toString() << Qt::endl;
                        break;
                }
            }
        }
    }
}

void MemoryTable::on_Generate_clicked()
{
    QString fileName = "conf.txt";
    QFile conf(fileName);
    openFile(&conf);
    qDebug() << "Open File OK";
    outputFile(&conf);
    conf.close();
    QApplication::quit();
}

