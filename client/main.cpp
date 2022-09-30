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

#include <list>

using namespace std;
using namespace cv;

int main()

{



    //	Create a socket
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1)
    {
        return 1;
    }

    //	Create a hint structure for the server we're connecting with
    int port = 54000;
    string ipAddress = "127.0.0.1";

    sockaddr_in hint;
    hint.sin_family = AF_INET;
    hint.sin_port = htons(port);
    inet_pton(AF_INET, ipAddress.c_str(), &hint.sin_addr);

    //	Connect to the server on the socket
    int connectRes = connect(sock, (sockaddr*)&hint, sizeof(hint));
    if (connectRes == -1)
    {
        return 1;
    }

    //	While loop:
    char buf[4096];
    


    

    do {
        //		Enter lines of text

        
        int filter;

        //user choose filter 

        cout<< "Digite el filtro deseado \n  1.Filtro EScala de grises \n  2.Filtro Gaussian Blur \n  3.Correccion de Brillo \n  4.Correccion de Gamma \n  "; cin>>filter;




        //		Send to server
        Mat frame = imread("./Cat.jpg",IMREAD_COLOR);

        int  imgSize = frame.total()*frame.elemSize();


        // Send data here
        int sendRes = send(sock, frame.data, imgSize, 0);


        if (sendRes == -1)
        {
            cout << "Could not send to server! Whoops!\r\n";
            continue;
        }


        memset(buf, 0, 4096);
        

        // Wait for server response

        Mat  img = Mat::zeros( 480,481, CV_8UC3);
        int  newimgSize = img.total()*img.elemSize();
        uchar sockData[imgSize];
        int bytes = 0;

        //Receive data here

       

        for (int i = 0; i < newimgSize; i += bytes) {
            
                if ((bytes = recv(sock, sockData +i, newimgSize  - i, 0)) == -1)  {
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

        //imshow("Grey Filter", img);

        cv::waitKey(0);


    } while(true);

    

    //	Close the socket
    close(sock);

    return 0;
}