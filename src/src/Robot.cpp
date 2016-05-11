#include "WPILib.h"
#include "Option.h"
#include "SigmaDrive.h"

#define FORWARD -1
#define BACKWARD 1


/**
 * This is a demo program showing the use of the RobotDrive  class.
 * The SampleRobot class is the base of a robot application that will automatically call your
 * Autonomous and OperatorControl methods at the right time as controlled by the switches on
 * the driver station or the field controls.
 *
 * WARNING: While it may look like a good choice to use for your code if you're inexperienced,
 * don't. Unless you know what you are doing, complex code will be much more difficult under
 * this system. Use IterativeRobot or Command-Based instead if you're new.
 */
class Robot: public SampleRobot
{
	SigmaDrive *Base; // robot drive system; replaces (drive108)
	Joystick *leftStick, *rightStick, *controller;
	SendableChooser *chooser;
	Encoder *leftEnc, *rightEnc, *shooterEnc;
	VictorSP *intake, *leftIndexer, *rightIndexer, *armMoter;
	Option *Auto;



	const std::string autoNameDefault = "Default";
	const std::string autoNameCustom = "My Auto";

public:
	void RobotInit()
	{
		Base = new SigmaDrive();
		//Autonomous options
		chooser = new SendableChooser();
		chooser->AddDefault("Low Bar", new Option(1));
		chooser->AddObject("Breaching Defenses", new Option(2));
		chooser->AddObject("Two Point Auto", new Option(3));
		SmartDashboard::PutData("Auto", chooser);

		leftEnc = new Encoder(8,9, false, Encoder::EncodingType::k4X);
		rightEnc = new Encoder(6,7, true, Encoder::EncodingType::k4X);
		shooterEnc = new Encoder(4,5);

		controller = new Joystick(2);

		leftStick = new Joystick(0);
		rightStick = new Joystick(1);
	}

	/**
	 * This autonomous (along with the chooser code above) shows how to select between different autonomous modes
	 * using the dashboard. The sendable chooser code works with the Java SmartDashboard. If you prefer the LabVIEW
	 * Dashboard, remove all of the chooser code and uncomment the GetString line to get the auto name from the text box
	 * below the Gyro
	 *
	 * You can add additional auto modes by adding additional comparisons to the if-else structure below with additional strings.
	 * If using the SendableChooser make sure to add them to the chooser code above as well.
	 */
	void Autonomous()
	{
		std::string autoSelected = *((std::string*)chooser->GetSelected());
		//std::string autoSelected = SmartDashboard::GetString("Auto Selector", autoNameDefault);
		std::cout << "Auto selected: " << autoSelected << std::endl;
		Auto = (Option*) chooser->GetSelected();
		if(Auto->Get() == 1)
		{
			//Low Bar code here
			std::cout << "Running custom Autonomous" << std::endl;
 	// stop robot
		}
		else if(Auto->Get() == 2)
		{
			 //Standard defense codes here
			std::cout << "Running default Autonomous" << std::endl;
	// stop robot
		}
		else if(Auto->Get() == 3)
		{
			//2 point auto code here
		}
		else
		{
			//Low Bar code here if its not default
		}

	}

	/**
	 * Runs the motors with arcade steering.
	 */
	void OperatorControl()
	{
		//myRobot.SetSafetyEnabled(true);
		while (IsOperatorControl() && IsEnabled())
		{
			//Driver Controls
			Base->TankDrive(leftStick->GetY(), rightStick->GetY());
			if (controller->GetRawAxis(3)>0.2)//Brings arm down
			{
				Base->ArmDown();
			}
			else if (controller->GetRawAxis(2)>0.2)//Brings arm up
			{
				Base->ArmUp();
			}

			if(rightStick->GetRawButton(1))
			{
				Base->Shift(true); // High Gear = reverse
			}
			else if(leftStick->GetRawButton(1))
			{
				Base->Shift(false); // Low Gear = forward
			}// drive with arcade style (use right stick)
			else if(rightStick->GetRawButton(3))
			{
				intake->Set(0.8);//Intake code for driver
			}
			//Operator Controls
			if (controller->GetRawButton(4))
			{
				Base->Shooter(true);//shooter position is aimed up
			}
			else if (controller->GetRawButton(2))
			{
				Base->Shooter(false);//shooter position is aimed down
			}

			else if(controller->GetRawButton(6))
			{
			/*
			{
				int choice = 1;
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
						}
						counter++;
						std::printf("CHOICE 2\r\n");
						break;
					case 3:
						intake->Set(0.0);
						std::printf("CHOICE 3\r\n");
						break;
		        }
				*/
			}
			else if(controller->GetRawButton(1))
			{
				Base->ShootBall(true);
			}

			Wait(0.005);				// wait for a motor update time
		}

	}
	//Autonomous Methods
private:

	/**
	 * Runs during test mode
	 */
	void Test()
	{
	}
};

START_ROBOT_CLASS(Robot)
