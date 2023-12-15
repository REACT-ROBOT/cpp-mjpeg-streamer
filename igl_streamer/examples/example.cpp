#include <opencv2/opencv.hpp>

#include <nadjieb/mjpeg_streamer.hpp>
#include "igl_to_opencv.hpp"

/*extern "C" {
#include "igl3_image.h"
}*/

// for convenience
using MJPEGStreamer = nadjieb::MJPEGStreamer;

/*Igl_Image *src1;
unsigned char *src1_p;*/
IglToCvImage image;

static int igl_height = 240;
static int igl_width = 320;
static int shm_id =1000;


void
init()
{
  image.iglToOpencvShmInit(shm_id, igl_width ,igl_height);

}

int main() {
    /*cv::VideoCapture cap(0);
    if (!cap.isOpened()) {
        std::cerr << "VideoCapture not opened\n";
        exit(EXIT_FAILURE);
    }*/
    unsigned char *pic;
    init();
/*    pic = get_pixel(src1, src1_p, 320, 240)*/

    std::vector<int> params = {cv::IMWRITE_JPEG_QUALITY, 90};

    MJPEGStreamer streamer;

    // By default "/shutdown" is the target to graceful shutdown the streamer
    // if you want to change the target to graceful shutdown:
    //      streamer.setShutdownTarget("/stop");

    // By default std::thread::hardware_concurrency() workers is used for streaming
    // if you want to use 4 workers instead:
    //      streamer.start(8080, 4);
    streamer.start(8080);

    // Visit /shutdown or another defined target to stop the loop and graceful shutdown
    while (streamer.isRunning()) {
        cv::Mat frame;
            frame =   image.iglToOpencvCreateCvMat();
        //cap >> frame;
        if (frame.empty()) {
            std::cerr << "frame not grabbed\n";
            exit(EXIT_FAILURE);
        }

        // http://localhost:8080/bgr
        std::vector<uchar> buff_bgr;
        cv::imencode(".jpg", frame, buff_bgr, params);
        streamer.publish("/bgr", std::string(buff_bgr.begin(), buff_bgr.end()));

        cv::Mat hsv;
        cv::cvtColor(frame, hsv, cv::COLOR_BGR2HSV);

        // http://localhost:8080/hsv
        std::vector<uchar> buff_hsv;
        cv::imencode(".jpg", hsv, buff_hsv, params);
        streamer.publish("/hsv", std::string(buff_hsv.begin(), buff_hsv.end()));

        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }

    streamer.stop();
}
