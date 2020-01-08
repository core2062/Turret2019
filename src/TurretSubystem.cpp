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
    int imageWidth = 1024;
    bool hasCenterX = false;
    double centerX = 0;
    hasCenterX = table->GetBoolean("Has Center X", false);
    if (hasCenterX) {
        centerX = table->GetNumber("Center X", -1);
        if( std::abs(centerX-(imageWidth/2))<50){
            //leave zero
        } else if(centerX<(imageWidth/2)){
            inputMotorValue = 0.1;
        } else if(centerX>(imageWidth/2)) {
            inputMotorValue = -0.1;
        } else{

        }
    }
    bool atLeftStop = ((m_turret.GetSelectedSensorPosition(0)) > (m_startupTurretPosition + 468.0));
    bool atRightStop = ((m_turret.GetSelectedSensorPosition(0)) < (m_startupTurretPosition - 468.0));

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

