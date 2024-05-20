//page4
#include <iostream>

using namespace std;

class Money {
    public:
    Money(){balance = 0 ;};
    ~Money(){};
    void setYenRate(int Rate);
    void setDolllar(double doll);
    int getYen(){return balance;};

    private:
    int balance;
    int YenRate;
};

void Money::setYenRate(int Rate){
    YenRate = Rate;
}

void Money::setDolllar(double doll){
    balance = (int) (YenRate * doll);
}

int main(int argc, char* argv[]){
    int Rate;
    double value;
    Money* dv = new Money();
    cout << "1$/円>";
    cin >> Rate;

    dv->setYenRate(Rate);
    cout << "balance(dollar)>";
    cin >> value;
    dv->setDolllar(value);
    cout << "balance(Yen)= " << dv->getYen() << endl;

    return 0;
}