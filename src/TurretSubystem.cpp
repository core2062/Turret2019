#include <TurretSubsystem.h>
#include <Robot.h>
#include <COREControl/COREPID.h>
TurretSubsystem::TurretSubsystem(): m_turret(TURRET_PORT),
                                    m_KP("KP", 0.0005),
                                    m_KI("KI", 0),
                                    m_KD("KD",0),
                                    m_KF("KF",0), 
                                    corePID(0, 0, 0, 0) {
    std::cout << "Turret Subsystem constructer called" << std::endl;
}

void TurretSubsystem::robotInit() {
    operatorJoystick->RegisterButton(CORE::COREJoystick::JoystickButton::X_BUTTON);
    InitTalons();
    // start NetworkTables
    ntinst = nt::NetworkTableInstance::GetDefault();
    ntinst.StartClientTeam(2062);

}

void TurretSubsystem::teleopInit() {
    m_startupTurretPosition = m_turret.GetSelectedSensorPosition(0);
}

void TurretSubsystem::teleop() {
    auto table = ntinst.GetTable("limelight");
    bool hasCenterX = table->GetNumber("tv", 0.0) == 1;
    double conversion = 4096 / -360; // convert degrees to ticks
    // calculate center error as a percent output for the motor
    double centerError = table->GetNumber("tx", 0.0) * conversion;
    double motorPercent = corePID.Calculate(centerError);
    bool atLeftStop = m_turret.GetSelectedSensorPosition(0) < (m_startupTurretPosition - 468.0);
    bool atRightStop = m_turret.GetSelectedSensorPosition(0) > (m_startupTurretPosition + 468.0);
    bool xButtonPressed = operatorJoystick->GetButton(CORE::COREJoystick::JoystickButton::X_BUTTON);
    if (hasCenterX && xButtonPressed && ((!atRightStop && centerError < 0) || (!atLeftStop && centerError > 0))) {
        SetTurret(motorPercent);
    } else {
        SetTurret(0.0);
    }

    SmartDashboard::PutNumber("Turret position", m_turret.GetSelectedSensorPosition(0));
    SmartDashboard::PutNumber("Center Error", centerError);
    SmartDashboard::PutBoolean("HasTable", hasCenterX);
    SmartDashboard::PutBoolean("At Left Stop", atLeftStop);
    SmartDashboard::PutBoolean("At Right Stop", atRightStop);
    SmartDashboard::PutBoolean("X Button Pressed", operatorJoystick->GetButton(CORE::COREJoystick::JoystickButton::X_BUTTON));
}

void TurretSubsystem::SetTurret(double turretPercent) {
    m_turret.Set(ControlMode::PercentOutput, turretPercent);
}

void TurretSubsystem::InitTalons() {
	// Sets up talons
	m_turret.Set(ControlMode::PercentOutput, 0);
    // Zero the sensor
    m_turret.SetSelectedSensorPosition(0, 0, 10);
}
