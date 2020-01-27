//
//  QB1.cpp
//  test_Hanchao_Chen
//
//  Created by 陈翰超 on 2020/1/27.
//  Copyright © 2020 Hanchao Chen. All rights reserved.
//

#include <iostream>
using namespace std;

void func()
{
    int a;
    
    while (1)
    {
        cout << "please input a positve number:" << endl;
        cin >> a;
        if (a <= 0)
            cout << "wrong input" << endl;
        else
            break;
    }

    double x, y;
    y = a / 2.618;
    x = 1.618 * y;
    cout << "x = " << x << endl;
    cout << "y = " << y << endl;

    return;
}

int main3()
{
    func();
    return 0;
}
