; Auto-generated. Do not edit!


(cl:in-package ros_odrive-msg)


;//! \htmlinclude odrive_msg.msg.html

(cl:defclass <odrive_msg> (roslisp-msg-protocol:ros-message)
  ((target
    :reader target
    :initarg :target
    :type cl:fixnum
    :initform 0)
   (vbus
    :reader vbus
    :initarg :vbus
    :type cl:float
    :initform 0.0)
   (error0
    :reader error0
    :initarg :error0
    :type cl:integer
    :initform 0)
   (state0
    :reader state0
    :initarg :state0
    :type cl:integer
    :initform 0)
   (vel0
    :reader vel0
    :initarg :vel0
    :type cl:float
    :initform 0.0)
   (pos0
    :reader pos0
    :initarg :pos0
    :type cl:float
    :initform 0.0)
   (curr0B
    :reader curr0B
    :initarg :curr0B
    :type cl:float
    :initform 0.0)
   (curr0C
    :reader curr0C
    :initarg :curr0C
    :type cl:float
    :initform 0.0)
   (temp0
    :reader temp0
    :initarg :temp0
    :type cl:float
    :initform 0.0)
   (error1
    :reader error1
    :initarg :error1
    :type cl:integer
    :initform 0)
   (state1
    :reader state1
    :initarg :state1
    :type cl:integer
    :initform 0)
   (vel1
    :reader vel1
    :initarg :vel1
    :type cl:float
    :initform 0.0)
   (pos1
    :reader pos1
    :initarg :pos1
    :type cl:float
    :initform 0.0)
   (curr1B
    :reader curr1B
    :initarg :curr1B
    :type cl:float
    :initform 0.0)
   (curr1C
    :reader curr1C
    :initarg :curr1C
    :type cl:float
    :initform 0.0)
   (temp1
    :reader temp1
    :initarg :temp1
    :type cl:float
    :initform 0.0))
)

