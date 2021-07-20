#include "QCell.h"

QCell::QCell()
    : m_iAddr(0x10), m_chSymbol(' '), m_bIsCursor(false)
{}

QCell::QCell(int iAddrNew)
    : m_iAddr(iAddrNew), m_chSymbol(' '), m_bIsCursor(false)
{}

QCell::QCell(int iAddrNew, char chSymbolNew, bool bIsCursorNew)
    : m_iAddr(iAddrNew), m_chSymbol(chSymbolNew), m_bIsCursor(bIsCursorNew)
{}

void QCell::SetAddr(int iAddrNew)
{
    m_iAddr = iAddrNew;
}

void QCell::SetSymbol(char chSymbolNew)
{
    m_chSymbol = chSymbolNew;
}

void QCell::ActivateCursor()
{
    m_bIsCursor = true;
    this->setStyleSheet("background-color: red");
}

int QCell::GetAddr()
{
    return m_iAddr;
}

char QCell::GetSymbol()
{
    return m_chSymbol;
}

bool QCell::IsCursorOn()
{
    return m_bIsCursor;
}

void QCell::Update()
{
    this->setText(QChar(m_chSymbol));
}

void QCell::CursorOff()
{
    this->setStyleSheet("background-color: white");
    m_bIsCursor = false;
}
