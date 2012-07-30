#include "findingscolormapdialog.h"

FindingsColorMapDialog::FindingsColorMapDialog(QWidget *parent) :
    QDialog(parent)
  ,m_Layout(NULL)
  ,m_LabelInfo(NULL)
  ,m_ComboBoxColorMap(NULL)
  ,m_ButtonApply(NULL)
  ,m_ButtonCancel(NULL)
  ,m_Applied(false)
{
    m_IconColorMap.addPixmap(QPixmap(":/resources/colormap.png"));

    this->InitializeDialog();
}

FindingsColorMapDialog::~FindingsColorMapDialog()
{
}


void FindingsColorMapDialog::InitializeDialog()
{
    static bool initialized = false;

    if(initialized == false)
    {
        this->GetLayout()->addWidget(this->GetLabelInfo(),0,0,1,2);
        this->GetLayout()->addWidget(this->GetComboBoxColorMap(),1,0,1,2);
        this->GetLayout()->addWidget(this->GetButtonApply(),2,0,1,1);
        this->GetLayout()->addWidget(this->GetButtonCancel(),2,1,1,1);

        this->GetLayout()->setMargin(20);
        this->GetLayout()->setSpacing(20);

        this->setLayout(this->GetLayout());
    }
}

void FindingsColorMapDialog::SlotApply()
{
    m_Applied = true;

    this->close();
}

bool FindingsColorMapDialog::GetApplied()
{
    return m_Applied;
}

void FindingsColorMapDialog::SetApplied(bool applied)
{
    m_Applied = applied;
}


QGridLayout* FindingsColorMapDialog::GetLayout()
{
    if(m_Layout == NULL)
    {
        m_Layout = new QGridLayout(this);
    }

    return m_Layout;
}

QLabel* FindingsColorMapDialog::GetLabelInfo()
{
    if(m_LabelInfo == NULL)
    {
        m_LabelInfo = new QLabel("Select a color table and Apply. In the next step please center the ROI for the Finding by clicking one time to place it's center and a second time to determine it's size", this);
        m_LabelInfo->setWordWrap(true);
    }

    return m_LabelInfo;
}

QComboBox* FindingsColorMapDialog::GetComboBoxColorMap()
{
    if(m_ComboBoxColorMap == NULL)
    {
        m_ComboBoxColorMap = new QComboBox(this);
        m_ComboBoxColorMap->addItem(m_IconColorMap,"Longitudinal PET/CT Analysis Color Table");
    }

    return m_ComboBoxColorMap;
}

QPushButton* FindingsColorMapDialog::GetButtonApply()
{
    if(m_ButtonApply == NULL)
    {
        m_ButtonApply = new QPushButton("Apply",this);
        connect(m_ButtonApply, SIGNAL(clicked()), this, SLOT(SlotApply()) );
    }

    return m_ButtonApply;
}

QPushButton* FindingsColorMapDialog::GetButtonCancel()
{
    if(m_ButtonCancel == NULL)
    {
        m_ButtonCancel = new QPushButton("Cancel",this);
        connect(m_ButtonCancel, SIGNAL(clicked()), this, SLOT(close()));
    }

    return m_ButtonCancel;
}



