import matplotlib.pyplot as plt
import numpy as np
trainx=np.array([0,1,2,3])
trainy=np.array([4,5,6,7])
t=[i for i in range(len(trainx)-1,len(trainx)+len(trainy)-1)]

plt.plot(trainx)
plt.plot(t,trainy)
plt.show()

