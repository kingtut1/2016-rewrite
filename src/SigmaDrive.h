/*
 * SigmaDrive.h
 *
 *  Created on: May 2, 2016
 *      Author: Robotics
 */
#include "WPILib.h"
#ifndef SRC_SIGMADRIVE_H_
#define SRC_SIGMADRIVE_H_

class SigmaDrive
{
public:
	VictorSP *left1,*left2,*right1,*right2;
	RobotDrive *drive108;
	DoubleSolenoid *shifter, *shooterAim;
	Encoder *leftEnc, *rightEnc;
	ADXRS450_Gyro *gyro;
	SigmaDrive();
	void TankDrive(double l, double r);
	void TankDrive(Joystick l, Joystick r);
	void Shift(bool High);
	virtual ~SigmaDrive();
	void Shooter(bool Aim);
	void Intake(bool Intake);
};
#endif /* SRC_SIGMADRIVE_H_ */
