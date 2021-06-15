#ifndef QCELL_H
#define QCELL_H
#include <QPushButton>

class QCell : QPushButton
{
private:
    int m_iAddr;
    char m_chSymbol;
    bool m_bIsCursor;
public:
    QCell();
    QCell(int iaddrNew);
    QCell(int iAddrNew, char chSymbolNew, bool bIsCursorNew);

    void SetAddr(int iAddrNew);
    void SetSymbol(char chSymbolNew);
    void ActivateCursor(bool bIsCursorNew);

    int GetAddr();
    char GetSymbol();
    bool IsCursorOn();

};
#endif // QCELL_H
