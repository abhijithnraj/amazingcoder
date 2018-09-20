#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Thu Sep 20 09:43:38 2018

@author: abhijith
"""

import numpy as np

n=np.array([i for i in range(-1,2)])
print(n)
y=[1,2,-2]
import matplotlib.pyplot as plt

def x(t,l):
    plt.scatter(t,y)
    plt.plot(t,y,linestyle='dashed',label=l)
x(n,'x(n)')  #what should be applied to n-1 to make it n
x(n+1,'x(n-1)')
plt.plot()

#for -n-1

plt.legend()
plt.plot()