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


void ImageSeriesSelectionWidget::UpdateStudiesTable(Patient* patient, const QList<Study *>& allSelectedStudies)
{
    QList<Study*> studiesList;

    if(patient == NULL)
        this->GetStudiesTable()->UpdateTable(studiesList, allSelectedStudies);

    else
        this->GetStudiesTable()->UpdateTable(*patient->GetStudies(), allSelectedStudies);
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

 void ImageSeriesSelectionWidget::UpdatePatientsNamesListNodeComboBox(const QString& selected)
 {
    this->UpdatePatientNamesList();
    this->GetNodeComboBoxSelectPatient()->Update(selected);
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
