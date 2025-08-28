#include "header\curves_lib.h"
#include "header\curvefactory.h"

#include <stdexcept>
#include <random>

/* CurveFactoryRegistry begin*/ 

CurveFactoryRegistry& CurveFactoryRegistry::getInstance() {
    static CurveFactoryRegistry instance;
    return instance;
}

void CurveFactoryRegistry::registerFactory(const std::string& type, std::unique_ptr<ICurveFactory> factory) {
    _factories_map[type] = std::move(factory);
}

std::unique_ptr<Curve> CurveFactoryRegistry::createCurve(const std::string& type) const {
    auto it { _factories_map.find(type) };
    if (it == _factories_map.end()) {
        throw std::runtime_error("Unknown type curve: " + type);
    }

    return it -> second -> createCurve();
}

std::vector<std::string> CurveFactoryRegistry::getAvailableTypes() const {
    std::vector<std::string> types;
    for (const auto& type: _factories_map) {
        types.push_back(type.first);
    }

    return types;
}

/* CurveFactoryRegistry end*/ 



std::unique_ptr<Curve> CurveFactory::CircleFactory::createCurve() const {
    static std::uniform_real_distribution dist{.1, 10.0};
    static std::mt19937 rgen(std::random_device{}());

    return std::make_unique<Circle>(dist(rgen));
}

std::unique_ptr<Curve> CurveFactory::ElipseFactory::createCurve() const {
    static std::uniform_real_distribution dist{.1, 10.0};
    static std::mt19937 rgen(std::random_device{}());

    return std::make_unique<Elipse>(dist(rgen), dist(rgen));
}

std::unique_ptr<Curve> CurveFactory::HelixFactory::createCurve() const {
    static std::uniform_real_distribution radiusDist{.1, 10.0};
    static std::uniform_real_distribution stepDist{.5, 5.0};
    static std::mt19937 rgen(std::random_device{}());

    return std::make_unique<Helix>(radiusDist(rgen), stepDist(rgen));
}



