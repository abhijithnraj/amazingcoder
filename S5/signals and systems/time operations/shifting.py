#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Thu Sep 20 12:36:20 2018

@author: abhijith
"""
import numpy as np
import matplotlib.pyplot as plt
x_possible_values=np.linspace(-10,10,201) #-10,-9.9,9.8 .... 9.7,9.8,9.9,10
x=np.linspace(-1,1,3) #-1,0,1 
y=np.asarray([-1,0,-2]) 

def find_label(a,b,method_name=''):
    label=''
    a_string=str(a)
    b_string=str(b)
    if(a==1):
        a_string=''
    if(a==-1):
        a_string='-'
    if(b==0):
        label='x('+a_string+'n)'
        label+=' '+method_name
        return label
    operation='+'
    if(b<0):
        b=b*-1
        b_string=str(b)
        operation='-'
    label='x('+a_string+'n'+operation+b_string+')'
    label+=' '+method_name
    return label
    


def shifted_x_abhiram_method(a,b,x,y): #for x'=ax+b
    shifted_x=[]
    for i in x_possible_values:
        if(a*i+b in x):
            shifted_x.append(i)
    return shifted_x

def shifted_x_abhijith_method(a,b,x,y): #for x'=ax+b
    shifted_x=(x-b)/a
    return shifted_x
def plot_graph(x,y,lab,plt):
    plt.scatter(x,y)
    plt.plot(x,y,label=lab,linestyle="dashed")
    return plt


a,b=-2,3 #x'=ax+b
lab=find_label(a,b)
plt=plot_graph(x,y,'x(n)',plt)

shifted_x1=shifted_x_abhiram_method(a,b,x,y)
shifted_x2=shifted_x_abhijith_method(a,b,x,y)
if(all(shifted_x1==shifted_x2)):
    plt.title("Both your methods produce same results")
else:
    plt.title("Different Answers in both your methods")

plt=plot_graph(shifted_x1,y,lab+" abhiram",plt)    #n'=1*n+2
plt=plot_graph(shifted_x2,y,lab+" abhijith",plt) #n'=-1*n-2
plt.gcf().set_size_inches(10,6)
#plt.xticks(np.linspace(-5,5,11))
plt.legend()
plt.grid()
plt.show()
            
