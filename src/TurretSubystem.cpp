#include <TurretSubsystem.h>
#include <Robot.h>
TurretSubsystem::TurretSubsystem(): m_turret(TURRET_PORT){
std::cout << "Turret Subsystem constructer called" << std::endl;
}


void TurretSubsystem::robotInit() {
    operatorJoystick->RegisterAxis(CORE::COREJoystick::LEFT_STICK_X);
    InitTalons();
      // start NetworkTables
    ntinst = nt::NetworkTableInstance::GetDefault();
    ntinst.StartClientTeam(2062);
}

void TurretSubsystem::teleopInit() {
    m_startupTurretPosition = m_turret.GetSelectedSensorPosition(0);
}

void TurretSubsystem::teleop() {
    double inputMotorValue = 0;
   auto table = ntinst.GetTable("COREVision");
    int imageCenterX = 1024/2;
    bool hasCenterX = false;
    double targetCenterX = 0;
    hasCenterX = table->GetBoolean("Has Center X", false);
    if (hasCenterX) {
        targetCenterX = table->GetNumber("Center X", -1);
        double targetCenterXOffset = targetCenterX-imageCenterX;
        inputMotorValue =  (targetCenterXOffset/imageCenterX)*0.25;
    }
    //positive is right
    // inputMotorValue = (-operatorJoystick->GetAxis(CORE::COREJoystick::JoystickAxis::LEFT_STICK_X))*0.20;
    bool atLeftStop = ((m_turret.GetSelectedSensorPosition(0)) < (m_startupTurretPosition - 468.0));
    bool atRightStop = ((m_turret.GetSelectedSensorPosition(0)) > (m_startupTurretPosition + 468.0));
    SmartDashboard::PutBoolean("Left Stop", atLeftStop);
    SmartDashboard::PutBoolean("Right Stop", atRightStop);
    if(-0.075 < inputMotorValue && inputMotorValue < 0.075){
        inputMotorValue = 0;
    }
    if ((atRightStop && inputMotorValue < 0) || (atLeftStop && inputMotorValue > 0)) {
        inputMotorValue = 0;
    }
    SmartDashboard::PutNumber("Motor Value", inputMotorValue);
    m_turret.Set(ControlMode::PercentOutput, inputMotorValue);
    SmartDashboard::PutNumber("Turret position", m_turret.GetSelectedSensorPosition(0));
}

void TurretSubsystem::InitTalons() {
	// Sets up talons
	m_turret.Set(ControlMode::PercentOutput, 0);
}

