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
    std::string image_path = "../stair_sample.jpg";
    cv::Mat img_RGB, img_gray, img_edge, img_result;
    img_RGB = cv::imread(image_path, cv::IMREAD_COLOR);
    if(img_RGB.empty())
    {
        std::cout << "Could not read the image: " << image_path << std::endl;
        return 1;
    }
    // img to grayscale
    cv::cvtColor(img_RGB, img_gray, cv::COLOR_BGR2GRAY);

    // Edge detection
    cv::Canny(img_gray, img_edge, 50, 200, 3);
    cv::cvtColor(img_edge, img_result, cv::COLOR_GRAY2BGR);

    // Standard Hough Line Transform
    std::vector<cv::Vec4i> lines; // will hold the results of the detection
    cv::HoughLinesP(img_edge, lines, 1, CV_PI/180, 50, 50, 10); // runs the actual detection

    // Draw the lines

    for(size_t i = 0; i < lines.size(); i++){
        cv::Vec4i l = lines[i];
        cv::line(img_result, cv::Point(l[0], l[1]), cv::Point(l[2], l[3]), cv::Scalar(0,0,255), 2, cv::LINE_AA);
    }
    cv::imshow("Display window", img_result);



    int k = cv::waitKey(0); // Wait for a keystroke in the window
    cv::destroyAllWindows();
    return 0;
}