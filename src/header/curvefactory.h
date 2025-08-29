#ifndef CURVEFACTORY_H
#define CURVEFACTORY_H

#pragma once

#include "curves_lib.h"

#include <memory>
#include <string>
#include <vector>
#include <map>

struct ICurveFactory 
{
    virtual ~ICurveFactory() = default;
    virtual std::unique_ptr<Curve> createCurve() const = 0;
    virtual std::string getType() const = 0;
};

struct CurveFactoryRegistry 
{
    static CurveFactoryRegistry& getInstance();

    void registerFactory(const std::string&, std::unique_ptr<ICurveFactory>);
    std::unique_ptr<Curve> createCurve(const std::string&) const;
    std::vector<std::string> getAvailableTypes() const;

private:
    CurveFactoryRegistry() = default;
    std::map<std::string, std::unique_ptr<ICurveFactory>> _factories_map;
};


/*
    Различные реализации кривых.
*/
namespace CurveFactory {

    struct CircleFactory final: ICurveFactory {
        std::unique_ptr<Curve> createCurve() const override;
        std::string getType() const override { return "Circle"; }
    };

    struct ElipseFactory final: ICurveFactory {
        std::unique_ptr<Curve> createCurve() const override;
        std::string getType() const override { return "Elipse"; }
    };

    struct HelixFactory final: ICurveFactory {
        std::unique_ptr<Curve> createCurve() const override;
        std::string getType() const override { return "Helix"; }
    };

};


#endif