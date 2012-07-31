#include "analysiswidget.h"
#include "separator.h"

AnalysisWidget::AnalysisWidget(QWidget *parent) :
    QWidget(parent)
  ,m_Layout(NULL)
  ,m_LabelSelectStudy(NULL)
  ,m_ButtonReportSummary(NULL)
  ,m_RadioButtonQualitative(NULL)
  ,m_RadioButtonQuantitative(NULL)
{

    this->InitializeWidget();

}


AnalysisWidget::~AnalysisWidget()
{
    if(m_HBoxLayoutAnalysisTypeBoxes)
        m_HBoxLayoutAnalysisTypeBoxes->deleteLater();
}

void AnalysisWidget::InitializeWidget()
{
    static bool initialized = false;

    if(initialized == false)
    {
        m_HBoxLayoutAnalysisTypeBoxes = new QHBoxLayout();

        m_HBoxLayoutAnalysisTypeBoxes->addWidget(this->GetRadioButtonQualitative(),1,Qt::AlignCenter);
        m_HBoxLayoutAnalysisTypeBoxes->addWidget(this->GetRadioButtonQuantitative(),1,Qt::AlignCenter);

        this->GetLayout()->addLayout(m_HBoxLayoutAnalysisTypeBoxes,1);
        this->GetLayout()->addWidget(new Separator(this));
        this->GetLayout()->addWidget(this->GetLabelSelectStudy());
        this->GetLayout()->addWidget(new Separator(this));
        this->GetLayout()->addWidget(this->GetButtonReportSummary());

        this->setLayout(this->GetLayout());

        initialized = true;
    }
}

void AnalysisWidget::SlotStudyCheckboxToggled(bool toggled)
{
    QCheckBox* sender = (QCheckBox*) QObject::sender();

    int idx = m_StudySelectCheckBoxes.indexOf(sender);

    if(idx != -1)
    {
        if(toggled)
            emit SignalAddStudyToView(idx);
        else
            emit SignalRemoveStudyFromView(idx);
    }
}

QVBoxLayout* AnalysisWidget::GetLayout()
{
    if(m_Layout == NULL)
    {
        m_Layout = new QVBoxLayout(this);
    }

    return m_Layout;
}

QLabel* AnalysisWidget::GetLabelSelectStudy()
{
    if(m_LabelSelectStudy == NULL)
    {
        m_LabelSelectStudy = new QLabel("Select studies for comparison:",this);
    }

    return m_LabelSelectStudy;
}

QPushButton* AnalysisWidget::GetButtonReportSummary()
{
    if(m_ButtonReportSummary == NULL)
    {
        m_ButtonReportSummary = new QPushButton("Show Summary Report",this);

        connect(m_ButtonReportSummary, SIGNAL(clicked()), this, SIGNAL(SignalShowReportSummaryDialog()) );
    }

    return m_ButtonReportSummary;
}

QRadioButton* AnalysisWidget::GetRadioButtonQualitative()
{
    if(m_RadioButtonQualitative == NULL)
    {
        m_RadioButtonQualitative = new QRadioButton("Qualitative",this);

        connect(m_RadioButtonQualitative,SIGNAL(clicked()), this, SIGNAL(SignalQualitativeSelected()));
    }

    return m_RadioButtonQualitative;
}

QRadioButton* AnalysisWidget::GetRadioButtonQuantitative()
{
    if(m_RadioButtonQuantitative == NULL)
    {
        m_RadioButtonQuantitative = new QRadioButton("Quantitative",this);
        connect(m_RadioButtonQuantitative,SIGNAL(clicked()), this, SIGNAL(SignalQuantitativeSelected()));
    }

    return m_RadioButtonQuantitative;
}

void AnalysisWidget::UpdateStudiesList(QStringList input)
{
    for(int i=0; i < m_StudySelectCheckBoxes.size(); ++i)
    {
        this->GetLayout()->removeWidget(m_StudySelectCheckBoxes.at(i));
        m_StudySelectCheckBoxes.value(i)->deleteLater();
    }
    m_StudySelectCheckBoxes.clear();

    for(int j=0; j < input.size(); ++j)
    {
        QCheckBox* cb = new QCheckBox(input.at(j), this);
        cb->setChecked(true);
        cb->setStyleSheet("margin-left: 30px");
        connect(cb,SIGNAL(toggled(bool)),this,SLOT(SlotStudyCheckboxToggled(bool)) );
        this->GetLayout()->insertWidget(3+j,cb);
        m_StudySelectCheckBoxes.append(cb);
    }
}
