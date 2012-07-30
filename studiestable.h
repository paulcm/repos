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

    void InsertTableRow(bool selected, const QString& date, const QString& time, const QString& modality);
    void ClearTableContents();

    void CheckTableRow(int row);

signals:
    void SignalStudySelected(int idx, bool selected);

public slots:





protected slots:
    void SlotCellChanged(int row, int column);


};

#endif // STUDIESTABLE_H
