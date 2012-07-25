#include "reportselectionwidget.h"
#include <QMessageBox>
#include <QInputDialog>

#include "separator.h"

ReportSelectionWidget::ReportSelectionWidget(QList<Report *>* reports, QWidget *parent) :
    QWidget(parent)
  ,m_Layout(NULL)
  ,m_LabelInfo(NULL)
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
        this->GetLayout()->addWidget(this->GetLabelInfo(),0,0,1,2,Qt::AlignLeft);
        this->GetLayout()->addWidget(new Separator(this),1,0,1,2);

        this->GetLayout()->addWidget(this->GetLabelSelect(),2,0,1,1,Qt::AlignRight);
        this->GetLayout()->addWidget(this->GetNodeComboBoxSelectReport(),2,1,1,1,Qt::AlignLeft);

        this->GetLayout()->setColumnStretch(0,1);
        this->GetLayout()->setColumnStretch(1,3);

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

void ReportSelectionWidget::SlotCreateReport()
{
    QString name = QInputDialog::getText(NULL,"Create Report","Name:");

    if(!name.isEmpty())
        emit SignalCreateNewReport(name);
}

void ReportSelectionWidget::SlotRenameReport(const QString& oldname)
{
    this->GetNodeComboBoxSelectReport()->SetCurrentIndex(oldname);

    QString rename = QInputDialog::getText(NULL,"Rename Report","Name:",QLineEdit::Normal, oldname);

    if(!rename.isEmpty())
        emit SignalRenameReport(oldname,rename);
}

void ReportSelectionWidget::SlotDeleteReport(const QString& name)
{
    this->GetNodeComboBoxSelectReport()->SetCurrentIndex(name);

    int ret = QMessageBox::question(NULL,"Delete Report", "Are you sure you want to delete "+name+"?",QMessageBox::Yes,QMessageBox::Cancel);

    if(ret == QMessageBox::Yes)
        emit SignalDeleteReport(name);
}


QGridLayout* ReportSelectionWidget::GetLayout()
{
    if(m_Layout == NULL)
    {
        m_Layout = new QGridLayout(this);
    }

    return m_Layout;
}

QLabel* ReportSelectionWidget::GetLabelInfo()
{
    if(m_LabelInfo == NULL)
    {
        m_LabelInfo = new QLabel("Create a new Report or select an existing one", this);
        //m_LabelInfo->setWordWrap(true);
        m_LabelInfo->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Preferred);
    }

    return m_LabelInfo;
}

QLabel* ReportSelectionWidget::GetLabelSelect()
{
    if(m_LabelSelect == NULL)
    {
        m_LabelSelect = new QLabel("Select Report", this);
    }

    return m_LabelSelect;
}

NodeComboBox* ReportSelectionWidget::GetNodeComboBoxSelectReport()
{
    if(m_NodeComboBoxSelectReport == NULL)
    {
        m_NodeComboBoxSelectReport = new NodeComboBox("Report",this->UpdateListReportNames(),this);

        connect(m_NodeComboBoxSelectReport, SIGNAL(SignalCreate()), this, SLOT(SlotCreateReport()) );
        connect(m_NodeComboBoxSelectReport, SIGNAL(SignalDelete(QString)), this, SLOT(SlotDeleteReport(QString)) );
        connect(m_NodeComboBoxSelectReport, SIGNAL(SignalRename(QString)), this, SLOT(SlotRenameReport(QString)) );
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
