/*** 
 * @Author: liqunwu
 * @Date: 2023-10-12 11:18:04
 * @Description: 
 * @Copyright (c) 2023 by zhejianglab, All Rights Reserved.
 */
#include <iostream>

using namespace std;

class base {
    public:
    virtual void test() {
        printf("base class\n");
    }
    // virtual void test2() = 0;
};

class A:public base {
    public:
    void test() {
        printf("sub class\n");
    }
};

int main() {
    base *b;
    b = new A();

    b->test();

    return 0;
}

