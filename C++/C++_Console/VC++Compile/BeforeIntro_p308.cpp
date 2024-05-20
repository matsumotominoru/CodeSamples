//ブラックジャックのゲーム

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//〇定数
#define CMAX 52 //トランプのカードの枚数
#define BUFF_SIZE 256 //キーボードからの入力バッファの大きさ

#define randmize() srand(time(NULL)) //乱数の初期化 warning C4244: '引数': 'time_t' から 'unsigned int' への変換です。データが失われる可能性があります。

//〇構造体
//引いたカードを格納する。
struct input {
    int card[CMAX];//引いたカード
    int num;//カードの数
};

//〇関数
int comp(void);//コンピューターがカードを引く
int getcard(struct input *inp_card); //人がカードを引く
void print_card(const struct input *inp_card, const char *card[]);//引いたカードの表示
int calc(const struct input *inp_card);//得点の計算


int main()
{
    const char *card[] = { "0","A","2","3","4","5","6","7","8","9","10","J","Q","K" };//カードの種類
    int gain_card;//引いたカード
    int c_score;//コンピューターのスコア
    int h_score;//プレイヤーのスコア
    char in[BUFF_SIZE];//入力した文字列
    struct input h_card = { {0},0 };//プレイヤーが引いたカード{手札、手札の枚数}

    printf("ブラックジャックゲーム\nカードの合計が21に近いほうが勝ちです。\nしかし、得点が22以上だと負けです。\n");
    randmize();//乱数の初期化。srand(time(0))に展開
    c_score = comp();//コンピューターの得点計算
    //最初のカードを引く
    gain_card = getcard(&h_card);
    printf("'%s'を引きました。\n", card[gain_card]);
    printf("もう一枚引きますか？(y/n):");
    //カード上限まで引くか、nを入力するまでループ
    while (h_card.num < CMAX && fgets(in, BUFF_SIZE, stdin) != NULL) {
        if (strncmp(in, "y", 1) == 0) {//一文字目がyのとき
            gain_card = getcard(&h_card);//カードを引く
            printf("'%s'を引きました。\n", card[gain_card]);
            print_card(&h_card, card);//手札の表示
            printf("もう一枚引きますか？(y/n):");
        }
        else if (strncmp(in, "n", 1) == 0)
            break;
        else
            printf("yかnのどちらかを入力してください。\n");
    }
    //スコアの計算
    h_score = calc(&h_card);
    printf("あなたのスコアは%d、コンピューターのスコアは%d\n", h_score, c_score);
    if (c_score <= 21 && (h_score > 21 || h_score < c_score)) {
        printf("あなたの負けです。");
    }
    else if (h_score <= 21 && (c_score > 21 || c_score < h_score)) {
        printf("あなたの勝ちです。");
    }
    else {
        printf("引き分けです。");
    }

    return 0;
}

int comp() {
    return rand() % 8 + 16;
}

int getcard(struct input *h_card) {
    int x; //引いたカード

    x = rand() % 13 + 1;
    h_card->card[h_card->num] = x;
    ++(h_card->num);

    return x;
}

void print_card(const struct input *inp_card, const char *card[]) {
    printf("いままで引いたカードは ");
    for (int i = 0; i < inp_card->num; i++)
    {
        printf("%s ", card[inp_card->card[i]]);
    }
    printf("です\n");
}

int calc(const struct input *inp_card)
{
    const int ncard[] = { 0,1,2,3,4,5,6,7,8,9,10,10,10,10 };//カードの点数
    int n1 = 0;//Aカードの枚数
    int score = 0;//点数

    for (int i = 0; i < inp_card->num; i++)
    {
        score += ncard[inp_card->card[i]];
        if (inp_card->card[i] == 1)
            n1++;

    }
    while (n1 > 0) {
        if (score <= (21 - 10))
            score += 10;
        n1--;
    }

    return score;

}

