# C:\13-1\cps2\ble\bluetooth_module.py

import bluetooth

def discover_devices():
    devices = bluetooth.discover_devices()
    for device in devices:
        print(f"Found device: {device}")
