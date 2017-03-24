//
//  matMorphOper.cpp
//  erlangNoise
//
//  Created by артем on 23.03.17.
//  Copyright © 2017 артем. All rights reserved.
//

#include <stdio.h>
#include <set>
int clamp(int value,int min,int max) {
    if (value < min) {
        return min;
    }
    if (value > max) {
        return max;
    }
    return value;
}
///////////////////////////////////////////////////////////////////////////////////////////////////
// spec clamp func for check intensity
int intensClamp(int value) {
    return clamp(value,0,255);
}
///////////////////////////////////////////////////////////////////////////////////////////////////
cv::Mat changeMatColor(cv::Mat _inputElement, uchar _color) {
    cv::Mat resultElement = _inputElement.clone();
    for (int i =0 ; i < resultElement.rows; i++) {
        for (int j = 0 ; j < resultElement.cols; j++) {
            resultElement.at<uchar>(i,j) = _color;
        }
    }
    return resultElement;
}
///////////////////////////////////////////////////////////////////////////////////////////////////

cv::Mat dilationForGrayScale (const cv::Mat _noiseImg,const int _sizeOfStructElem) {
    cv::Mat clearImg = _noiseImg.clone();
    cv::Mat zeroImg = _noiseImg.clone();
    zeroImg = changeMatColor(zeroImg, 0);
    
    int structColor = 20;
    // for example rad of elem(5x5) is (5-1)/2 = 2
    int radiusOfStructElem = (_sizeOfStructElem - 1) / 2 ;
    // check valid of struct size
    if ((_sizeOfStructElem % 2)==0) {
        printf("size of struct element can't be a multiple of two,pls change size\n");
        exit(-4);
    }
    //find max value in every point environment
    for (int i =0 ; i < clearImg.rows; i++) {
        for (int j = 0 ; j < clearImg.cols; j++) {
            // create temp max for everyone environment
            int maxValue = 0;
            //check the inviroment of dot(i,j) using radiusOfStructElem
            for (int vertBarrier = -radiusOfStructElem; vertBarrier < radiusOfStructElem; vertBarrier++) {
                for (int horisBarrier = -radiusOfStructElem; horisBarrier < radiusOfStructElem; horisBarrier++) {
                    //pls dont attempt to understand this
                    int Brr = intensClamp(clearImg.at<uchar>(clamp(i+vertBarrier, 0, clearImg.rows),clamp(j+horisBarrier, 0, clearImg.cols)) + structColor);
                    if (Brr > maxValue) {
                        maxValue = Brr;
                    }
                }
            }
            zeroImg.at<uchar>(i,j) = maxValue;
            maxValue = 0;
        }
    }
    return zeroImg;
}
///////////////////////////////////////////////////////////////////////////////////////////////////

cv::Mat erosionForGrayScale (const cv::Mat _noiseImg,const int _sizeOfStructElem) {
    cv::Mat clearImg = _noiseImg.clone();
    cv::Mat zeroImg = _noiseImg.clone();
    zeroImg = changeMatColor(zeroImg, 0);
    
    int structColor = 20;
    // for example rad of elem(5x5) is (5-1)/2 = 2
    int radiusOfStructElem = (_sizeOfStructElem - 1) / 2 ;
    // check valid of struct size
    if ((_sizeOfStructElem % 2)==0) {
        printf("size of struct element can't be a multiple of two,pls change size\n");
        exit(-4);
    }
    //find min value in every point environment
    for (int i =0 ; i < clearImg.rows; i++) {
        for (int j = 0 ; j < clearImg.cols; j++) {
            // create temp max for everyone environment
            int minValue = 255;
            //check the inviroment of dot(i,j) using radiusOfStructElem
            for (int vertBarrier = -radiusOfStructElem; vertBarrier < radiusOfStructElem; vertBarrier++) {
                for (int horisBarrier = -radiusOfStructElem; horisBarrier < radiusOfStructElem; horisBarrier++) {
                    //pls dont attempt to understand this
                    int Brr = intensClamp(clearImg.at<uchar>(clamp(i+vertBarrier, 0, clearImg.rows),clamp(j+horisBarrier, 0, clearImg.cols)) - structColor);
                    if (Brr < minValue) {
                        minValue = Brr;
                    }
                }
            }
            zeroImg.at<uchar>(i,j) = minValue;
            minValue = 255;
        }
    }
    return zeroImg;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Mat convertToSingleChannel (cv::Mat _input) {
    cv:Mat singlechannelPic(_input.rows, _input.cols, CV_8U);
    cvtColor(_input, singlechannelPic, CV_BGR2GRAY);
    return singlechannelPic;
}
