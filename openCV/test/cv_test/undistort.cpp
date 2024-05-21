//
// Created by donghyuk on 24. 5. 22.
//


#include <opencv2/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/calib3d.hpp>


// Use sstream to create image names including integer
#include <sstream>

#include <iostream>


/// camera calibrate parameters
cv::Mat matrix = (cv::Mat_<double>(3, 3) << 1.16840596e+03, 0.0, 9.88861582e+02, 0.0, 1.17207804e+03, 6.02792542e+02,
        0.0, 0.0, 1.0);
cv::Mat distortion = (cv::Mat_<double>(1, 5) << -0.34674492, 0.20385693, 0.00038561, -0.0008934, -0.09134574);

int main(void){


    // Load the grid image
    cv::Mat grid = cv::imread("../grid.png");
    if (grid.empty()) {
        std::cout << "Error loading image: grid.png" << std::endl;
        return -1;
    }

    // Undistort the grid image
    cv::Mat undistortedGrid;
    undistort(grid, undistortedGrid, matrix, distortion);

    // Display the undistorted image
    cv::imshow("Undistorted Grid", undistortedGrid);
    cv::waitKey(0);

    return 0;
}

