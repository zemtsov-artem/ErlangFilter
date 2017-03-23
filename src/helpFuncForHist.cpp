//
//  grayToBin.cpp
//  erlangNoise
//
//  Created by артем on 17.03.17.
//  Copyright © 2017 артем. All rights reserved.
//

#include <stdio.h>
//x
void initHistArr(uint *_histArr){
    for (int i =0; i<256; i++) {
        *(_histArr + i) = 0;
    }
}
//////////////////////////////////////////////////////////////////////////////////////////
void fillArrayWithValuesFromGI(uint *_histArr ,Mat _grayScaleImageMatrix){
    Mat_<uchar> grayScaleImageMatrixPtr = _grayScaleImageMatrix;
    for (int i =0; i<_grayScaleImageMatrix.rows; i++) {
        for (int j = 0; j < _grayScaleImageMatrix.cols; j++) {
            *(_histArr+grayScaleImageMatrixPtr(i,j))+=1;
        }
    }
}
//////////////////////////////////////////////////////////////////////////////////////////
uint findMaxValueInHistArrayAndFixIndex(uint* _histArr,uint *_ptrToTheFlagVariable) {
    uint tempMax = *(_histArr);
    for (int i =0; i<256; i++) {
        if (*(_histArr+i) > tempMax ) {
            tempMax = *(_histArr+i);
            *(_ptrToTheFlagVariable) = i;
        }
        
    }
    return tempMax;
}

//////////////////////////////////////////////////////////////////////////////////////////
