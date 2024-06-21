#include <dlib/dnn.h>
#include <dlib/opencv.h>
#include <dlib/image_processing/frontal_face_detector.h>
#include <opencv2/opencv.hpp>
#include <iostream>

int main()
{

    dlib::array2d<dlib::bgr_pixel> dlibFrame;
    cv::Mat frame;
    cv::VideoCapture stream = cv::VideoCapture(0);

    if (!stream.isOpened())
    {
        std::cout << "Error while opening camera!" << std::endl;
        return -1;
    }

    dlib::frontal_face_detector face_detector = dlib::get_frontal_face_detector();

    dlib::shape_predictor shape_predictor;
    dlib::deserialize("models/shape_predictor_5_face_landmarks.dat") >> shape_predictor;

    // anet_type net;
    // dlib::deserialize("models/dlib_face_recognition_resnet_v1.dat") >> net;

    for (;;)
    {
        stream >> frame;

        // convert opencv frame to dlib frame
        dlib::assign_image(dlibFrame, dlib::cv_image<dlib::bgr_pixel>(frame));

        // run face detection
        std::vector<dlib::rectangle> faces = face_detector(dlibFrame);

        for (dlib::rectangle face : faces)
        {
            // get face chips
            dlib::full_object_detection shape = shape_predictor(dlibFrame, face);

            std::cout << "num parts: " << shape.num_parts() << std::endl;

            for (int i = 0; i < shape.num_parts(); i++)
            {
                std::cout << "part " << i << " " << shape.part(i) << std::endl;
            }
        }

        char key = (char)cv::waitKey(10);
        if (key == 'q')
        {
            cv::destroyAllWindows();
            break;
        }
    }

    stream.release();

    return 0;
}