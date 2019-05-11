import serial
import string
import time

black = (0, 0, 0)
white = (255, 255, 255)
blue = (0, 0, 255)
green = (0, 255, 0)
red = (255, 0, 0)
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
posx = [1000]
posy = [1000]

grabbed = False

space = Actor('space',(100 , 100))

def draw():
    screen.fill((0, 1, 0))
    screen.draw.text('Hunter Luckless', (200, 20), color="orange", fontsize=30)
    drawrect()
    drawspace()
    for i in range(len(targetx)):
        draw_target((targetx[i],targety[i]),(0,255,0))
    for j in range(len(barrierx)):
        draw_target((barrierx[j],barriery[j]),(255,0,0))
    if grabbed:
        screen.draw.text('Grabbed target!', (400, 550), color="orange", fontsize=25)

def drawspace():
    space.draw()

def drawrect():
    r1 = Rect((96, 96), (144, 144))
    r2 = Rect((336, 96), (144, 144))
    r3 = Rect((96, 336), (144, 144))
    r4 = Rect((336, 336), (144, 144))
    screen.draw.rect(r1, white)
    screen.draw.rect(r2, white)
    screen.draw.rect(r3, white)
    screen.draw.rect(r4, white)

def draw_target(pos,color):
    xpos = pos[0]
    ypos = pos[1]
    screen.draw.filled_circle((xpos, ypos), 3, color)  # draw a green circle at the position


def update(dt):
    global c, HEIGHT
    global x, analog, targetx, targety, dotColor
    global grabbed
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
        if(values[0] == 'k'):
            grabbed = True
            print("grabbed!")
        if(values[0] == 'l'):
            grabbed = False
        if(values[0] == 'p'):
            posx.append(int(values[1]))
            posy.append(int(values[1]))
        space = Actor('space',(posx[1] , posy[1]))
        posx.pop(0)
        posy.pop(0)



def on_mouse_down(button, pos):
    print("Mouse button", button, "down at", pos)
    ser.write(b'o')
    ser.write(str(pos[0]).encode())
    ser.write(b'\n')
    ser.write(str(pos[1]).encode())
    ser.write(b'\n')

def on_key_down(key):  # key names are saved in CAPS
    # Use the following keys for driving
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
    # Use the following keys for more precise movement

    # use the following keys for gripper
    if key.name == 'UP': # open gripper
        ser.write(b'0')
        print("Sent 0")
    if key.name == 'DOWN':
        ser.write(b'9')
        print("Sent 9")

ser = serial.Serial('COM5', 9600)
