//
//  main.cpp
//  erlangNoise
//
//  Created by артем on 17.03.17.
//  Copyright © 2017 артем. All rights reserved.
//

#include <stdio.h>

//
//  Black-white(lab1)
//
//  Created by артем on 03.03.17.
//  Copyright © 2017 артем. All rights reserved.
//
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "iostream"
#include "../src/workWithHist.cpp"
#include "../src/helpFuncForHist.cpp"
#include "../src/matMorphOper.cpp"

//rows cols
using namespace cv;
using namespace std;

int main( )
{
    Mat erlangePic = imread("example.jpg");
    if(! erlangePic.data ) {
        cout <<  "Could not open or find the image" << std::endl ;
        return -1;
    }
    double tempCount = 15;
    // declarate arr
    uint *histArrOfErlangPic = new uint[256];
    // init arr and filling from gray image
    initHistArr(histArrOfErlangPic);
    fillArrayWithValuesFromGI(histArrOfErlangPic, erlangePic);
    // the declaration of the flags of the describing min an max
    uint maxPoint = 0;
    uint higthOfErlangHist = findMaxValueInHistArrayAndFixIndex(histArrOfErlangPic, &maxPoint);
    //show max and min values for debug
    cout <<"max value = " << higthOfErlangHist << " in point - " << maxPoint << endl;
    //show histogram
    Mat histOfErlangPic = getNewHistWihtParam(histArrOfErlangPic, 256, higthOfErlangHist,4);
    
    //some debug
    std::cout << "erl max = " <<  findErlangNoiseMax(0, 255, tempCount, tempCount)<<std::endl;

    // use dilation
    Mat dilationMat = dilationForGrayScale(erlangePic, 11);
    Mat erosionMat = erosionForGrayScale(erlangePic, 3);
    Mat dilationAndErosionMat = erosionForGrayScale(dilationMat, 3);
    //show time
    imshow("input image", erlangePic);
    imshow("erlangPicHist",histOfErlangPic);
    imshow("pic after dilation", dilationMat);
    imshow("pic after erosion", erosionMat);
    imshow("final pic", dilationAndErosionMat);
    imshow("tempPic",createPicForFilter(256,256));
    waitKey(0);
    return 0;
}

