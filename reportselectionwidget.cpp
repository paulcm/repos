#include "reportselectionwidget.h"
#include <QMessageBox>
#include <QInputDialog>

#include "separator.h"

ReportSelectionWidget::ReportSelectionWidget(QList<Report *>* reports, QWidget *parent) :
    QWidget(parent)
  ,m_Layout(NULL)
  ,m_LabelSelect(NULL)
  ,m_NodeComboBoxSelectReport(NULL)
  ,m_ComboBoxItemNone("None")
  ,m_ComboBoxItemRename("Rename current Report")
  ,m_ComboBoxItemCreate("Create new Report")
  ,m_ComboBoxItemDelete("Delete current Report")
  ,m_ComboBoxSplitter("_______________________________________")
{
    m_ReportsPtr = reports;
    this->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Preferred);
    this->InitializeWidget();
}

ReportSelectionWidget::~ReportSelectionWidget()
{
}


void ReportSelectionWidget::InitializeWidget()
{
    static bool initialized = false;

    if(initialized == false)
    {
        this->GetLayout()->addWidget(this->GetLabelSelect(),0,0);
        this->GetLayout()->addWidget(this->GetNodeComboBoxSelectReport(),0,1);

        this->GetLayout()->setColumnStretch(1,2);

        this->setLayout(this->GetLayout());
    }
}

void ReportSelectionWidget::UpdateReportSelectorNodeComboBox(Report* currentReport)
{
    this->UpdateListReportNames();

    if(currentReport)
        this->GetNodeComboBoxSelectReport()->Update(currentReport->GetReportName());
    else
        this->GetNodeComboBoxSelectReport()->Update();
}



QGridLayout* ReportSelectionWidget::GetLayout()
{
    if(m_Layout == NULL)
    {
        m_Layout = new QGridLayout(this);
    }

    return m_Layout;
}


QLabel* ReportSelectionWidget::GetLabelSelect()
{
    if(m_LabelSelect == NULL)
    {
        m_LabelSelect = new QLabel("Select Report:", this);
    }

    return m_LabelSelect;
}

NodeComboBox* ReportSelectionWidget::GetNodeComboBoxSelectReport()
{
    if(m_NodeComboBoxSelectReport == NULL)
    {
        m_NodeComboBoxSelectReport = new NodeComboBox("Report",this->UpdateListReportNames(),this);

        connect(m_NodeComboBoxSelectReport, SIGNAL(SignalCreate(QString)), this, SIGNAL(SignalCreateNewReport(QString)) );
        connect(m_NodeComboBoxSelectReport, SIGNAL(SignalDelete(QString)), this, SIGNAL(SignalDeleteReport(QString)) );
        connect(m_NodeComboBoxSelectReport, SIGNAL(SignalRename(QString,QString)), this, SIGNAL(SignalRenameReport(QString,QString)) );
        connect(m_NodeComboBoxSelectReport, SIGNAL(SignalSelected(QString)), this, SIGNAL(SignalChangeReport(QString)) );

        m_NodeComboBoxSelectReport->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Preferred);
    }

    return m_NodeComboBoxSelectReport;
}

QList<QString>* ReportSelectionWidget::UpdateListReportNames()
{
    m_ListReportNames.clear();

    for(int i=0; i < m_ReportsPtr->size(); ++i)
    {
        m_ListReportNames.append(m_ReportsPtr->at(i)->GetReportName());
    }

    return &m_ListReportNames;
}
