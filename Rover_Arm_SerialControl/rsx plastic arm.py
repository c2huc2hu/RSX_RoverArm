import serial, time
import pygame

SHOULDER_OFFSET = 222

# INITIALIZE SERIAL PORT
for i in range(10):
    try:
        ser = serial.Serial("/dev/ttyACM" + str(i))
        break
    except serial.SerialException:
        pass

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

# INITIALIZE PRESET POSITIONS
STANDARD = 0
READING = 1
STORED = 2
VERTICAL = 3
NUM_POSITIONS = 4
preset_positions = {STANDARD : bytearray([255, 120, 135, 90]),
                    READING : bytearray([255, 90, 70, 90]),
                    STORED : bytearray([255, 5, 175, 90]),
                    VERTICAL : bytearray([255, 90, 175, 90])}
                    # 255 means "ignore me"


joints = [90, 120, 220-120, 130]  # set initial angles of each of the joints
# elbow, shoulder 1, shoulder 2, base

def to_bytearray(arr):
    """
    Convert arr, an array of floats or ints to a byte array 
    """
    b = []
    for i in arr:
        b.append(int(i))
    return bytearray(b)

# Main loop
while(True):
    clock.tick(60)
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            quit()
    pygame.event.pump()

    # Check the buttons to see if the user wants a preset position
    """
    for i in range(NUM_POSITIONS):
        if joystick.get_button(i):
            # Use a preconfigured position
            for j in range(len(joints)):
                if preset_positions[i][j] != 255:  # 255 is the "ignore" flag
                    joints[j] = preset_positions[i][j]
            break
    """

    # Check the joystick axes to see if the user is using them. 
    changed = False
    for i in range(4):
        if abs(joystick.get_axis(i)) > 0.1:  # eliminate noise
            joints[i] += joystick.get_axis(i) / 5
            changed = True
        if 5 > joints[i]:
            joints[i] = 5
        if 175 < joints[i]:
            joints[i] = 175
#    joints[2] = 0
    joints[2] = SHOULDER_OFFSET - joints[1]
    
    if changed:
        ser.write(str(to_bytearray(joints)))
    print(list(to_bytearray(joints)))
