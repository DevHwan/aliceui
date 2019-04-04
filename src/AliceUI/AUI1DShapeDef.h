#pragma once

#include <glm/gtx/rotate_vector.hpp>
#include <cassert>

struct AUIShapeLine
{
    glm::dvec3 pos[2];

    AUIShapeLine() {}

    //////////////////////////////////////////////////////////////////////////
    // Make
    static AUIShapeLine Make() { return AUIShapeLine(); }
    static AUIShapeLine MakePos(const glm::dvec3& p1, const glm::dvec3& p2) { AUIShapeLine l; l.SetPos1(p1); l.SetPos2(p2); return l; }
    static AUIShapeLine MakePos(double x1, double y1, double z1, double x2, double y2, double z2) { AUIShapeLine l; l.SetPos1(x1, y1, z1); l.SetPos2(x2, y2, z2); return l; }

    void SetPos1(const glm::dvec3& p) { pos[0] = p; }
    void SetPos1(double x, double y, double z) { pos[0] = glm::dvec3(x, y, z); }
    void SetPos2(const glm::dvec3& p) { pos[1] = p; }
    void SetPos2(double x, double y, double z) { pos[1] = glm::dvec3(x, y, z); }
};

struct AUIShapeCircle
{
    glm::dvec3 pos;
    glm::dvec3 norm;
    double radius;


    //////////////////////////////////////////////////////////////////////////
    // Base constructor
    AUIShapeCircle() : norm(0.0, 0.0, 1.0), radius(1.0) { }


    //////////////////////////////////////////////////////////////////////////
    // Make
    static AUIShapeCircle Make() { return AUIShapeCircle(); }
    static AUIShapeCircle MakePos(double x, double y, double z) { AUIShapeCircle c; c.SetPos(x, y, z); return c; }
    static AUIShapeCircle MakeNorm(double nx, double ny, double nz) { AUIShapeCircle c; c.SetNorm(nx, ny, nz); return c; }
    static AUIShapeCircle MakeRadius(double r) { AUIShapeCircle c; c.SetRadius(r); return c; }
    static AUIShapeCircle MakePosNormRadius(const glm::dvec3& pos, const glm::dvec3& norm, double radius) { AUIShapeCircle c; c.SetPos(pos); c.SetNorm(norm); c.SetRadius(radius); return c; }
    static AUIShapeCircle MakePosNormRadius(double x, double y, double z, double nx, double ny, double nz, double r) { AUIShapeCircle c; c.SetPos(x, y, z); c.SetNorm(nx, ny, nz); c.SetRadius(r); return c; }


    //////////////////////////////////////////////////////////////////////////
    // Setter
    void SetPos(const glm::dvec3& p) { pos = p; }
    void SetPos(double x, double y, double z) { pos = glm::dvec3(x, y, z); }
    void SetNorm(const glm::dvec3& n) { norm = glm::normalize(n); }
    void SetNorm(double nx, double ny, double nz) { norm = glm::normalize(glm::dvec3(nx, ny, nz)); }
    void SetRadius(double r) { radius = r; }
};

struct AUIShapeArc
{
    glm::dvec3 pos;
    glm::dvec3 norm;
    glm::dvec3 dir;
    double radius;
    double angle[2] = { 0.0, };


    //////////////////////////////////////////////////////////////////////////
    // Base constructor
    AUIShapeArc() : norm(0.0, 0.0, 1.0), radius(1.0), dir(1.0, 0.0, 0.0) { angle[0] = 0.; angle[1] = 360.; }


    //////////////////////////////////////////////////////////////////////////
    // Make
    static AUIShapeArc Make() { return AUIShapeArc(); }
    static AUIShapeArc MakePos(double x, double y, double z) { AUIShapeArc c; c.SetPos(x, y, z); return c; }
    static AUIShapeArc MakeNorm(double nx, double ny, double nz) { AUIShapeArc c; c.SetNorm(nx, ny, nz); return c; }
    static AUIShapeArc MakeRadius(double r) { AUIShapeArc c; c.SetRadius(r); return c; }
    static AUIShapeArc MakePosNormRadiusAngle(glm::dvec3 p, glm::dvec3 n, glm::dvec3 d, double r, double as, double a)
    {
        AUIShapeArc arc; arc.SetPos(p); arc.norm = glm::normalize(n); arc.dir = glm::normalize(d);  arc.SetRadius(r); arc.SetStartAngle(as); arc.SetAngle(a); arc.ValidateArc(); return arc;
    }


