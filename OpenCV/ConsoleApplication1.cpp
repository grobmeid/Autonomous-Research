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

/****************************INCLUDES****************************************/
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgcodecs.hpp> //Responsible for imread in opencv
#include <opencv2/imgproc.hpp>
#include <iostream>
/****************************INCLUDES****************************************/
/****************************NAMESPACES**************************************/
using namespace std;
using namespace cv;
/****************************NAMESPACES**************************************/


int main(int argc, char** argv)
{
	//Essential for assuring we aqquire a valid imane name argument at command line
	//As shown in class, we will be manually entering the image for this walkthrough
	//For practicality we want this as a loop and receiving files from blender. 

	
	//** This is just one image, it will have to be multiple when we receive images 
	//** from blender. 

	//** I will have to change the file path for this current image, but for now this will
	//** be ok as a testing point
	String imageName("boxcuttest.png");
	if (argc > 1)
	{
		imageName = argv[1];
	}

	//Storing the data of the loaded image
	src = imread(samples::findFile(imageName), IMREAD_COLOR);

	// two possible tests, one to just call a function, the other
	// to print directly. 
	if (src.empty())
	{
		help();
		return -1;
	}
	
	if (!src.data)                              
	{
		cout << "Could not open or find the image" << endl;
		return -1;
	}

	namedWindow("Display window", WINDOW_AUTOSIZE);
	imshow("Display window", image);                   

	waitKey(0);                                      
	return 0;
}


