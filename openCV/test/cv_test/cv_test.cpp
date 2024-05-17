//
// Created by donghyuk on 24. 5. 17.
//
#include <opencv2/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
int main()
{
    //std::string image_path = samples::findFile("starry_night.jpg");
    std::string image_path = "../grid.png";
    cv::Mat img_RGB, img_gray;
    img_RGB = cv::imread(image_path, cv::IMREAD_COLOR);
    if(img_RGB.empty())
    {
        std::cout << "Could not read the image: " << image_path << std::endl;
        return 1;
    }
    cv::cvtColor(img_RGB, img_gray, cv::COLOR_BGR2GRAY);
    cv::imshow("Display window", img_gray);
    int k = cv::waitKey(0); // Wait for a keystroke in the window

    return 0;
}