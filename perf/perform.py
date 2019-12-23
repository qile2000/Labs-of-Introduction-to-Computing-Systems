import sys
from scipy import stats
import pandas as pd
import numpy as np
import matplotlib.pyplot as plt  

function=sys.argv[1]

timedata = pd.read_csv("./timedata",header=None,sep=',')
print(timedata.describe())
if(function=="multimod_p1" or\
   function=="multimod_p2" or\
   function=="multimod_p3"):
    timedata.columns = ["runtime(Microsecond)","a","b","m"]
else:
    timedata.columns = ["runtime(Microsecond)"]

#Kolmogorov-Smirnov
u = timedata['runtime(Microsecond)'].mean()  
std = timedata['runtime(Microsecond)'].std()  
print(stats.kstest(timedata['runtime(Microsecond)'],\
      'norm', (u, std)))
# if p > 0.05, it is norm
'''
#figure
plt.bar(timedata.index, timedata["runtime(Microsecond)"])
plt.ylabel("runtime(Microsecond)")
plt.xlabel("round")
plt.grid()
plt.show()

#a,b,m
if(function=="multimod_p1" or\
   function=="multimod_p2" or\
   function=="multimod_p3"):
    plt.scatter(timedata["a"],timedata["runtime(Microsecond)"],\
                c="red",label="a",s=2.)
    plt.scatter(timedata["b"],timedata["runtime(Microsecond)"],\
                c="green",label="b",s=2.)
    plt.scatter(timedata["m"],timedata["runtime(Microsecond)"],\
                c="blue",label="m",s=2.)
    plt.xlabel("a,b,m")
    plt.ylabel("runtime(Microsecond)")
    plt.show()
'''
#a,b bin 1
if(function=="multimod_p1" or\
   function=="multimod_p2" or\
   function=="multimod_p3"):
    a_1_num=[]
    a_1_count = 0
    b_1_num=[]
    b_1_count = 0
    for x in timedata.loc[:,"a"]:
        numx=int(x)
        while numx>0:
            if(numx&1==1):
                a_1_count=a_1_count+1
            numx>>=1
        a_1_num.append(a_1_count)
        a_1_count=0
    for y in timedata.loc[:,"b"]:
        numy=int(y)
        while numy>0:
            if(numy&1==1):
                b_1_count=b_1_count+1
            numy>>=1
        b_1_num.append(b_1_count)
        b_1_count=0
    plt.scatter(a_1_num,timedata["runtime(Microsecond)"],\
                c="red",label="a_1_num",s=4.)
    plt.scatter(b_1_num,timedata["runtime(Microsecond)"],\
                c="blue",label="b_1_num",s=4.)
    plt.xlabel("a_1_num,b_1_num")
    plt.ylabel("runtime(Microsecond)")
    plt.show()
