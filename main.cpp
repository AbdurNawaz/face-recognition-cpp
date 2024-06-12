#include <dlib/image_processing/frontal_face_detector.h>
#include <dlib/opencv.h>
#include <opencv2/opencv.hpp>
#include <iostream>

using namespace dlib;
using namespace std;
using namespace cv;

int main() {

    frontal_face_detector face_detector = get_frontal_face_detector();

    Mat frame;
    array2d<dlib::bgr_pixel> dlibFrame;
    VideoCapture cap = VideoCapture(0);

    if (!cap.isOpened()){
        cout << "Couldn't open camera" << endl;
        return -1;
    }

    namedWindow("Webcam", 1);

    while(true){
        cap >> frame;

        dlib::assign_image(dlibFrame, dlib::cv_image<dlib::bgr_pixel>(frame));

        std::vector<dlib::rectangle> faces = face_detector(dlibFrame);

        for (dlib::rectangle face: faces){
            draw_rectangle(dlibFrame, face, rgb_pixel(255, 0, 0), 4);
        }

        Mat changedFrame = dlib::toMat(dlibFrame);

        if (frame.empty()){
            break;
        }
        imshow("image", changedFrame);
        if ( (char) waitKey(10) == 'q'){
            break;
        }
    }
    return 0;
}