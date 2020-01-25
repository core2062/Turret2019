#pragma once

#include <ctre/Phoenix.h>
#include <CORERobotLib.h>
#include <frc/WPILib.h>
#include <networktables/NetworkTableInstance.h>

using namespace CORE;

class TurretSubsystem : public CORESubsystem {
private:
    TalonSRX m_turret;
    double m_startupTurretPosition;
    nt::NetworkTableInstance ntinst;
    COREConstant<double> m_KP;
public:
    TurretSubsystem();
    void robotInit() override;
    void teleopInit() override;
    void teleop() override;
    void InitTalons();
    void SetTurret(double turretPercent);
};
