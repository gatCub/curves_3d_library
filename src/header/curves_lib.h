#ifndef CURVES_LIB_H
#define CURVES_LIB_H

#pragma once

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
    virtual Point3D getPoint(double) const = 0;
    virtual Vector3D getDerivat(double) const = 0;
};

struct IHasRadius 
{
    virtual ~IHasRadius() = default;
    virtual double getRadius() const = 0;
};

struct IHasSecondaryRadius
{
    virtual ~IHasSecondaryRadius() = default;
    virtual double getSecondaryRadius() const = 0;
};

struct IHasStep
{
    virtual ~IHasStep() = default;
    virtual double getStep() const = 0;
};


struct Circle final: Curve, IHasRadius 
{
    Circle(double r):  _radius(r) {}

    Point3D getPoint(double) const override;
    Vector3D getDerivat(double) const override;
    double getRadius() const override { return _radius; }

private:
    double _radius;
};

struct Elipse final: Curve, IHasRadius, IHasSecondaryRadius 
{
    Elipse(double rX, double rY): _radiusX(rX), _radiusY(rY) {}

    Point3D getPoint(double) const override;
    Vector3D getDerivat(double) const override;
    double getRadius() const override { return _radiusX; }
    double getSecondaryRadius() const override { return _radiusY; }

private: 
    double _radiusX, _radiusY;
};

struct Helix final: Curve, IHasRadius, IHasStep 
{
    Helix(double r, double s): _radius(r), _step(s) {}
    Point3D getPoint(double) const override;
    Vector3D getDerivat(double) const override;
    double getRadius() const override { return _radius; }
    double getStep() const override { return _step; }

private:
    double _radius, _step;
};

//Интерфейс для рандомного создания кривых

void initialCurveFactories();
std::vector<std::unique_ptr<Curve>> createRandomArrayCurve(size_t);

#endif