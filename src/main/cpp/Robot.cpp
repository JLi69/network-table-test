// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "Robot.h"
#include <fmt/core.h>
#include <frc/smartdashboard/SmartDashboard.h>
#include <iostream>
#include <math.h>
#include <ntcore_c.h>

void Robot::RobotInit()
{
	srand(time(NULL));
	auto inst = nt::NetworkTableInstance::GetDefault();
	auto table = inst.GetTable("datatable");
	robotNumEntry = table->GetEntry("robotNum");
	robotNumber = (double)(rand() % 100 + 1);
	robotNumEntry.SetDouble(robotNumber);
	robotNumEntry.AddListener(
		[](const nt::EntryNotification &event)
		{
			std::cout << "Hello World\n";
		}, NT_NOTIFY_UPDATE | NT_NOTIFY_NEW);
}

void Robot::TeleopPeriodic()
{
	double val = robotNumEntry.GetDouble(0.0);
	std::cout << "Robot Number: " << val << '\n';
	std::cout << "Client number: " << robotNumber << '\n';

	robotNumber += 0.1;
	if(robotNumber - floor(robotNumber) > 0.8)	
		robotNumEntry.SetDouble(robotNumber);
}

#ifndef RUNNING_FRC_TESTS
int main() 
{
	return frc::StartRobot<Robot>();
}
#endif
