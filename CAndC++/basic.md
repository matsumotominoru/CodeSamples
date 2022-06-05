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

## Tokenize

### Sample 1

```C++
#include <vector>
#include <string>
#include <sstream>
#include <iostream>

using namespace std;

int main(void){
    vector<string> tokens;
    string temp_str;
    string my_string = "5 1 3 4 5 12 6 8 1 3";
    stringstream ss(my_string); //convert my_string into string stream

    while(getline(ss, temp_str, ' ')){ //use a space as a delimiter for cutting string
        tokens.push_back(temp_str);
    }
    cout << "Array size is " << tokens.size() << endl;
    for(int i = 0; i < tokens.size(); i++) {
      cout << tokens[i] << endl;
   }
    return 0;
}
```
