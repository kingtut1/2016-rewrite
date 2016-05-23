#include "WPILib.h"
#include "Option.h"
#include "SigmaDrive.h"

#define FORWARD -1
#define BACKWARD 1
#define HIGHSPEED 1130
#define LOWSPEED 285.5
#define HIGHGEAR 1111
#define LOWGEAR 2222
#define TICKSPERFEET 421

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
	Option *Auto;
/*
	const std::string autoNameDefault = "Default";
	const std::string autoNameCustom = "My Auto";
*/
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
		//Joysticks
		leftStick = new Joystick(0);
		rightStick = new Joystick(1);
		controller = new Joystick(2);

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
			printf("Hiiiiiiiiiiiii");
			std::cout << "Running Lowbar code" << std::endl;
			Base->Lowbar();
			std::cout << "Running custom Autonomous" << std::endl;
 	// stop robot
		}
		else if(Auto->Get() == 2)
		{
			 //Standard defense codes here
			std::cout << "Running defenses code" << std::endl;
			Base->Moat();
			std::cout << "Running default Autonomous" << std::endl;
	// stop robot
		}
		else if(Auto->Get() == 3)
		{
			//2 point auto code here
			std::cout << "Running TwoPointAuto" << std::endl;
			Base->TwoPointAuto();
			/*
			 * Testing Auto
			 */
			Base->rightEnc->Reset();
			Base->leftEnc->Reset();
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
			Base->TankDrive(leftStick->GetY(), rightStick->GetY());
			//Operator Controls
			if (controller->GetRawAxis(3)>0.2)//Brings arm down
			{
				Base->ArmDown();
			}
			else if (controller->GetRawAxis(2)>0.2)//Brings arm up
			{
				Base->ArmUp();
			}
			//Driver Controls
			if(rightStick->GetRawButton(1))
			{
				Base->Shift(true); // High Gear = reverse
			}
			else if(leftStick->GetRawButton(1))
			{
				Base->Shift(false); // Low Gear = forward
			}// drive with arcade style (use right stick)

			//Operator Controls
			if (controller->GetRawButton(4))//Y
			{
				Base->Shooter(true);//shooter position is up
			}
			else if (controller->GetRawButton(2))//B
			{
				Base->Shooter(false);//shooter position is down
			}
			//Intaking & Shooting Actions
			if(controller->GetRawButton(6))//LB(Intake)
			{
				Base->Intake();
			}
			else if(controller->GetRawButton(5))//RB(Release)
			{
				Base->Release();
			}
			else if(controller->GetRawButton(3))//X button
			{
				if(controller->GetRawButton(1))//A button
				{
					Base->Shoot(true);
				}
				else
				{
					Base->Shoot(false);
				}
			}
			else
			{
				Base->StopAll();
			}
			Wait(0.005);// wait for a motor update time
		}
	}
};

START_ROBOT_CLASS(Robot)
