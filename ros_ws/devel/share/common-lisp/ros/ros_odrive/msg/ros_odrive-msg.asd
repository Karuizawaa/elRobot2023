
(cl:in-package :asdf)

(defsystem "ros_odrive-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils )
  :components ((:file "_package")
    (:file "odrive_ctrl" :depends-on ("_package_odrive_ctrl"))
    (:file "_package_odrive_ctrl" :depends-on ("_package"))
    (:file "odrive_msg" :depends-on ("_package_odrive_msg"))
    (:file "_package_odrive_msg" :depends-on ("_package"))
  ))