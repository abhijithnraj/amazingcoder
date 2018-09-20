#program created by Abhijith N Raj of R4 TKMCE to plot a log graph
from termcolor import colored
author_name = "Abhijith N Raj"
author_org  = "TKMCE"
disclosure =colored("Program created created by ","blue")+colored(author_name,"red")+"("+colored(author_org,"green")+") "+colored("to plot a logarithmic graph","blue")
print(disclosure)
 
import math
import matplotlib.pyplot as plt

#defining the limits
initial_limit,final_limit = 1,10000000000

#creating a list of x values ranging the limits
x=[i for i in range(initial_limit,final_limit,100)] + [i*0.1 for i in range(1,10)]
x.sort()
#calculating the log of all x values
y=[math.log(i) for i in x]
#adding the values to plot function
plt.plot(x,y)
#setting the labels
plt.suptitle("Logarithmic Function Graph By Abhijith N Raj", fontsize=20)
plt.xlabel('X', fontsize=15)
plt.ylabel('log(x)',fontsize=15)

#displaying the plot
plt.show()

#greetings
print(colored("Hope You enjoyed it!!. Dont forget to leave the comments","magenta"))
