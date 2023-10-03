#ifndef EDGE_H
#define EDGE_H
#include <opencv2/imgproc.hpp>
#include <vector>

class Edge {
public:
    Edge() {}
    Edge(const cv::Point& u, const cv::Point& v) : u(u), v(v) {}
    cv::Point u;
    cv::Point v;
};


void getAllSizes (std::vector <std::vector <cv::Point2f> > corners, const cv::Size& patternSize, std::vector< std::vector <cv::Size> >& cellSizes, std::vector <cv::Size>& boardSizes, double& maxLength);
void getAllEdges (std::vector <std::vector <cv::Point2f> > corners, const cv::Size& patternSize, std::vector <Edge>& boardEdges, Edge& maxEdge);
void drawEdges (cv::Mat& output, const std::vector<Edge>& edges, const cv::Scalar& color, int thick=1, int lineType=cv::LINE_8, int shift=0);
void putLengthText (cv::Mat& output, Edge e, double scale, const cv::Scalar &color, int thick=1, int lineType=cv::LINE_8);
void process (const cv::Mat& in, const cv::Size &patternSize, cv::Mat& output);

#endif // EDGE_H

