//
//  matMorphOper.cpp
//  erlangNoise
//
//  Created by артем on 17.03.17.
//  Copyright © 2017 артем. All rights reserved.
//

#include <stdio.h>

// create working image
cv::Mat createPicForFilter (const int rows,const int cols) {
    double leftRowBarrier = double(rows/4);
    double rightRowBarrier = double(rows*3/4);
    double leftColBarrier = double(cols/4);
    double rightColBarrier = double(cols*3/4);
    double midCol = double(cols/2);
    double midRows = double(rows/2);

    cv::Mat result = cv::Mat::zeros(rows,cols,CV_8U);
    //add grey square
    for (double i = leftRowBarrier ; i<rightRowBarrier; i++) {
        for (double j = leftColBarrier  ; j < rightColBarrier; j++) {
            result.at<uchar>(i,j) = 155;
        }
    }
    //add dark square in the middle
    for (double i = midRows-20 ; i<midRows+20; i++) {
        for (double j = midCol-20  ; j < midCol+20; j++) {
            result.at<uchar>(i,j) = 70
            ;
        }
    }
    return result;
}

//////////////////////////////////////////////////////////////////////////////////////////
uint factorialFunc(const int _inputValue ) {
    if ((_inputValue == 1) || (_inputValue == 0) ){
        return 1;
    }
    else {
        return _inputValue * (factorialFunc (_inputValue - 1 ));
    }
}

//////////////////////////////////////////////////////////////////////////////////////////
double erlangNoise (
                  const int _z,
                  const double _a,
                  const double _b
                  ) {
    // a and b are parametrs from erlang noise
    // erlang noice formula is
    // key value is pe(z)
    // if z >=0 --> pe(z) = a*(b-1)^(b-1) / (b-1)! * e ^ -(b-1)
    // if z < 0 --> pe(z) = 0
    // where a > 0 , b is a positive int
    if ((_a <= 0) && ( _b<=0 )) {
        return -1;
    }
    double result = 0;
    
    if (_z >=0 ) {
        result = double(_a * pow(_b-1,_b-1))  / double((factorialFunc(_b-1))) * double(exp(-(_b-1) ) );
    }
    printf("erlang noise result is %f\n",double(_a * pow(_b-1,_b-1))  / double((factorialFunc(_b-1))) * double(exp(-(_b-1) ) ));
    printf("z - %d a - %f b - %f\n",_z,_a,_b);
    return result;
}

//////////////////////////////////////////////////////////////////////////////////////////
double findErlangNoiseMax(const int _start,const int _finish, const double _a,const double _b) {
    double max = 0 ;
    for (int i = _start; i <= _finish; i++) {
        if (erlangNoise(i, _a, _b) > max ) {
            max = erlangNoise(i, _a, _b);
        }
    }
    return max;
}


