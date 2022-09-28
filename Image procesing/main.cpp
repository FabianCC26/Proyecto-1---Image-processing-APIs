
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/core.hpp>



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


int main(){
    cv::Mat image;
    image = cv::imread("./sample.jpeg", cv::IMREAD_COLOR);

    cv::Mat gaussianImg;
    cv::Mat grayImg;
    cv::Mat BrightImg;
    cv::Mat GammaImg;

    cv:: GaussianBlur(image,gaussianImg,cv::Size(45,45),0);
    cv:: cvtColor(image,grayImg, cv::COLOR_RGB2GRAY);

    //last 2 spaces for change brightness
    image.convertTo(BrightImg,-1,2,40);

    gammaCorrection(image, GammaImg, 2.2);

    cv::imshow("Original image", image);
    cv::imshow("Gamma", GammaImg);
    cv::imshow("Gaussian", gaussianImg);
    cv::imshow("Gray", grayImg);
    cv::imshow("Bright", BrightImg);
    cv::waitKey(0);
    return 0;
}