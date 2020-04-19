/*
 *
 *	Author:			Drew Grobmeier
 *	Purpose:		To outline boxes and show next arrow
 *	Date:			4/18/2020
 *	Version:		V1
 *	Walkthrough:	4/20/2020
 *
 */

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
using namespace std;
using namespace cv;

int main(int argc, char** argv)
{
	//Essential for assuring we aqquire a valid imane name argument at command line
	//As shown in class, we will be manually entering the image for this walkthrough
	//For practicality we want this as a loop and receiving files from blender. 

	if (argc != 2)
	{
		cout << " Usage: display_image ImageToLoadAndDisplay" << endl;
		return -1;
	}

	//Storing the data of the loaded image
	Mat image;

	//Reading the file using imread
	image = imread(argv[1], CV_LOAD_IMAGE_COLOR);

	if (!image.data)                              
	{
		cout << "Could not open or find the image" << endl;
		return -1;
	}

	namedWindow("Display window", WINDOW_AUTOSIZE);
	imshow("Display window", image);                   

	waitKey(0);                                      
	return 0;
}


