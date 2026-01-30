#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <limits>
#include <ctime>
#include <cstdlib>

// 定义Point结构体
struct Point {
    int x, y;
    Point(int x = 0, int y = 0) : x(x), y(y) {}
};

// 计算两点之间的欧几里得距离
double calcDistance(const Point& p1, const Point& p2) {
    return sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2));
}

// 暴力解法：计算每一对点的距离并返回最小值
double bruteForce(std::vector<Point>& points) {
    double minDist = std::numeric_limits<double>::max();
    for (size_t i = 0; i < points.size(); ++i) {
        for (size_t j = i + 1; j < points.size(); ++j) {
            minDist = std::min(minDist, calcDistance(points[i], points[j]));
        }
    }
    return minDist;
}

// 比较函数，用于排序按 x 坐标排序
bool compareX(const Point& p1, const Point& p2) {
    return p1.x < p2.x;
}

// 比较函数，用于排序按 y 坐标排序
bool compareY(const Point& p1, const Point& p2) {
    return p1.y < p2.y;
}


/*
* 传入的PointX中点的的横坐标是排序过的
*/
double closestPairRecursive(std::vector<Point>& pointsX, std::vector<Point>& pointsY) 
{
    size_t n = pointsX.size();
    if (n <= 3) 
    {
        double minDist = std::numeric_limits<double>::max();
        for (size_t i = 0; i < n; ++i) {
            for (size_t j = i + 1; j < n; ++j) {
                minDist = std::min(minDist, calcDistance(pointsX[i], pointsX[j]));
            }
        }
        return minDist;
    }

    size_t mid = n / 2;
    Point midPoint = pointsX[mid];

    // 分别递归求解左半部分和右半部分
    std::vector<Point> leftX(pointsX.begin(), pointsX.begin() + mid); 
    std::vector<Point> rightX(pointsX.begin() + mid, pointsX.end());

    std::vector<Point> leftY, rightY;
    for (const auto& p : pointsY) {
        if (p.x <= midPoint.x) leftY.push_back(p);
        else rightY.push_back(p);
    }

    double leftDist = closestPairRecursive(leftX, leftY);
    double rightDist = closestPairRecursive(rightX, rightY);

    double minDist = std::min(leftDist, rightDist);

    // 合并：检查跨越中间线的点对
    std::vector<Point> strip;
    for (const auto& p : pointsY) {
        if (std::abs(p.x - midPoint.x) < minDist) {
            strip.push_back(p);
        }
    }

    // 对于每一个位于strip中的点，我们只需检查与其右边最多6个点的距离
    for (size_t i = 0; i < strip.size(); ++i) {
        for (size_t j = i + 1; j < strip.size() && strip[j].y - strip[i].y < minDist; ++j) {
            minDist = std::min(minDist, calcDistance(strip[i], strip[j]));
        }
    }

    return minDist;
}

// 外部接口函数
double closestPair(std::vector<Point>& points) {
    // 按x坐标排序
    std::vector<Point> pointsX = points;
    std::sort(pointsX.begin(), pointsX.end(), compareX);

    // 按y坐标排序
    std::vector<Point> pointsY = points;
    std::sort(pointsY.begin(), pointsY.end(), compareY);

    return closestPairRecursive(pointsX, pointsY);
}

// 生成随机点
std::vector<Point> generateRandomPoints(int numPoints, int maxCoord) {
    std::vector<Point> points;
    srand(time(0));
    for (int i = 0; i < numPoints; ++i) {
        points.push_back(Point(rand() % maxCoord, rand() % maxCoord));
    }
    return points;
}

int main() {
    int numPoints = 10000;  // 点的数量
    int maxCoord = 10000;   // 坐标范围

    // 生成随机点
    std::vector<Point> points = generateRandomPoints(numPoints, maxCoord);

    // 暴力求解
    clock_t start = clock();
    double minDistBruteForce = bruteForce(points);
    clock_t end = clock();
    double bruteForceTime = double(end - start) / CLOCKS_PER_SEC;
    std::cout << "Brute Force Minimum Distance: " << minDistBruteForce << std::endl;
    std::cout << "Brute Force Time: " << bruteForceTime << " seconds" << std::endl;

    // 分治法求解
    start = clock();
    double minDistDivideConquer = closestPair(points);
    end = clock();
    double divideConquerTime = double(end - start) / CLOCKS_PER_SEC;
    std::cout << "Divide and Conquer Minimum Distance: " << minDistDivideConquer << std::endl;
    std::cout << "Divide and Conquer Time: " << divideConquerTime << " seconds" << std::endl;

    return 0;
}
