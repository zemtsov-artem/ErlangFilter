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
cv::Mat colorTheStructElem(const cv::Mat _inputElement,const uchar _color) {
    cv::Mat resultElement = _inputElement.clone();
    for (int i =0 ; i < resultElement.rows; i++) {
        for (int j = 0 ; j < resultElement.cols; j++) {
            resultElement.at<uchar>(i,j) = _color;
        }
    }
    return resultElement;
}
///////////////////////////////////////////////////////////////////////////////////////////////////
// unused
std::set<int> findAllIntesiesFromImg (cv::Mat _imageMat) {
    std::set<int> resultSet;
    for (int i = 0; i < _imageMat.rows; i++) {
        for (int j = 0; j < _imageMat.cols; j++) {
            resultSet.insert(_imageMat.at<uchar>(i,j));
        }
    }
    return resultSet;
}
///////////////////////////////////////////////////////////////////////////////////////////////////

cv::Mat dilationForGrayScale (const cv::Mat _noiseImg,const int _sizeOfStructElem) {
    cv::Mat clearImg = _noiseImg.clone();
    int structColor = 10;
    // for example rad of elem(5x5) is (5-1)/2 = 2
    int radiusOfStructElem = (_sizeOfStructElem - 1) / 2 ;
    // check valid of struct size
    if ((_sizeOfStructElem % 2)==0) {
        printf("size of struct element can't be a multiple of two,pls change size\n");
        exit(-4);
    }
    // if everybody is allright lets create struct element
    cv::Mat structElement = cv::Mat::zeros(_sizeOfStructElem,_sizeOfStructElem,CV_8U);
    // fill the str elem
    colorTheStructElem(structElement,structColor);
    //find max value in every point environment
    for (int i =0 ; i < clearImg.rows; i++) {
        for (int j = 0 ; j < clearImg.cols; j++) {
            // create temp max for everyone environment
            int maxValue = 0;
            for (int vertBarrier = -radiusOfStructElem; vertBarrier < radiusOfStructElem; vertBarrier++) {
                for (int horisBarrier = -radiusOfStructElem; horisBarrier < radiusOfStructElem; horisBarrier++) {
                    if (clearImg.at<uchar>(intensClamp(i+vertBarrier),intensClamp(j+horisBarrier)) > maxValue) {
                        maxValue = clearImg.at<uchar>(intensClamp(i+vertBarrier),intensClamp(j+horisBarrier));
                    }
                }
            }
            clearImg.at<uchar>(i,j) = maxValue;
            maxValue = 0;
        }
    }
    return clearImg;
}
///////////////////////////////////////////////////////////////////////////////////////////////////

cv::Mat erosionForGrayScale (const cv::Mat _noiseImg,const int _sizeOfStructElem) {
    cv::Mat clearImg = _noiseImg.clone();
    int structColor = 10;
    // for example rad of elem(5x5) is (5-1)/2 = 2
    int radiusOfStructElem = (_sizeOfStructElem - 1) / 2 ;
    
    if ((_sizeOfStructElem % 2)==0) {
        printf("size of struct element can't be a multiple of two,pls change size\n");
        exit(-4);
    }
    cv::Mat structElement = cv::Mat::zeros(_sizeOfStructElem,_sizeOfStructElem,CV_8U);
    // fill the str elem
    colorTheStructElem(structElement,structColor);
    //find min value in every point environment
    for (int i =0 ; i < clearImg.rows; i++) {
        for (int j = 0 ; j < clearImg.cols; j++) {
            // create temp max for everyone environment
            int minValue = 255;
            for (int vertBarrier = -radiusOfStructElem; vertBarrier < radiusOfStructElem; vertBarrier++) {
                for (int horisBarrier = -radiusOfStructElem; horisBarrier < radiusOfStructElem; horisBarrier++) {
                    if (clearImg.at<uchar>(intensClamp(i+vertBarrier),intensClamp(j+horisBarrier)) < minValue) {
                        minValue = clearImg.at<uchar>(intensClamp(i+vertBarrier),intensClamp(j+horisBarrier));
                    }
                }
            }
            clearImg.at<uchar>(i,j) = minValue;
            minValue = 255;
        }
    }
    return clearImg;
}
