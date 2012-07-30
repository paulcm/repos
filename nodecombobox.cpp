#include "nodecombobox.h"

#include <QMessageBox>
#include <QInputDialog>

QString NodeComboBox::NONE_VALUE = "None";

NodeComboBox::NodeComboBox(const QString& description, QList<QString>* values, QWidget *parent) :
    QComboBox(parent)
  ,m_StringCreate("Create new ")
  ,m_StringRename("Rename current ")
  ,m_StringDelete("Delete current ")
  ,m_StringSeparator("_________________________ ")
{
    m_Description = description;
    m_Values = values;

    m_DefaultValues.append(m_StringSeparator);
    m_StringRename = m_StringRename + m_Description + " ";
    m_DefaultValues.append(m_StringRename);
    m_StringCreate = m_StringCreate + m_Description + " ";
    m_DefaultValues.append(m_StringCreate);
    m_StringDelete = m_StringDelete + m_Description + " ";
    m_DefaultValues.append(m_StringDelete);

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
        if(selected.compare(m_StringCreate) == 0)
        {
            QString name = QInputDialog::getText(NULL,"Create "+m_Description,"Name:");
            name = name.trimmed();

            if(this->CheckNameAlreadyExists(name,true))
            {
                this->SetCurrentIndex(m_LastSelectedNode);
                return;
            }

            if(!name.isEmpty())
                emit SignalCreate(name);
            else
                this->SetCurrentIndex(m_LastSelectedNode);
        }

        if(m_LastSelectedNode.compare(NONE_VALUE) != 0)
        {
            this->SetCurrentIndex(m_LastSelectedNode);

            if(selected.compare(m_StringRename) == 0)
            {
                QString rename = QInputDialog::getText(NULL,"Rename "+m_Description,"Name:",QLineEdit::Normal, m_LastSelectedNode);
                rename = rename.trimmed();

                if(rename.compare(m_LastSelectedNode) != 0)
                {
                    if(this->CheckNameAlreadyExists(rename,true))
                        return;

                    if(!rename.isEmpty())
                        emit SignalRename(m_LastSelectedNode,rename);
                }


            }
            else if(selected.compare(m_StringDelete) == 0)
            {
                int ret = QMessageBox::question(NULL,"Delete "+m_Description, "Are you sure you want to delete "+m_LastSelectedNode+" ?",QMessageBox::Yes,QMessageBox::Cancel);

                if(ret == QMessageBox::Yes)
                    emit SignalDelete(m_LastSelectedNode);
            }
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
        m_DefaultValues.removeOne(m_StringCreate);
        break;
    case RENAME:
        m_DefaultValues.removeOne(m_StringRename);
        break;
    case DELETE:
        m_DefaultValues.removeOne(m_StringDelete);
        break;
    case SEPPARATOR:
        m_DefaultValues.removeOne(m_StringSeparator);
        break;
    }
}

bool NodeComboBox::CheckNameAlreadyExists(const QString& name, bool showWarning)
{
    for(int i=0; i < this->count(); ++i)
    {
        if(this->itemText(i).compare(name) == 0)
        {
            if(showWarning)
                QMessageBox::warning(NULL,"Duplicate Name","A "+m_Description+" with this name already exists!");

            return true;
        }
    }

    return false;
}



