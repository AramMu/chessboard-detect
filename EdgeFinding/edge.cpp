#include "edge.h"
#include <vector>
#include <opencv2/opencv.hpp>
#include <sstream>
#include <iomanip>

class CompareX {
public:
    bool operator () (const cv::Point2f& p1, const cv::Point2f& p2) const {
        return p1.x < p2.x;
    }
};
class CompareY {
public:
    bool operator () (const cv::Point2f& p1, const cv::Point2f& p2) const {
        return p1.y < p2.y;
    }
};

int sqr (int x) {
    return x*x;
}

double distance (const cv::Point& p1, const cv::Point& p2) {
    return std::sqrt (sqr(p1.x-p2.x) + sqr(p1.y-p2.y));
}

void getAllSizes (std::vector <std::vector <cv::Point2f> > corners, const cv::Size& patternSize, std::vector< std::vector<cv::Size> >& cellSizes, std::vector <cv::Size>& boardSizes, double& maxLength) {
    boardSizes = std::vector <cv::Size> (corners.size());
    cellSizes = std::vector <std::vector <cv::Size> > (corners.size(), std::vector<cv::Size> ( (patternSize.height-1) * (patternSize.width-1)));
    for (int k = 0; k < corners.size(); ++k) {
        std::sort (corners[k].begin(), corners[k].end(), CompareY());
        for (int i = 0; i < patternSize.height; ++i) {
            std::sort (corners[k].begin() + i*patternSize.width, corners[k].begin() + (i+1)*patternSize.width, CompareX());
        }
        int ind=0;
        for (int i = 0; i < patternSize.height-1; ++i) {
            for (int j = 0; j < patternSize.width-1; ++j) {
                int cornInd = i*patternSize.width + j;
                cellSizes[k][ind] = cv::Size (corners[k][cornInd+patternSize.width+1] - corners[k][cornInd]);
                ++ind;
            }
        }
        boardSizes[k] = cv::Size (corners[k].back() - corners[k][0]);
    }
    if (corners.size() == 2) {
        if (corners[0][0].x > corners[1][0].x) {
            corners[0].swap(corners[1]);
        }
        cv::Point left (corners[0][ (patternSize.height/2) * patternSize.width]);
        cv::Point right (corners[1][ (patternSize.height/2) * patternSize.width + patternSize.width-1 ]);
        maxLength = distance (left, right);
    }
}


void getAllEdges (std::vector <std::vector <cv::Point2f> > corners, const cv::Size& patternSize, std::vector <Edge>& boardEdges, Edge& maxEdge) {
    boardEdges = std::vector <Edge> (corners.size());
    for (int k = 0; k < corners.size(); ++k) {
        std::sort (corners[k].begin(), corners[k].end(), CompareY());
        for (int i = 0; i < patternSize.height; ++i) {
            std::sort (corners[k].begin() + i*patternSize.width, corners[k].begin() + (i+1)*patternSize.width, CompareX());
        }
        boardEdges[k] = Edge (corners[k][0], corners[k][patternSize.width-1]);
    }
    if (corners.size() == 2) {
        if (corners[0][0].x > corners[1][0].x) {
            corners[0].swap(corners[1]);
        }
        cv::Point left (corners[0][ (patternSize.height/2) * patternSize.width]);
        cv::Point right (corners[1][ (patternSize.height/2) * patternSize.width + patternSize.width-1 ]);
        maxEdge = Edge(left, right);
    }
}

void putLengthText (cv::Mat& output, Edge e, double scale, const cv::Scalar& color, int thick, int lineType) {
    int font = cv::FONT_HERSHEY_SIMPLEX;
    double value = distance (e.u, e.v);
    std::stringstream ss;
    ss << std::setprecision(5) << value << "px";
    std::string text;
    ss >> text;
    cv::Point pos( (e.u+e.v) / 2);
    pos.y -= scale*40;
    cv::putText(output, text, pos, font, scale, color, thick, lineType);
}

void process (const cv::Mat& in, const cv::Size& patternSize, cv::Mat& output) {
    cv::Scalar RED(0,0,255);
    cv::Mat input = in.clone();
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
    double textScale(2);
    int textThick(4);
    int lineThick(10);

    output = in.clone();
    for (int i = 0; i < boardSizes.size(); ++i) {
        cv::line(output, boardEdges[i].u, boardEdges[i].v, RED, lineThick);
        putLengthText(output, boardEdges[i], textScale, RED, textThick);
    }
    if (allCorners.size() == 2) {
        putLengthText(output, maxEdge, textScale, RED, textThick);
        cv::line(output, maxEdge.u, maxEdge.v, RED, lineThick);
    }
}


void drawEdges (cv::Mat& output, const std::vector<Edge>& edges, const cv::Scalar& color, int thick, int lineType, int shift) {
    for (int i = 0; i < edges.size(); ++i) {
        cv::line(output, edges[i].u, edges[i].v, color, thick);
    }
}

