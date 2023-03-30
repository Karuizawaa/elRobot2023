;; Auto-generated. Do not edit!


(when (boundp 'ros_odrive::odrive_msg)
  (if (not (find-package "ROS_ODRIVE"))
    (make-package "ROS_ODRIVE"))
  (shadow 'odrive_msg (find-package "ROS_ODRIVE")))
(unless (find-package "ROS_ODRIVE::ODRIVE_MSG")
  (make-package "ROS_ODRIVE::ODRIVE_MSG"))

(in-package "ROS")
;;//! \htmlinclude odrive_msg.msg.html


(defclass ros_odrive::odrive_msg
  :super ros::object
  :slots (_target _vbus _error0 _state0 _vel0 _pos0 _curr0B _curr0C _temp0 _error1 _state1 _vel1 _pos1 _curr1B _curr1C _temp1 ))

(defmethod ros_odrive::odrive_msg
  (:init
   (&key
    ((:target __target) 0)
    ((:vbus __vbus) 0.0)
    ((:error0 __error0) 0)
    ((:state0 __state0) 0)
    ((:vel0 __vel0) 0.0)
    ((:pos0 __pos0) 0.0)
    ((:curr0B __curr0B) 0.0)
    ((:curr0C __curr0C) 0.0)
    ((:temp0 __temp0) 0.0)
    ((:error1 __error1) 0)
    ((:state1 __state1) 0)
    ((:vel1 __vel1) 0.0)
    ((:pos1 __pos1) 0.0)
    ((:curr1B __curr1B) 0.0)
    ((:curr1C __curr1C) 0.0)
    ((:temp1 __temp1) 0.0)
    )
   (send-super :init)
   (setq _target (round __target))
   (setq _vbus (float __vbus))
   (setq _error0 (round __error0))
   (setq _state0 (round __state0))
   (setq _vel0 (float __vel0))
   (setq _pos0 (float __pos0))
   (setq _curr0B (float __curr0B))
   (setq _curr0C (float __curr0C))
   (setq _temp0 (float __temp0))
   (setq _error1 (round __error1))
   (setq _state1 (round __state1))
   (setq _vel1 (float __vel1))
   (setq _pos1 (float __pos1))
   (setq _curr1B (float __curr1B))
   (setq _curr1C (float __curr1C))
   (setq _temp1 (float __temp1))
   self)
  (:target
   (&optional __target)
   (if __target (setq _target __target)) _target)
  (:vbus
   (&optional __vbus)
   (if __vbus (setq _vbus __vbus)) _vbus)
  (:error0
   (&optional __error0)
   (if __error0 (setq _error0 __error0)) _error0)
  (:state0
   (&optional __state0)
   (if __state0 (setq _state0 __state0)) _state0)
  (:vel0
   (&optional __vel0)
   (if __vel0 (setq _vel0 __vel0)) _vel0)
  (:pos0
   (&optional __pos0)
   (if __pos0 (setq _pos0 __pos0)) _pos0)
  (:curr0B
   (&optional __curr0B)
   (if __curr0B (setq _curr0B __curr0B)) _curr0B)
  (:curr0C
   (&optional __curr0C)
   (if __curr0C (setq _curr0C __curr0C)) _curr0C)
  (:temp0
   (&optional __temp0)
   (if __temp0 (setq _temp0 __temp0)) _temp0)
  (:error1
   (&optional __error1)
   (if __error1 (setq _error1 __error1)) _error1)
  (:state1
   (&optional __state1)
   (if __state1 (setq _state1 __state1)) _state1)
  (:vel1
   (&optional __vel1)
   (if __vel1 (setq _vel1 __vel1)) _vel1)
  (:pos1
   (&optional __pos1)
   (if __pos1 (setq _pos1 __pos1)) _pos1)
  (:curr1B
   (&optional __curr1B)
   (if __curr1B (setq _curr1B __curr1B)) _curr1B)
  (:curr1C
   (&optional __curr1C)
   (if __curr1C (setq _curr1C __curr1C)) _curr1C)
  (:temp1
   (&optional __temp1)
   (if __temp1 (setq _temp1 __temp1)) _temp1)
  (:serialization-length
   ()
   (+
    ;; uint8 _target
    1
    ;; float32 _vbus
    4
    ;; int32 _error0
    4
    ;; int32 _state0
    4
    ;; float32 _vel0
    4
    ;; float32 _pos0
    4
    ;; float32 _curr0B
    4
    ;; float32 _curr0C
    4
    ;; float32 _temp0
    4
    ;; int32 _error1
    4
    ;; int32 _state1
    4
    ;; float32 _vel1
    4
    ;; float32 _pos1
    4
    ;; float32 _curr1B
    4
    ;; float32 _curr1C
    4
    ;; float32 _temp1
    4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; uint8 _target
       (write-byte _target s)
     ;; float32 _vbus
       (sys::poke _vbus (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; int32 _error0
       (write-long _error0 s)
     ;; int32 _state0
       (write-long _state0 s)
     ;; float32 _vel0
       (sys::poke _vel0 (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _pos0
       (sys::poke _pos0 (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _curr0B
       (sys::poke _curr0B (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _curr0C
       (sys::poke _curr0C (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _temp0
       (sys::poke _temp0 (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; int32 _error1
       (write-long _error1 s)
     ;; int32 _state1
       (write-long _state1 s)
     ;; float32 _vel1
       (sys::poke _vel1 (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _pos1
       (sys::poke _pos1 (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _curr1B
       (sys::poke _curr1B (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _curr1C
       (sys::poke _curr1C (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _temp1
       (sys::poke _temp1 (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; uint8 _target
     (setq _target (sys::peek buf ptr- :char)) (incf ptr- 1)
   ;; float32 _vbus
     (setq _vbus (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; int32 _error0
     (setq _error0 (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; int32 _state0
     (setq _state0 (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; float32 _vel0
     (setq _vel0 (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _pos0
     (setq _pos0 (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _curr0B
     (setq _curr0B (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _curr0C
     (setq _curr0C (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _temp0
     (setq _temp0 (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; int32 _error1
     (setq _error1 (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; int32 _state1
     (setq _state1 (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; float32 _vel1
     (setq _vel1 (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _pos1
     (setq _pos1 (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _curr1B
     (setq _curr1B (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _curr1C
     (setq _curr1C (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _temp1
     (setq _temp1 (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;;
   self)
  )

(setf (get ros_odrive::odrive_msg :md5sum-) "eb65cc10642e566cfb0f9b5b6bce62b3")
(setf (get ros_odrive::odrive_msg :datatype-) "ros_odrive/odrive_msg")
(setf (get ros_odrive::odrive_msg :definition-)
      "#Header header    # ROS Message headaer

uint8 target      # Target

float32 vbus      # Bus voltage

int32 error0      # Axis 0 error
int32 state0      # Axis 0 state
float32 vel0      # Axis 0 velocity 
float32 pos0      # Axis 0 encoder position
float32 curr0B    # Axis 0 motor channel B current
float32 curr0C    # Axis 0 motor channel C current
float32 temp0     # Axis 0 invertr temperature

int32 error1      # Axis 1 error
int32 state1      # Axis 1 state
float32 vel1      # Axis 1 velocity 
float32 pos1      # Axis 1 encoder position
float32 curr1B    # Axis 1 motor channel B current
float32 curr1C    # Axis 1 motor channel C current
float32 temp1     # Axis 1 inverter temperature


")



(provide :ros_odrive/odrive_msg "eb65cc10642e566cfb0f9b5b6bce62b3")


