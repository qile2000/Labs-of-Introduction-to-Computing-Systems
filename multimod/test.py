import random
import os
#######
from scipy import stats
import pandas as pd
import matplotlib.pyplot as plt  
#######
#p1, p2 or p3
choosen_func_no = "1 "

#run time
total_runtime = 0
MS_PER_SEC = 1000

#test instances number
test_num=50

#generate test a b m
LIMIT=2**10-1
wrong_num=0

#for condition judge

wrong_result_condition_num=0
right_result_condition_num=0
#######
alis=[]
blis=[]
mlis=[]
runtimelis=[]
#####
for i in range(test_num):
    a=random.randint(0,LIMIT)
    b=random.randint(0,LIMIT)
    m=random.randint(1,LIMIT)

########
    alis.append(a)
    blis.append(b)
    mlis.append(m)




########

    whole_command ="/home/qile/ics-workbench/multimod/main -i "+\
                   choosen_func_no+str(a)+" "+str(b)+" "+str(m)
    opened_file=os.popen(whole_command)

    result_list=opened_file.readlines()
    
    run_time=result_list[1].strip()
    total_runtime+=int(run_time)
    ####
    runtimelis.append(int(run_time))
    ####

'''
    condition=0
    lowbit=int(len(bin(a*b)))-2-52
    if((2**lowbit)<=m):
        print("lowbit:"+str(lowbit)+"\n")
        condition=1
    
    my_result=result_list[0].strip()
    if(int(my_result)!=(a*b%m)):
        wrong_num=wrong_num+1
        
        if(condition==1):
            wrong_result_condition_num=wrong_result_condition_num+1
        
        print("wrong result: "+"\n"\
              +str(a)+" * "+str(b)+" % "+str(m)+"\n"\
              +"my_result:"+str(my_result)+"\n"\
              +"right result:"+str(a*b%m)+"\n")
    else:
        
        if(condition==1):
            right_result_condition_num=right_result_condition_num+1
        
        print("right result: "+"\n"\
              +"for a:"+str(a)+" b:"+str(b)+" m:"+str(m)+"\n"\
              +"result:"+str(my_result)+"\n")
        
print("in "+str(test_num)+"tests, right times:"+str(test_num-wrong_num)+\
      ", wrong times:"+str(wrong_num)+"\n")

total_runtime=float(total_runtime)/MS_PER_SEC
print("for "+str(test_num)+"tests, total runtime is: "+str(total_runtime)+" ms\n"\
      "average time for one test is: "+str(float(total_runtime/test_num))+" ms\n")

print("for all "+str(test_num-wrong_num)+" right results, "+str(right_result_condition_num)+" of them satisfy the condition\n")
print("for all "+str(wrong_num)+" wrong results, "+str(wrong_result_condition_num)+" of them satisfy the condition\n")
'''
alist = pd.DataFrame(alis, columns=['a']) 
blist = pd.DataFrame(blis, columns=['b']) 
mlist = pd.DataFrame(mlis, columns=['m']) 
runtime = pd.DataFrame(runtimelis, columns=['r']) 
#Kolmogorov-Smirnov
u = runtime['r'].mean()  
std = runtime['r'].std()  
print(stats.kstest(runtime['r'],\
      'norm', (u, std)))
# if p > 0.05, it is norm

#figure
plt.bar(range(test_num), runtime['r'])
plt.ylabel("runtime(Microsecond)")
plt.xlabel("round")
plt.grid()
plt.show()


plt.scatter(alist['a'],runtime['r'],\
                c="red",label="a",s=2.)
plt.scatter(blist['b'],runtime['r'],\
                c="green",label="b",s=2.)
plt.scatter(mlist['m'],runtime['r'],\
                c="blue",label="m",s=2.)
plt.xlabel("a,b,m")
plt.ylabel("runtime(Microsecond)")
plt.show()

a_1_num=[]
a_1_count = 0
b_1_num=[]
b_1_count = 0
for x in alis:
    numx=x
    while numx>0:
        if(numx&1==1):
            a_1_count=a_1_count+1
        numx>>=1
    a_1_num.append(a_1_count)
    a_1_count=0
for y in blis:
    numy=y
    while numy>0:
        if(numy&1==1):
            b_1_count=b_1_count+1
        numy>>=1
    b_1_num.append(b_1_count)
    b_1_count=0
plt.scatter(a_1_num,runtime['r'],\
                c="red",label="a_1_num",s=4.)
plt.scatter(b_1_num,runtime['r'],\
                c="blue",label="b_1_num",s=4.)
plt.xlabel("a_1_num,b_1_num")
plt.ylabel("runtime(Microsecond)")
plt.show()