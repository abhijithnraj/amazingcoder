#/usr/bin/python3
import matplotlib.pyplot as plt
import math
from cartesian_plane import *
build_cartesian_plane(5)
x=[i*0.1 for i in range(-40,40)]
y1=[4*math.sin(i) for i in x]
#y2=[math.sin(-i) for i in x]
y3=[4*math.sin(i-1) for i in x]
y4=[4*math.sin(i-2) for i in x]
y5=[4*math.sin(i/2) for i in x]
plt.plot(x,y1)
plt.plot(x,y3)
plt.plot(x,y4)
plt.plot(x,y5)
plt.show()

