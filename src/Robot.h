#pragma once

#include <string>

#include <TurretSubsystem.h>

#include <CORERobotLib.h>

#define TURRET_PORT 18

class Robot : public CORERobot 
{
public:
    Robot();
    void robotInit() override;
    void teleopInit() override;
    void teleop() override;
	void test() override;
	void testInit() override;
    static Robot * GetInstance();
    TurretSubsystem turretSubsystem;
private:
    static Robot * m_instance;
};
