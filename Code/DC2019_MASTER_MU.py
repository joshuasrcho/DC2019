import serial
import string

WIDTH = 576  # Board is 6ft x 6ft. Increment by 0.125 inch
HEIGHT = 576
TITLE = "Battleship"
c = 0
x = [0]*100  # list of size 100 initialized to 0
analog = 0
targetx = [1000]
targety = [1000]
barrierx = [1000]
barriery = [1000]

def draw():
    screen.fill((0, 0, 0))
    for i in range(len(targetx)):
        draw_target((targetx[i],targety[i]),(0,255,0))
    for j in range(len(barrierx)):
        draw_target((barrierx[j],barriery[j]),(255,0,0))


def draw_target(pos,color):
    xpos = pos[0]
    ypos = pos[1]
    screen.draw.filled_circle((xpos, ypos), 3, color)  # draw a green circle at the position


def update(dt):
    global c, HEIGHT
    global x, analog, targetx, targety, dotColor
    c = (c + 1) % 256
    while ser.in_waiting:
        line = ser.read_until().strip()  # strip() removes the \r\n
        values = line.decode('ascii').split(' ')
        print(values)
        if(values[0] == 'o'):
            barrierx.append(int(values[1]))
            barriery.append(int(values[2]))
        if(values[0] == 'r'):
            barrierx.append(int(values[1]))
            barriery.append(int(values[2]))
        if(values[0] == 'g'):
            targetx.append(int(values[1]))
            targety.append(int(values[2]))


def on_mouse_down(button, pos):
    print("Mouse button", button, "down at", pos)
    ser.write(b'o')
    ser.write(str(pos[0]).encode())
    ser.write(b'\n')
    ser.write(str(pos[1]).encode())
    ser.write(b'\n')

def on_mouse_up(button, pos):
    print("Mouse button", button, "up at", pos)
    ser.write(b'p')
    ser.write(b'a')

def on_key_down(key):  # key names are saved in CAPS
    if key.name == 'W':
        ser.write(b'w')
        print("Sent w")
    if key.name == 'S':
        ser.write(b's')
        print("Sent s")
    if key.name == 'A':
        ser.write(b'a')
        print("Sent a")
    if key.name == 'D':
        ser.write(b'd')
        print("Sent d")
ser = serial.Serial('COM9', 9600)
