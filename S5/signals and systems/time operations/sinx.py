import matplotlib.pyplot as plt
from math import sin

limit_big=40
limit_small=int(limit_big/10)+1
A=1


x_axis=[0 for i in range(-limit_big,limit_big,1)]
x=[i*0.1 for i in range(-limit_big,limit_big,1)]
x_dots=[i for i in range(-limit_small,limit_small,1)]
y_dots=[0 for i in range(-limit_small,limit_small,1)]
y1=[A*sin(t) for t in x]
y2=[A*sin(t-1) for t in x]
y3=[A*sin(t+1) for t in x]

plt.plot(x,x_axis,c="black")
plt.plot(x_axis,x,c="black")
plt.plot(x,y1)
plt.plot(x,y2)
plt.plot(x,y3)
plt.scatter(x_dots,y_dots,c="black")
plt.scatter(y_dots,x_dots,c="black")
plt.title("sin(x)")
plt.show()
