#include "separator.h"

Separator::Separator(QWidget *parent) :
    QFrame(parent)
{
    this->setFrameStyle(QFrame::HLine | QFrame::Sunken);
}

Separator::~Separator()
{
}
