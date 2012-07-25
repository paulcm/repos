#include "categorybutton.h"

CategoryButton::CategoryButton(const QString& text, QWidget *parent) :
    QPushButton(parent)
  ,m_State(CLOSED)
{
    m_IconOpened.addPixmap(QPixmap(":/resources/opened.png"));
    m_IconClosed.addPixmap(QPixmap(":/resources/closed.png"));

    this->setText(text);

    this->setIcon(m_IconClosed);
    this->setStyleSheet("text-align: left; padding-left: 5px;");
    this->setMaximumHeight(24);

    connect( this, SIGNAL(clicked()), this, SLOT(SlotClicked()) );
}



CategoryButton::~CategoryButton()
{
}


const CategoryButton::ButtonState& CategoryButton::GetButtonState()
{
    return m_State;
}

void CategoryButton::SlotClicked()
{
    if(m_State == OPEN)
    {
        m_State = CLOSED;
        this->setIcon(m_IconClosed);
        emit SignalButtonState(m_State);
    }
    else if(m_State == CLOSED)
    {
        m_State = OPEN;
        this->setIcon(m_IconOpened);
        emit SignalButtonState(m_State);
    }
}

