#include "WPILib.h"
#include "Option.h"
#include "SigmaDrive.h"

/**
 * This is a demo program showing the use of the RobotDrive class.
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
	SigmaDrive *Base; // robot drive system
	Joystick leftStick, rightStick; // only joystick
	SendableChooser *chooser;
	const std::string autoNameDefault = "Default";
	const std::string autoNameCustom = "My Auto";

public:
	Robot() :	// these must be initialized in the same order
			leftStick(0), rightStick(1),		// as they are declared above.
			chooser(),
			Base()
	{
		//Note SmartDashboard is not initialized here, wait until RobotInit to make SmartDashboard calls

	}

	void RobotInit()
	{
		Base = new SigmaDrive();

		chooser = new SendableChooser();
		chooser->AddDefault("Low Bar", new Option(1));
		chooser->AddObject("Defenses", new Option(2));
		chooser->AddObject("Two Point Auto", new Option(3));
		SmartDashboard::PutData("Auto", chooser);
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

		if(autoSelected == autoNameCustom){
			//Custom Auto goes here
			std::cout << "Running custom Autonomous" << std::endl;
 	// stop robot
		} else {
			//Default Auto goes here
			std::cout << "Running default Autonomous" << std::endl;
	// stop robot
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
			Base->TankDrive(leftStick.GetY(), rightStick.GetY());
			if(rightStick.GetRawButton(1))
			{
				Base->Shift(true); // High Gear = reverse
			}
			else if(leftStick.GetRawButton(1))
			{
				Base->Shift(false); // Low Gear = forward
			}// drive with arcade style (use right stick)
			if (controller->GetRawButton(4))
			{
				Base->Shooter(true);//shooter aim up
			}
			else if (controller->GetRawButton(2))
			{
				Base->Shooter(false);//shooter aim down
			}
			Wait(0.005);				// wait for a motor update time
		}

	}

	/**
	 * Runs during test mode
	 */
	void Test()
	{
	}
};

START_ROBOT_CLASS(Robot)
