
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/core.hpp>

#include <iostream>
using namespace std;



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

//Grey filter operations


void GreyFilter(cv::Mat image){

    cv::Mat greyImg;

    cv:: cvtColor(image,greyImg, cv::COLOR_RGB2GRAY);

    cv::imshow("Grey Filter", greyImg);

}

//gaussian blur filter operations

void GaussianFilter (cv::Mat image, int blurlvl){

    cv::Mat gaussianImg;

    cv:: GaussianBlur(image,gaussianImg,cv::Size(blurlvl,blurlvl),0);

    cv::imshow("Gaussian", gaussianImg);


}

//Bright filter operations

void BrightFilter (cv::Mat image, int brillolvl){

    cv::Mat BrightImg;

    image.convertTo(BrightImg,-1,2,brillolvl);

    cv::imshow("Bright", BrightImg);

}

//Gamma filter operations 

void GammaFilter (cv::Mat image, int gammalvl){

    cv::Mat GammaImg;

    gammaCorrection(image, GammaImg, gammalvl);


    cv::imshow("Gamma", GammaImg);

}

//main function

int main(){

    //Image extraction

    cv::Mat image;

    image = cv::imread("./sample.jpeg", cv::IMREAD_COLOR);

    int filter;

    //user choose filter 

    cout<< "Digite el filtro deseado \n  1.Filtro EScala de grises \n  2.Filtro Gaussian Blur \n  3.Correccion de Brillo \n  4.Correccion de Gamma \n  "; cin>>filter;


    if (filter == 1){

        GreyFilter(image);

    }


    if (filter == 2){

        int blurlvl;

        //user choose filter parameters

        cout<< "Digite el nivel deseado de blur ( 5, 15, 25, 35, 45):  "; cin>>blurlvl;

        //filter limitations

        if (blurlvl == 5 || blurlvl == 15  || blurlvl == 25  || blurlvl == 35  || blurlvl == 45 ) {

            GaussianFilter(image,blurlvl);
        }
        else
        {
            main();

        }

        

    }

    if (filter == 3){

        int brillolvl;

        //user choose filter parameters

        cout<< "Digite el nivel deseado de brillo (-100 -> 100):  "; cin>>brillolvl;

        //filter limitations

        if (brillolvl > -101 && brillolvl < 101){

            BrightFilter(image,brillolvl);
        }
        else
        {
            main();
        }

    }

    if (filter == 4){

        int gammalvl;

        //user choose filter parameters

        cout<< "Digite el nivel deseado de gamma (1 -> 5):  "; cin>>gammalvl;


        //filter limitations


        if (gammalvl > 0 && gammalvl < 6){

            GammaFilter(image,gammalvl);
        }
        else
        {
            main();
        }

    }

    //in case of not choosing a valid filter

    if (filter < 1 || filter > 4) {

        main();
    }


    cv::waitKey(0);

    return 0;
}