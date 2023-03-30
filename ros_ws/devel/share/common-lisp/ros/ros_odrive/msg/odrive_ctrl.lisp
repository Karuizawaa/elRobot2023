; Auto-generated. Do not edit!


(cl:in-package ros_odrive-msg)


;//! \htmlinclude odrive_ctrl.msg.html

(cl:defclass <odrive_ctrl> (roslisp-msg-protocol:ros-message)
  ((target
    :reader target
    :initarg :target
    :type cl:fixnum
    :initform 0)
   (command
    :reader command
    :initarg :command
    :type cl:integer
    :initform 0)
   (axis
    :reader axis
    :initarg :axis
    :type cl:fixnum
    :initform 0)
   (fval
    :reader fval
    :initarg :fval
    :type cl:float
    :initform 0.0)
   (fval2
    :reader fval2
    :initarg :fval2
    :type cl:float
    :initform 0.0))
)

(cl:defclass odrive_ctrl (<odrive_ctrl>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <odrive_ctrl>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'odrive_ctrl)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name ros_odrive-msg:<odrive_ctrl> is deprecated: use ros_odrive-msg:odrive_ctrl instead.")))

(cl:ensure-generic-function 'target-val :lambda-list '(m))
(cl:defmethod target-val ((m <odrive_ctrl>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader ros_odrive-msg:target-val is deprecated.  Use ros_odrive-msg:target instead.")
  (target m))

(cl:ensure-generic-function 'command-val :lambda-list '(m))
(cl:defmethod command-val ((m <odrive_ctrl>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader ros_odrive-msg:command-val is deprecated.  Use ros_odrive-msg:command instead.")
  (command m))

(cl:ensure-generic-function 'axis-val :lambda-list '(m))
(cl:defmethod axis-val ((m <odrive_ctrl>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader ros_odrive-msg:axis-val is deprecated.  Use ros_odrive-msg:axis instead.")
  (axis m))

(cl:ensure-generic-function 'fval-val :lambda-list '(m))
(cl:defmethod fval-val ((m <odrive_ctrl>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader ros_odrive-msg:fval-val is deprecated.  Use ros_odrive-msg:fval instead.")
  (fval m))

(cl:ensure-generic-function 'fval2-val :lambda-list '(m))
(cl:defmethod fval2-val ((m <odrive_ctrl>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader ros_odrive-msg:fval2-val is deprecated.  Use ros_odrive-msg:fval2 instead.")
  (fval2 m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <odrive_ctrl>) ostream)
  "Serializes a message object of type '<odrive_ctrl>"
  (cl:let* ((signed (cl:slot-value msg 'target)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 256) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    )
  (cl:let* ((signed (cl:slot-value msg 'command)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'axis)) ostream)
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'fval))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'fval2))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <odrive_ctrl>) istream)
  "Deserializes a message object of type '<odrive_ctrl>"
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'target) (cl:if (cl:< unsigned 128) unsigned (cl:- unsigned 256))))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'command) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'axis)) (cl:read-byte istream))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'fval) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'fval2) (roslisp-utils:decode-single-float-bits bits)))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<odrive_ctrl>)))
  "Returns string type for a message object of type '<odrive_ctrl>"
  "ros_odrive/odrive_ctrl")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'odrive_ctrl)))
  "Returns string type for a message object of type 'odrive_ctrl"
  "ros_odrive/odrive_ctrl")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<odrive_ctrl>)))
  "Returns md5sum for a message object of type '<odrive_ctrl>"
  "11157a5f66bebeef0ff837893ae31cd8")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'odrive_ctrl)))
  "Returns md5sum for a message object of type 'odrive_ctrl"
  "11157a5f66bebeef0ff837893ae31cd8")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<odrive_ctrl>)))
  "Returns full string definition for message of type '<odrive_ctrl>"
  (cl:format cl:nil "#Header header    # ROS Message headaer~%~%int8 target     # target~%~%int32 command   # Command ID~%uint8 axis      # Axis number~%float32 fval    # Float value ~%float32 fval2   # Float second value (in case of dual axis command)~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'odrive_ctrl)))
  "Returns full string definition for message of type 'odrive_ctrl"
  (cl:format cl:nil "#Header header    # ROS Message headaer~%~%int8 target     # target~%~%int32 command   # Command ID~%uint8 axis      # Axis number~%float32 fval    # Float value ~%float32 fval2   # Float second value (in case of dual axis command)~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <odrive_ctrl>))
  (cl:+ 0
     1
     4
     1
     4
     4
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <odrive_ctrl>))
  "Converts a ROS message object to a list"
  (cl:list 'odrive_ctrl
    (cl:cons ':target (target msg))
    (cl:cons ':command (command msg))
    (cl:cons ':axis (axis msg))
    (cl:cons ':fval (fval msg))
    (cl:cons ':fval2 (fval2 msg))
))
