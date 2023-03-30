from odrive_ros import odrive_interface
od = odrive_interface.ODriveInterfaceAPI()
od.connect()
od.calibrate()      # does a calibration
od.engage()         # get ready to drive
od.drive(1000,1000) # drive axis0 and axis1
od.release()        # done