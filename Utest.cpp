#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/core.hpp>

#include <iostream>
using namespace std;



//Grey filter operations

int GreyFilter(cv::Mat image, int height, int width){

    cv::Mat greyImg;

    cv:: cvtColor(image,greyImg, cv::COLOR_RGB2GRAY);

    //cv::imshow("Grey Filter", greyImg);


    if(height != greyImg.size[0] || width != greyImg.size[1]){

        return -1;

    }


    return 0;

}

//gaussian blur filter operations

int GaussianFilter (cv::Mat image, int blurlvl, int height, int width){

    cv::Mat gaussianImg;

    cv:: GaussianBlur(image,gaussianImg,cv::Size(blurlvl,blurlvl),0);

    //cv::imshow("Gaussian", gaussianImg);

    if(height != gaussianImg.size[0] || width != gaussianImg.size[1]){

        return -1;

    }


    return 0;


}

//Bright filter operations

int BrightFilter (cv::Mat image, int brillolvl, int height, int width){

    cv::Mat BrightImg;

    image.convertTo(BrightImg,-1,2,brillolvl);

    //cv::imshow("Bright", BrightImg);

    if(height != BrightImg.size[0] || width != BrightImg.size[1]){

        return -1;

    }


    return 0;

}

//gamma correction operations 

void gammaCorrection(const cv::Mat &src, cv::Mat &dst, const float gamma)
{
    float invGamma = 1 / gamma;

    cv::Mat table(1, 256, CV_8U);
    uchar *p = table.ptr();
    for (int i = 0; i < 256; ++i) {
        p[i] = (uchar) (pow(i / 255.0, invGamma) * 255);
    }

    LUT(src, table, dst);

}

//Gamma filter operations 

int GammaFilter (cv::Mat image, int gammalvl, int height, int width){

    cv::Mat GammaImg;

    gammaCorrection(image, GammaImg, gammalvl);


    //cv::imshow("Gamma", GammaImg);

    if(height != GammaImg.size[0] || width != GammaImg.size[1]){

        return -1;

    }

    return 0;


}


//Unitari tests

int main(){

    int estado = 5;

    cv::Mat image;

    image = cv::imread("./sample.jpeg", cv::IMREAD_COLOR);

    int height = image.size[0];

    int widht = image.size[1];


    estado = GreyFilter(image,height,widht);
    cout<<estado<<endl;

   

    estado = GaussianFilter(image,45,height,widht);
    cout<<estado<<endl;
   

    estado = BrightFilter(image,100,height,widht);
    cout<<estado<<endl;
  

    estado = GammaFilter(image,5,height,widht);
    cout<<estado<<endl;

    cout<<"test completed\n";


}