//
//  QC.cpp
//  test_Hanchao_Chen
//
//  Created by 陈翰超 on 2020/1/27.
//  Copyright © 2020 Hanchao Chen. All rights reserved.
//

#include <iostream>
#include <cmath>
using namespace std;

class point
{
public:
    double x;
    double y;
    void getvalues(){
        cout << "Please input the x: " << endl;
        cin >> this->x;
        cout << "Please input the y: " << endl;
        cin >> this->y;
    }
};

point find_point_p(point p1, point p2, point p3){
    double u = ((p3.x-p1.x)*(p2.x-p1.x)+(p3.y-p1.y)*(p2.y-p1.y))/(pow(p1.x-p2.x,2)+pow(p1.y-p2.y,2));
    point p;
    p.x = p1.x+u*(p2.x-p1.x);
    p.y = p1.y+u*(p2.y-p1.y);
    return p;
}

double distance(point p1, point p2)
{
    double d;
    d = sqrt(pow(p1.x-p2.x,2)+pow(p1.y-p2.y,2));
    return d;
}

int main4()
{
    point p1,p2,p3, p4;
    cout << "enter first point p2" << endl;
    p1.getvalues();
    cout << "enter second point p1" << endl;
    p2.getvalues();
    if (p1.x == p2.x && p1.y ==p2.y)
    {
        cout << "Two points are coincident!" << endl;
        return -1;
    }
    cout << "enter third point p3" << endl;
    p3.getvalues();

    p4 = find_point_p(p1, p2, p3);
    cout << "The point on the segment that is closest is: ("<<p4.x<<","<<p4.y<<")" << endl;
    double dist;
    dist = distance(p3, p4);
    cout << "the shortest distance is: " << dist << endl;
    
    return 0;
}
