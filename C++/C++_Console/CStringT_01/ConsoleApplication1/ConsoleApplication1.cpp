#include "stdafx.h"

//
//CStringT クラスのテスト
//文字コードはマルチバイト文字
int main()
{
    // 普通に宣言する場合
    CStringT<TCHAR, StrTraitATL<TCHAR> > s1 = _T("ABCDEFあ");
    s1.Append(_T("GHIJKL"));
    _tprintf(_T("%s\n"), (LPCTSTR)s1);

    // MFC ベースのアプリ内で使用可能 (CString は CStringT の別名になっている)
    CString s2 = _T("abcdefあ");
    s2.Append(_T("GHIJKL"));
    //wprintf_s(L"%s\n", (LPCSTR)s2);

    // ATL ベースのアプリ内のみ使用可能 (CAtlString は CStringT の別名になっている)
    CAtlString s3 = _T("ABCDEFあ");
    s3.Append(_T("ghijkl"));
    //wprintf_s(L"%s\n", (LPCSTR)s3);

    // C の関数で文字列のように使用できる。
    CHAR buff[80];
    StrCpy(buff, s3);
    //wprintf_s(L"%s\n", buff);

    // BSTR といっしょに使用
    BSTR bstr = s1.AllocSysString();
    wprintf_s(L"%s\n", bstr);
    s2 = bstr;
    //wprintf_s(L"%s\n", s2);

    ::SysFreeString(bstr);
    getchar();
    return 0;
}