#include "studysliderwidget.h"

#include <iostream>

StudySliderWidget::StudySliderWidget(QWidget *parent) :
    QWidget(parent)
  ,m_Layout(NULL)
  ,m_LabelInfo(NULL)
  ,m_LabelSelectedStudy(NULL)
  ,m_SliderStudySelector(NULL)
{
    this->InitializeWidget();
}

StudySliderWidget::~StudySliderWidget()
{
}


void StudySliderWidget::UpdateValues(int min, int max, int selected, QString label)
{
    if(selected < min || selected > max)
        return;

    this->GetSliderStudySelector()->setMinimum(min);
    this->GetSliderStudySelector()->setMaximum(max);
    this->GetSliderStudySelector()->setValue(selected);
    this->GetLabelSelectedStudy()->setText(label);
}

int StudySliderWidget::GetSliderPosition()
{
    return this->GetSliderStudySelector()->value();
}

void StudySliderWidget::InitializeWidget()
{
    static bool initialized = false;

    if(initialized == false)
    {
        int row = 0;

        this->GetLayout()->addWidget(this->GetLabelInfo(),row,0,1,1,Qt::AlignLeft);
        this->GetLayout()->addWidget(this->GetLabelSelectedStudy(),row,1,1,1,Qt::AlignLeft);
        row++;
        this->GetLayout()->addWidget(this->GetSliderStudySelector(),row,0,1,2);
        row++;
        this->GetLayout()->addItem(new QSpacerItem(20,1,QSizePolicy::Minimum,QSizePolicy::Expanding),row,1,1,2);

        this->GetLayout()->setColumnStretch(0,0);
        this->GetLayout()->setColumnStretch(1,2);

        this->setLayout(this->GetLayout());

        initialized = true;
    }
}


QLabel* StudySliderWidget::GetLabelInfo()
{
    if(m_LabelInfo == NULL)
    {
        m_LabelInfo = new QLabel("Current Timepoint:", this);
    }

    return m_LabelInfo;
}

QLabel* StudySliderWidget::GetLabelSelectedStudy()
{
    if(m_LabelSelectedStudy == NULL)
    {
        m_LabelSelectedStudy = new QLabel("T",this);
        m_LabelSelectedStudy->setAlignment(Qt::AlignLeft);
        m_LabelSelectedStudy->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Preferred);
    }

    return m_LabelSelectedStudy;
}

QSlider* StudySliderWidget::GetSliderStudySelector()
{
    if(m_SliderStudySelector == NULL)
    {
        m_SliderStudySelector = new QSlider(Qt::Horizontal, this);
        m_SliderStudySelector->setTickPosition(QSlider::TicksBelow);
        m_SliderStudySelector->setMinimum(0);

        m_SliderStudySelector->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Preferred);

        connect(m_SliderStudySelector, SIGNAL(valueChanged(int)), this, SIGNAL(SignalSliderPositionChanged(int)) );

        this->UpdateValues();
    }

    return m_SliderStudySelector;
}

QGridLayout* StudySliderWidget::GetLayout()
{
    if(m_Layout == NULL)
    {
        m_Layout = new QGridLayout(this);
    }

    return m_Layout;
}
