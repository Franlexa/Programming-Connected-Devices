# C:\13-1\cps2\main.py

from ble import bluetooth_module

def main():
    print("Discovering Bluetooth devices:")
    bluetooth_module.discover_devices()

if __name__ == "__main__":
    main()
