#include <TurretSubsystem.h>
#include <Robot.h>
TurretSubsystem::TurretSubsystem(): m_turret(TURRET_PORT),
                                    m_KP("KP", 0.0005) {
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
    auto table = ntinst.GetTable("COREVision");
    int imageCenterX = 128;
    bool hasCenterX = table->GetBoolean("Has Center X", false);
    double targetCenterX = table->GetNumber("Center X", -1);
    double centerError = (targetCenterX - imageCenterX) * 2.764 * m_KP.Get();
    bool atLeftStop = ((m_turret.GetSelectedSensorPosition(0)) < (m_startupTurretPosition - 468.0));
    bool atRightStop = ((m_turret.GetSelectedSensorPosition(0)) > (m_startupTurretPosition + 468.0));
    bool xButtonPressed = operatorJoystick->GetButton(CORE::COREJoystick::JoystickButton::X_BUTTON);
    if (hasCenterX && xButtonPressed && ((!atRightStop && centerError < 0) || (!atLeftStop && centerError > 0))) {
        SetTurret(centerError);
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
