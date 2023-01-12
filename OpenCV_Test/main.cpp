#include <opencv2/opencv.hpp>
#include <stdio.h>

using namespace cv;
using namespace std;

int main() {
    
    Mat image;

    namedWindow("Display window");

    VideoCapture cap(-1);

    if (!cap.isOpened()) {
        cout << "cannot open camera\n";
    }

    while (true) {
        cap >> image;

        imshow("Dipslay window", image);

        waitKey(25);
    }

return 0;
}