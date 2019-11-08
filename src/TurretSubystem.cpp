#include <TurretSubsystem.h>
#include <Robot.h>
TurretSubsystem::TurretSubsystem(): m_turret(TURRET_PORT){
std::cout << "Turret Subsystem constructer called" << std::endl;
}


void TurretSubsystem::robotInit() {
    m_turret.Set(ControlMode::PercentOutput, 0);
    operatorJoystick->RegisterAxis(CORE::COREJoystick::LEFT_STICK_X);
    InitTalons();
    
}

void TurretSubsystem::teleopInit() { 
    a = m_turret.GetSelectedSensorPosition(0);
}

void TurretSubsystem::teleop() {
    bool atLeftStop = ((m_turret.GetSelectedSensorPosition(0)) > (a + 368.0));
    bool atRightStop = ((m_turret.GetSelectedSensorPosition(0)) < (a - 368.0));
    double inputMotorValue = (-operatorJoystick->GetAxis(CORE::COREJoystick::JoystickAxis::LEFT_STICK_X))*0.10;

    if ((atLeftStop && inputMotorValue < 0) || atRightStop && inputMotorValue > 0) { 
        inputMotorValue = 0;  
    }

    m_turret.Set(ControlMode::PercentOutput, inputMotorValue);
    SmartDashboard::PutNumber("Turret position", m_turret.GetSelectedSensorPosition(0));
}

void TurretSubsystem::InitTalons() {
	// Sets up talons
	m_turret.Set(ControlMode::PercentOutput, 0);
}

