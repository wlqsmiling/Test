/*** 
 * @Author: liqunwu
 * @Date: 2023-10-11 14:47:18
 * @Description: 
 * @Copyright (c) 2023 by zhejianglab, All Rights Reserved.
 */
#include <iostream>
using namespace std;

void myFunction(int myNumbers[9]) {
    for(int i = 0 ; i < 9; i++) {
        cout<<myNumbers[i]<<endl;
    }
}

void myFunction(char a) {
    
}

int main() {
    int array[9] = {0};
    // myFunction(array);
    for(int a:array) {

    }
}