import serial
import string
import time
import numpy as np

transMat = np.array([[1,0],[0,1],[0,0]])
dimMat = np.array([[0,0],[0,72*8],[36*8,36*8],[72*8, 72*8], [72*8, 0]])
dimMatVive = [[0,0,1],[0,0,1],[0,0,1],[0,0,1],[0,0,1]]

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
posx = 0
posy = 0

grabbed = False
orientation_offset =0
space = Actor('space',midbottom = (posx, posy))

def draw():
    screen.fill((0, 1, 0))
    screen.draw.text('Hunter Luckless', (200, 20), color="orange", fontsize=30)
    screen.draw.text(str(posx), (450, 20), color="orange", fontsize=30)
    screen.draw.text(',', (465, 20), color="orange", fontsize=30)
    screen.draw.text(str(posy), (480, 20), color="orange", fontsize=30)
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
    global grabbed, posx, posy
    c = (c + 1) % 256
    while ser.in_waiting:
        line = ser.read_until().strip()  # strip() removes the \r\n
        values = line.decode('ascii').split(' ')
        if (ser.in_waiting > 10):
            ser.reset_input_buffer()
        #print(values)
        if(values[0] == 'r'):
            bx = (int(values[1]))
            by = (int(values[2]))

            position = np.array([[bx],[by],[1]])
            position = np.dot(transMat.T,position)

            bx = position.item(0)
            by = HEIGHT - position.item(1)
            barrierx.append(bx)
            barriery.append(by)
        if(values[0] == 'g'):
            vx = (int(values[1]))
            vy = (int(values[2]))

            position = np.array([[vx],[vy],[1]])
            position = np.dot(transMat.T,position)

            vx = position.item(0)
            vy = HEIGHT - position.item(1)
            targetx.append(vx)
            targety.append(vy)
        if(values[0] == 'k'):
            grabbed = True
            print("grabbed!")
        if(values[0] == 'l'):
            grabbed = False
        if(values[0] == 'p'):
            posx = (int(values[1]))
            posy = (int(values[2]))

            position = np.array([[posx],[posy],[1]])
            position = np.dot(transMat.T,position)

            posx = position.item(0)
            posy = position.item(1)

            space.pos = (posx,HEIGHT-posy)

        if(values[0] == 'i'):
            angle = int(values[1])
            space.angle = -angle - orientation_offset



def on_mouse_down(button, pos):
    print("Mouse button", button, "down at", pos)
    ser.write(b'o')
    ser.write(str(pos[0]).encode())
    ser.write(b'\n')
    ser.write(str(pos[1]).encode())
    ser.write(b'\n')

def on_key_down(key):
    global transMat
    global orientation_offset
    # key names are saved in CAPS
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
        ser.write(b'8')
        print("Sent 8")
    if key.name == 'DOWN':
        ser.write(b'9')
        print("Sent 9")

    if key.name == 'K_1':
        print(posx)
        print(posy)
        dimMatVive[0][0] = posx
        dimMatVive[0][1] = posy
        print(dimMatVive)
    if key.name == 'K_2':
        dimMatVive[1][0] = posx
        dimMatVive[1][1] = posy
        print(dimMatVive)
    if key.name == 'K_3':
        dimMatVive[2][0] = posx
        dimMatVive[2][1] = posy
        print(dimMatVive)
    if key.name == 'K_4':
        dimMatVive[3][0] = posx
        dimMatVive[3][1] = posy
        print(dimMatVive)
    if key.name == 'K_5':
        dimMatVive[4][0] = posx
        dimMatVive[4][1] = posy
        print(dimMatVive)
    if key.name == 'K_6':
        dimMatVive2 = np.array(dimMatVive)
        transMat = np.linalg.solve(np.dot(dimMatVive2.T, dimMatVive2),np.dot(dimMatVive2.T, dimMat))
        print(transMat)

    if key.name == 'K_7':
        orientation_offset += 90






ser = serial.Serial('COM5', 9600)