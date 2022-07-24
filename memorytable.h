#ifndef MEMORYTABLE_H
#define MEMORYTABLE_H

#include <QDialog>
#include <QTableWidget>
#include <QComboBox>
#include <QStringList>
#include <QWidget>
#include <QDebug>
#include <QMap>
#include <QFile>

using namespace std;

namespace Ui {
class MemoryTable;
}

class MemoryTable : public QDialog
{
    Q_OBJECT

public:
    explicit MemoryTable(QWidget *parent = nullptr);
    ~MemoryTable();

private slots:
    void on_AddTable_clicked();
    void on_DeleteTable_clicked();
    void on_AddConf_clicked();
    void on_DeleteLastConf_clicked();

    void on_Cancel_clicked();

    void on_Generate_clicked();

private:
    void addComboBox(QTableWidget *tableWidget, int row);
    void addConfTablePage();
    void updateConfTableMap(int widgetIndex);
    void updateComboBox();
    void openFile(QFile *file);
    void outputFile(QFile *file);

    Ui::MemoryTable *ui;
    QMap<int, QTableWidget*> ConfTableMap;
    QMap<int, QComboBox*> MemoryTypeComboBoxMap;
    QMap<int, QComboBox*> BisrComboBoxMap;
    QMap<int, QComboBox*> VTComboBoxMap;
    QMap<int, QComboBox*> SortComboBoxMap;
    int MemoryTypeCBIndex;
    int BisrCBIndex;
    int VTCBIndex;
    int SortCBIndex;
};

#endif // MEMORYTABLE_H
