import serial
import pyvjoy

import time
import pydirectinput
import threading

PORTA = "COM3"
BAUD = 115200

arduino = serial.Serial(PORTA, BAUD)

j = pyvjoy.VJoyDevice(1)

while True:
    try:
        linha = arduino.readline().decode().strip()

        x, y, z = map(int, linha.split(","))

        eixo_x = int(x * 32768 / 1023)
        eixo_y = int(y * 32768 / 1023)
        eixo_z = int(z * 32768 / 1023)

        j.set_axis(pyvjoy.HID_USAGE_X, eixo_x)
        j.set_axis(pyvjoy.HID_USAGE_Y, eixo_y)
        j.set_axis(pyvjoy.HID_USAGE_Z, eixo_z)

    except:
        pass