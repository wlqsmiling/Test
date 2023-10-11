/*** 
 * @Author: liqunwu
 * @Date: 2023-10-11 10:21:01
 * @Description: 
 * @Copyright (c) 2023 by zhejianglab, All Rights Reserved.
 */

#include <iostream>
using namespace std;

bool fooo() {
    int a = 0;

    return a > 0;
}

class BeforeMain
{
    public:
    static bool foo;
};

bool BeforeMain::foo = fooo();

int main() {
    cout<<BeforeMain::foo<<endl;
}
