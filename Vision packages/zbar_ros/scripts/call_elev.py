#!/usr/bin/env python
import  rospy
from std_msgs.msg import UInt16
from std_msgs.msg import String

rospy.init_node("Call_elev")
pub = rospy.Publisher("servo", UInt16, queue_size=1)

def callback(kinect_data):
    #if kinect_data == 'A':
    pub.publish(130)
    rospy.sleep(5)
    pub.publish(0)
    rospy.sleep(20)
    #print(kinect_data)
    
	
rospy.Subscriber("barcode",String,callback)
rospy.spin()
