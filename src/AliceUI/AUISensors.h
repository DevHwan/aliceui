#pragma once

#include "AUISensor.h"
#include "AUI1DShapeDef.h"

#include <vector>

class ALICEUI_API MAUISensorUtil
{
public:
    bool static IsIntersectLine(const glm::vec3& vRayOrg, const glm::vec3& vRayDir, float fRayRad, const AUIShapeLine& line, float& fHitDistance);
    bool static IsIntersectCircle(const glm::vec3& vRayOrg, const glm::vec3& vRayDir, float fRayRad, const AUIShapeCircle& circle, float& fHitDistance);
    bool static IsIntersectArc(const glm::vec3& vRayOrg, const glm::vec3& vRayDir, float fRayRad, const AUIShapeArc& arc, float& fHitDistance);
    bool static IsIntersectEllipse(const glm::vec3& vRayOrg, const glm::vec3& vRayDir, float fRayRad, const AUIShapeEllipse& ellipse, float& fHitDistance);
    bool static IsIntersectEllipseArc(const glm::vec3& vRayOrg, const glm::vec3& vRayDir, float fRayRad, const AUIShapeEllipseArc& ellipseArc, float& fHitDistance);
};

class ALICEUI_API MAUISphereSensor : public AUISensor
{
public:
    MAUISphereSensor() = default;
    ~MAUISphereSensor() override = default;

    void SetMatrix(const glm::mat4& matSensor) override {
        m_matSensorInv = glm::inverse(matSensor);
    }
    bool UpdateHit(const glm::vec3& vRayOrg, const glm::vec3& vRayDir) override;
    float GetHitDistance() const override {
        return m_fHitDistance;
    }
    glm::vec3 GetHitPos() const override {
        return m_vHitPos;
    }
    void SetAABB(float left, float top, float right, float bottom, float front, float back) override {
        // TODO
    }

    glm::vec3 GetHidDir() const {
        return m_vHitDir;
    }
    void SetSphere(const glm::vec3& pos, float radius) {
        m_vSpherePos = pos;
        m_fSphereRadius = radius;
    }
private:
    glm::vec3 m_vHitDir;
    glm::mat4 m_matSensorInv;
    glm::vec3 m_vSpherePos;
    glm::vec3 m_vHitPos;
    float m_fHitDistance = 0.0f;
    float m_fSphereRadius = 0.0f;
};

class ALICEUI_API MAUICircleBoundarySensor : public AUISensor
{
public:
    MAUICircleBoundarySensor() = default;
    ~MAUICircleBoundarySensor() override = default;

    void SetMatrix(const glm::mat4& matSensor) override {
        m_matSensorInv = glm::inverse(matSensor);
    }
    bool UpdateHit(const glm::vec3& vRayOrg, const glm::vec3& vRayDir) override;
    float GetHitDistance() const override {
        return m_fHitDistance;
    };
    glm::vec3 GetHitPos() const override {
        return m_vHitPos;
    }
    void SetAABB(float left, float top, float right, float bottom, float front, float back) override {
        // TODO
    }

    void SetCircle(float radius) {
        m_fRadius = radius;
    }
private:
    glm::mat4 m_matSensorInv;
    glm::vec3 m_vHitPos;
    float m_fRadius = 0.0f;
    float m_fBoundarySize = 5.0f;
    float m_fHitDistance = 0.0f;
};

class ALICEUI_API MAUILinesSensor : public AUISensor
{
public:
    MAUILinesSensor() = default;
    ~MAUILinesSensor() override = default;

    void SetMatrix(const glm::mat4& matSensor) override {
        m_matSensorInv = glm::inverse(matSensor);
    }
    bool UpdateHit(const glm::vec3& vRayOrg, const glm::vec3& vRayDir) override;
    float GetHitDistance() const override {
        return m_fHitDistance;
    }
    glm::vec3 GetHitPos() const override {
        return m_vHitPos;
    }
    void SetAABB(float left, float top, float right, float bottom, float front, float back) override {
        this->SetBox({ left, top, front }, { right, bottom, back });
    }

    void SetBox(glm::vec3 minBox, glm::vec3 maxBox)
    {
        //todo
    }

    void SetLine(const std::vector< AUIShapeLine >& arrLines)
    {
        m_arrLines = arrLines;
    }
    void AddLine(const AUIShapeLine& Line)
    {
        m_arrLines.emplace_back(Line);
    }
    void AddLine(const glm::dvec3 pos1, const glm::dvec3 pos2)
    {
        m_arrLines.emplace_back(AUIShapeLine::MakePos(pos1, pos2));
    }
    void ClearLine()
    {
        m_arrLines.clear();
    }

    void SetCircle(const std::vector< AUIShapeCircle >& arrCircles)
    {
        m_arrCircle = arrCircles;
    }
    void AddCircle(const AUIShapeCircle& Circle)
    {
        m_arrCircle.emplace_back(Circle);
    }
    void ClearCircle()
    {
        m_arrCircle.clear();
    }

    void SetArc(const std::vector< AUIShapeArc >& arrArcs)
    {
        m_arrArc = arrArcs;
    }
    void AddArc(const AUIShapeArc& Arc)
    {
        m_arrArc.emplace_back(Arc);
    }
    void ClearArc()
    {
        m_arrArc.clear();
    }

    void SetEllipse(const std::vector< AUIShapeEllipse >& arrEllipses)
    {
        m_arrEllipse = arrEllipses;
    }
    void AddEllipse(const AUIShapeEllipse& Ellipse)
    {
        m_arrEllipse.emplace_back(Ellipse);
    }
    void ClearEllipse()
    {
        m_arrEllipse.clear();
    }

    void SetEllipseArc(const std::vector< AUIShapeEllipseArc >& arrEllipseArcs)
    {
        m_arrEllipseArc = arrEllipseArcs;
    }
    void AddEllipseArc(const AUIShapeEllipseArc& EllipseArc)
    {
        m_arrEllipseArc.emplace_back(EllipseArc);
    }
    void ClearEllipseArc()
    {
        m_arrEllipseArc.clear();
    }

private:
    std::vector< AUIShapeLine > m_arrLines;
    std::vector< AUIShapeCircle > m_arrCircle;
    std::vector< AUIShapeArc > m_arrArc;
    std::vector< AUIShapeEllipse > m_arrEllipse;
    std::vector< AUIShapeEllipseArc > m_arrEllipseArc;

    AUIShapeLine m_lines;
    glm::vec3 m_vHitPos;
    glm::mat4 m_matSensorInv;
    float m_fHitDistance = 0.0f;
};
