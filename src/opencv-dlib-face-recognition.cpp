#include <dlib/dnn.h>
#include <dlib/opencv.h>
#include <dlib/image_processing/frontal_face_detector.h>
#include <opencv2/opencv.hpp>
#include <boost/chrono.hpp>
#include <iostream>

using namespace dlib;
using namespace std;

template <template <int, template <typename> class, int, typename> class block, int N, template <typename> class BN, typename SUBNET>
using residual = add_prev1<block<N, BN, 1, tag1<SUBNET>>>;

template <template <int, template <typename> class, int, typename> class block, int N, template <typename> class BN, typename SUBNET>
using residual_down = add_prev2<avg_pool<2, 2, 2, 2, skip1<tag2<block<N, BN, 2, tag1<SUBNET>>>>>>;

template <int N, template <typename> class BN, int stride, typename SUBNET>
using block = BN<con<N, 3, 3, 1, 1, relu<BN<con<N, 3, 3, stride, stride, SUBNET>>>>>;

template <int N, typename SUBNET>
using ares = relu<residual<block, N, affine, SUBNET>>;
template <int N, typename SUBNET>
using ares_down = relu<residual_down<block, N, affine, SUBNET>>;

template <typename SUBNET>
using alevel0 = ares_down<256, SUBNET>;
template <typename SUBNET>
using alevel1 = ares<256, ares<256, ares_down<256, SUBNET>>>;
template <typename SUBNET>
using alevel2 = ares<128, ares<128, ares_down<128, SUBNET>>>;
template <typename SUBNET>
using alevel3 = ares<64, ares<64, ares<64, ares_down<64, SUBNET>>>>;
template <typename SUBNET>
using alevel4 = ares<32, ares<32, ares<32, SUBNET>>>;

using anet_type = loss_metric<fc_no_bias<128, avg_pool_everything<
                                                  alevel0<
                                                      alevel1<
                                                          alevel2<
                                                              alevel3<
                                                                  alevel4<
                                                                      max_pool<3, 3, 2, 2, relu<affine<con<32, 7, 7, 2, 2, input_rgb_image_sized<150>>>>>>>>>>>>>;

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

    anet_type net;
    dlib::deserialize("models/dlib_face_recognition_resnet_model_v1.dat") >> net;

    for (;;)
    {
        stream >> frame;

        auto start_t = std::chrono::high_resolution_clock::now();

        // convert opencv frame to dlib frame
        dlib::assign_image(dlibFrame, dlib::cv_image<dlib::bgr_pixel>(frame));

        // run face detection
        std::vector<dlib::matrix<dlib::rgb_pixel>> faces;

        for (dlib::rectangle face : face_detector(dlibFrame))
        {
            // get face chips
            dlib::full_object_detection shape = shape_predictor(dlibFrame, face);
            dlib::matrix<dlib::rgb_pixel> face_chip;
            dlib::extract_image_chip(dlibFrame, dlib::get_face_chip_details(shape, 150, 0.25), face_chip);
            faces.push_back(std::move(face_chip));
        }

        if (faces.size() > 0)
        {
            std::cout << "Detected " << faces.size() << " faces(s)" << std::endl;
            std::vector<dlib::matrix<float, 0, 1>> face_descriptors = net(faces);
        }

        auto end_t = std::chrono::high_resolution_clock::now();
        std::cout << "Time to process: " << std::chrono::duration<double, std::milli>(end_t - start_t).count() << "ms" << std::endl;

        cv::imshow("Webcam", frame);
        char key = (char)cv::waitKey(10);
        if (key == 'q')
        {
            break;
        }
    }

    stream.release();
    cv::destroyAllWindows();

    return 0;
}