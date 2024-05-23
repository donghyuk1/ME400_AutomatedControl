//
// Created by donghyuk on 24. 5. 17.
//
/* openCVGrab: A sample program showing to convert Pylon images to opencv MAT.

	Copyright 2017 Matthew Breit <matt.breit@gmail.com>

	Licensed under the Apache License, Version 2.0 (the "License");
	you may not use this file except in compliance with the License.
	You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

	Unless required by applicable law or agreed to in writing, software
	distributed under the License is distributed on an "AS IS" BASIS,
	WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
	See the License for the specific language governing permissions and
	limitations under the License.

	THIS SOFTWARE REQUIRES ADDITIONAL SOFTWARE (IE: LIBRARIES) IN ORDER TO COMPILE
	INTO BINARY FORM AND TO FUNCTION IN BINARY FORM. ANY SUCH ADDITIONAL SOFTWARE
	IS OUTSIDE THE SCOPE OF THIS LICENSE.
*/
// Include files to use OpenCV API.
#include <opencv2/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/calib3d.hpp>

/// math library to calculate camera yaw angle
#include <math.h>

// Include files to use the PYLON API.
#include <pylon/PylonIncludes.h>

// Use sstream to create image names including integer
#include <sstream>

// Namespace for using pylon objects.
using namespace Pylon;

// Namespace for using GenApi objects
using namespace GenApi;

/// Namespace for using opencv objects.
using namespace cv;

/// Namespace for using cout.
using namespace std;

/// camera parameters yml file path
cv::String parameters_path = SRC_DIR "/CameraCalibrate/camparameters.yml";
cv::String calibrate_path = SRC_DIR "/CameraCalibrate/calibrate.yml";

/// Camera calibration parameters;
//Mat matrix = (cv::Mat_<double>(3, 3) << 1.16840596e+03, 0.0, 9.88861582e+02, 0.0, 1.17207804e+03, 6.02792542e+02,
//        0.0, 0.0, 1.0);
//Mat distortion = (cv::Mat_<double>(1, 5) << -0.34674492, 0.20385693, 0.00038561, -0.0008934, -0.09134574);
Mat camera_matrix = cv::Mat_<float>(3, 3);
Mat distortion = cv::Mat_<float>(1, 5);

/// Camera sizing parameters
bool is_crop, is_resize;
int crop_height_start, crop_height_end, crop_width_start, crop_width_end;
vector<int> checkerboard_size(2);
float scale_x, scale_y;
float line_gradient_threshold;


int readData(){

    cv::FileStorage fs_params(parameters_path, cv::FileStorage::READ);
    if(!fs_params.isOpened()) {
        std::cout << "file path : " << parameters_path << std::endl;
        std::cerr << "Failed to open camparameters.yml" << std::endl;
        exit(-1);
        return -1;
    }else {

        fs_params["is_crop"] >> is_crop;
        fs_params["crop_height_start"] >> crop_height_start;
        fs_params["crop_height_end"] >> crop_height_end;
        fs_params["crop_width_start"] >> crop_width_start;
        fs_params["crop_width_end"] >> crop_width_end;
        fs_params["checkerboard_size"] >> checkerboard_size;
        fs_params["is_resize"] >> is_resize;
        fs_params["scale_x"] >> scale_x;
        fs_params["scale_y"] >> scale_y;
        fs_params["line_gradient_threshold"] >> line_gradient_threshold;

        cout << "is_crop: " << is_crop << endl;
        cout << "crop_height_start: " << crop_height_start << endl;
        cout << "crop_height_end: " << crop_height_end << endl;
        cout << "crop_width_start: " << crop_width_start << endl;
        cout << "crop_width_end: " << crop_width_end << endl;
        cout << "checkerboard_size: " << checkerboard_size[0] << "x" << checkerboard_size[1] << endl;
        cout << "is_resize: " << is_resize << endl;
        cout << "scale_x: " << scale_x << endl;
        cout << "scale_y: " << scale_y << endl;
        cout << "line_gradient_threshold: " << line_gradient_threshold << endl;

        fs_params.release();
    }
    cv::FileStorage fs_calibrate(calibrate_path, cv::FileStorage::READ);
    if(!fs_calibrate.isOpened()) {
        std::cerr << "Failed to open calibrate.yml" << std::endl;
        return -1;
    }else{
        fs_calibrate["camera_matrix"] >> camera_matrix;
        fs_calibrate["distortion_coeff"] >> distortion;

        fs_calibrate.release();
    }

    return 0;
}



