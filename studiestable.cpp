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

}

StudiesTable::~StudiesTable()
{
}



void StudiesTable::UpdateTable(QList<Study*> studies, const QList<Study*>& allSelectedStudies)
{
    this->ClearTableContents();

    for(int i=0; i < studies.size(); ++i)
    {
        Study* tempStudy = studies.at(i);

        this->insertRow(i);
        this->setVerticalHeaderItem(i,NULL);

        QCheckBox* cb = new QCheckBox(this);
        connect(cb, SIGNAL(toggled(bool)), this, SLOT(SlotTableCheckBoxClicked(bool)) );

        if(allSelectedStudies.contains(tempStudy))
            cb->setChecked(true);
        else
            cb->setChecked(false);

        m_ListTableCheckBoxes.append(cb);

        int col = 0;


        this->setCellWidget(i,col++,cb);
        this->setItem(i,col++,new QTableWidgetItem(tempStudy->GetDateStr()));
        this->setItem(i,col++,new QTableWidgetItem(tempStudy->GetTimeStr()));
        this->setItem(i,col++,new QTableWidgetItem(tempStudy->GetModalityStr()));

    }


}

void StudiesTable::ClearTableContents()
{


    int i;

    for(i=0; i < m_ListTableCheckBoxes.size();++i)
    {
        m_ListTableCheckBoxes.at(i)->deleteLater();
    }
    m_ListTableCheckBoxes.clear();

    for(;this->rowCount() > 0;)
    {
        this->removeRow(this->rowCount()-1);
    }
}


void StudiesTable::SlotTableCheckBoxClicked(bool toggled)
{
    QCheckBox* senderCB = (QCheckBox*) QObject::sender();

    for(int i=0; i < m_ListTableCheckBoxes.size(); ++i)
    {
        if(m_ListTableCheckBoxes.at(i) == senderCB)
            emit SignalStudySelected(i,toggled);
    }
}
