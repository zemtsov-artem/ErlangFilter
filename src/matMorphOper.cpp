//
//  matMorphOper.cpp
//  erlangNoise
//
//  Created by артем on 17.03.17.
//  Copyright © 2017 артем. All rights reserved.
//

#include <stdio.h>

uint factorialFunc(const int _inputValue ) {
    if ((_inputValue == 1) || (_inputValue == 0) ){
        return 1;
    }
    else {
        return _inputValue * (factorialFunc (_inputValue - 1 ));
    }
}

uint calcCountOfNoisePixels(const int _size, const int _proc) {
    return (_size * _proc / 100);
}

double erlangNoise (
                  const int _z,
                  const int _a,
                  const int _b
                  ) {
    // a and b are parametrs from erlang noise
    // erlang noice formula is
    // key value is pe(z)
    // if z >=0 --> pe(z) = a^b*z^(b-1) / (b-1)! * e ^(-a*z)
    // if z < 0 --> pe(z) = 0
    // where a > 0 , b is a positive int
    if ((_a <= 0) && ( _b<=0 )) {
        return -1;
    }
    double result = 0;
    
    if (_z >=0 ) {
        result = (pow(_a,_b) * pow(_z,_b-1) ) / double((factorialFunc(_b-1))) * exp(-_a*_z);
    }
    return result;
}


double findErlangNoiseMax(const int _start,const int _finish, const int _a,const int _b) {
    double max = 0 ;
    for (int i = _start; i <= _finish; i++) {
        if (erlangNoise(i, _a, _b) > max ) {
            max = erlangNoise(i, _a, _b);
            printf("max %f\n",erlangNoise(i, _a, _b));
        }
    }
    return max;
}


