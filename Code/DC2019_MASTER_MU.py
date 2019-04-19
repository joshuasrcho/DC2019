import serial
import string

WIDTH = 576  # Board is 6ft x 6ft. Increment by 0.125 inch
HEIGHT = 576
TITLE = "Battleship"
c = 0
x = [0]*100  # list of size 100 initialized to 0
analog = 0
targetx = 1000
targety = 1000

def draw():
    screen.fill((0, 0, 0))
    screen.draw.text(str(analog), (250, 20), color="orange", fontsize=80)  # top left to bottom right, ypos is inverted
    draw_target((targetx,targety))


def draw_target(pos):
    xpos = pos[0]
    ypos = pos[1]
    screen.draw.filled_circle((xpos, ypos), 3, (0, 255, 0))  # draw a green circle at the position


def update(dt):
    global c, HEIGHT
    global x, analog, targetx, targety
    c = (c + 1) % 256
    while ser.in_waiting:
        line = ser.read_until().strip()  # strip() removes the \r\n
        values = line.decode('ascii').split(' ')
        print(values)
        if(values[0] == 'x'):
            x[int(values[1])] = int(values[2])
            print(x)
        if(values[0] == 'a'):
            analog = int(values[1])
        if(values[0] == 'o'):
            targetx = int(values[1])
            targety = int(values[2])
            print(targetx)
            print(targety)


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
    if key.name == 'X':
        ser.write(b'x')
        print("Sent x")
    if key.name == 'C':
        ser.write(b'c')
        print("Sent c")

ser = serial.Serial('COM6', 9600)