;; Auto-generated. Do not edit!


(when (boundp 'ros_odrive::odrive_ctrl)
  (if (not (find-package "ROS_ODRIVE"))
    (make-package "ROS_ODRIVE"))
  (shadow 'odrive_ctrl (find-package "ROS_ODRIVE")))
(unless (find-package "ROS_ODRIVE::ODRIVE_CTRL")
  (make-package "ROS_ODRIVE::ODRIVE_CTRL"))

(in-package "ROS")
;;//! \htmlinclude odrive_ctrl.msg.html


(defclass ros_odrive::odrive_ctrl
  :super ros::object
  :slots (_target _command _axis _fval _fval2 ))

(defmethod ros_odrive::odrive_ctrl
  (:init
   (&key
    ((:target __target) 0)
    ((:command __command) 0)
    ((:axis __axis) 0)
    ((:fval __fval) 0.0)
    ((:fval2 __fval2) 0.0)
    )
   (send-super :init)
   (setq _target (round __target))
   (setq _command (round __command))
   (setq _axis (round __axis))
   (setq _fval (float __fval))
   (setq _fval2 (float __fval2))
   self)
  (:target
   (&optional __target)
   (if __target (setq _target __target)) _target)
  (:command
   (&optional __command)
   (if __command (setq _command __command)) _command)
  (:axis
   (&optional __axis)
   (if __axis (setq _axis __axis)) _axis)
  (:fval
   (&optional __fval)
   (if __fval (setq _fval __fval)) _fval)
  (:fval2
   (&optional __fval2)
   (if __fval2 (setq _fval2 __fval2)) _fval2)
  (:serialization-length
   ()
   (+
    ;; int8 _target
    1
    ;; int32 _command
    4
    ;; uint8 _axis
    1
    ;; float32 _fval
    4
    ;; float32 _fval2
    4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; int8 _target
       (write-byte _target s)
     ;; int32 _command
       (write-long _command s)
     ;; uint8 _axis
       (write-byte _axis s)
     ;; float32 _fval
       (sys::poke _fval (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _fval2
       (sys::poke _fval2 (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; int8 _target
     (setq _target (sys::peek buf ptr- :char)) (incf ptr- 1)
     (if (> _target 127) (setq _target (- _target 256)))
   ;; int32 _command
     (setq _command (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; uint8 _axis
     (setq _axis (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; float32 _fval
     (setq _fval (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _fval2
     (setq _fval2 (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;;
   self)
  )

(setf (get ros_odrive::odrive_ctrl :md5sum-) "11157a5f66bebeef0ff837893ae31cd8")
(setf (get ros_odrive::odrive_ctrl :datatype-) "ros_odrive/odrive_ctrl")
(setf (get ros_odrive::odrive_ctrl :definition-)
      "#Header header    # ROS Message headaer

int8 target     # target

int32 command   # Command ID
uint8 axis      # Axis number
float32 fval    # Float value 
float32 fval2   # Float second value (in case of dual axis command)


")



(provide :ros_odrive/odrive_ctrl "11157a5f66bebeef0ff837893ae31cd8")


