# Basic

## Standard I/O

### Sample 1

```C++
#include <iostream>
using namespace std;
//Input
//n
//x_1 y_1
//x_2 y_2
//...
//x_n y_n

int main(void){
    int n;
    string token1, token2;

    cin >> n;//get number of input lines
    for(int i = 0; i < n; i++) {
        cin >> token1 >> token2;//get two strings delimited by a space
        cout << "hello = " << token1 << " , world = " << token2 << endl;
    }
    return 0;
}
```
