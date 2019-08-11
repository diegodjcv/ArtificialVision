#include <cstdlib>
#include <iostream>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/video/video.hpp>
#include <opencv2/videoio/videoio.hpp>
#include <opencv2/imgcodecs/imgcodecs.hpp>
#include <math.h>

#include <SerialStream.h>

using namespace std;
using namespace cv;
using namespace LibSerial ;

int hMin, sMin, vMin = 124;
int hMax = 99, sMax = 62, vMax = 189;

void eventoHMin(int v, void *p){
    cout << "Valor: " << v << endl;
}

void eventoHMax(int v, void *p){
    cout << "Valor: " << v << endl;
}

void eventoSMin(int v, void *p){
    cout << "Valor: " << v << endl;
}

void eventoSMax(int v, void *p){
    cout << "Valor: " << v << endl;
}

void eventoVMin(int v, void *p){
    cout << "Valor: " << v << endl;
}

void eventoVMax(int v, void *p){
    cout << "Valor: " << v << endl;
}

double distancia(double a1[7], double a2[7]){
    double suma = 0.0;
    for(int i=0;i<7;i++){
        suma+=((a1[i]-a2[i])*(a1[i]-a2[i]));
    }
    
    return sqrt(suma);
}


int main(int argc, char *args[]){
        
    SerialStream my_serial_stream ;
    my_serial_stream.Open( "/dev/ttyACM0" ) ;
    my_serial_stream.SetBaudRate( SerialStreamBuf::BAUD_115200  ) ;
    my_serial_stream.SetCharSize( SerialStreamBuf::CHAR_SIZE_8 ) ;
    my_serial_stream.SetNumOfStopBits(1) ;
    my_serial_stream.SetFlowControl( SerialStreamBuf::FLOW_CONTROL_HARD );

    Mat frame;
    Mat segmentada;
    Mat hsv;
    
    VideoCapture video(2);
    video.set(CAP_PROP_FRAME_WIDTH, 640);
    video.set(CAP_PROP_FRAME_HEIGHT, 480);
    
    namedWindow("segmentada",WINDOW_AUTOSIZE);
    namedWindow("seg",WINDOW_AUTOSIZE);
    
    createTrackbar("HMin","video",&hMin,180,eventoHMin);
    createTrackbar("HMax","video",&hMax,180,eventoHMax);
    createTrackbar("SMin","video",&sMin,255,eventoSMin);    
    createTrackbar("SMax","video",&sMax,255,eventoSMax);    
    createTrackbar("VMin","video",&vMin,255,eventoVMin);    
    createTrackbar("VMax","video",&vMax,255,eventoVMax);    
    Mat clon;
    Mat seguim;
    Mat imagen;
    Mat vtn1;
    Mat vtn2;
    Mat vtn3;
    Mat vtn4;
    
    srand(time(NULL));
    
    double momentosBD[7] = {0.200796, 0.00872375, 0.000485274, 1.68589e-05, 5.2391e-10, -7.68682e-07, -1.43207e-09};
    double momentos[7];
    double dist = 0.0;
    double epsi = 0.04;
    double cx = 0, cy = 0;
    
    if (video.isOpened()){
        while(1==1){
            video >> frame;
            cvtColor(frame,hsv,COLOR_BGR2HSV);
            
            clon = frame.clone();
            seguim = frame.clone();
            cvtColor(clon, imagen, COLOR_BGR2GRAY);
            
            GaussianBlur(clon,vtn1,Size(35,35),0);
            medianBlur ( vtn1, vtn2, 5 );
            erode(vtn2, vtn3, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) );
            dilate( vtn3, imagen, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) ); 
            
            inRange(imagen,Scalar(hMin,sMin,vMin),Scalar(hMax,sMax,vMax),segmentada);
            
            Moments iMoments = moments(segmentada, true);
            HuMoments(iMoments, momentos);
            
            dist = distancia(momentosBD, momentos);
            
            for (int i =0;i<480;i++){
                circle(seguim,Point(320,i), 0.5, Scalar(45,100,50),1);
            }
            for (int i =0;i<640;i++){
                circle(seguim,Point(i,240), 0.5, Scalar(45,100,50),1);
            }
            
            if (dist<=epsi){
                cx = iMoments.m10/iMoments.m00;
                cy = iMoments.m01/iMoments.m00;
                circle(seguim,Point(cx,cy), 10, Scalar(255,255,255),3);
                int a=round((cx-320)/3);
                
                if(a>1){
                    //cout << "D" << endl;
                    my_serial_stream << 'D' ;
                }else{
                    if(a<-1){
                        //cout << "I" << endl;
                        my_serial_stream << 'I' ;
                    }
                }
            }
            cv::flip(seguim,seguim,1);
            cv::flip(segmentada,segmentada,1);
            imshow("segmentada",segmentada);
            imshow("seg", seguim);
            if(waitKey(23)==27){
                my_serial_stream.Close() ;
                break;
            }
        }
   }
    return 0;
}
