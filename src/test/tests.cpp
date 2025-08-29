#include "../header/curves_lib.h"

#include <cassert>
#include <iostream>
#include <cmath>
#include <algorithm>

using namespace std;

bool ApproxEqual(double a, double b, double ep = 1e-10) {
    return std::abs(a - b) < ep;
}

void testValidCurveCreation() {
    Circle circle(5.0);
    assert(ApproxEqual(circle.getRadius(), 5.0));

    Elipse elipse(3.0, 4.0);
    assert(ApproxEqual(elipse.getRadius(), 3.0));
    assert(ApproxEqual(elipse.getSecondaryRadius(), 4.0));
    
    Helix helix(2.0, 1.0);
    assert(ApproxEqual(helix.getRadius(), 2.0));
    assert(ApproxEqual(helix.getStep(), 1.0));
}

void testInvalidCurveCreation() {
    
    try {
        Circle circle(-1.0);
        assert(false);
    } 
    catch (const std::invalid_argument& e) {
        assert(std::string(e.what()).find("positive") != std::string::npos);
    }
    
    try {
        Elipse elipse(-1.0, 2.0);
        assert(false);
    } 
    catch (const std::invalid_argument& e) {
        assert(std::string(e.what()).find("positive") != std::string::npos);
    }

    try {
        Helix helix(-1.0, 1.0);
        assert(false);
    } 
    catch (const std::invalid_argument& e) {
        assert(std::string(e.what()).find("positive") != std::string::npos);
    }
   
}

void testPointCalculation() {

    const double t = (2 * std::acos(0.0)) / 4;
    
    Circle circle(2.0);
    Point3D circlePoint = circle.getPoint(t);
    assert(ApproxEqual(circlePoint._x, 2.0 * std::cos(t)));
    assert(ApproxEqual(circlePoint._y, 2.0 * std::sin(t)));
    assert(ApproxEqual(circlePoint._z, 0.0));
    
    Elipse elipse(3.0, 4.0);
    Point3D elipsePoint = elipse.getPoint(t);
    assert(ApproxEqual(elipsePoint._x, 3.0 * std::cos(t)));
    assert(ApproxEqual(elipsePoint._y, 4.0 * std::sin(t)));
    assert(ApproxEqual(elipsePoint._z, 0.0));
    
    Helix helix(2.0, 1.0);
    Point3D helixPoint = helix.getPoint(t);
    assert(ApproxEqual(helixPoint._x, 2.0 * std::cos(t)));
    assert(ApproxEqual(helixPoint._y, 2.0 * std::sin(t)));
    assert(ApproxEqual(helixPoint._z, 1.0 * t / (4 * std::acos(0.0))));
    
}

void testDerivativeCalculation() {

    const double t = (2 * std::acos(0.0)) / 4;
    
    Circle circle(2.0);
    Vector3D circlePoint = circle.getDerivat(t);
    assert(ApproxEqual(circlePoint._x, -2.0 * std::sin(t)));
    assert(ApproxEqual(circlePoint._y, 2.0 * std::cos(t)));
    assert(ApproxEqual(circlePoint._z, 0.0));
    
    Elipse elipse(3.0, 4.0);
    Vector3D elipsePoint = elipse.getDerivat(t);
    assert(ApproxEqual(elipsePoint._x, -3.0 * std::sin(t)));
    assert(ApproxEqual(elipsePoint._y, 4.0 * std::cos(t)));
    assert(ApproxEqual(elipsePoint._z, 0.0));
    
    Helix helix(2.0, 1.0);
    Vector3D helixPoint = helix.getDerivat(t);
    assert(ApproxEqual(helixPoint._x, -2.0 * std::sin(t)));
    assert(ApproxEqual(helixPoint._y, 2.0 * std::cos(t)));
    assert(ApproxEqual(helixPoint._z, 1.0 / (4 * std::acos(0.0))));
    
}

void testCurveFactory() {
    auto length {1000};
    initialCurveFactories();
    
    auto curves = createRandomArrayCurve(length);
    assert(curves.size() == length);
    
    for (const auto& curve : curves) {
        assert(curve != nullptr);
    }

}


int main() {
    
    testValidCurveCreation(); 
    cout << "[TEST]\tThe \"testValidCurveCreation\" test was passed successfully\n";

    testInvalidCurveCreation(); 
    cout << "[TEST]\tThe \"testInvalidCurveCreation\" test was passed successfully\n";

    testPointCalculation(); 
    cout << "[TEST]\tThe \"testPointCalculation\" test was passed successfully\n";

    testDerivativeCalculation(); 
    cout << "[TEST]\tThe \"testDerivativeCalculation\" test was passed successfully\n";

    testCurveFactory(); 
    cout << "[TEST]\tThe \"testCurveFactory\" test was passed successfully\n";

    cout << "--------------------[TESTS COMPLITED]--------------------" << std::endl;
}