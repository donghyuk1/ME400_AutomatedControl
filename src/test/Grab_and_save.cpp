//
// Created by donghyuk on 24. 5. 23.
//
// Include files to use the pylon API.
#include <pylon/PylonIncludes.h>

#include <opencv2/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/calib3d.hpp>
#include <iostream>
#include <ctime>
#include <iomanip>
#include <sstream>


// Namespace for using pylon objects.
using namespace Pylon;

// Namespace for using cout.
using namespace std;
using namespace cv;

// Number of images to be grabbed.
static const uint32_t c_countOfImagesToGrab = 1;


/// camera parameters yml file path
cv::String parameters_path = "/home/donghyuk/workspace/ME400/AutomatedControl/src/CameraCalibrate/camparameters.yml";
cv::String calibrate_path = "/home/donghyuk/workspace/ME400/AutomatedControl/src/CameraCalibrate/calibrate.yml";

/// Camera calibration parameters;
//Mat matrix = (cv::Mat_<double>(3, 3) << 1.16840596e+03, 0.0, 9.88861582e+02, 0.0, 1.17207804e+03, 6.02792542e+02,
//        0.0, 0.0, 1.0);
//Mat distortion = (cv::Mat_<double>(1, 5) << -0.34674492, 0.20385693, 0.00038561, -0.0008934, -0.09134574);
Mat camera_matrix = cv::Mat_<double>(3, 3);
Mat distortion = cv::Mat_<double>(1, 5);

/// Camera sizing parameters
bool is_crop, is_resize;
int crop_height_start, crop_height_end, crop_width_start, crop_width_end;
vector<int> checkerboard_size(2);
float scale_x, scale_y;

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

        cout << "is_crop: " << is_crop << endl;
        cout << "crop_height_start: " << crop_height_start << endl;
        cout << "crop_height_end: " << crop_height_end << endl;
        cout << "crop_width_start: " << crop_width_start << endl;
        cout << "crop_width_end: " << crop_width_end << endl;
        cout << "checkerboard_size: " << checkerboard_size[0] << "x" << checkerboard_size[1] << endl;
        cout << "is_resize: " << is_resize << endl;
        cout << "scale_x: " << scale_x << endl;
        cout << "scale_y: " << scale_y << endl;

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



std::string getCurrentTimestamp() {
    auto now = std::chrono::system_clock::now();
    auto in_time_t = std::chrono::system_clock::to_time_t(now);
    std::tm tm;
    localtime_r(&in_time_t, &tm);  // Use localtime_r for thread-safe local time

    std::stringstream ss;
    ss << std::put_time(&tm, "%Y-%m-%d_%H-%M-%S");
    return ss.str();
}

int main(int /*argc*/, char* /*argv*/[])
{
    // The exit code of the sample application.
    int exitCode = 0;

    // Before using any pylon methods, the pylon runtime must be initialized.
    PylonInitialize();

    try
    {
        // Create an instant camera object with the camera device found first.
        CInstantCamera camera(CTlFactory::GetInstance().CreateFirstDevice());

        // Print the model name of the camera.
        cout << "Using device " << camera.GetDeviceInfo().GetModelName() << endl;

        readData();

        // The parameter MaxNumBuffer can be used to control the count of buffers
        // allocated for grabbing. The default value of this parameter is 10.
        camera.MaxNumBuffer = 5;

        // Start the grabbing of c_countOfImagesToGrab images.
        camera.StartGrabbing(c_countOfImagesToGrab);

        // This smart pointer will receive the grab result data.
        CGrabResultPtr ptrGrabResult;

        // Create pylon image format converter and pylon image
        CImageFormatConverter formatConverter;
        formatConverter.OutputPixelFormat = PixelType_BGR8packed;
        CPylonImage pylonImage;

        // Camera.StopGrabbing() is called automatically by the RetrieveResult() method
        // when c_countOfImagesToGrab images have been retrieved.
        while (camera.IsGrabbing())
        {
            // Wait for an image and then retrieve it. A timeout of 5000 ms is used.
            camera.RetrieveResult(5000, ptrGrabResult, TimeoutHandling_ThrowException);

            // Image grabbed successfully?
            if (ptrGrabResult->GrabSucceeded()) {
                // Access the image data.
                cout << "SizeX: " << ptrGrabResult->GetWidth() << endl;
                cout << "SizeY: " << ptrGrabResult->GetHeight() << endl;
                const uint8_t* pImageBuffer = (uint8_t*)ptrGrabResult->GetBuffer();
                cout << "Gray value of first pixel: " << (uint32_t)pImageBuffer[0] << endl << endl;

                // Convert Pylon image to OpenCV image
                cv::Mat openCvImage, img_gray, img_gray_downscaled, img_gray_undistorted;
                formatConverter.Convert(pylonImage, ptrGrabResult);
                openCvImage = cv::Mat(ptrGrabResult->GetHeight(), ptrGrabResult->GetWidth(), CV_8UC3, (uint8_t*)pylonImage.GetBuffer());

                // hough transform using openCV
                cvtColor(openCvImage, img_gray, COLOR_BGR2GRAY);

                /// crop image if is_crop true
                if(is_crop){
                    img_gray = img_gray(cv::Range(crop_height_start, crop_height_end), cv::Range(crop_width_start, crop_width_end));
                }

                /// resize image if is_resize true
                if(is_resize){
                    std::cout << "resizing..." << scale_x << " " << scale_y << std::endl;
                    cv::resize(img_gray, img_gray_downscaled, cv::Size(), scale_x, scale_y, cv::INTER_LINEAR);
                }else{
                    img_gray_downscaled = img_gray;
                }

                undistort(img_gray_downscaled, img_gray_undistorted, camera_matrix, distortion);
                // Get the current timestamp and create the filename
                std::string timestamp = getCurrentTimestamp();
                std::string filename = "./" + timestamp + ".png";

                // Save the image to the current directory with the timestamp as filename
                cv::imwrite(filename, img_gray_undistorted);

                cout << "Image saved as " << filename << endl;
            }
            else {
                cout << "Error: " << std::hex << ptrGrabResult->GetErrorCode() << std::dec << " " << ptrGrabResult->GetErrorDescription() << endl;
            }
        }
    }
    catch (const GenericException& e)
    {
        // Error handling.
        cerr << "An exception occurred." << endl
             << e.GetDescription() << endl;
        exitCode = 1;
    }

    // Releases all pylon resources.
    PylonTerminate();

    return exitCode;
}