    //////////////////////////////////////////////////////////////////////////
    // Setter
    void SetPos(const glm::dvec3& p) { pos = p; }
    void SetPos(double x, double y, double z) { pos = glm::dvec3(x, y, z); }
    void SetNorm(const glm::dvec3& n)
    {
        norm = glm::normalize(n);
        ValidateArc();
        return;
    }
    void SetNorm(double nx, double ny, double nz) { SetNorm(glm::dvec3(nx, ny, nz)); }
    void SetDir(const glm::dvec3& d)
    {
        dir = glm::normalize(d);
        ValidateArc();
        return;
    }
    void SetDir(double dx, double dy, double dz) { SetDir(glm::dvec3(dx, dy, dz)); }

    void SetRadius(double r) { radius = r; }
    void SetStartAngle(double a) { angle[0] = a; }
    void SetAngle(double a) { angle[1] = a; }

    glm::dvec3 GetStartDir() const {
        return glm::normalize(glm::rotate(dir, glm::radians(angle[0]), norm));
    }
    glm::dvec3 GetEndDir() const {
        return glm::normalize(glm::rotate(dir, glm::radians(angle[1]), norm));
    }

    void ValidateArc()
    {
        if (glm::abs(glm::abs(dot(norm, dir)) - 1.0) < DBL_EPSILON)
            assert(false);

        auto v = glm::cross(dir, norm);
        dir = glm::normalize(glm::cross(norm, v));
    }

};

struct AUIShapeEllipse
{
    glm::dvec3 pos;
    glm::dvec3 norm;
    double radiusMajor;
    double radiusMinor;
    glm::dvec3 axisMajor;
    glm::dvec3 axisMinor;


    //////////////////////////////////////////////////////////////////////////
    // Base constructor
    AUIShapeEllipse() : norm(0.0, 0.0, 1.0), radiusMajor(1.0), radiusMinor(1.0), axisMajor(1.0, 0.0, 0.0), axisMinor(0.0, 1.0, 0.0) { }


    //////////////////////////////////////////////////////////////////////////
    // Make
    static AUIShapeEllipse Make() { return AUIShapeEllipse(); }
    static AUIShapeEllipse MakePos(double x, double y, double z) { AUIShapeEllipse c; c.SetPos(x, y, z); return c; }
    static AUIShapeEllipse MakeNorm(double nx, double ny, double nz) { AUIShapeEllipse c; c.SetNorm(nx, ny, nz); return c; }
    static AUIShapeEllipse MakeRadiusMajor(double r) { AUIShapeEllipse c; c.SetRadiusMajor(r); return c; }
    static AUIShapeEllipse MakeRadiusMinor(double r) { AUIShapeEllipse c; c.SetRadiusMinor(r); return c; }
    static AUIShapeEllipse MakePosNormRadius(const glm::dvec3& pos, const glm::dvec3& norm,
        double rMajor, double rMinor, const glm::dvec3& axisMajor, const glm::dvec3& axisMinor)
    {
        AUIShapeEllipse c;
        c.SetPos(pos);
        c.SetNorm(norm);
        c.SetRadiusMajor(rMajor);
        c.SetRadiusMinor(rMinor);
        c.SetAxisMajor(axisMajor);
        c.SetAxisMinor(axisMinor);
        return c;
    }

    static AUIShapeEllipse MakePosNormRadius(double x, double y, double z,
        double nx, double ny, double nz,
        double rMajor, double rMinor,
        double aMajorx, double aMajory, double aMajorz,
        double aMinorx, double aMinory, double aMinorz)
    {
        AUIShapeEllipse c;
        c.SetPos(x, y, z);
        c.SetNorm(nx, ny, nz);
        c.SetRadiusMajor(rMajor);
        c.SetRadiusMinor(rMinor);
        c.SetAxisMajor(aMajorx, aMajory, aMajorz);
        c.SetAxisMinor(aMinorx, aMinory, aMinorz);
        return c;
    }

    //////////////////////////////////////////////////////////////////////////
    // Setter
    void SetPos(const glm::dvec3& p) { pos = p; }
    void SetPos(double x, double y, double z) { pos = glm::dvec3(x, y, z); }
    void SetNorm(const glm::dvec3& n) { norm = glm::normalize(n); }
    void SetNorm(double nx, double ny, double nz) { norm = glm::normalize(glm::dvec3(nx, ny, nz)); }
    void SetRadiusMajor(double r) { radiusMajor = r; }
    void SetRadiusMinor(double r) { radiusMinor = r; }
    void SetAxisMajor(const glm::dvec3& axis) { axisMajor = axis; }
    void SetAxisMajor(double x, double y, double z) { axisMajor = glm::dvec3(x, y, z); }
    void SetAxisMinor(const glm::dvec3& axis) { axisMinor = axis; }
    void SetAxisMinor(double x, double y, double z) { axisMinor = glm::dvec3(x, y, z); }
};

