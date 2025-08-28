#ifndef CURVES_LIB_H
#define CURVES_LIB_H

#pragma once

#include <random>
#include <memory>
#include <vector>

/*Вспомогательаня структура для трехмерной точки.*/
struct  Point3D
{
    double _x{}, _y{}, _z{};
    Point3D(double x = 0, double y = 0, double z = 0): _x(x), _y(y), _z(z) {}
};

/*Вспомогательаня структура для трехмерного вектора.*/
struct  Vector3D
{
    double _x{}, _y{}, _z{};
    Vector3D(double x = 0, double y = 0, double z = 0): _x(x), _y(y), _z(z) {}
};


struct Curve
{
    virtual ~Curve() = default;
    virtual Point3D getPoint(double t) const = 0;
    virtual Vector3D getDerivat(double t) const = 0;
    virtual double getRadius() const = 0;

};

struct Circle: Curve 
{
    Circle(double r):  _radius(r) {}

    Point3D getPoint(double t) const override;
    Vector3D getDerivat(double t) const override;
    double getRadius() const override { return _radius; }

private:
    double _radius;
};


namespace CurveFactory {
    std::unique_ptr<Curve> createRandomCurve (std::mt19937& genr);
    std::vector<std::unique_ptr<Curve>> createRandomArrayCurve(std::mt19937& genr, size_t count);
}

#endif