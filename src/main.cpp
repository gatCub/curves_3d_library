#include <cmath>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <numeric>
#include <execution>
#include <memory>
#include "header\curves_lib.h"

int main(int argc, char** argv) {
    const double t { (2 * std::acos(0.0)) / 4};
    const int curvesCount {10};

    initialCurveFactories();
    auto curvesVector {createRandomArrayCurve(curvesCount)};
    
    std::cout << "Points and derivatives at t = PI/4: \n" << std::endl;
    std::cout.precision(3); 

    for (const auto& curve: curvesVector) {
        Point3D point {curve -> getPoint(t)};
        Vector3D derivat {curve -> getDerivat(t)};

        std::ostringstream stream_temp; 
        stream_temp  << "Point: (" << std::fixed << std::setprecision(3) << point._x << ", " << point._y << ", " << point._z << ")\t"
                << "Derivative: (" << std::fixed << std::setprecision(3) << derivat._x << ", " << derivat._y << ", " << derivat._z << ")";
        std::cout << stream_temp.str() << std::endl;
    }

    std::vector<Circle*> circleVector;
    for (const auto& curve: curvesVector) {
        if (dynamic_cast<Circle*>(curve.get())) {
            circleVector.push_back(static_cast<Circle*>(curve.get()));
        }
    }
    std::sort(circleVector.begin(), circleVector.end(), [](Circle* a, Circle* b) {return a -> getRadius() < b -> getRadius();});

    std::cout << "\nSorted circle: \t";
    for (const auto& circle: circleVector) {
        std::cout << circle -> getRadius() << "  ";
    }
    std::cout << std::endl;
    
    double sumRadius {  std::transform_reduce(std::execution::par, 
                        circleVector.begin(), circleVector.end(), 
                        0.0, std::plus<>(),
                        [] (const Circle* item) { return item -> getRadius(); })};

    
   std::cout << "\nTotal sum of radius: \t" << sumRadius << std::endl;

    std::cin.get();
    return 0;
}