;; Auto-generated. Do not edit!


(when (boundp 'position_msgs::ObjectPositions)
  (if (not (find-package "POSITION_MSGS"))
    (make-package "POSITION_MSGS"))
  (shadow 'ObjectPositions (find-package "POSITION_MSGS")))
(unless (find-package "POSITION_MSGS::OBJECTPOSITIONS")
  (make-package "POSITION_MSGS::OBJECTPOSITIONS"))

(in-package "ROS")
;;//! \htmlinclude ObjectPositions.msg.html
(if (not (find-package "STD_MSGS"))
  (ros::roseus-add-msgs "std_msgs"))


(defclass position_msgs::ObjectPositions
  :super ros::object
  :slots (_header _object_positions ))

(defmethod position_msgs::ObjectPositions
  (:init
   (&key
    ((:header __header) (instance std_msgs::Header :init))
    ((:object_positions __object_positions) (let (r) (dotimes (i 0) (push (instance position_msgs::ObjectPosition :init) r)) r))
    )
   (send-super :init)
   (setq _header __header)
   (setq _object_positions __object_positions)
   self)
  (:header
   (&rest __header)
   (if (keywordp (car __header))
       (send* _header __header)
     (progn
       (if __header (setq _header (car __header)))
       _header)))
  (:object_positions
   (&rest __object_positions)
   (if (keywordp (car __object_positions))
       (send* _object_positions __object_positions)
     (progn
       (if __object_positions (setq _object_positions (car __object_positions)))
       _object_positions)))
  (:serialization-length
   ()
   (+
    ;; std_msgs/Header _header
    (send _header :serialization-length)
    ;; position_msgs/ObjectPosition[] _object_positions
    (apply #'+ (send-all _object_positions :serialization-length)) 4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; std_msgs/Header _header
       (send _header :serialize s)
     ;; position_msgs/ObjectPosition[] _object_positions
     (write-long (length _object_positions) s)
     (dolist (elem _object_positions)
       (send elem :serialize s)
       )
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; std_msgs/Header _header
     (send _header :deserialize buf ptr-) (incf ptr- (send _header :serialization-length))
   ;; position_msgs/ObjectPosition[] _object_positions
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _object_positions (let (r) (dotimes (i n) (push (instance position_msgs::ObjectPosition :init) r)) r))
     (dolist (elem- _object_positions)
     (send elem- :deserialize buf ptr-) (incf ptr- (send elem- :serialization-length))
     ))
   ;;
   self)
  )

(setf (get position_msgs::ObjectPositions :md5sum-) "81cb5bcd0e3ca25231cb43df334f871f")
(setf (get position_msgs::ObjectPositions :datatype-) "position_msgs/ObjectPositions")
(setf (get position_msgs::ObjectPositions :definition-)
      "Header header
ObjectPosition[] object_positions

================================================================================
MSG: std_msgs/Header
# Standard metadata for higher-level stamped data types.
# This is generally used to communicate timestamped data 
# in a particular coordinate frame.
# 
# sequence ID: consecutively increasing ID 
uint32 seq
#Two-integer timestamp that is expressed as:
# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')
# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')
# time-handling sugar is provided by the client library
time stamp
#Frame this data is associated with
string frame_id

================================================================================
MSG: position_msgs/ObjectPosition
string Class
int64 x
int64 y
int64 z

")



(provide :position_msgs/ObjectPositions "81cb5bcd0e3ca25231cb43df334f871f")


