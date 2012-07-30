#include "findingswidget.h"

FindingsWidget::FindingsWidget(QList<Finding *>* findings, QWidget *parent) :
    QWidget(parent)
  ,m_Layout(NULL)
  ,m_LabelSelectFinding(NULL)
  ,m_LabelSelectSegmentation(NULL)
  ,m_NodeComboBoxSelectFinding(NULL)
  ,m_NodeComboBoxSelectSegmentation(NULL)
{
    m_FindingsPtr = findings;

    this->InitializeWidget();
}


FindingsWidget::~FindingsWidget()
{
}

void FindingsWidget::SetFindings(QList<Finding*>* findings)
{
    m_FindingsPtr = findings;
}

void FindingsWidget::InitializeWidget()
{
    static bool initialized = false;

    if(initialized == false)
    {
        this->GetLayout()->addWidget(this->GetLabelSelectFinding(),0,0);
        this->GetLayout()->addWidget(this->GetNodeComboBoxSelectFinding(),0,1);
        this->GetLayout()->addWidget(new Separator(this),1,0,1,2);
        this->GetLayout()->addWidget(this->GetLabelSelectSegmentation(),2,0);
        this->GetLayout()->addWidget(this->GetNodeComboBoxSelectSegmentation(),2,1);

        this->GetLayout()->setColumnStretch(1,2);

        this->setLayout(this->GetLayout());
    }
}


QGridLayout* FindingsWidget::GetLayout()
{
    if(m_Layout == NULL)
    {
        m_Layout = new QGridLayout(this);
    }

    return m_Layout;
}

QLabel* FindingsWidget::GetLabelSelectFinding()
{
    if(m_LabelSelectFinding == NULL)
    {
        m_LabelSelectFinding = new QLabel("Select Finding:", this);
    }

    return m_LabelSelectFinding;
}

QLabel* FindingsWidget::GetLabelSelectSegmentation()
{
    if(m_LabelSelectSegmentation == NULL)
    {
        m_LabelSelectSegmentation = new QLabel("Select Segmentation:", this);
    }

    return m_LabelSelectSegmentation;
}

NodeComboBox* FindingsWidget::GetNodeComboBoxSelectFinding()
{
    if(m_NodeComboBoxSelectFinding == NULL)
    {
        m_NodeComboBoxSelectFinding = new NodeComboBox("Finding",this->UpdateFindingNamesList(),this);

        connect(m_NodeComboBoxSelectFinding, SIGNAL(SignalCreate(QString)), this, SIGNAL(SignalCreateNewFinding(QString)) );
        connect(m_NodeComboBoxSelectFinding, SIGNAL(SignalDelete(QString)), this, SIGNAL(SignalDeleteFinding(QString)) );
        connect(m_NodeComboBoxSelectFinding, SIGNAL(SignalRename(QString,QString)), this, SIGNAL(SignalRenameFinding(QString,QString)) );
        connect(m_NodeComboBoxSelectFinding, SIGNAL(SignalSelected(QString)), this, SIGNAL(SignalChangeFinding(QString)) );

        m_NodeComboBoxSelectFinding->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Preferred);
    }

    return m_NodeComboBoxSelectFinding;
}

NodeComboBox* FindingsWidget::GetNodeComboBoxSelectSegmentation()
{
    if(m_NodeComboBoxSelectSegmentation == NULL)
    {
        m_NodeComboBoxSelectSegmentation = new NodeComboBox("Segmentation",this->UpdateSegmentationNamesList(NULL,QDateTime::currentDateTime()),this);

        connect(m_NodeComboBoxSelectSegmentation, SIGNAL(SignalCreate(QString)), this, SIGNAL(SignalCreateNewSegmentation(QString)) );
        connect(m_NodeComboBoxSelectSegmentation, SIGNAL(SignalDelete(QString)), this, SIGNAL(SignalDeleteSegmentation(QString)) );
        connect(m_NodeComboBoxSelectSegmentation, SIGNAL(SignalRename(QString,QString)), this, SIGNAL(SignalRenameSegmentation(QString,QString)) );
        connect(m_NodeComboBoxSelectSegmentation, SIGNAL(SignalSelected(QString)), this, SIGNAL(SignalChangeSegmentation(QString)) );

        m_NodeComboBoxSelectSegmentation->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Preferred);
    }

    return m_NodeComboBoxSelectSegmentation;
}

QList<QString>* FindingsWidget::UpdateFindingNamesList()
{
    m_ListFindingNames.clear();

    if(m_FindingsPtr != NULL)
    {
        for(int i=0; i < m_FindingsPtr->size(); ++i)
        {
            Finding* tempFinding = m_FindingsPtr->at(i);
            m_ListFindingNames.append(tempFinding->GetFindingName());
        }
    }

    return &m_ListFindingNames;
}

QList<QString>* FindingsWidget::UpdateSegmentationNamesList(Finding* finding, QDateTime studyDate)
{
    m_ListSegmentationNames.clear();

    if(finding != NULL)
    {
        for(int i=0; i < finding->GetSegmentations(studyDate).size();++i)
        {
            m_ListSegmentationNames.append(finding->GetSegmentations(studyDate).at(i)->GetSegmentationName());
        }
    }

    return &m_ListSegmentationNames;
}

void FindingsWidget::UpdateFindingsNameListNodeComboBox(Finding* currentFinding)
{
    this->UpdateFindingNamesList();
    //this->UpdateSegmentationNamesList(currentFinding);

    if(currentFinding)
        this->GetNodeComboBoxSelectFinding()->Update(currentFinding->GetFindingName());
    else
        this->GetNodeComboBoxSelectFinding()->Update();

    this->GetNodeComboBoxSelectSegmentation()->Update();
}

void FindingsWidget::UpdateSegmentationNameListNodeComboBox(Finding* currentFinding, Segmentation* currentSegmentation)
{
    if(currentFinding == NULL || currentSegmentation == NULL)
    {
        this->UpdateSegmentationNamesList(currentFinding,QDateTime::currentDateTime());
        this->GetNodeComboBoxSelectSegmentation()->Update();
        return;
    }

    QDateTime dt = currentSegmentation->GetImageSeries()->GetImageSeriesDateTime();

    if(currentFinding->GetSegmentations(dt).contains(currentSegmentation))
    {

        this->UpdateSegmentationNamesList(currentFinding,dt);

        if(currentSegmentation)
            this->GetNodeComboBoxSelectSegmentation()->Update(currentSegmentation->GetSegmentationName());
        else
            this->GetNodeComboBoxSelectSegmentation()->Update();
    }
}
