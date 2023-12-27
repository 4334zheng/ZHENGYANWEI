from turtle import *

def go_to(x, y):
    up()
    goto(x, y)
    down()

def person(x, y, r):
    head(x, y, r)
    arms(x,y)
    legs(x,y)

def head(x, y, r):
    go_to(x, y)
    speed(6)
    circle(r)

def legs(x, y):
    go_to(x, y)
    right(90)
    forward(80)
    left(20)
    forward(55)
    right(20)
    forward(20)
    left(90)
    go_to(x, y-80)
    forward(30)
    right(70)
    forward(60)
    left(70)

def arms(x, y):
    go_to(x, y-30)
    forward(35)
    go_to(x, y-30)
    right(135)
    forward(30)
    left(135)

def ball(x, y, size):
    go_to(x, y)
    circle(size)

def show_figure():
    pensize(2)
    color('black')
    getscreen().tracer(10, 0)

    person(-60, 120, 20)
    ball(0, 0, 10)

    done()

if __name__ == "__main__":
    show_figure()
