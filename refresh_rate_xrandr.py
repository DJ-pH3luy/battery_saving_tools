#!/usr/bin/env python3

import subprocess
import time

def get_ac():
    with open('/sys/class/power_supply/AC0/online', 'r') as f:
        ac = f.read()
    return ac

def set_rate(ac):
    if ac == "1\n":
        subprocess.call('xrandr -r 144',shell=True)
        print("Set rate to 144")
    else:
        subprocess.call('xrandr -r 60',shell=True)
        print("Set rate to 60")

def gnome_animations(ac):
    if ac == "1\n":
        subprocess.call('gsettings set org.gnome.desktop.interface enable-animations true',shell=True)
        print("Enabled animations")
    else:
        subprocess.call('gsettings set org.gnome.desktop.interface enable-animations false',shell=True)
        print("Disabled animations")

if __name__ == "__main__":
    ac_old = get_ac()
    set_rate(ac_old)
    gnome_animations(ac_old)

    while True:
        time.sleep(2)
        ac_new = get_ac()
        if ac_new != ac_old:
            ### Just comment out the things you don't want/need ###
            set_rate(ac_new)
            gnome_animations(ac_new)
            ac_old = ac_new
