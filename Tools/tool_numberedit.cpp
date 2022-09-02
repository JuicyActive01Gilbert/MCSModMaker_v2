#include "tool_numberedit.h"

Tool_NumberEdit::Tool_NumberEdit(QWidget *parent) : QSpinBox(parent)
{
    initialize();
}

Tool_NumberEdit::~Tool_NumberEdit()
{

}

void Tool_NumberEdit::initialize()
{
    this->setButtonSymbols(QSpinBox::NoButtons);
    this->setRange(-99999999999,99999999999);
}
