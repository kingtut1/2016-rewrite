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
	armMotor = new VictorSP(5);
	intake = new VictorSP(4);
	leftIndexer = new VictorSP(3);
	rightIndexer = new VictorSP(2);
	shooter = new VictorSP(1);




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

void SigmaDrive::TankDrive(Joystick l, Joystick r)
{
	drive108->TankDrive(l,r);
}

void SigmaDrive::TankDrive(double l, double r)
{
	drive108->TankDrive(l,r);
}

void SigmaDrive::Shift(bool High){
	if(true)
	{//right->GetRawButton(1)
		shifter->Set(DoubleSolenoid::kForward); // High Gear = reverse
	}
	else
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
	else//controller->GetRawButton(2)
	{
		shooterAim->Set(DoubleSolenoid::kForward); //Down
	}
}
void SigmaDrive::ArmDown()
{
	if(!Lowerlimit->Get())
	{
		armMotor->Set(0.50);
	}
	else
	{
		armMotor->Set(0.0);
	}
}
void SigmaDrive::ArmUp()
{
	if(!Upperlimit->Get() && !(shooterAim->Get() == DoubleSolenoid::kReverse))
	{
		armMotor->Set(.50);
	}
	else
	{
		armMotor->Set(0.0);
	}
}
void SigmaDrive::ShootBall(bool shoot)
{
	if(true)
	{
	//In theory the motor has to run for n time in order to reach full speed which will allow accuracy to improve
		for(int i = 0; i < 4; i++)
		{
			shooter->Set(0.9);
			Wait(1);
		}
	//After four seconds the Index motors will run shooting the ball
		rightIndexer->Set(-1.0);
		leftIndexer->Set(1.0);
	}
	else
	{
		shooter->Set(0.0);
		rightIndexer->Set(0.0);
		leftIndexer->Set(0.0);
	}
}
void SigmaDrive::IntakeAndShoot(bool run)
{
	if(true)
	{
		intake->Set(0.8);

	}
}
void SigmaDrive::Intake(bool running)
{
	if(running)
	{
		intake->Set(0.8);
	}
	else
	{
		intake->Set(0.0);
	}
}
