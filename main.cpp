/*
**********************************************
Tool to make it easier to find the HSV values needed to isolate a chosen colour.
The raw camera feed is shown along with the inRange result. Silders allow the HSV limits to be changed during runtime.
**********************************************
*/

// Include files for required libraries
#include <stdio.h>
#include <iostream>
#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"

using namespace cv;

int main( )
{
    namedWindow("HSV Tester");   // Create a GUI window called photo

    int lowH = 0, highH = 179, lowS = 0, highS = 255, lowV = 0, highV = 255;    // Initialise some variables for HSV limits

    createTrackbar("Low Hue", "HSV Tester", &lowH, 179, NULL);      // Create trackbar controls for each HSV limit
    createTrackbar("High Hue", "HSV Tester", &highH, 179, NULL);

    createTrackbar("Low Sat", "HSV Tester", &lowS, 255, NULL);
    createTrackbar("High Sat", "HSV Tester", &highS, 255, NULL);

    createTrackbar("Low Value", "HSV Tester", &lowV, 255, NULL);
    createTrackbar("High Value", "HSV Tester", &highV, 255, NULL);
    Mat frame = imread("BlueApple.bmp"); // Open an image file and store in a new matrix variable

    while(1)    // Main loop to perform image processing
    {
        lowH = getTrackbarPos("Low Hue", "HSV Tester");        // Update the variables with the trackbar setting
        highH = getTrackbarPos("High Hue", "HSV Tester");
        lowS = getTrackbarPos("Low Sat", "HSV Tester");
        highS = getTrackbarPos("High Sat", "HSV Tester");
        lowV = getTrackbarPos("Low Value", "HSV Tester");
        highV = getTrackbarPos("High Value", "HSV Tester");

        Mat frameHSV;       // Convert the frame to HSV and apply the limits
        cvtColor(frame, frameHSV, COLOR_BGR2HSV);
        inRange(frameHSV, Scalar(lowH, lowS, lowV), Scalar(highH, highS, highV), frameHSV);

        Mat comparison;     // Join the two into a single image
        cvtColor(frameHSV, frameHSV, COLOR_GRAY2BGR);   // In range returns the equivalent of a grayscale image so we need to convert this before concatenation
        hconcat(frame, frameHSV, comparison);

        imshow("HSV Tester", comparison); //Display the image in the window

        int key = cv::waitKey(1);   // Wait 1ms for a keypress (required to update windows

        key = (key==255) ? -1 : key;    // Check if the esc key has been pressed
        if (key == 27)
            break;
	}

	destroyAllWindows();

	return 0;
}
/*
int SymbolRecognition(Mat frame){

    Mat framecopy = frame.clone(); // create a copy of the input frame
    Mat image;
    cvtColor(frame, image, COLOR_BGR2HSV);  //convert image to hsv

    // Define the color range to select pink objects in the image
    Scalar lower_range = Scalar(145,30,30);
    Scalar upper_range = Scalar(165,245,245);

    // Create a binary mask with the selected pink color range
    Mat pink_mask;
    inRange(image, lower_range, upper_range, pink_mask);

    // Find the contour with the biggest area in the pink mask
    vector<vector<Point>>contours;
    vector<Vec4i> hierarchy;
    int savedContour = -1;
    double maxArea = 0.0;
    findContours(pink_mask, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE, Point());

    for (int i = 0; i< contours.size(); i++)
    {
        double area = contourArea(contours[i]);
        if (area > maxArea)
        {
            maxArea = area;
            savedContour = i;
        }
    }

    // Create a mask from the largest pink contour and draw it onto a copy of the input frame
    Mat mask = Mat::zeros(frame.size(), CV_8UC1);
    drawContours(mask, contours, savedContour, Scalar(255), FILLED, 8);
    Mat masked_image;
    frame.copyTo(masked_image, mask);

    // Find the contours of the pink mask to extract the outermost contour
vector<vector<Point>> contours2;
vector<Vec4i> hierarchy2;
findContours(mask, contours2, hierarchy2, RETR_TREE, CHAIN_APPROX_SIMPLE);

// Find the four corners of the outermost contour using approxPolyDP
vector<Point> contour_poly;
approxPolyDP(contours2[0], contour_poly, 3, true);
vector<Point2i> corners;
for (int i = 0; i < contour_poly.size(); i++) {
    corners.push_back(Point2i(contour_poly[i].x, contour_poly[i].y));
}

// Sort the corners in clockwise order, starting from the top left corner
sort(corners.begin(), corners.end(), [](const Point2i& a, const Point2i& b) {
    return a.y < b.y;
});
vector<Point2i> corners_top = {corners[0], corners[1]};
vector<Point2i> corners_bottom = {corners[2], corners[3]};
sort(corners_top.begin(), corners_top.end(), [](const Point2i& a, const Point2i& b) {
    return a.x < b.x;
});
sort(corners_bottom.begin(), corners_bottom.end(), [](const Point2i& a, const Point2i& b) {
    return a.x > b.x;
});
corners = {corners_top[0], corners_top[1], corners_bottom[0], corners_bottom[1]};

// Define the destination points for the transformation
int xsize = 350;
int ysize = 350;
Point2f dst[4] = {Point2i(0, 0), Point2i(xsize, 0), Point2i(xsize, ysize), Point2i(0, ysize)};

// Perform the perspective transformation
framecopy = transformPerspective(corners, framecopy, xsize, ysize);

    // Compare the symbol image with a set of predefined symbols to recognize the symbol
    // ...

    imshow("Output", framecopy);
//    imshow("Symbol", symbol_image);

    return 0;
}
*/


