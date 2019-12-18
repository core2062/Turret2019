#pragma once

#include <ctre/Phoenix.h>
#include <CORERobotLib.h>
#include <frc/WPILib.h>

using namespace CORE;

class TurretSubsystem :  public CORESubsystem
{
private:
    TalonSRX m_turret;
    double m_startupTurretPosition;

public:
    TurretSubsystem();
    void robotInit() override;
    void teleopInit() override;
    void teleop() override;
	void Setrotate();
	void SetOff();
    void InitTalons();

};
