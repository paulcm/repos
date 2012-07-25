#ifndef IMAGESERIESSELECTIONWIDGET_H
#define IMAGESERIESSELECTIONWIDGET_H

#include <QWidget>
#include <QGridLayout>
#include <QLabel>
#include <QComboBox>
#include <QTableWidget>
#include <QCheckBox>
#include <QList>
#include <QMap>
#include "nodecombobox.h"
#include "studiestable.h"

#include "patient.h"
#include "study.h"

class ImageSeriesSelectionWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ImageSeriesSelectionWidget(QList<Patient*>* patients, QWidget *parent = 0);
    ~ImageSeriesSelectionWidget(void);
    
    void UpdatePatientsNamesListNodeComboBox(const QString& selected);

    void UpdateStudiesTable(Patient* patient, const QList<Study*>& allSelectedStudies);

signals:
//    void SignalImageSeriesSelected(int idx);
//    void SignalImageSeriesDeselected(int idx);
      void SignalPatientChanged(const QString& name);
      void SignalStudySelected(int idx, bool selected);

public slots:
//    void SlotAddPatient(const Patient* patient);


protected:
     QGridLayout* GetLayout();
     QLabel* GetLabelSelectPatient();
     NodeComboBox* GetNodeComboBoxSelectPatient();
     StudiesTable* GetStudiesTable();

     QList<QString>* UpdatePatientNamesList();

     void InitializeWidget();

protected slots:
    //void SlotPatientChanged(const QString& name);

private:
    QGridLayout* m_Layout;
    QLabel* m_LabelSelectPatient;
    NodeComboBox* m_NodeComboBoxSelectPatient;
    StudiesTable* m_StudiesTable;

    QList<Patient*>* m_PatientsPtr;
    QList<Study*>* m_StudiesPtr;
    QList<QString> m_ListPatientNames;


//    QList<Patient*> m_Patients;
//    QList<QCheckBox*> m_CheckBoxes;
};

#endif // IMAGESERIESSELECTIONWIDGET_H
