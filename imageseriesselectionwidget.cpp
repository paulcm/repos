#include "imageseriesselectionwidget.h"

#include "separator.h"

ImageSeriesSelectionWidget::ImageSeriesSelectionWidget(QList<Patient*>* patients, QWidget *parent) :
    QWidget(parent)
  ,m_Layout(NULL)
  ,m_LabelSelectPatient(NULL)
  ,m_NodeComboBoxSelectPatient(NULL)
  ,m_StudiesTable(NULL)
{
    m_PatientsPtr = patients;

    this->InitializeWidget();
}

ImageSeriesSelectionWidget::~ImageSeriesSelectionWidget()
{
}

void ImageSeriesSelectionWidget::LockPatientSelection(bool lock)
{
    this->GetNodeComboBoxSelectPatient()->setDisabled(lock);
    if(lock)
        this->GetNodeComboBoxSelectPatient()->setToolTip("Patient selection has been disabled since there already has been created a finding for the current Patient.\n\nIn order to change the Patient please create a new Report or remove all Findings for the current Patient!");
    else
        this->GetNodeComboBoxSelectPatient()->setToolTip("");
}

void ImageSeriesSelectionWidget::InitializeWidget()
{
    static bool initialized = false;

    if(initialized == false)
    {
        this->GetLayout()->addWidget(this->GetLabelSelectPatient(),0,0);
        this->GetLayout()->addWidget(this->GetNodeComboBoxSelectPatient(),1,0);
        this->GetLayout()->addWidget(new Separator(this),2,0);
        this->GetLayout()->addWidget(this->GetStudiesTable(),3,0);

        this->setLayout(this->GetLayout());
    }
}

void ImageSeriesSelectionWidget::UndoTableRowCheck(int row)
{
    this->GetStudiesTable()->CheckTableRow(row);
}

void ImageSeriesSelectionWidget::UpdateStudiesTable(QList<Study*>* allPatientStudies, const QList<Study*>& selectedPatientStudies)
{
    this->GetStudiesTable()->ClearTableContents();

    if(allPatientStudies == NULL)
        return;

    for(int i=0; i < allPatientStudies->size(); ++i)
    {
        Study* tempStudy = allPatientStudies->value(i);

        bool selected = selectedPatientStudies.contains(tempStudy);

        this->GetStudiesTable()->InsertTableRow(selected,tempStudy->GetDateStr(),tempStudy->GetTimeStr(),tempStudy->GetModalityStr());
    }
}


QGridLayout* ImageSeriesSelectionWidget::GetLayout()
{
    if(m_Layout == NULL)
    {
        m_Layout = new QGridLayout(this);
    }

    return m_Layout;
}

QLabel* ImageSeriesSelectionWidget::GetLabelSelectPatient()
{
    if(m_LabelSelectPatient == NULL)
    {
        m_LabelSelectPatient = new QLabel("Select a Patient from the DICOM Database", this);
    }

    return m_LabelSelectPatient;
}


NodeComboBox* ImageSeriesSelectionWidget::GetNodeComboBoxSelectPatient()
{
    if(m_NodeComboBoxSelectPatient == NULL)
    {
        m_NodeComboBoxSelectPatient = new NodeComboBox("Patient",this->UpdatePatientNamesList(),this);
        m_NodeComboBoxSelectPatient->HideOperator(NodeComboBox::DELETE);
        m_NodeComboBoxSelectPatient->HideOperator(NodeComboBox::CREATE);
        m_NodeComboBoxSelectPatient->HideOperator(NodeComboBox::RENAME);
        m_NodeComboBoxSelectPatient->HideOperator(NodeComboBox::SEPPARATOR);

        m_NodeComboBoxSelectPatient->Update();

        connect(m_NodeComboBoxSelectPatient, SIGNAL(SignalSelected(QString)), this, SIGNAL(SignalPatientChanged(QString)) );
    }

    return m_NodeComboBoxSelectPatient;
}

QList<QString>* ImageSeriesSelectionWidget::UpdatePatientNamesList()
{
    m_ListPatientNames.clear();

    for(int i=0; i < m_PatientsPtr->size(); ++i)
    {
        Patient* tempPat = m_PatientsPtr->at(i);
        m_ListPatientNames.append(tempPat->GetName());
    }

    return &m_ListPatientNames;
}

 void ImageSeriesSelectionWidget::UpdatePatientsNamesListNodeComboBox(Patient* currentPatient)
 {
     this->UpdatePatientNamesList();

     if(currentPatient)
         this->GetNodeComboBoxSelectPatient()->Update(currentPatient->GetName());
     else
         this->GetNodeComboBoxSelectPatient()->Update();
 }

 StudiesTable* ImageSeriesSelectionWidget::GetStudiesTable()
 {
     if(m_StudiesTable == NULL)
     {
         m_StudiesTable = new StudiesTable(this);

         connect(m_StudiesTable, SIGNAL(SignalStudySelected(int,bool)), this, SIGNAL(SignalStudySelected(int,bool)) );
     }

     return m_StudiesTable;
 }
