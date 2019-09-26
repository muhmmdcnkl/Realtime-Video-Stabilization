#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "opencv2/features2d/features2d.hpp"
#include "opencv2/xfeatures2d/nonfree.hpp"
#include "opencv2/flann/flann.hpp"
#include "opencv2/calib3d/calib3d.hpp"
#include <opencv2/opencv.hpp>
#include <iostream>
#include <cmath>
#include <fstream>
#include <time.h>
#include <videostab.h>



using namespace std;
using namespace cv;


const int HORIZONTAL_BORDER_CROP = 30;

int main()
{

    //Create a object of stabilization class
    VideoStab stab;

    //Initialize the VideoCapture object
    VideoCapture cap(0);
    //VideoCapture cap("videoplayback1.mp4");

    Mat frame_2, frame2;
    Mat frame_1, frame1;



    cap >> frame_1;
    cvtColor(frame_1, frame1, COLOR_BGR2GRAY);

    Mat smoothedMat(2,3,CV_64F);

    VideoWriter outputVideo;
    outputVideo.open("outputVideo.avi" , CV_FOURCC('X' , 'V' , 'I' , 'D'), 30 , frame_1.size());



    //int i=0;

    while(true)
    {

        cap >> frame_2;

        if(frame_2.data == NULL)
        {
            break;
        }

        cvtColor(frame_2, frame2, COLOR_BGR2GRAY);

        Mat smoothedFrame;

        smoothedFrame = stab.stabilize(frame_1 , frame_2);
        outputVideo.write(smoothedFrame);
        //i++;
        //imwrite("file"+ std::to_string(i) +".jpg",smoothedFrame);
        //imwrite("file"+ std::to_string(i) + std::to_string(i) +".jpg",frame_2);




        //imshow("Stabilized Video" , smoothedFrame);






        char c = (char) waitKey(10);
            if( c == 27 )
              break;


        frame_1 = frame_2.clone();
        frame2.copyTo(frame1);


    }

    return 0;
}
