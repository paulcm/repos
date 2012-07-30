#include "studiestable.h"

StudiesTable::StudiesTable(QWidget *parent) :
    QTableWidget(parent)
{

    this->setColumnCount(4);
    this->setRowCount(0);

    this->setColumnWidth(0,18);
    this->setHorizontalHeaderItem(0, new QTableWidgetItem(""));
    this->setColumnWidth(1,100);
    this->setHorizontalHeaderItem(1, new QTableWidgetItem("Date"));
    this->setColumnWidth(2,100);
    this->setHorizontalHeaderItem(2, new QTableWidgetItem("Time"));
    this->setColumnWidth(3,81);
    this->setHorizontalHeaderItem(3, new QTableWidgetItem("Modality"));

    this->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Preferred);

    this->connect(this, SIGNAL(cellChanged(int,int)), this, SLOT(SlotCellChanged(int,int)));
}

StudiesTable::~StudiesTable()
{
}



void StudiesTable::InsertTableRow(bool selected, const QString& date, const QString& time, const QString& modality)
{
    this->disconnect(this, SIGNAL(cellChanged(int,int)), this, SLOT(SlotCellChanged(int,int)));

    int row = this->rowCount();
    int col = 0;

    this->insertRow(row);
    this->setVerticalHeaderItem(row,NULL);

    QTableWidgetItem* checkBoxItem = new QTableWidgetItem();

    if(selected)
        checkBoxItem->setCheckState(Qt::Checked);
    else
        checkBoxItem->setCheckState(Qt::Unchecked);

    this->setItem(row,col++,checkBoxItem);
    this->setItem(row,col++,new QTableWidgetItem(date));
    this->setItem(row,col++,new QTableWidgetItem(time));
    this->setItem(row,col++,new QTableWidgetItem(modality));

    this->connect(this, SIGNAL(cellChanged(int,int)), this, SLOT(SlotCellChanged(int,int)));
}

void StudiesTable::CheckTableRow(int row)
{
    this->disconnect(this, SIGNAL(cellChanged(int,int)), this, SLOT(SlotCellChanged(int,int)));
    this->item(row, 0)->setCheckState(Qt::Checked);
    this->connect(this, SIGNAL(cellChanged(int,int)), this, SLOT(SlotCellChanged(int,int)));
}

void StudiesTable::ClearTableContents()
{
    this->clearContents();

    while(this->rowCount() > 0)
    {
        this->removeRow(this->rowCount()-1);
    }
}


void StudiesTable::SlotCellChanged(int row, int column)
{
    if(column == 0 && this->rowCount() > 0)
    {
        QTableWidgetItem* tempItem = this->item(row,column);

        if(tempItem)
        {
            bool checked = tempItem->checkState() == Qt::Checked;
            emit SignalStudySelected(row,checked);
        }
    }
}
