
#include "CMyFindReplaceDialog.hpp"


LRESULT CMyFindReplaceDialog::OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/) {
	CenterWindow(GetParent());

	return TRUE;
}


LRESULT CMyFindReplaceDialog::OnCloseCmd(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/) {
	EndDialog(wID);

	return 0;
}
