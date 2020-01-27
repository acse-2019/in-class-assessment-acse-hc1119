//
//  testQD.cpp
//  test_Hanchao_Chen
//
//  Created by 陈翰超 on 2020/1/27.
//  Copyright © 2020 Hanchao Chen. All rights reserved.
//

#include <iostream>
#include <math.h>
#include <ctime>
#include "Matrix.hpp"
#include "CSRMatrix.hpp"

using namespace std;

int main()
{

   int rows = 4;
   int cols = 4;
    
  
    
    // Use computeTrace
    int nnzs = 4;
    auto *m_values = new int[nnzs];
    auto *m_rowdata = new int[nnzs + 1];
    auto *m_coldata = new int[nnzs];
    auto m1 = new CSRMatrix<int>(rows, cols, nnzs, m_values, m_rowdata, m_coldata);
    
    for (int i = 0; i < nnzs; i++)
    {
       m_values[i] = i;
    }
    
    m_rowdata[0] = 0;
    m_rowdata[1] = 0;
    m_rowdata[2] = 2;
    m_rowdata[3] = 3;
    m_rowdata[4] = 4;

    m_coldata[0] = 0;
    m_coldata[1] = 1;
    m_coldata[2] = 2;
    m_coldata[3] = 1;
    
    m1->computeTrace();
    
    delete m1;
    delete[] m_values;
    delete[] m_coldata;
    delete[] m_rowdata;
    
    //use copy constructor
    CSRMatrix<int> m2(m1);
    
    system("pause");

}

