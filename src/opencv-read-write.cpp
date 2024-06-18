#include <opencv2/opencv.hpp>
#include <iostream>
#include <stdlib.h>
#include <string>

int main(int argc, char *argv[]){

    if (argc < 2){
        std::cout << "Please enter input & output location of video files" << std::endl;
    }

    cv::VideoCapture cap;
    std::string videoInput = argv[1];
    if (videoInput.at(0) == '0'){
        cap = cv::VideoCapture(0);
    } else {
        cap = cv::VideoCapture(videoInput);
    }
    
    cv::Mat frame;

    if (!cap.isOpened()){
        std::cout << "Error occured while opening stream" << std::endl;
    }

    int frame_width = static_cast<int>(cap.get(3));
    int frame_height = static_cast<int>(cap.get(4));
    cv::Size frame_size = cv::Size(frame_width, frame_height);

    int fourcc = cv::VideoWriter::fourcc('M', 'P', '4', 'V');
    std::string outputPath = argv[2];
    cv::VideoWriter writer = cv::VideoWriter(outputPath, fourcc, cap.get(cv::CAP_PROP_FPS), frame_size);

    while(cap.isOpened()){
        bool isGrabbed = cap.read(frame);
        if (!isGrabbed){
            break;
        }
        cv::imshow("Frame", frame);
        writer.write(frame);

        int key = cv::waitKey(10);
        if (key == 'q'){
            break;
        }
    }

    cap.release();
    cv::destroyAllWindows();
    writer.release();

    std::cout << "File has been written to: " << outputPath << std::endl;

    return 0;
}