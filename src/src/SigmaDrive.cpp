/*
 * SigmaDrive.cpp
 *
 *  Created on: May 2, 2016
 *      Author: Robotics
 */

#include <SigmaDrive.h>

#define FORWARD -1
#define BACKWARD 1
#define HIGHSPEED 1130
#define LOWSPEED 285.5
#define HIGHGEAR 1111
#define LOWGEAR 2222
#define TICKSPERFEET 421

SigmaDrive::SigmaDrive() {
	// TODO Auto-generated constructor stub
	//VictorSP
	left1 = new VictorSP(9);//og 9//front left motor
	left2 = new VictorSP(8);//back left motor
	right1 = new VictorSP(7);//front right motor
	right2 = new VictorSP(6);//back right motor
	leftIndexer = new VictorSP(3);
	rightIndexer = new VictorSP(2);
	armMotor = new VictorSP(5);
	shooter = new VictorSP(1);
	intake = new VictorSP(4);
	//Ultrasonic
	ballDetect = new Ultrasonic(3,2);
	ballDetect->SetEnabled(true);
	ballDetect->SetAutomaticMode(true);
	//Encoders
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
	if(High)
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
	if(Up)//controller->GetRawButton(4)
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
	if(!Upperlimit->Get() && !(shooterAim->Get() == DoubleSolenoid::kReverse) )
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
	if(!Lowerlimit->Get())
	{
		armMotor->Set(-0.28);
	}
	else
	{
		armMotor->Set(0.0);
	}
}
void SigmaDrive::Intake()
{
	switch(choice)
	{
		case 1:
			intake->Set(-0.85);
			leftIndexer->Set(-0.50108);
			rightIndexer->Set(0.50108);
			if(ballDetect->GetRangeInches()<3)
			{
				choice = 2;
				counter = 0;
			}
			std::printf("CHOICE 1\r\n");
			break;
		case 2:
			if(counter%315 == 0)//115
			{
				leftIndexer->Set(0.0);
				rightIndexer->Set(0.0);
				choice = 3;
				counter++;
				std::printf("CHOICE 2\r\n");
			}
			break;

		case 3:
				intake->Set(0.0);
				std::printf("CHOICE 3\r\n");
				choice = 1;
				break;
	}
}

void SigmaDrive::Release()
{
	shooter->Set(0);
	intake->Set(0.7);
	leftIndexer->Set(1.0);
	rightIndexer->Set(-1.0);
	choice = 1;
}

void SigmaDrive::Shoot(bool fire)
{
	intake->Set(0.0);
	shooter->Set(0.9);
	if(fire){
		leftIndexer->Set(-1.0);
		rightIndexer->Set(1.0);
	}else{
		leftIndexer->Set(0.0);
		rightIndexer->Set(0.0);
	}
	choice = 1;
}

void SigmaDrive::StopAll()
{
	shooter->Set(0.0);
	intake->Set(0.0);
	leftIndexer->Set(0.0);
	rightIndexer->Set(0.0);
	choice = 1;
}

void SigmaDrive::RunTobyRun(int Direction, int Gear, double Distance, double SpeedPWM)//with Encoders
{
	bool done = false;
	int ticks = Distance * TICKSPERFEET;
	if (Direction == FORWARD)
	{
		rightEnc->SetReverseDirection(false);
	}
	else
	{
		rightEnc->SetReverseDirection(true);
	}
	rightEnc->Reset();
	while (!done)
	{
		printf ("ticks = %d until %d\r\n", rightEnc->Get(), ticks);
		if(rightEnc->Get() < ticks)
		{
			drive108->TankDrive(SpeedPWM * Direction, SpeedPWM * Direction);
		}
		else
		{
			drive108->TankDrive(0.0,0.0);
			done = true;
		}
		Wait(.005);
	}
}
void SigmaDrive::Moat()
{
	Shift(false);//Low Gear
	Shooter(true);//shooterAim Up
	RunTobyRun(FORWARD, LOWGEAR, 12.5, 1.0);
}
void SigmaDrive::TwoPointAuto()
{
	Shift(false);
	Wait(1);
	RunTobyRun(FORWARD, LOWGEAR, 7, 0.7);
}
void SigmaDrive::Lowbar()
{
	Shift(false);
	ArmDown();
	RunTobyRun(FORWARD, LOWGEAR, 12, 0.7);
	RunTobyRun(BACKWARD, LOWGEAR, 11, 0.7);
}

