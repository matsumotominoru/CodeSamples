// ConsoleMFC.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include "pch.h"
#include "framework.h"
#include "ConsoleMFC.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//構造体定義
typedef struct SCT_POPULATION {
    char urban[1024];
    int ipopulation;
}sctPopulation;

//プロトタイプ宣言
void setPopulation(CArray<sctPopulation>* sctpop);

// 唯一のアプリケーション オブジェクトです

CWinApp theApp;

using namespace std;

int main()
{
    int nRetCode = 0;

    HMODULE hModule = ::GetModuleHandle(nullptr);

    if (hModule != nullptr)
    {
        // MFC を初期化して、エラーの場合は結果を出力する
        if (!AfxWinInit(hModule, nullptr, ::GetCommandLine(), 0))
        {
            // TODO: アプリケーションの動作を記述するコードをここに挿入してください。
            wprintf(L"致命的なエラー: MFC の初期化が失敗しました\n");
            nRetCode = 1;
        }
        else
        {
            //構造体可変配列を宣言
            CArray <sctPopulation> sctpop;

            //東京都の都市別人口を構造体可変配列にセット
            setPopulation(&sctpop);

            //構造体可変配列の内容をコンソールに出力
            for (int i = 0; i < sctpop.GetSize(); i++)
            {
                printf(" %-20s %9d人\n", sctpop.GetAt(i).urban, sctpop.GetAt(i).ipopulation);
            }

            //コマンドプロンプト画面が閉じないようにする
            system("pause");
        }
    }
    else
    {
        // TODO: 必要に応じてエラー コードを変更してください
        wprintf(L"致命的なエラー: GetModuleHandle が失敗しました\n");
        nRetCode = 1;
    }

    return nRetCode;
}

/*************************************************
関数名 setPopulation
機能   可変構造体配列に東京都都市別人口データを設定
出典   総務省統計局「都市別人口」
*************************************************/
void setPopulation(CArray<sctPopulation>* sctpop)
{
    CString cbuf, cdat;

    sctPopulation wkpop;
    sctpop->RemoveAll();

    const char* urbanPopulation[] = {
        "千代田区,56873",
        "中央区,138088",
        "港区,240585",
        "新宿区,327712",
        "文京区,207413",
        "台東区,189795",
        "墨田区,258423",
        "江東区,493952",
        "品川区,372077",
        "目黒区,269689",
        "大田区,707455",
        "世田谷区,874332",
        "渋谷区,217008",
        "中野区,316625",
        "杉並区,547165",
        "豊島区,275507",
        "北区,338084",
        "荒川区,209087",
        "板橋区,544172",
        "練馬区,714656",
        "足立区,674111",
        "葛飾区,449527",
        "江戸川区,680262",
        "八王子,562572",
        "立川,179090",
        "武蔵野,142138",
        "三鷹,182092",
        "青梅,137052",
        "府中,254551",
        "昭島,112727",
        "調布,224191",
        "町田,426648",
        "小金井,117427",
        "小平,186958",
        "日野,180975",
        "東村山,151412",
        "国分寺,119379",
        "国立,74558",
        "福生,58553",
        "狛江,79096",
        "東大和,86162",
        "清瀬,74374",
        "東久留米,116494",
        "武蔵村山,72092",
        "多摩,147486",
        "稲城,86594",
        "羽村,56604",
        "あきる野,81697",
        "西東京,198267",
        "0"
    };

    for (int i = 0;; i++)
    {
        //ループ終了条件（"0"が出現したらデータセット終了）
        if (strcmp(urbanPopulation[i], "0") == 0) break;

        //対象インデックスの文字列を取得
        cbuf = urbanPopulation[i];



        //cbufの1カラム目（都市名）をセット
        AfxExtractSubString(cdat, cbuf, 0, ',');
        //CStringをLPCSTRへマクロを使って変換する
        strcpy_s(wkpop.urban, CT2CA(cdat));



        //cbufの2カラム目（人口）をセット
        AfxExtractSubString(cdat, cbuf, 1, ',');
        wkpop.ipopulation = atoi(CStringA(cdat));



        //構造体可変配列にセット
        sctpop->Add(wkpop);
    }
    return;
}

