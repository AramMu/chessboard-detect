#include <iostream>
#include <vector>
#include <opencv2/opencv.hpp>
#include <string>
#include <sstream>
#include "EdgeFinding/edge.h"


int main() {
    int fileCount = 5;
    cv::Size patternSize(7,7);
    cv::namedWindow("AAA", CV_WINDOW_NORMAL);
    cv::namedWindow("BBB", CV_WINDOW_NORMAL);
    cv::Mat input = cv::imread("Images/1.jpg");
    cv::Mat output;
    process(input, patternSize, output);
    cv::imwrite("Images/out.png", output);
    /*
    for (int fileNum = 1; fileNum <= fileCount; ++fileNum) {
        std::stringstream ssInput;
        ssInput << "Images/" << fileNum << ".jpg";
        std::string str;
        ssInput >> str;
        cv::Mat input = cv::imread(str);
        cv::Mat output = input.clone();
        std::vector <cv::Point2f> corners;

        std::vector <std::vector <cv::Point2f> > allCorners;
        while (true) {
            bool isFound = cv::findChessboardCorners(input, patternSize, corners);
            cv::drawChessboardCorners(input, patternSize, corners, isFound);
            if (!isFound) {
                break;
            }
            allCorners.push_back(corners);
        }
        std::vector <std::vector <cv::Size> > cellSizes;
        std::vector <cv::Size> boardSizes;
        double maxLength;
        getAllSizes(allCorners, patternSize, cellSizes, boardSizes, maxLength);
        std::vector <Edge> boardEdges;
        Edge maxEdge;
        getAllEdges(allCorners, patternSize, boardEdges, maxEdge);
        std::cout << "Max length is " << maxLength << std::endl;
        std::cout << "Board sizes" << std::endl;
        for (int i = 0; i < boardSizes.size(); ++i) {
            cv::line(output, boardEdges[i].u, boardEdges[i].v, RED, 10);
            putLengthText(output, boardEdges[i], 2, RED, 2);
            std::cout << boardSizes[i].width << " " << boardSizes[i].height << std::endl;
        }
        if (allCorners.size() == 2) {
            putLengthText(output, maxEdge, 2, RED, 2);
            cv::line(output, maxEdge.u, maxEdge.v, RED, 10);
        }




        cv::imshow("AAA", input);
        cv::imshow("BBB", output);

        cv::waitKey(0);

        std::cout << "Cell sizes" << std::endl;
        for (int i = 0; i < cellSizes.size(); ++i) {
            std::cout << "The " << i << "-th board cell sizes" << std::endl;
            for (int j = 0; j < cellSizes[i].size(); ++j) {
                std::cout << cellSizes[i][j].width << " " << cellSizes[i][j].height << std::endl;
            }
        }


        std::stringstream ssOutput;
        ssOutput << "Images/" << fileNum << "out.jpg";
        ssOutput >> str;
        cv::imwrite(str, output);
        cv::waitKey(0);
    }

    */
    cv::destroyAllWindows();
    return 0;
}

