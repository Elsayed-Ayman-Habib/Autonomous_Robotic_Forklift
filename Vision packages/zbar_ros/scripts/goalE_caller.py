#!/usr/bin python
import  rospy
from std_msgs.msg import Bool
from std_msgs.msg import String

rospy.init_node("goalE_caller")
pub = rospy.Publisher("goalE_ZBAR_Request", Bool, queue_size=1)

def callback(kinect_data):
    check_Map1 = 'A1'
    if(check_Map1 == kinect_data.data):
        pub.publish(True)
        rospy.sleep(10)
        #print(kinect_data)
rospy.Subscriber("barcode",String,callback)
rospy.spin()
