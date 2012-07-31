#include "reporttree.h"

#include <iostream>

ReportTree::ReportTree(QWidget *parent) :
    QTreeWidget(parent)
{
    this->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Preferred);
    this->connect(this,SIGNAL(itemClicked(QTreeWidgetItem*,int)),this,SLOT(SlotItemClicked(QTreeWidgetItem*,int)));
    this->headerItem()->setText(0,"Findings");
}

ReportTree::~ReportTree()
{
}


void ReportTree::UpdateTree(const QList<TreeInput>& input)
{
    this->clear();

    for(int i=0; i < input.size(); ++i)
    {

        QTreeWidgetItem* findingItem = new QTreeWidgetItem(QStringList(input.value(i).findingName));

        std::cout << "TLI count before " << this->topLevelItemCount() << std::endl;
        this->invisibleRootItem()->addChild(findingItem);
        std::cout << "TLI count after " << this->topLevelItemCount() << std::endl;
        for(int j=0; j < input.value(i).segmentationNames.size(); ++j)
        {
            QTreeWidgetItem* segmentationItem = new QTreeWidgetItem(QStringList(input.value(i).segmentationNames.at(j)));
            findingItem->addChild(segmentationItem);
            findingItem->setExpanded(true);
        }
    }
}

void ReportTree::SlotItemClicked(QTreeWidgetItem* item, int column)
{
    QString positionCode;

    for(int i=0; i < this->invisibleRootItem()->childCount(); ++i)
    {
        if(this->invisibleRootItem()->child(i) == item)
            positionCode.setNum(i);
        else
        {
            for(int j=0; j < this->invisibleRootItem()->child(i)->childCount(); ++j)
            {
                if(this->invisibleRootItem()->child(i)->child(j) == item)
                    positionCode.setNum(i) += QString().setNum(j);
            }
        }
    }

    emit SignalItemSelected(positionCode);

}


