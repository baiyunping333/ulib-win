#include <windows.h>
#include <tchar.h>
#include <commctrl.h>
#include "ucombobox.h"

UComboBox::UComboBox(HWND hParent, UINT nResource, HINSTANCE hInst)
: UControl(hParent, nResource, hInst)
{
    m_dwStyles |= CBS_DROPDOWN;
}

UComboBox::UComboBox()
: UControl()
{}

UComboBox::~UComboBox()
{}

BOOL UComboBox::create()
{
    return UControl::create(_T("COMBOBOX"));
}

/*
BOOL UComboBox::destroy()
{
    ::DestroyWindow(m_hSelf);
    return TRUE;
}
*/

//
BOOL UComboBox::setCurSel(const int nIndex/*=0*/)
{
    return sendMsg(CB_SETCURSEL, nIndex, 0);
}

//
int UComboBox::getCurSel()
{
    return sendMsg(CB_GETCURSEL, 0, 0);
}

//
BOOL UComboBox::addText(const TCHAR *lpszText)
{
    int index = 0;
    index = sendMsg(CB_ADDSTRING, 0, (LPARAM)lpszText);

    if (CB_ERR == index)
    {
        return FALSE;
    }
    return TRUE;
}

int UComboBox::getText(TCHAR *lpszText)
{
    return this->getWindowText(lpszText, 256);
}

BOOL UComboBox::setItemData(int nIndex, DWORD dwData)
{
    return this->sendMsg(CB_SETITEMDATA, (WPARAM)nIndex, (LPARAM)dwData);
}

DWORD UComboBox::getItemData(int nIndex)
{
    return this->sendMsg(CB_GETITEMDATA, (WPARAM)nIndex);
}