struct AUIShapeEllipseArc
{
    glm::dvec3 pos;
    glm::dvec3 norm;
    double radiusMajor;
    double radiusMinor;
    glm::dvec3 axisMajor;
    glm::dvec3 axisMinor;
    double startAngle;
    double endAngle;


    //////////////////////////////////////////////////////////////////////////
    // Base constructor
    AUIShapeEllipseArc() : norm(0.0, 0.0, 1.0), radiusMajor(1.0), radiusMinor(1.0), axisMajor(1.0, 0.0, 0.0), axisMinor(0.0, 1.0, 0.0), startAngle(0.0), endAngle(0.0) { }


    //////////////////////////////////////////////////////////////////////////
    // Make
    static AUIShapeEllipseArc Make() { return AUIShapeEllipseArc(); }
    static AUIShapeEllipseArc MakePos(double x, double y, double z) { AUIShapeEllipseArc c; c.SetPos(x, y, z); return c; }
    static AUIShapeEllipseArc MakeNorm(double nx, double ny, double nz) { AUIShapeEllipseArc c; c.SetNorm(nx, ny, nz); return c; }
    static AUIShapeEllipseArc MakeRadiusMajor(double r) { AUIShapeEllipseArc c; c.SetRadiusMajor(r); return c; }
    static AUIShapeEllipseArc MakeRadiusMinor(double r) { AUIShapeEllipseArc c; c.SetRadiusMinor(r); return c; }
    static AUIShapeEllipseArc MakeStartAngle(double angle) { AUIShapeEllipseArc c; c.SetStartAngle(angle); return c; }
    static AUIShapeEllipseArc MakeEndAngle(double angle) { AUIShapeEllipseArc c; c.SetEndAngle(angle); return c; }
    static AUIShapeEllipseArc MakePosNormRadiusAngle(const glm::dvec3& pos, const glm::dvec3& norm,
        double rMajor, double rMinor, const glm::dvec3& axisMajor, const glm::dvec3& axisMinor, const double aStart, const double aEnd)
    {
        AUIShapeEllipseArc c;
        c.SetPos(pos);
        c.SetNorm(norm);
        c.SetRadiusMajor(rMajor);
        c.SetRadiusMinor(rMinor);
        c.SetAxisMajor(axisMajor);
        c.SetAxisMinor(axisMinor);
        c.SetStartAngle(aStart);
        c.SetEndAngle(aEnd);
        return c;
    }

    static AUIShapeEllipseArc MakePosNormRadiusAngle(double x, double y, double z,
        double nx, double ny, double nz,
        double rMajor, double rMinor,
        double aMajorx, double aMajory, double aMajorz,
        double aMinorx, double aMinory, double aMinorz,
        double aStart, double aEnd)
    {
        AUIShapeEllipseArc c;
        c.SetPos(x, y, z);
        c.SetNorm(nx, ny, nz);
        c.SetRadiusMajor(rMajor);
        c.SetRadiusMinor(rMinor);
        c.SetAxisMajor(aMajorx, aMajory, aMajorz);
        c.SetAxisMinor(aMinorx, aMinory, aMinorz);
        c.SetStartAngle(aStart);
        c.SetEndAngle(aEnd);
        return c;
    }

    //////////////////////////////////////////////////////////////////////////
    // Setter
    void SetPos(const glm::dvec3& p) { pos = p; }
    void SetPos(double x, double y, double z) { pos = glm::dvec3(x, y, z); }
    void SetNorm(const glm::dvec3& n) { norm = glm::normalize(n); }
    void SetNorm(double nx, double ny, double nz) { norm = glm::normalize(glm::dvec3(nx, ny, nz)); }
    void SetRadiusMajor(double r) { radiusMajor = r; }
    void SetRadiusMinor(double r) { radiusMinor = r; }
    void SetAxisMajor(const glm::dvec3& axis) { axisMajor = axis; }
    void SetAxisMajor(double x, double y, double z) { axisMajor = glm::dvec3(x, y, z); }
    void SetAxisMinor(const glm::dvec3& axis) { axisMinor = axis; }
    void SetAxisMinor(double x, double y, double z) { axisMinor = glm::dvec3(x, y, z); }
    void SetStartAngle(double angle) { startAngle = angle; }
    void SetEndAngle(double angle) { endAngle = angle; }
};
