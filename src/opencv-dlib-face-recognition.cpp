#include <dlib/image_processing/frontal_face_detector.h>
#include <dlib/opencv.h>
#include <dlib/dnn.h>
#include <opencv2/opencv.hpp>
#include <iostream>

using namespace dlib;

template <template <int,template<typename>class,int,typename> class block, int N, template<typename>class BN, typename SUBNET>
using residual = add_prev1<block<N,BN,1,tag1<SUBNET>>>;

template <template <int,template<typename>class,int,typename> class block, int N, template<typename>class BN, typename SUBNET>
using residual_down = add_prev2<avg_pool<2,2,2,2,skip1<tag2<block<N,BN,2,tag1<SUBNET>>>>>>;

template <int N, template <typename> class BN, int stride, typename SUBNET> 
using block  = BN<con<N,3,3,1,1,relu<BN<con<N,3,3,stride,stride,SUBNET>>>>>;

template <int N, typename SUBNET> using ares      = relu<residual<block,N,affine,SUBNET>>;
template <int N, typename SUBNET> using ares_down = relu<residual_down<block,N,affine,SUBNET>>;

template <typename SUBNET> using alevel0 = ares_down<256,SUBNET>;
template <typename SUBNET> using alevel1 = ares<256,ares<256,ares_down<256,SUBNET>>>;
template <typename SUBNET> using alevel2 = ares<128,ares<128,ares_down<128,SUBNET>>>;
template <typename SUBNET> using alevel3 = ares<64,ares<64,ares<64,ares_down<64,SUBNET>>>>;
template <typename SUBNET> using alevel4 = ares<32,ares<32,ares<32,SUBNET>>>;

using anet_type = loss_metric<fc_no_bias<128,avg_pool_everything<
                            alevel0<
                            alevel1<
                            alevel2<
                            alevel3<
                            alevel4<
                            max_pool<3,3,2,2,relu<affine<con<32,7,7,2,2,
                            input_rgb_image_sized<150>
                            >>>>>>>>>>>>;

int mian(){

    dlib::array2d<dlib::bgr_pixel> dlibFrame;
    cv::Mat frame;
    cv::VideoCapture stream = cv::VideoCapture(0);

    if (!stream.isOpened()){
        std::cout << "Error while opening camera!" << std::endl;
        return -1;
    }

    dlib::frontal_face_detector face_detector = dlib::get_frontal_face_detector();

    dlib::shape_predictor shape_predictor;
    dlib::deserialize("models/shape_predictor_5_face_landmarks.dat") >> shape_predictor;

    anet_type net;
    dlib::deserialize("models/dlib_face_recognition_resnet_v1.dat") >> net;

    for(;;){
        stream >> frame;

        //convert opencv frame to dlib frame
        dlib::assign_image(dlibFrame, dlib::cv_image<dlib::bgr_pixel>(frame));

        //run face detection
        std::vector<dlib::rectangle> faces =  face_detector(dlibFrame);

        for(dlib::rectangle face: faces){
            //get face chips
            dlib::full_object_detection shape = shape_predictor(dlibFrame, face);

            std::cout << "num parts: " << shape.num_parts() << std::endl;

            for(int i=0;i<shape.num_parts();i++){
                std::cout << "part " << i << " " << shape.part(i) << std::endl;
            }
        }

        char key = (char)cv::waitKey(10);
        if (key == 'q'){
            cv::destroyAllWindows();
            break;
        }
    }

    stream.release();

    return 0;

}