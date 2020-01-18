#include <TurretSubsystem.h>
#include <Robot.h>
TurretSubsystem::TurretSubsystem(): m_turret(TURRET_PORT){
std::cout << "Turret Subsystem constructer called" << std::endl;
}


void TurretSubsystem::robotInit() {
    operatorJoystick->RegisterAxis(CORE::COREJoystick::JoystickAxis::LEFT_STICK_X);
    operatorJoystick->RegisterButton(CORE::COREJoystick::JoystickButton::B_BUTTON);
    operatorJoystick->RegisterButton(CORE::COREJoystick::JoystickButton::X_BUTTON);
    InitTalons();
      // start NetworkTables
    ntinst = nt::NetworkTableInstance::GetDefault();
    ntinst.StartClientTeam(2062);
}

void TurretSubsystem::teleopInit() {
    m_startupTurretPosition = m_turret.GetSelectedSensorPosition(0);
    //m_turret.Set(ControlMode::MotionMagic, m_startupTurretPosition);

}

void TurretSubsystem::teleop() {
    // m_turret.Set(ControlMode::MotionMagic, m_startupTurretPosition + 300);
    //    m_turret.Set(ControlMode::PercentOutput, 0.5);
    SmartDashboard::PutNumber("Turret position", m_turret.GetSelectedSensorPosition(0));
    if (operatorJoystick->GetButton(CORE::COREJoystick::JoystickButton::B_BUTTON)) {
        // m_startupTurretPosition = m_turret.GetSelectedSensorPosition(0);
        m_turret.Set(ControlMode::MotionMagic, m_startupTurretPosition + 300);
    } else if (operatorJoystick->GetButton(CORE::COREJoystick::JoystickButton::X_BUTTON)) {
        // m_startupTurretPosition = m_turret.GetSelectedSensorPosition(0);
        m_turret.Set(ControlMode::MotionMagic, m_startupTurretPosition - 300);
    }
    // double motorValue =(-operatorJoystick->GetAxis(CORE::COREJoystick::JoystickAxis::LEFT_STICK_X))*0.20;
    // m_turret.Set(ControlMode::PercentOutput, motorValue);
    // SmartDashboard::PutNumber("Motor Value", motorValue);
    // m_bPressed = operatorJoystick->GetButton(CORE::COREJoystick::JoystickButton::B_BUTTON);
    // m_xPressed = operatorJoystick->GetButton(CORE::COREJoystick::JoystickButton::X_BUTTON);

}
// some code;
/*
    double inputMotorValue = 0;
   auto table = ntinst.GetTable("COREVision");
   int imageCenterX = 512;
    bool hasCenterX = false;
    double targetCenterXBridge = 0;
    double targetCenterX = 0;
    hasCenterX = table->GetBoolean("Has Center X", false);
    if (hasCenterX) {
        targetCenterXBridge = table->GetNumber("Center X", -1);
        targetCenterX = (targetCenterXBridge / 7.15783587306);
        std::cout << "targetCenterX" << std::endl;
        // double targetCenterXOffset = targetCenterX-imageCenterX;
        // inputMotorValue =  (targetCenterXOffset/imageCenterX)*0.2;
    }
    //positive is right
    // inputMotorValue = (-operatorJoystick->GetAxis(CORE::COREJoystick::JoystickAxis::LEFT_STICK_X))*0.20;
    bool atLeftStop = ((m_turret.GetSelectedSensorPosition(0)) < (m_startupTurretPosition - 468.0));
    bool atRightStop = ((m_turret.GetSelectedSensorPosition(0)) > (m_startupTurretPosition + 468.0));
    SmartDashboard::PutBoolean("Left Stop", atLeftStop);
    SmartDashboard::PutBoolean("Right Stop", atRightStop);
     if(targetCenterX > (m_startupTurretPosition + 468.0)){
        std::cout << "at right" << std::endl;
    }else if(targetCenterX < (m_startupTurretPosition - 468.0)){
        std::cout << "at left" << std::endl;
    }else{
        m_turret.Set(ControlMode::MotionMagic, targetCenterX);
        std::cout << "motion" << std::endl;
    }
   
    SmartDashboard::PutNumber("Motor Value", inputMotorValue);
    SmartDashboard::PutNumber("Largest Center X", targetCenterX); // make into encoder units/degrees
    // m_turret.Set(ControlMode::PercentOutput, inputMotorValue);
    
    SmartDashboard::PutNumber("Turret position", m_turret.GetSelectedSensorPosition(0));
     if ((atRightStop && inputMotorValue < 0) || (atLeftStop && inputMotorValue > 0)) {
        inputMotorValue = 0;
    }
*/
/*
* 1. Find angle of focal width of camera Horizontal FOV: 62.2 degrees, Vertical FOV: 48.8 degrees
* 2. Convert cameraWidthUnits to degrees 16.46302251 CU = 1 DEG
* 3. Convert to encoder units (Ticks) 11.377777777777778  4096 / 360
* 4. Make it so that if targetCenterX (in encoder units) is greater than rightStop or leftStop do nothing but if in range have turret move
*/

void TurretSubsystem::InitTalons() {
	// Sets up talons
	m_turret.Set(ControlMode::PercentOutput, 0);
        /* Configure Sensor Source for Primary PID */
    // m_turret.ConfigSelectedFeedbackSensor(FeedbackDevice::CTRE_MagEncoder_Relative,
    //                                     0, 
    //                                     10);
    /**
     * Configure Talon SRX Output and Sesnor direction accordingly
     * Invert Motor to have green LEDs when driving Talon Forward / Requesting Postiive Output
     * Phase sensor to have positive increment when driving Talon Forward (Green LED)
     */
    // m_turret.SetSensorPhase(false);
    // m_turret.SetInverted(false);

    // /* Set relevant frame periods to be at least as fast as periodic rate */
    // m_turret.SetStatusFramePeriod(StatusFrameEnhanced::Status_13_Base_PIDF0, 10, 10);
    // m_turret.SetStatusFramePeriod(StatusFrameEnhanced::Status_10_MotionMagic, 10, 10);

    // /* Set the peak and nominal outputs */
    // m_turret.ConfigNominalOutputForward(0, 10);
    // m_turret.ConfigNominalOutputReverse(0, 10);
    // m_turret.ConfigPeakOutputForward(1, 10);
    // m_turret.ConfigPeakOutputReverse(-1, 10);

    // /* Set Motion Magic gains in slot0 - see documentation */
    // m_turret.SelectProfileSlot(0, 0);
    // m_turret.Config_kF(0, 0.3, 10);
    // m_turret.Config_kP(0, 0.1, 10);
    // m_turret.Config_kI(0, 0.0, 10);
    // m_turret.Config_kD(0, 0.0, 10);

    // /* Set acceleration and vcruise velocity - see documentation */
    // m_turret.ConfigMotionCruiseVelocity(1500, 10);
    // m_turret.ConfigMotionAcceleration(1500, 10);

    /* Zero the sensor */
    m_turret.SetSelectedSensorPosition(0, 0, 10);
}

