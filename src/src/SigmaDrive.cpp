/*
 * SigmaDrive.cpp
 *
 *  Created on: May 2, 2016
 *      Author: Robotics
 */

#include <SigmaDrive.h>

SigmaDrive::SigmaDrive() {
	// TODO Auto-generated constructor stub

	left1 = new VictorSP(9);//og 9//front left motor
	left2 = new VictorSP(8);//back left motor
	right1 = new VictorSP(7);//front right motor
	right2 = new VictorSP(6);//back right motor

	leftEnc = new Encoder(8,9, false, Encoder::EncodingType::k4X);
	rightEnc = new Encoder(6,7, true, Encoder::EncodingType::k4X);

	drive108 = new RobotDrive(left1,left2,right1,right2);

	shifter = new DoubleSolenoid(0,1);
	shooterAim = new DoubleSolenoid(2,3);

	Lowerlimit = new DigitalInput(0);
	Upperlimit = new DigitalInput(1);


	gyro = new ADXRS450_Gyro();
	gyro->Calibrate();

}

SigmaDrive::~SigmaDrive() {
	// TODO Auto-generated destructor stub
}

void SigmaDrive::TankDrive(Joystick l, Joystick r){
	drive108->TankDrive(l,r);
}

void SigmaDrive::TankDrive(double l, double r){
	drive108->TankDrive(l,r);
}

void SigmaDrive::Shift(bool High){
	if(true)
	{//right->GetRawButton(1)
		shifter->Set(DoubleSolenoid::kForward); // High Gear = reverse
	}
	else if(false)
	{//left->GetRawButton(1)
		shifter->Set(DoubleSolenoid::kReverse); // Low Gear = forward
	}
}

void SigmaDrive::Shooter(bool Up)
{
	if(true)//controller->GetRawButton(4)
	{
		shooterAim->Set(DoubleSolenoid::kReverse); //Up
	}
	else if(false)//controller->GetRawButton(2)
	{
		shooterAim->Set(DoubleSolenoid::kForward); //Down
	}
}
void SigmaDrive::Arm(bool Up);