int main(int argc, char* argv[])
{
    // The exit code of the sample application.
    int exitCode = 0;

    // Automagically call PylonInitialize and PylonTerminate to ensure the pylon runtime system
    // is initialized during the lifetime of this object.
    Pylon::PylonAutoInitTerm autoInitTerm;

    /// read camera parameters & distortion coeff
    readData();

    try
    {
        // Create an instant camera object with the camera device found first.
        cout << "Creating Camera..." << endl;
        CInstantCamera camera(CTlFactory::GetInstance().CreateFirstDevice());

        // or use a device info object to use a specific camera
        //CDeviceInfo info;
        //info.SetSerialNumber("21694497");
        //CInstantCamera camera( CTlFactory::GetInstance().CreateFirstDevice(info));
        cout << "Camera Created." << endl;
        // Print the model name of the camera.
        cout << "Using device " << camera.GetDeviceInfo().GetModelName() << endl;

        // The parameter MaxNumBuffer can be used to control the count of buffers
        // allocated for grabbing. The default value of this parameter is 10.
        camera.MaxNumBuffer = 10;

        // create pylon image format converter and pylon image
        CImageFormatConverter formatConverter;
        formatConverter.OutputPixelFormat= PixelType_BGR8packed;
        CPylonImage pylonImage;

        // Create an OpenCV image
        Mat openCvImage, img_gray_downscaled, img_gray, img_edge, img_result;
        Mat img_histeq, img_filtered;
        Mat img_gray_undistorted;

        // Average filter kernel
        Mat avg_kernel = Mat::ones(5, 5, CV_32F) / 25;

        // average slope
        float yaw_angle;
        int valid_count;


        // Start the grabbing of c_countOfImagesToGrab images.
        // The camera device is parameterized with a default configuration which
        // sets up free-running continuous acquisition.
        //camera.StartGrabbing( c_countOfImagesToGrab);
        camera.StartGrabbing(GrabStrategy_OneByOne);

        // This smart pointer will receive the grab result data.
        CGrabResultPtr ptrGrabResult;

        // Camera.StopGrabbing() is called automatically by the RetrieveResult() method
        // when c_countOfImagesToGrab images have been retrieved.
        while ( camera.IsGrabbing())
        {
            // Wait for an image and then retrieve it. A timeout of 5000 ms is used.
            camera.RetrieveResult( 5000, ptrGrabResult, TimeoutHandling_ThrowException);

            // Image grabbed successfully?
            if (ptrGrabResult->GrabSucceeded())
            {
                // Access the image data.
                int sizeX = ptrGrabResult->GetWidth();
                int sizeY = ptrGrabResult->GetHeight();

                /// Initialize yaw parameter
                yaw_angle = 0;
                valid_count = 0;

//                std::cout << "Before image resize : " << "SizeX: " << sizeX <<
//                    ", SizeY: " << sizeY << std::endl;
                const uint8_t *pImageBuffer = (uint8_t *) ptrGrabResult->GetBuffer();
                //std::cout << "Gray value of first pixel: " << (uint32_t) pImageBuffer[0] << std::endl << std::endl;

                // Convert the grabbed buffer to pylon image
                formatConverter.Convert(pylonImage, ptrGrabResult);

                // Create an OpenCV image out of pylon image
                openCvImage= cv::Mat(ptrGrabResult->GetHeight(), ptrGrabResult->GetWidth(), CV_8UC3, (uint8_t *) pylonImage.GetBuffer());

                // hough transform using openCV
                cvtColor(openCvImage, img_gray, COLOR_BGR2GRAY);

                /// crop image if is_crop true
                if(is_crop){
                    img_gray = img_gray(cv::Range(crop_height_start, crop_height_end), cv::Range(crop_width_start, crop_width_end));
                }

                /// resize image if is_resize true
                if(is_resize){
                    //std::cout << "resizing..." << scale_x << " " << scale_y << std::endl;
                    cv::resize(img_gray, img_gray_downscaled, cv::Size(), scale_x, scale_y, cv::INTER_LINEAR);
                }else{
                    img_gray_downscaled = img_gray;
                }

                undistort(img_gray_downscaled, img_gray_undistorted, camera_matrix, distortion);

                /// Histogram equalization
                equalizeHist(img_gray_undistorted, img_histeq);

                /// Apply average filter
                filter2D(img_histeq, img_filtered, -1, avg_kernel, Point(-1, -1), (0, 0), BORDER_REPLICATE);

                /// Edge detection using Canny
                Canny(img_filtered, img_edge, 50, 200, 3);

                /// just for drawing lines
                cvtColor(img_edge, img_result, COLOR_GRAY2BGR);

                /// vector to store lines
                vector<Vec4i> lines;
                HoughLinesP(img_edge, lines, 3, CV_PI/180, 50, 50, 10);

                for(size_t i = 0; i < lines.size(); i++) {
                    Vec4i l = lines[i];
                    //std::cout << l << std::endl;
                    float grad_ = float(l[3] - l[1]) / float(l[2] - l[0]);
                    if (abs(grad_) > line_gradient_threshold) {
                        continue;
                    } else {
                        yaw_angle += atan(grad_);
                        valid_count += 1;
                        line(img_result, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(0, 0, 255), 2, LINE_AA);
                    }
                }

                if(valid_count > 0){
                    yaw_angle = yaw_angle / valid_count;
                } else{
                    yaw_angle = 0;
                }

                std::cout << "Average angle : " << yaw_angle * 180 / CV_PI << std::endl;


                // Create a display window
                namedWindow( "OpenCV Display Window", cv::WINDOW_NORMAL);//AUTOSIZE //FREERATIO
                // Display the current image with opencv
                imshow( "OpenCV Display Window", img_result);
                // Define a timeout for customer's input in ms.
                // '0' means indefinite, i.e. the next image will be displayed after closing the window
                // '1' means live stream
                waitKey(1);

            }
            else
            {
                cout << "Error: " << ptrGrabResult->GetErrorCode() << " " << ptrGrabResult->GetErrorDescription() << endl;
            }
        }
    }
    catch (GenICam::GenericException &e)
    {
        // Error handling.
        cerr << "An exception occurred." << endl
             << e.GetDescription() << endl;
        exitCode = 1;
    }

    // Comment the following two lines to disable waiting on exit.
//    cerr << endl << "Press Enter to exit." << endl;
//    while( cin.get() != '\n');

    return exitCode;
}