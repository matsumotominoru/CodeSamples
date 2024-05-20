#include <iostream>

using namespace std;

int main()
{
    setlocale(LC_ALL, "");

    wchar_t en[] = L"Hello";
    wchar_t ru[] = L"Привет"; //Russian language
    wcout << ru
         << endl
         << en;
    return 0;
}