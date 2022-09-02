#include "tool_doubleedit.h"

Tool_DoubleEdit::Tool_DoubleEdit(QWidget *parent) : QDoubleSpinBox(parent)
{
    initialize();
}

Tool_DoubleEdit::~Tool_DoubleEdit()
{

}

void Tool_DoubleEdit::initialize()
{
    this->setButtonSymbols(QDoubleSpinBox::NoButtons);
    this->setRange(-99999999999,99999999999);
}
