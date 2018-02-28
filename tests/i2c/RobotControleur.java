package org.firstchampionship.equipe5910.robot2018;

import edu.wpi.first.wpilibj.I2C;
import edu.wpi.first.wpilibj.I2C.Port;
import edu.wpi.first.wpilibj.IterativeRobot;
import edu.wpi.first.wpilibj.RobotController;
import edu.wpi.first.wpilibj.Timer;

public class RobotControleur extends IterativeRobot {
	
	@Override
	public void robotInit() {
		System.out.println("robotInit()");
	}

	@Override
	public void autonomousInit() {
	}

	@Override
	public void autonomousPeriodic() {
		Scheduler.getInstance().run(); // pour faire marcher les commandes
	}

	@Override
	public void teleopInit() {	
		System.out.println("teleopInit()");
	}

	
	@Override
	public void teleopPeriodic() {		
	}
	@Override
	public void disabledInit() {
	}
	
	
	public I2C lienLed;
	byte[] message = new byte[1];
	byte[] vide = new byte[1];
	@Override
	public void testInit() {
		lienLed = new I2C(I2C.Port.kOnboard,4);
		message[0] = 'a';		
	}
	
	@Override
	public void testPeriodic() {
		// System.out.println("testPeriodic()");
		// http://first.wpi.edu/FRC/roborio/beta/docs/java/edu/wpi/first/wpilibj/command/Scheduler.html
		Scheduler.getInstance().run(); // pour faire marcher les commandes
	    lienLed.transaction(message, 1,vide,0);
	    Timer.delay(1);
	}

}
