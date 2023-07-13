; Auto-generated. Do not edit!


(cl:in-package position_msgs-msg)


;//! \htmlinclude ObjectPositions.msg.html

(cl:defclass <ObjectPositions> (roslisp-msg-protocol:ros-message)
  ((header
    :reader header
    :initarg :header
    :type std_msgs-msg:Header
    :initform (cl:make-instance 'std_msgs-msg:Header))
   (object_positions
    :reader object_positions
    :initarg :object_positions
    :type (cl:vector position_msgs-msg:ObjectPosition)
   :initform (cl:make-array 0 :element-type 'position_msgs-msg:ObjectPosition :initial-element (cl:make-instance 'position_msgs-msg:ObjectPosition))))
)

(cl:defclass ObjectPositions (<ObjectPositions>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <ObjectPositions>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'ObjectPositions)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name position_msgs-msg:<ObjectPositions> is deprecated: use position_msgs-msg:ObjectPositions instead.")))

(cl:ensure-generic-function 'header-val :lambda-list '(m))
(cl:defmethod header-val ((m <ObjectPositions>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader position_msgs-msg:header-val is deprecated.  Use position_msgs-msg:header instead.")
  (header m))

(cl:ensure-generic-function 'object_positions-val :lambda-list '(m))
(cl:defmethod object_positions-val ((m <ObjectPositions>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader position_msgs-msg:object_positions-val is deprecated.  Use position_msgs-msg:object_positions instead.")
  (object_positions m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <ObjectPositions>) ostream)
  "Serializes a message object of type '<ObjectPositions>"
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'header) ostream)
  (cl:let ((__ros_arr_len (cl:length (cl:slot-value msg 'object_positions))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_arr_len) ostream))
  (cl:map cl:nil #'(cl:lambda (ele) (roslisp-msg-protocol:serialize ele ostream))
   (cl:slot-value msg 'object_positions))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <ObjectPositions>) istream)
  "Deserializes a message object of type '<ObjectPositions>"
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'header) istream)
  (cl:let ((__ros_arr_len 0))
    (cl:setf (cl:ldb (cl:byte 8 0) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) __ros_arr_len) (cl:read-byte istream))
  (cl:setf (cl:slot-value msg 'object_positions) (cl:make-array __ros_arr_len))
  (cl:let ((vals (cl:slot-value msg 'object_positions)))
    (cl:dotimes (i __ros_arr_len)
    (cl:setf (cl:aref vals i) (cl:make-instance 'position_msgs-msg:ObjectPosition))
  (roslisp-msg-protocol:deserialize (cl:aref vals i) istream))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<ObjectPositions>)))
  "Returns string type for a message object of type '<ObjectPositions>"
  "position_msgs/ObjectPositions")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'ObjectPositions)))
  "Returns string type for a message object of type 'ObjectPositions"
  "position_msgs/ObjectPositions")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<ObjectPositions>)))
  "Returns md5sum for a message object of type '<ObjectPositions>"
  "81cb5bcd0e3ca25231cb43df334f871f")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'ObjectPositions)))
  "Returns md5sum for a message object of type 'ObjectPositions"
  "81cb5bcd0e3ca25231cb43df334f871f")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<ObjectPositions>)))
  "Returns full string definition for message of type '<ObjectPositions>"
  (cl:format cl:nil "Header header~%ObjectPosition[] object_positions~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%string frame_id~%~%================================================================================~%MSG: position_msgs/ObjectPosition~%string Class~%int64 x~%int64 y~%int64 z~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'ObjectPositions)))
  "Returns full string definition for message of type 'ObjectPositions"
  (cl:format cl:nil "Header header~%ObjectPosition[] object_positions~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%string frame_id~%~%================================================================================~%MSG: position_msgs/ObjectPosition~%string Class~%int64 x~%int64 y~%int64 z~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <ObjectPositions>))
  (cl:+ 0
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'header))
     4 (cl:reduce #'cl:+ (cl:slot-value msg 'object_positions) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ (roslisp-msg-protocol:serialization-length ele))))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <ObjectPositions>))
  "Converts a ROS message object to a list"
  (cl:list 'ObjectPositions
    (cl:cons ':header (header msg))
    (cl:cons ':object_positions (object_positions msg))
))