(cl:defclass odrive_msg (<odrive_msg>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <odrive_msg>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'odrive_msg)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name ros_odrive-msg:<odrive_msg> is deprecated: use ros_odrive-msg:odrive_msg instead.")))

(cl:ensure-generic-function 'target-val :lambda-list '(m))
(cl:defmethod target-val ((m <odrive_msg>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader ros_odrive-msg:target-val is deprecated.  Use ros_odrive-msg:target instead.")
  (target m))

(cl:ensure-generic-function 'vbus-val :lambda-list '(m))
(cl:defmethod vbus-val ((m <odrive_msg>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader ros_odrive-msg:vbus-val is deprecated.  Use ros_odrive-msg:vbus instead.")
  (vbus m))

(cl:ensure-generic-function 'error0-val :lambda-list '(m))
(cl:defmethod error0-val ((m <odrive_msg>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader ros_odrive-msg:error0-val is deprecated.  Use ros_odrive-msg:error0 instead.")
  (error0 m))

(cl:ensure-generic-function 'state0-val :lambda-list '(m))
(cl:defmethod state0-val ((m <odrive_msg>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader ros_odrive-msg:state0-val is deprecated.  Use ros_odrive-msg:state0 instead.")
  (state0 m))

(cl:ensure-generic-function 'vel0-val :lambda-list '(m))
(cl:defmethod vel0-val ((m <odrive_msg>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader ros_odrive-msg:vel0-val is deprecated.  Use ros_odrive-msg:vel0 instead.")
  (vel0 m))

(cl:ensure-generic-function 'pos0-val :lambda-list '(m))
(cl:defmethod pos0-val ((m <odrive_msg>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader ros_odrive-msg:pos0-val is deprecated.  Use ros_odrive-msg:pos0 instead.")
  (pos0 m))

(cl:ensure-generic-function 'curr0B-val :lambda-list '(m))
(cl:defmethod curr0B-val ((m <odrive_msg>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader ros_odrive-msg:curr0B-val is deprecated.  Use ros_odrive-msg:curr0B instead.")
  (curr0B m))

(cl:ensure-generic-function 'curr0C-val :lambda-list '(m))
(cl:defmethod curr0C-val ((m <odrive_msg>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader ros_odrive-msg:curr0C-val is deprecated.  Use ros_odrive-msg:curr0C instead.")
  (curr0C m))

(cl:ensure-generic-function 'temp0-val :lambda-list '(m))
(cl:defmethod temp0-val ((m <odrive_msg>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader ros_odrive-msg:temp0-val is deprecated.  Use ros_odrive-msg:temp0 instead.")
  (temp0 m))

(cl:ensure-generic-function 'error1-val :lambda-list '(m))
(cl:defmethod error1-val ((m <odrive_msg>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader ros_odrive-msg:error1-val is deprecated.  Use ros_odrive-msg:error1 instead.")
  (error1 m))

(cl:ensure-generic-function 'state1-val :lambda-list '(m))
(cl:defmethod state1-val ((m <odrive_msg>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader ros_odrive-msg:state1-val is deprecated.  Use ros_odrive-msg:state1 instead.")
  (state1 m))

(cl:ensure-generic-function 'vel1-val :lambda-list '(m))
(cl:defmethod vel1-val ((m <odrive_msg>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader ros_odrive-msg:vel1-val is deprecated.  Use ros_odrive-msg:vel1 instead.")
  (vel1 m))

(cl:ensure-generic-function 'pos1-val :lambda-list '(m))
(cl:defmethod pos1-val ((m <odrive_msg>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader ros_odrive-msg:pos1-val is deprecated.  Use ros_odrive-msg:pos1 instead.")
  (pos1 m))

(cl:ensure-generic-function 'curr1B-val :lambda-list '(m))
(cl:defmethod curr1B-val ((m <odrive_msg>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader ros_odrive-msg:curr1B-val is deprecated.  Use ros_odrive-msg:curr1B instead.")
  (curr1B m))

(cl:ensure-generic-function 'curr1C-val :lambda-list '(m))
(cl:defmethod curr1C-val ((m <odrive_msg>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader ros_odrive-msg:curr1C-val is deprecated.  Use ros_odrive-msg:curr1C instead.")
  (curr1C m))

(cl:ensure-generic-function 'temp1-val :lambda-list '(m))
(cl:defmethod temp1-val ((m <odrive_msg>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader ros_odrive-msg:temp1-val is deprecated.  Use ros_odrive-msg:temp1 instead.")
  (temp1 m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <odrive_msg>) ostream)
  "Serializes a message object of type '<odrive_msg>"
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'target)) ostream)
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'vbus))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let* ((signed (cl:slot-value msg 'error0)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
  (cl:let* ((signed (cl:slot-value msg 'state0)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'vel0))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'pos0))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'curr0B))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'curr0C))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'temp0))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let* ((signed (cl:slot-value msg 'error1)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
  (cl:let* ((signed (cl:slot-value msg 'state1)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'vel1))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'pos1))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'curr1B))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'curr1C))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'temp1))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <odrive_msg>) istream)
  "Deserializes a message object of type '<odrive_msg>"
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'target)) (cl:read-byte istream))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'vbus) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'error0) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'state0) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'vel0) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'pos0) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'curr0B) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'curr0C) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'temp0) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'error1) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'state1) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'vel1) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'pos1) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'curr1B) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'curr1C) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'temp1) (roslisp-utils:decode-single-float-bits bits)))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<odrive_msg>)))
  "Returns string type for a message object of type '<odrive_msg>"
  "ros_odrive/odrive_msg")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'odrive_msg)))
  "Returns string type for a message object of type 'odrive_msg"
  "ros_odrive/odrive_msg")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<odrive_msg>)))
  "Returns md5sum for a message object of type '<odrive_msg>"
  "eb65cc10642e566cfb0f9b5b6bce62b3")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'odrive_msg)))
  "Returns md5sum for a message object of type 'odrive_msg"
  "eb65cc10642e566cfb0f9b5b6bce62b3")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<odrive_msg>)))
  "Returns full string definition for message of type '<odrive_msg>"
  (cl:format cl:nil "#Header header    # ROS Message headaer~%~%uint8 target      # Target~%~%float32 vbus      # Bus voltage~%~%int32 error0      # Axis 0 error~%int32 state0      # Axis 0 state~%float32 vel0      # Axis 0 velocity ~%float32 pos0      # Axis 0 encoder position~%float32 curr0B    # Axis 0 motor channel B current~%float32 curr0C    # Axis 0 motor channel C current~%float32 temp0     # Axis 0 invertr temperature~%~%int32 error1      # Axis 1 error~%int32 state1      # Axis 1 state~%float32 vel1      # Axis 1 velocity ~%float32 pos1      # Axis 1 encoder position~%float32 curr1B    # Axis 1 motor channel B current~%float32 curr1C    # Axis 1 motor channel C current~%float32 temp1     # Axis 1 inverter temperature~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'odrive_msg)))
  "Returns full string definition for message of type 'odrive_msg"
  (cl:format cl:nil "#Header header    # ROS Message headaer~%~%uint8 target      # Target~%~%float32 vbus      # Bus voltage~%~%int32 error0      # Axis 0 error~%int32 state0      # Axis 0 state~%float32 vel0      # Axis 0 velocity ~%float32 pos0      # Axis 0 encoder position~%float32 curr0B    # Axis 0 motor channel B current~%float32 curr0C    # Axis 0 motor channel C current~%float32 temp0     # Axis 0 invertr temperature~%~%int32 error1      # Axis 1 error~%int32 state1      # Axis 1 state~%float32 vel1      # Axis 1 velocity ~%float32 pos1      # Axis 1 encoder position~%float32 curr1B    # Axis 1 motor channel B current~%float32 curr1C    # Axis 1 motor channel C current~%float32 temp1     # Axis 1 inverter temperature~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <odrive_msg>))
  (cl:+ 0
     1
     4
     4
     4
     4
     4
     4
     4
     4
     4
     4
     4
     4
     4
     4
     4
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <odrive_msg>))
  "Converts a ROS message object to a list"
  (cl:list 'odrive_msg
    (cl:cons ':target (target msg))
    (cl:cons ':vbus (vbus msg))
    (cl:cons ':error0 (error0 msg))
    (cl:cons ':state0 (state0 msg))
    (cl:cons ':vel0 (vel0 msg))
    (cl:cons ':pos0 (pos0 msg))
    (cl:cons ':curr0B (curr0B msg))
    (cl:cons ':curr0C (curr0C msg))
    (cl:cons ':temp0 (temp0 msg))
    (cl:cons ':error1 (error1 msg))
    (cl:cons ':state1 (state1 msg))
    (cl:cons ':vel1 (vel1 msg))
    (cl:cons ':pos1 (pos1 msg))
    (cl:cons ':curr1B (curr1B msg))
    (cl:cons ':curr1C (curr1C msg))
    (cl:cons ':temp1 (temp1 msg))
))
