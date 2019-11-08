#include <Robot.h>

#include <iostream>

#include <frc/WPILib.h>
Robot * Robot::m_instance;
Robot::Robot() {
std::cout << "Robot Subsystem constructer called" << std::endl;
m_instance = this;
}

void Robot::teleop() {}

void Robot::robotInit() {}

void Robot::teleopInit() {}

void Robot::test() {}

void Robot::testInit() {}

Robot * Robot::GetInstance() {
	return m_instance;
}


#ifndef RUNNING_FRC_TESTS
int main() { 
    std:cout << "Int main called" << std::endl;
	return frc::StartRobot<Robot>(); 
}
#endif
