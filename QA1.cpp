//
//  main.cpp
//  test_Hanchao_Chen
//
//  Created by 陈翰超 on 2020/1/27.
//  Copyright © 2020 Hanchao Chen. All rights reserved.
//

#include <iostream>
using namespace std;

void f(int a)
{
    int count = 0;
    while (1)
    {
        cout << "please input an integer:" << endl;
        cin >> a;
        if (a <= 0)
            cout << "wrong input" << endl;
        else
            break;
    }
    int temp;
    temp = a;
    
    while (temp != 0)
    {
        temp = temp / 10;
        count++;
    }
    
    int b = 0;
    int out = 0;
    for (int i = 1; i < count+1; i++)
    {
        b = a % 10;
        a = (a - b)/10;
        out = out*10 + b;
    }
    cout << out << endl;
    return;
}

int main0()
{
    int t = 1234567;
    f(t);
    return 0;
}
