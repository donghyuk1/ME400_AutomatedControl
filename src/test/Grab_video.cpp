#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/videoio.hpp>  // For VideoWriter

// Include files to use the PYLON API.
#include <pylon/PylonIncludes.h>

// Use sstream to create image names including integer
#include <sstream>
#include <iostream>
#include <csignal> // For signal handling
#include <ctime>

// Namespace for using pylon objects.
using namespace Pylon;

// Namespace for using GenApi objects
using namespace GenApi;

// Namespace for using opencv objects.
using namespace cv;

// Namespace for using cout.
using namespace std;

// Number of images to be grabbed.
static const uint32_t c_countOfImagesToGrab = 2000;

// Global flag to indicate when to stop grabbing images
volatile sig_atomic_t stopGrabbing = 0;

// Signal handler for SIGINT
void signalHandler(int signum)
{
    stopGrabbing = 1;
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

int main(int argc, char* argv[])
{
    // Register signal handler for SIGINT
    signal(SIGINT, signalHandler);

    // The exit code of the sample application.
    int exitCode = 0;

    // Automagically call PylonInitialize and PylonTerminate to ensure the pylon runtime system
    // is initialized during the lifetime of this object.
    Pylon::PylonAutoInitTerm autoInitTerm;

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
        formatConverter.OutputPixelFormat = PixelType_BGR8packed;
        CPylonImage pylonImage;

        // Create an OpenCV image
        Mat openCvImage;

        // Video writer object
        VideoWriter videoWriter;
        bool isVideoWriterInitialized = false;

        // Start the grabbing of c_countOfImagesToGrab images.
        // The camera device is parameterized with a default configuration which
        // sets up free-running continuous acquisition.
        //camera.StartGrabbing( c_countOfImagesToGrab);
        camera.StartGrabbing(GrabStrategy_OneByOne);

        // This smart pointer will receive the grab result data.
        CGrabResultPtr ptrGrabResult;

        // Camera.StopGrabbing() is called automatically by the RetrieveResult() method
        // when c_countOfImagesToGrab images have been retrieved.
        while (camera.IsGrabbing() && !stopGrabbing)
        {
            // Wait for an image and then retrieve it. A timeout of 5000 ms is used.
            camera.RetrieveResult(5000, ptrGrabResult, TimeoutHandling_ThrowException);

            // Image grabbed successfully?
            if (ptrGrabResult->GrabSucceeded())
            {
                // Access the image data.
                cout << "SizeX: " << ptrGrabResult->GetWidth() << endl;
                cout << "SizeY: " << ptrGrabResult->GetHeight() << endl;
                const uint8_t *pImageBuffer = (uint8_t *)ptrGrabResult->GetBuffer();
                cout << "Gray value of first pixel: " << (uint32_t)pImageBuffer[0] << endl << endl;

                // Convert the grabbed buffer to pylon image
                formatConverter.Convert(pylonImage, ptrGrabResult);
                // Create an OpenCV image out of pylon image
                openCvImage = cv::Mat(ptrGrabResult->GetHeight(), ptrGrabResult->GetWidth(), CV_8UC3, (uint8_t *)pylonImage.GetBuffer());

                // Initialize the VideoWriter object the first time a frame is grabbed
                if (!isVideoWriterInitialized)
                {
                    std::string timestamp = getCurrentTimestamp();
                    std::string filename = SRC_DIR "/saved_img/" + timestamp + ".avi";
                    // Define the codec and create a VideoWriter object
                    videoWriter.open(filename, VideoWriter::fourcc('M', 'J', 'P', 'G'), 30, openCvImage.size(), true);
                    if (!videoWriter.isOpened())
                    {
                        cerr << "Could not open the video writer" << endl;
                        return -1;
                    }
                    isVideoWriterInitialized = true;
                }

                // Write the current frame to the video
                videoWriter.write(openCvImage);

                // Create a display window
                //namedWindow("OpenCV Display Window", cv::WINDOW_NORMAL); //AUTOSIZE //FREERATIO
                // Display the current image with OpenCV
                //imshow("OpenCV Display Window", openCvImage);
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

        // Stop grabbing
        camera.StopGrabbing();

        // Release the VideoWriter object
        videoWriter.release();

        cout << "Video saved successfully!" << endl;
    }
    catch (GenICam::GenericException &e)
    {
        // Error handling.
        cerr << "An exception occurred." << endl
             << e.GetDescription() << endl;
        exitCode = 1;
    }

    // Comment the following two lines to disable waiting on exit.
    //cerr << endl << "Press Enter to exit." << endl;
    //while (cin.get() != '\n');

    return exitCode;
}