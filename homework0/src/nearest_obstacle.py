#! /usr/bin/env python

import rospy
from sensor_msgs.msg import LaserScan
from std_msgs.msg import String


rospy.init_node('nearest_node', anonymous=True)
pub = rospy.Publisher('nearest_ob', String, queue_size=10)
#rate = rospy.Rate(10) # 10Hz


def callback(scan_info):
    print 'callback called'
    nearest_dist = 'Nearest object at:' + str(min(scan_info.ranges))
    rospy.loginfo('about to publish info: %s', nearest_dist)
    pub.publish(nearest_dist)

def nearest():
    # subsciber
    rospy.Subscriber('base_scan', LaserScan, callback)
    rospy.loginfo(">>>>>>>>> Everything ok <<<<<<<<<")

    rospy.spin()


if __name__ == '__main__':
    try:
        nearest()
    except rospy.ROSInterruptException:
        pass

