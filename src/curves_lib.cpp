#include "header\curves_lib.h"
#include "header\curvefactory.h"

#include <random>
#include <cmath>

Point3D Circle::getPoint (double t) const {
    return Point3D {_radius * cos(t), _radius * sin(t), 0}; 
}

Vector3D Circle::getDerivat(double t) const {
    return Vector3D {-_radius * sin(t), _radius * cos(t), 0};
}

Point3D Elipse::getPoint (double t) const {
    return Point3D {_radiusX * cos(t), _radiusY * sin(t), 0}; 
}

Vector3D Elipse::getDerivat(double t) const {
    return Vector3D {-_radiusX * sin(t), _radiusY * cos(t), 0};
}

Point3D Helix::getPoint (double t) const {
    return Point3D {_radius * cos(t), _radius * sin(t), _step * t / (2 * (2 * std::acos(0.0))) }; 
}

Vector3D Helix::getDerivat(double t) const {
    return Vector3D {-_radius * sin(t), _radius * cos(t), _step / (2 * (2 * std::acos(0.0))) };
}



//Фабрика
void initialCurveFactories() {
    auto& registry { CurveFactoryRegistry::getInstance() };

    registry.registerFactory("Circle", std::make_unique<CurveFactory::CircleFactory>());
    registry.registerFactory("Elipse", std::make_unique<CurveFactory::ElipseFactory>());
    registry.registerFactory("Helix", std::make_unique<CurveFactory::HelixFactory>());
}

std::vector<std::unique_ptr<Curve>> createRandomArrayCurve(size_t count) {
    auto& registry { CurveFactoryRegistry::getInstance() };
    auto availableTypes {registry.getAvailableTypes()};

    if (availableTypes.empty()) {
        throw std::runtime_error("No factories registered");
    }

    std::mt19937 rgen { std::random_device{}() };
    std::uniform_int_distribution typeDist{ 0, static_cast<int>(availableTypes.size() -1) };

    std::vector<std::unique_ptr<Curve>> curveArray;
    curveArray.reserve(count);

    for (auto i {0}; i < count; ++i) {
        auto typeIndex {typeDist(rgen)};
        curveArray.push_back(registry.createCurve(availableTypes[typeIndex]));
    }

    return curveArray;
}