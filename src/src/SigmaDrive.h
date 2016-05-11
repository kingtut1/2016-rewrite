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
	VictorSP *intake, *leftIndexer, *rightIndexer, *armMotor, *shooter;
	RobotDrive *drive108;
	DoubleSolenoid *shifter, *shooterAim;
	Encoder *leftEnc, *rightEnc;
	ADXRS450_Gyro *gyro;
	DigitalInput *Upperlimit, *Lowerlimit;
	SigmaDrive();
	void TankDrive(double l, double r);
	void TankDrive(Joystick l, Joystick r);
	void Shift(bool High);
	virtual ~SigmaDrive();
	void Shooter(bool Up);
	void ArmDown();
	void ArmUp();
	void Intake(bool running);
	void ShootBall(bool shoot);
	void IntakeAndShoot(bool run );
};
#endif /* SRC_SIGMADRIVE_H_ */
