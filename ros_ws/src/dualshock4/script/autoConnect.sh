#!/bin/bash
# Toggle connection to bluetooth device

mac="49:FA:A3:81:1C:A5" #Stik Robot Gadjah
# mac="D6:36:14:7F:6B:1B" #Stik Robot Kelinci

rfkill unblock bluetooth

while :
do
    gnome-control-center bluetooth &
    if bluetoothctl info "$mac" | grep -q 'Connected: no'; then
        if bluetoothctl info "$mac" | grep -q 'Paired: yes'; then
            bluetoothctl remove "$mac"
        fi
    	rfkill unblock bluetooth
        #bluetoothctl power on

    	bluetoothctl pair "$mac"
    	bluetoothctl connect "$mac"
    fi
    sleep 10
done