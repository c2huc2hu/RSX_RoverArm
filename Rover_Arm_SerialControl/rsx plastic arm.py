import serial, time
import pygame

# INITIALIZE SERIAL PORT
for i in range(10):
    try:
        ser = serial.Serial(i)
        print("Connected to port COM", i - 1)
        break
    except serial.SerialException:
        pass

# INTIALIZE PYGAME
pygame.init()
try:
    joystick = pygame.joystick.Joystick(0)
    joystick.init()
except Exception:
    raise Exception("Joystick not connected")
clock = pygame.time.Clock()

STANDARD = 0
READING = 1
STORED = 2
VERTICAL = 3
NUM_POSITIONS = 4

preset_positions = {STANDARD : bytearray([255, 120, 135, 90]),
                    READING : bytearray([255, 90, 70, 90]),
                    STORED : bytearray([255, 0, 180, 90]),
                    VERTICAL : bytearray([255, 90, 180, 90])}

joints = [90, 120, 135, 90]  # angles of each of the joints

def to_bytearray(arr):
    b = []
    for i in arr:
        b.append(int(i))
    return bytearray(b)

while(True):
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            quit()
    pygame.event.pump()
    
    for i in range(NUM_POSITIONS):
        if joystick.get_button(i):
            # Use a preconfigured position
            ser.write(str(preset_positions[i]))
            for i in range(len(joints)):
                joints[i] = int(preset_positions[i])
            break

    move_joints = False # flag indicating whether any joints should be moved. 
    for i in range(4):
        if abs(joystick.get_axis(i)) > 0.1:  # eliminate noise
            joints[i] += joystick.get_axis(i)
            move_joints = True
    ser.write(str(to_bytearray(joints)))
    print(to_bytearray(joints))
