//
//  workWithHist.cpp
//  erlangNoise
//
//  Created by артем on 17.03.17.
//  Copyright © 2017 артем. All rights reserved.
//
//rows cols
#include <opencv2/highgui.hpp>
#include "opencv2/imgproc.hpp"
#include "../src/erlangNoise.cpp"

using namespace cv;

Mat getNewHistWihtParam(uint *_arrayPtr,uint _sizeOfArray,uint _maxValueInArray,int _param) {
    //create zero mat
    //_param is a way to make less heigth of hist
    uint maxValueInArray = _maxValueInArray / _param;
    Mat myHist = Mat::zeros(maxValueInArray,_sizeOfArray,CV_8U);
    //fill mat
    for (int i = 0; i < 255; i++) {
        for (int j = 0; j < *(_arrayPtr + i); j += _param) {
            myHist.at<uchar>(maxValueInArray - j / _param , i) = 255;
        }
    }
    return myHist;
    
}


