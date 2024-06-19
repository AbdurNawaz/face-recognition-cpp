#include <dlib/image_processing/frontal_face_detector.h>
#include <dlib/opencv.h>
#include <opencv2/opencv.hpp>
#include <boost/chrono.hpp>
#include <iostream>

int main()
{

    dlib::frontal_face_detector face_detector = dlib::get_frontal_face_detector();

    cv::Mat frame;
    dlib::array2d<dlib::bgr_pixel> dlibFrame;
    cv::VideoCapture cap = cv::VideoCapture(0);

    if (!cap.isOpened())
    {
        std::cout << "Couldn't open camera" << std::endl;
        return -1;
    }

    while (true)
    {
        cap >> frame;

        dlib::assign_image(dlibFrame, dlib::cv_image<dlib::bgr_pixel>(frame));

        auto start_t = std::chrono::high_resolution_clock::now();

        std::vector<dlib::rectangle> faces = face_detector(dlibFrame, 0);

        auto end_t = std::chrono::high_resolution_clock::now();

        double time_diff = std::chrono::duration<double, std::milli>(end_t - start_t).count();

        std::cout << "Time difference: " << time_diff << std::endl;

        for (dlib::rectangle face : faces)
        {
            dlib::draw_rectangle(dlibFrame, face, dlib::rgb_pixel(255, 0, 0), 4);
        }

        cv::Mat changedFrame = dlib::toMat(dlibFrame);

        if (frame.empty())
        {
            break;
        }
        cv::imshow("image", changedFrame);
        if ((char)cv::waitKey(10) == 'q')
        {
            break;
        }
    }
    return 0;
}