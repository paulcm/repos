#ifndef STUDIESTABLE_H
#define STUDIESTABLE_H

#include <QTableWidget>

#include <QCheckBox>

#include "study.h"

class StudiesTable : public QTableWidget
{
    Q_OBJECT
public:
    explicit StudiesTable(QWidget *parent = 0);
    ~StudiesTable();


    void UpdateTable(QList<Study*> studies, const QList<Study*>& allSelectedStudies);

signals:
    void SignalStudySelected(int idx, bool selected);

public slots:


protected:
    void ClearTableContents();

protected slots:
    void SlotTableCheckBoxClicked(bool toggled);

private:
    QList<QCheckBox*> m_ListTableCheckBoxes;
};

#endif // STUDIESTABLE_H
