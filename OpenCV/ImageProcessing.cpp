/*
 *
 *	Author:			Drew Grobmeier
 *	Credit:			Sam Siewert, OpenCV Team
 *	Purpose:		To outline boxes and show next arrow
 *	Date:			4/19/2020
 *	Version:		V2
 *	Walkthrough:		4/20/2020
 * 	Comments:		//** signifies comments to be deleted when finished.
 *
 */

#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include <iostream>

using namespace cv;
using namespace std;

void help();

int main(int argc, char** argv)
{
    const char* filename = argc >= 2 ? argv[1] : "ImageProcessing2.png";

    Mat src = imread("ImageProcessing2.png", CV_LOAD_IMAGE_COLOR);

    //This srcDirectFile is to keep an original for end purposes, such as the car crashing. 
    Mat srcDirectFile = src.clone();

    //Just a check for if the image is open
    if (src.empty())
    {
        help();
        cout << "can not open " << filename << endl;
        return -1;
    }

    // I want to include grid points for where the monkey is at. 

    Mat img_blur;
    Mat dst, cdst;
    //This is where edge detection begins.
    Canny(src, dst, 50, 200, 3);
    cvtColor(dst, cdst, CV_GRAY2BGR);

    //This is supposed to grab the (monkey) and put a circle around it detecting the object.
    // it doesn't work currently, it has to ne remodeled.
    /*
    medianBlur(gray, img_blur, 5);
    vector<Vec3f> circles;
    HoughCircles(img_blur, circles, HOUGH_GRADIENT, 1, img.rows / 64, 200, 10, 5, 30);
    for (size_t i = 0; i < circles.size(); i++) {
        Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
        int radius = cvRound(circles[i][2]);
        circle(img, center, radius, Scalar(255, 255, 255), 2, 8, 0);
    }
    */

    // This function is going to include an arrow based off where the monkey is from the midpoint. 
    // If the monkey is in the middle, it will direct right or left,
    // if the monkey is on the right, it will detect left,
    // if the monkey is on the left, it will detect right. 


    //I am going to have this to detect lines (The road lines)
#if 0
    vector<Vec2f> lines;

    HoughLines(dst, lines, 1, CV_PI / 150, 100, 0, 0);

    for (size_t i = 0; i < lines.size(); i++)
    {
        float rho = lines[i][0], theta = lines[i][1];
        Point pt1, pt2;
        double a = cos(theta), b = sin(theta);
        double x0 = a * rho, y0 = b * rho;
        pt1.x = cvRound(x0 + 1000 * (-b));
        pt1.y = cvRound(y0 + 1000 * (a));
        pt2.x = cvRound(x0 - 1000 * (-b));
        pt2.y = cvRound(y0 - 1000 * (a));
        line(cdst, pt1, pt2, Scalar(0, 0, 255), 3, CV_AA);
     //   line(src, pt1, pt2, const Scalar(0, 255, 0), 2, lineType = 8, shift = 0);
    }
#else
    vector<Vec4i> lines;
    HoughLinesP(dst, lines, 1, CV_PI / 180, 50, 50, 10);
    for (size_t i = 0; i < lines.size(); i++)
    {
        Vec4i l = lines[i];
        line(cdst, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(0, 0, 255), 3, CV_AA);
     //   line(cdst, pt1, pt2, const Scalar(0, 255, 0), 2, lineType = 8, shift = 0);
    }
#endif
    imshow("source", src);
    imshow("detected lines", cdst);

    waitKey();

    return 0;
}

void help() {
    cout << "\nThis program demonstrates line finding with the Hough transform.\n"
        "Usage:\n"
        "./houghlines <image_name>, Default is pic1.jpg\n" << endl;
}


