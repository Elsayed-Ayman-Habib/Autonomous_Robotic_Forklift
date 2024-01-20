# Autonomous_Robotic_Forklift

Our forklift prioritizes safety above all else. Its design incorporates precise sizes, tolerances, and detailed working drawings for every component. We conducted comprehensive stress analysis for optimal performance. The final product stands out with its appealing shape, exceptional finishing, and seamless assembly.

Our project involved an embedded system with one Arduino Mega microcontroller as data buffer between the Jetson TX2 and two Tiva-C boards. Following AUTOSAR standards, our system incorporated the MCAL, HAL, and APP drivers. The MCAL layer included functionalities such as DIO, PORT, ADC, PWM, INTCTRL, UART, and TIMERS, while the HAL layer focused on Encoder, Motor, and LED functionalities. The App layer featured a PID controller, parsing capabilities, and serialization techniques for efficient data transmission.

We integrated ROS for Navigation and Localization, leveraging sensor data to determine the robot's position and orientation. This framework empowered our robot to navigate complex environments with confidence, ensuring optimal path planning, obstacle avoidance, and efficient movement.

We employed computer vision techniques using a pretrained YOLO CNN for object detection and recognition. Our computer vision module included QR code detection and scanning using the zbar ROS package, enabling the robot to identify goal destinations for precise movements.

The successful integration of ROS for Navigation and Localization in our project has advanced our understanding of robotics and equipped us with the skills necessary to contribute to the future of autonomous systems. I am proud of my team's accomplishments and look forward to further exploring innovation in robotics, leveraging cutting-edge technologies like ROS to redefine human-robot interaction.

# Tutorial

### Hardware
- Nvidia Jetson TX2
- 2 Tiva-C
- Arduino Mega (as buffer)
- 2 Encoders and 2 DC motors
- Potentiometer
- Batteries (2 for system (24V-24A) - 1 for Jetson (12V-12A))
- YDLidar
- Kinect V1
- Linear Fork DC Motor
- VNH5019 DC Motor Driver
- relay module
- Emergency Stop Position

### Software
- JetPack 4.6 (For Jetson)
- Ubuntu 18.4 here.
- ROS Melodic

### 1. Setting up the Ubuntu Environment.
- 1. install sdk manager in your laptob
  2. read user guide from Nvidia jetson tx2 datasheet
  3. follow this video to complete the steps [Link of Video](https://youtu.be/Ucg5Zqm9ZMk)

### 2. Setting up the ROS repositories.
- By Opening a terminal and run the following command to configure the Ubuntu repositories:
```
sudo sh -c 'echo "deb http://packages.ros.org/ros/ubuntu $(lsb_release -sc) main" >/etc/apt/sources.list.d/ros-latest.list'
```
### 3. Setting up the ROS keys.
- By Downloading the ROS keyring and adding it to the system by running the following command:
```
curl -s https://raw.githubusercontent.com/ros/rosdistro/master/ros.asc | sudo apt-key add -
```
### 4. Updating the package lists.
- By Running the following command to update the package lists from the repositories:
```
sudo apt update
```
### 5. Desktop-Full Installation.
- ROS Melodic offers different installation options. For most users, the DesktopFull or Desktop installation is recommended as it includes the most commonly used packages for ROS development. Running the following command will install the Desktop-Full version:
```
sudo apt install ros-melodic-desktop-full
```
### 6. Initializing rosdep.
- By Running the following commands to initialize rosdep, which is used to install system dependencies for ROS packages:
```
sudo rosdep init rosdep update
```
### 7. Setting up the environment.
```
echo "source /opt/ros/melodic/setup.bash" >> ~/.bashrc source ~/.bashrc
```
### 8. Verifying the installation.
- By opening a new terminal and running the following command to check if ROS Melodic is properly installed:
```
rosversion -d
```
- The output should display melodic, confirming a successful installation

###  move_base ROS installation for Navigation stack.
- The installation commands :
```
Cd catkin_ws/src
Git clone https://github.com/ros-planning/navigation.git
```

### Teb_local_planner ROS installation. 
- The installation commands :
```
Cd catkin_ws/src
rosdep install teb_local_planner
Git clone https://github.com/rst-tu-dortmund/teb_local_planner.git
```

### robot_pose_ekf ROS installation.
- The installation commands :
```
sudo apt-get install ros-melodic-robot-pose-ekf
```

## AMCL ROS installation.
- The installation commands :
```
sudo apt-get install ros-melodic-amcl
```

### TF ROS installation.
- The installation commands:
```
Cd catkin_ws/src
Git clone https://github.com/ros/geometry
```

### installing Kinect v1 drivers and dependencies.
- Steps of installation :
 1. Install the dependencies:
```
sudo apt-get install git-core cmake freeglut3-dev pkg-config build-essential libxmu-dev libxi-dev libusb-1.0-0-dev
sudo apt-get install git-core cmake freeglut3-dev pkg-config build-essential libxmu-dev libxi-dev libusb-1.0-0-dev
```
- 2. Get the libfreenect repository from GitHub:
```
cd ~/catkin_ws/src
git clone git://github.com/OpenKinect/libfreenect.git
```
- 3. Make and install:
```
cd libfreenect
mkdir build
cd build
cmake -L ..
sudo make install
sudo ldconfig /usr/local/lib64
sudo adduser $USER video
sudo adduser $USER plugdev
```
- 4. adding some device rules:
```
sudo nano /etc/udev/rules.d/51-kinect.rules
```
- 5. generating files and running Kinect test:
```
python3 src/fwfetcher.py
sudo cp src/audios.bin /usr/local/share/libfreenect
freenect-micview
freenect-glview
```
- 6. running Kinect with ROS:
```
cd catkin_ws
catkin_make
source devel/setup
roslaunch freenect_launch freenect.launch depth_registration:=true
```

# To launch our project.
- follow this commands:
```
roslaunch freenect_launch freenect.launch depth_registration:=true
roslaunch teb_local_planner_tutorials robot_carlike_in_stage.launch #the package launch
```
# Link of Report & Presentation and Video 
- https://drive.google.com/drive/folders/1iCM8DTQ_ik3RJ6Gb64cmEPBjMHCCbpft?usp=sharing

# Final Product 
<img src="https://github.com/Elsayed-Ayman-Habib/Autonomous_Robotic_Forklift/assets/107988619/e7f68b60-7d39-44e9-9d71-92c8798ba960">

# BY:
Abdelrahman Mahmoud Ehab
Abdelrahman Mostafa Mahmoud
Abdelrhman Motawea Ali
Abedlrahman Omar Abdelhalem
Anas Ahmed Talaat
El Sayed Ayman El Sayed
Mahmoud Ayman Abdelaziz
Mahmoud Tariq Mahmoud
Mahmoud Nassef Mohamed

# Thanks our Team
<img src="https://github.com/Elsayed-Ayman-Habib/Autonomous_Robotic_Forklift/assets/107988619/925d7e94-7c8c-4a84-9a63-44f17b58ee5b">
