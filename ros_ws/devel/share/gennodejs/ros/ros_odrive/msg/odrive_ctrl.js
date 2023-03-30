// Auto-generated. Do not edit!

// (in-package ros_odrive.msg)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;

//-----------------------------------------------------------

class odrive_ctrl {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.target = null;
      this.command = null;
      this.axis = null;
      this.fval = null;
      this.fval2 = null;
    }
    else {
      if (initObj.hasOwnProperty('target')) {
        this.target = initObj.target
      }
      else {
        this.target = 0;
      }
      if (initObj.hasOwnProperty('command')) {
        this.command = initObj.command
      }
      else {
        this.command = 0;
      }
      if (initObj.hasOwnProperty('axis')) {
        this.axis = initObj.axis
      }
      else {
        this.axis = 0;
      }
      if (initObj.hasOwnProperty('fval')) {
        this.fval = initObj.fval
      }
      else {
        this.fval = 0.0;
      }
      if (initObj.hasOwnProperty('fval2')) {
        this.fval2 = initObj.fval2
      }
      else {
        this.fval2 = 0.0;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type odrive_ctrl
    // Serialize message field [target]
    bufferOffset = _serializer.int8(obj.target, buffer, bufferOffset);
    // Serialize message field [command]
    bufferOffset = _serializer.int32(obj.command, buffer, bufferOffset);
    // Serialize message field [axis]
    bufferOffset = _serializer.uint8(obj.axis, buffer, bufferOffset);
    // Serialize message field [fval]
    bufferOffset = _serializer.float32(obj.fval, buffer, bufferOffset);
    // Serialize message field [fval2]
    bufferOffset = _serializer.float32(obj.fval2, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type odrive_ctrl
    let len;
    let data = new odrive_ctrl(null);
    // Deserialize message field [target]
    data.target = _deserializer.int8(buffer, bufferOffset);
    // Deserialize message field [command]
    data.command = _deserializer.int32(buffer, bufferOffset);
    // Deserialize message field [axis]
    data.axis = _deserializer.uint8(buffer, bufferOffset);
    // Deserialize message field [fval]
    data.fval = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [fval2]
    data.fval2 = _deserializer.float32(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    return 14;
  }

  static datatype() {
    // Returns string type for a message object
    return 'ros_odrive/odrive_ctrl';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '11157a5f66bebeef0ff837893ae31cd8';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    #Header header    # ROS Message headaer
    
    int8 target     # target
    
    int32 command   # Command ID
    uint8 axis      # Axis number
    float32 fval    # Float value 
    float32 fval2   # Float second value (in case of dual axis command)
    
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new odrive_ctrl(null);
    if (msg.target !== undefined) {
      resolved.target = msg.target;
    }
    else {
      resolved.target = 0
    }

    if (msg.command !== undefined) {
      resolved.command = msg.command;
    }
    else {
      resolved.command = 0
    }

    if (msg.axis !== undefined) {
      resolved.axis = msg.axis;
    }
    else {
      resolved.axis = 0
    }

    if (msg.fval !== undefined) {
      resolved.fval = msg.fval;
    }
    else {
      resolved.fval = 0.0
    }

    if (msg.fval2 !== undefined) {
      resolved.fval2 = msg.fval2;
    }
    else {
      resolved.fval2 = 0.0
    }

    return resolved;
    }
};

module.exports = odrive_ctrl;
