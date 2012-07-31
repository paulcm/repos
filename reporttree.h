#ifndef REPORTTREE_H
#define REPORTTREE_H

#include <QTreeWidget>



class ReportTree : public QTreeWidget
{
    Q_OBJECT
public:
    explicit ReportTree(QWidget *parent = 0);
    ~ReportTree();

    struct TreeInput {
        QString findingName;
        QStringList segmentationNames;
    };


    void UpdateTree(const QList<TreeInput>& input);


signals:
    void SignalItemSelected(const QString& positionCode);


protected slots:
    void SlotItemClicked(QTreeWidgetItem* item, int column);
    
protected:
    QTreeModel* GetModel();



};

#endif // REPORTTREE_H
