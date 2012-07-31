#include "findingscolormapdialog.h"

#include "separator.h"

FindingsColorMapDialog::FindingsColorMapDialog(QWidget *parent) :
    QDialog(parent)
  ,m_Layout(NULL)
  ,m_LabelMapInfo(NULL)
  ,m_LabelColorInfo(NULL)
  ,m_ComboBoxColorMap(NULL)
  ,m_ComboBoxLabelColors(NULL)
  ,m_ButtonApply(NULL)
  ,m_ButtonCancel(NULL)
  ,m_Applied(false)
{
    m_IconColorMap.addPixmap(QPixmap(":/resources/colormap.png"));
    m_IconColorTumor.addPixmap(QPixmap(":/resources/colormap_tumor.png"));
    m_IconColorNode.addPixmap(QPixmap(":/resources/colormap_node.png"));
    m_IconColorMetastasis.addPixmap(QPixmap(":/resources/colormap_metastasis.png"));
    m_IconColorReference.addPixmap(QPixmap(":/resources/colormap_reference.png"));

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
        this->GetLayout()->addWidget(this->GetLabelMapInfo(),0,0,1,1);
        this->GetLayout()->addWidget(this->GetComboBoxColorMap(),0,1,1,2);

        this->GetLayout()->addWidget(new Separator(this),1,0,1,3);

        this->GetLayout()->addWidget(this->GetLabelColorInfo(),2,0,1,1);
        this->GetLayout()->addWidget(this->GetComboBoxLabelColors(),2,1,1,2);


        this->GetLayout()->addWidget(this->GetButtonApply(),3,1,1,1);
        this->GetLayout()->addWidget(this->GetButtonCancel(),3,2,1,1);

        this->GetLayout()->setMargin(20);
        this->GetLayout()->setSpacing(20);

        this->setLayout(this->GetLayout());

        initialized = true;
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

QLabel* FindingsColorMapDialog::GetLabelMapInfo()
{
    if(m_LabelMapInfo == NULL)
    {
        m_LabelMapInfo = new QLabel("Select color table:", this);
    }

    return m_LabelMapInfo;
}

QLabel* FindingsColorMapDialog::GetLabelColorInfo()
{
    if(m_LabelColorInfo == NULL)
    {
        m_LabelColorInfo = new QLabel("Select type of Finding:", this);
    }

    return m_LabelColorInfo;
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

QComboBox* FindingsColorMapDialog::GetComboBoxLabelColors()
{
    if(m_ComboBoxLabelColors == NULL)
    {
        m_ComboBoxLabelColors = new QComboBox(this);
        m_ComboBoxLabelColors->addItem(m_IconColorTumor,"Tumor");
        m_ComboBoxLabelColors->addItem(m_IconColorNode,"Node");
        m_ComboBoxLabelColors->addItem(m_IconColorMetastasis,"Metastasis");
        m_ComboBoxLabelColors->addItem(m_IconColorReference,"Reference");
    }

    return m_ComboBoxLabelColors;
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

int FindingsColorMapDialog::GetSelectedLabelColor()
{
    return this->GetComboBoxLabelColors()->currentIndex();
}



