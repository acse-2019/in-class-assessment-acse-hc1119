//
//  Q2.cpp
//  test_Hanchao_Chen
//
//  Created by 陈翰超 on 2020/1/27.
//  Copyright © 2020 Hanchao Chen. All rights reserved.
//

#include <iostream>
#include <cmath>

using namespace std;

string f1(string *a, string *b)
{
    return *a+*b;
}

string fRef(string &a, string &b)
{
    return a+b;
}
int main1() {
    
    string first;
    string second;
    cout << "please enter 1st string: ";
    cin >> first;
    
    cout << "Please enter 2nd string: ";
    cin >> second;
    string *s1 = &first;
    string *s2 = &second;

    std::cout << "concentrate by pointer: " << f1(s1, s2) << endl;
    std::cout << "concentrate by ref: " << fRef(*s1, *s2) << endl;
    
    return 0;
}
