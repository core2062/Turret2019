#pragma once

#include <ctre/Phoenix.h>
#include <CORERobotLib.h>
#include <frc/WPILib.h>
#include <networktables/NetworkTableInstance.h>
#include <cmath>

using namespace CORE;

class TurretSubsystem :  public CORESubsystem
{
private:
    TalonSRX m_turret;
    double m_startupTurretPosition;
    nt::NetworkTableInstance ntinst;
    bool m_xPressed;
    bool m_bPressed;

public:
    TurretSubsystem();
    void robotInit() override;
    void teleopInit() override;
    void teleop() override;
	void Setrotate();
	void SetOff();
    void InitTalons();

};
