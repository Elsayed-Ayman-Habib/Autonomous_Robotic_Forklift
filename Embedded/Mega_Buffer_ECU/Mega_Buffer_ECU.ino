#include <ros.h>
#include <std_msgs/Int16.h>
#include <std_msgs/Float64.h>
#include <geometry_msgs/Twist.h>


ros::NodeHandle nh;


std_msgs::Float64 right_wheel_tick_count;
ros::Publisher rightPub("right_ticks", &right_wheel_tick_count);

std_msgs::Float64 left_wheel_tick_count;
ros::Publisher leftPub("left_ticks", &left_wheel_tick_count);

//std_msgs::Float64  steering_setpoint;
//ros::Publisher steering_setpoint_pub("Steering_setpoint", &steering_setpoint);

double SetPoint = 0.0 ;

double STEERING_angle;

// Distance from center of the left tire to the center of the right tire in m
const double WHEEL_BASE_W = 0.429;

// Distance from the back axe to the front axe in m
const double WHEEL_BASE_H = 0.358;

char* formatDouble2(double value1 , double value2)
{
  static char str3[10];
  static char str1[10];
  static char str2[10];
  int intValue1 = (int)(value1 * 100);
  int intValue2 = (int)(value2 * 100);

  if ( value1 >= 10.0)
  {
    sprintf(str1, "+%02d%02d", intValue1 / 100, abs(intValue1 % 100));
  }
  else if (value1 > 0.0 && value1 < 10.0)
  {
    sprintf(str1, "+%02d%02d", intValue1 / 100, abs(intValue1 % 100));
  }
  else if (value1 < 0.0 && value1 > -1.0)
  {
    sprintf(str1, "-%02d%02d", intValue1 / 100, abs(intValue1 % 100));
  }
  else if (value1 <= -1.0)
  {
    sprintf(str1, "%03d%02d", intValue1 / 100, abs(intValue1 % 100));
  }

  if ( value2 >= 10.0)
  {
    sprintf(str2, "+%02d%02d\n", intValue2 / 100, abs(intValue2 % 100));
  }
  else if (value2 > 0.0 && value2 < 10.0)
  {
    sprintf(str2, "+%02d%02d\n", intValue2 / 100, abs(intValue2 % 100));
  }
  else if (value2 < 0.0 && value2 > -1.0)
  {
    sprintf(str2, "-%02d%02d\n", intValue2 / 100, abs(intValue2 % 100));
  }
  else if (value2 <= -1.0)
  {
    sprintf(str2, "%03d%02d\n", intValue2 / 100, abs(intValue2 % 100));
  }

  sprintf(str3, "*%s%s\n", str1, str2);
  return str3;
}

char* formatDouble1(double value)
{
  static char str[10];
  int intValue = (int)(value * 100);

  if ( value >= 10.0)
  {
    sprintf(str, "+%02d%02d\n", intValue / 100, abs(intValue % 100));
  }
  else if (value > 0.0 && value < 10.0)
  {
    sprintf(str, "+%02d%02d\n", intValue / 100, abs(intValue % 100));
  }
  else if (value < 0.0 && value > -1.0)
  {
    sprintf(str, "-%02d%02d\n", intValue / 100, abs(intValue % 100));
  }
  else if (value <= -1.0)
  {
    sprintf(str, "%03d%02d\n", intValue / 100, abs(intValue % 100));
  }
return str;

}


void get_linear_velocity(const geometry_msgs::Twist& cmdVel)
{
  if (cmdVel.angular.z != 0 && cmdVel.linear.x != 0) {
    SetPoint = (atan((cmdVel.angular.z) * (WHEEL_BASE_H / cmdVel.linear.x)));
    // SetPoint=1.0;
  }
  else if (cmdVel.angular.z == 0)
  {
    SetPoint = 0;
  }

  if (SetPoint <= -0.01 && SetPoint >= -0.03)
  {
    SetPoint = -0.01;
  }

  double input = SetPoint + 0.01;
  char* formattedString1 = formatDouble1(input);
  Serial1.print(formattedString1);


  double input1 = (cmdVel.linear.x / cos(STEERING_angle)) + 0.01;
  double input2 = STEERING_angle + 0.01;
  char* formattedString2 = formatDouble2(input1, input2);
  Serial2.print(formattedString2);
}

// Set up ROS subscriber to the velocity command
ros::Subscriber<geometry_msgs::Twist> subCmdVel("cmd_vel", &get_linear_velocity );

void setup()
{
  //  Serial.begin(115200);

  nh.getHardware()->setBaud(115200);
  nh.initNode();
  nh.advertise(rightPub);
  nh.advertise(leftPub);
  ////    nh.advertise(steering_setpoint_pub);
  nh.subscribe(subCmdVel);
  Serial1.begin(115200);
  Serial2.begin(115200);   // Configure the UART pins and baud rate
}

void loop()
{
  nh.spinOnce();
  //    Calc_Set_point();
  //  if (Serial.available() ) {
  //    // read the incoming byte:
  //    String input = Serial.readStringUntil('\n');// Read the input as a string
  //    double x = atof(input.c_str());
  //    SetPoint = x;
  //  }
  // STEERING_angle=0.0;
if (Serial1.available() ) {
    String input = Serial1.readStringUntil('\n'); // Read the input as a string
    double x = atof(input.c_str());
STEERING_angle = x/100.0;
  }


  if (Serial2.available() ) {
    String input = Serial2.readStringUntil('\n'); // Read the input as a string
    int number1, number2;
    sscanf(input.c_str(), "%d%d", &number1, &number2);
    right_wheel_tick_count.data = number1 - 1.0;
    left_wheel_tick_count.data = number2 - 1.0;
  }

  //  Serial.print(Right_Tick_recive);
  //  Serial.print("   ");
  //  Serial.print(Left_Tick_recive);
  //  Serial.print("   ");
  //  Serial.println(formattedString);

  leftPub.publish( &left_wheel_tick_count );
  rightPub.publish( &right_wheel_tick_count );
  ////    steering_setpoint_pub.publish(&steering_setpoint);

}
