#include <opencv2/opencv.hpp>
#include <iostream>
#include <unistd.h>

int main()
{

    cv::Mat frame;
    cv::VideoCapture cap = cv::VideoCapture(0);

    if (!cap.isOpened())
    {
        std::cout << "Error while opening camera";
        return -1;
    }

    for (;;)
    {
        cap >> frame;

        cv::imshow("Webcam", frame);

        if ((char)cv::waitKey(25) == 'q')
        {
            cv::destroyAllWindows();
            break;
        }
    }
    cap.release();
}
