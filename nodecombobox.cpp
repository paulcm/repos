#include "nodecombobox.h"


QString NodeComboBox::NONE_VALUE = "None";

NodeComboBox::NodeComboBox(const QString& description, QList<QString>* values, QWidget *parent) :
    QComboBox(parent)
  ,m_StringCreate("Create new ")
  ,m_StringRename("Rename current ")
  ,m_StringDelete("Delete current ")
  ,m_StringSeparator("_________________________")
{
    m_Description = description;
    m_Values = values;

    m_DefaultValues.append(m_StringSeparator);
    m_DefaultValues.append(m_StringRename + m_Description);
    m_DefaultValues.append(m_StringCreate + m_Description);
    m_DefaultValues.append(m_StringDelete + m_Description);

    this->connect(this, SIGNAL(currentIndexChanged(QString)), this, SLOT(SlotSelectionChanged(QString)) );

    this->Update();
}


NodeComboBox::~NodeComboBox()
{
}

void NodeComboBox::Update(const QString &indexAtText)
{
    this->disconnect(this, SIGNAL(currentIndexChanged(QString)), this, SLOT(SlotSelectionChanged(QString)) );

    this->clear();

    this->addItem(NONE_VALUE);

    int i=0;

    for(i=0; i < m_Values->size(); ++i)
    {
        this->addItem(m_Values->at(i));
    }

    for(i=0; i < m_DefaultValues.size(); ++i)
    {
        this->addItem(m_DefaultValues.at(i));
    }


    this->SetCurrentIndex(indexAtText);

    this->connect(this, SIGNAL(currentIndexChanged(QString)), this, SLOT(SlotSelectionChanged(QString)) );

    if(this->IsSelectedEntryNode(this->currentText()))
        m_LastSelectedNode = this->currentText();
}


void NodeComboBox::SetCurrentIndex(const QString& text)
{
    this->disconnect(this, SIGNAL(currentIndexChanged(QString)), this, SLOT(SlotSelectionChanged(QString)) );

    int textIDX = this->findText(text);

    if(textIDX != -1)
        this->setCurrentIndex(textIDX);
    else
        this->setCurrentIndex(0);

    this->connect(this, SIGNAL(currentIndexChanged(QString)), this, SLOT(SlotSelectionChanged(QString)) );
}


bool NodeComboBox::IsSelectedEntryNode(const QString& name)
{
    bool result = true;

    if(m_DefaultValues.contains(name))
        result = false;

    return result;
}

void NodeComboBox::SlotSelectionChanged(const QString& selected)
{

    if(selected.compare(m_StringSeparator) == 0)
    {
        this->SetCurrentIndex(m_LastSelectedNode);
        return;
    }

    if(!m_DefaultValues.contains(selected))
        emit SignalSelected(selected);

    else
    {
        if(selected.compare(m_StringCreate+m_Description) == 0)
            emit SignalCreate();

        if(m_LastSelectedNode.compare(NONE_VALUE) != 0)
        {
            if(selected.compare(m_StringRename+m_Description) == 0)
                emit SignalRename(m_LastSelectedNode);
            else if(selected.compare(m_StringDelete+m_Description) == 0)
                emit SignalDelete(m_LastSelectedNode);
        }
        else
            this->SetCurrentIndex(m_LastSelectedNode);
    }
}

void NodeComboBox::HideOperator(Operator op)
{
    switch(op)
    {
    case CREATE:
        m_DefaultValues.removeOne(m_StringCreate + m_Description);
        break;
    case RENAME:
        m_DefaultValues.removeOne(m_StringRename + m_Description);
        break;
    case DELETE:
        m_DefaultValues.removeOne(m_StringDelete + m_Description);
        break;
    case SEPPARATOR:
        m_DefaultValues.removeOne(m_StringSeparator);
        break;
    }
}



