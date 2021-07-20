#ifndef QCELL_H
#define QCELL_H
#include <QPushButton>

class QCell : public QPushButton
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


    int GetAddr();
    char GetSymbol();
    bool IsCursorOn();

    void Update();
    void ActivateCursor();
    void CursorOff();
};
#endif // QCELL_H
