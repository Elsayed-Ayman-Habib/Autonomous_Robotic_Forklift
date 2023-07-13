// Auto-generated. Do not edit!

// (in-package position_msgs.msg)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;
let ObjectPosition = require('./ObjectPosition.js');
let std_msgs = _finder('std_msgs');

//-----------------------------------------------------------

class ObjectPositions {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.header = null;
      this.object_positions = null;
    }
    else {
      if (initObj.hasOwnProperty('header')) {
        this.header = initObj.header
      }
      else {
        this.header = new std_msgs.msg.Header();
      }
      if (initObj.hasOwnProperty('object_positions')) {
        this.object_positions = initObj.object_positions
      }
      else {
        this.object_positions = [];
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type ObjectPositions
    // Serialize message field [header]
    bufferOffset = std_msgs.msg.Header.serialize(obj.header, buffer, bufferOffset);
    // Serialize message field [object_positions]
    // Serialize the length for message field [object_positions]
    bufferOffset = _serializer.uint32(obj.object_positions.length, buffer, bufferOffset);
    obj.object_positions.forEach((val) => {
      bufferOffset = ObjectPosition.serialize(val, buffer, bufferOffset);
    });
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type ObjectPositions
    let len;
    let data = new ObjectPositions(null);
    // Deserialize message field [header]
    data.header = std_msgs.msg.Header.deserialize(buffer, bufferOffset);
    // Deserialize message field [object_positions]
    // Deserialize array length for message field [object_positions]
    len = _deserializer.uint32(buffer, bufferOffset);
    data.object_positions = new Array(len);
    for (let i = 0; i < len; ++i) {
      data.object_positions[i] = ObjectPosition.deserialize(buffer, bufferOffset)
    }
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    length += std_msgs.msg.Header.getMessageSize(object.header);
    object.object_positions.forEach((val) => {
      length += ObjectPosition.getMessageSize(val);
    });
    return length + 4;
  }

  static datatype() {
    // Returns string type for a message object
    return 'position_msgs/ObjectPositions';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '81cb5bcd0e3ca25231cb43df334f871f';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    Header header
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
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new ObjectPositions(null);
    if (msg.header !== undefined) {
      resolved.header = std_msgs.msg.Header.Resolve(msg.header)
    }
    else {
      resolved.header = new std_msgs.msg.Header()
    }

    if (msg.object_positions !== undefined) {
      resolved.object_positions = new Array(msg.object_positions.length);
      for (let i = 0; i < resolved.object_positions.length; ++i) {
        resolved.object_positions[i] = ObjectPosition.Resolve(msg.object_positions[i]);
      }
    }
    else {
      resolved.object_positions = []
    }

    return resolved;
    }
};

module.exports = ObjectPositions;
