#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string.h>
#include <string>



#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/core.hpp>
 
 
using namespace std;
using namespace cv;

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

void GreyFilter(Mat image, int clientSocket){

    Mat greyImg;

    cvtColor(image,greyImg,COLOR_RGB2GRAY);

    imshow("Grey Filter", greyImg);

    int  imgSize = greyImg.total()*greyImg.elemSize();

    // Echo message back to client
    send(clientSocket, greyImg.data,  imgSize, 0);


    

}


void GaussianFilter (cv::Mat image, int blurlvl, int clientSocket){

    cv::Mat gaussianImg;

    cv:: GaussianBlur(image,gaussianImg,cv::Size(blurlvl,blurlvl),0);

    cv::imshow("Gaussian", gaussianImg);

    int  imgSize = gaussianImg.total()*gaussianImg.elemSize();


    // Echo message back to client
    send(clientSocket, gaussianImg.data,  imgSize, 0);

}

//Bright filter operations

void BrightFilter (cv::Mat image, int brillolvl, int clientSocket){

    cv::Mat BrightImg;

    image.convertTo(BrightImg,-1,2,brillolvl);

    cv::imshow("Bright", BrightImg);

    int  imgSize = BrightImg.total()*BrightImg.elemSize();

    // Echo message back to client
    send(clientSocket, BrightImg.data,  imgSize, 0);

}

//Gamma filter operations 

void GammaFilter (cv::Mat image, int gammalvl,int clientSocket){

    cv::Mat GammaImg;

    gammaCorrection(image, GammaImg, gammalvl);

    int  imgSize = GammaImg.total()*GammaImg.elemSize();


    cv::imshow("Gamma", GammaImg);

     // Echo message back to client
    send(clientSocket, GammaImg.data,  imgSize, 0);

}



 
int main()
{
    // Create a socket
    int listening = socket(AF_INET, SOCK_STREAM, 0);
    if (listening == -1)
    {
        cerr << "Can't create a socket! Quitting" << endl;
        return -1;
    }
 
    // Bind the ip address and port to a socket
    sockaddr_in hint;
    hint.sin_family = AF_INET;
    hint.sin_port = htons(54000);
    inet_pton(AF_INET, "0.0.0.0", &hint.sin_addr);
 
    bind(listening, (sockaddr*)&hint, sizeof(hint));
 
    // Tell Winsock the socket is for listening
    listen(listening, SOMAXCONN);
 
    // Wait for a connection
    sockaddr_in client;
    socklen_t clientSize = sizeof(client);
 
    int clientSocket = accept(listening, (sockaddr*)&client, &clientSize);
 
    char host[NI_MAXHOST];      // Client's remote name
    char service[NI_MAXSERV];   // Service (i.e. port) the client is connect on
 
    memset(host, 0, NI_MAXHOST); // same as memset(host, 0, NI_MAXHOST);
    memset(service, 0, NI_MAXSERV);
 
    if (getnameinfo((sockaddr*)&client, sizeof(client), host, NI_MAXHOST, service, NI_MAXSERV, 0) == 0)
    {
        cout << host << " connected on port " << service << endl;
    }
    else
    {
        inet_ntop(AF_INET, &client.sin_addr, host, NI_MAXHOST);
        cout << host << " connected on port " << ntohs(client.sin_port) << endl;
    }
 
    // Close listening socket
    close(listening);
 
    // While loop: accept and echo message back to client
    char buf[4096];


 
    while (true)
    {
        memset(buf, 0, 4096);

        // Wait for client to send data
        Mat  img = Mat::zeros( 480,481, CV_8UC3);
        int  imgSize = img.total()*img.elemSize();
        uchar sockData[imgSize];
        int bytes = 0;

        //Receive data here

       

        for (int i = 0; i < imgSize; i += bytes) {
            
                if ((bytes = recv(clientSocket, sockData +i, imgSize  - i, 0)) == -1)  {
                    break;
                }
        }

        // Assign pixel value to img
        int ptr=0;
        for (int i = 0;  i < img.rows; i++) {
            for (int j = 0; j < img.cols; j++) {                                     
            img.at<cv::Vec3b>(i,j) = cv::Vec3b(sockData[ptr+ 0],sockData[ptr+1],sockData[ptr+2]);
            ptr=ptr+3;
            }
        }


        GreyFilter(img,clientSocket);
        GammaFilter(img,5,clientSocket);
        BrightFilter(img,100,clientSocket);
        GaussianFilter(img,45,clientSocket);



        cv::waitKey(0);
 

        cout << "prueba" << endl;


    

    }
 
    // Close the socket


    close(clientSocket);
    return 0;
}