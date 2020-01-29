#pragma once

#include <ctre/Phoenix.h>
#include <CORERobotLib.h>
#include <frc/WPILib.h>
#include <networktables/NetworkTableInstance.h>
#include <COREControl/COREPID.h>

using namespace CORE;

class TurretSubsystem : public CORESubsystem {
private:
    TalonSRX m_turret;
    double m_startupTurretPosition;
    nt::NetworkTableInstance ntinst;
    COREConstant<double> m_KP, m_KI, m_KD, m_KF;
    COREPID corePID;

public:
    TurretSubsystem();
    void robotInit() override;
    void teleopInit() override;
    void teleop() override;
    void InitTalons();
    void SetTurret(double turretPercent);
};
