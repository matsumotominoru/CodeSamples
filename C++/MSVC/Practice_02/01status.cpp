//page45
// 
//
// (c)Copyright Spacesoft corp., 2011 All rights reserved.
//                               Hiro KITAYAMA
//
#include <windows.h>
#include <stdio.h>

#define DIV     (1024*1024)


//----------------------------------------------------------------------------
// main
int main(void)
{
    MEMORYSTATUSEX memStatusEx;

    // GlobalMemoryStatusEx APIで、物理メモリと仮想メモリの
    // 両方に関するシステムの現在の使用状況の情報を取得
    memStatusEx.dwLength=sizeof(MEMORYSTATUSEX);
    GlobalMemoryStatusEx(&memStatusEx);

    printf("仮想アドレス空間の合計: %I64d Mバイト.\n",memStatusEx.ullTotalVirtual/DIV);

    printf("仮想アドレス空間の空き: %I64d Mバイト.\n",
                                    memStatusEx.ullAvailVirtual/DIV);

    printf("物理メモリの合計: %I64d Mバイト.\n",
                                    memStatusEx.ullTotalPhys/DIV);

    printf("物理メモリの空き: %I64d Mバイト.\n",
                                    memStatusEx.ullAvailPhys/DIV);

    printf("ページファイル(仮想メモリ)の合計: %I64d Mバイト.\n", memStatusEx.ullTotalPageFile/DIV);
    printf("ページファイル(仮想メモリ)の空き: %I64d Mバイト.\n", memStatusEx.ullAvailPageFile/DIV);

    printf("現在物理メモリの %d %% が使われています.\n\n",
                                    memStatusEx.dwMemoryLoad);

    return 0;
}
