import random
import os

#p1, p2 or p3
choosen_func_no = "1 "

#generate test a b m
LIMIT=2**63-1
wrong_num=0
for i in range(1000):
    a=random.randint(0,LIMIT)
    b=random.randint(0,LIMIT)
    m=random.randint(1,LIMIT)
    whole_command ="/home/qile/ics-workbench/multimod/main -i "+choosen_func_no+str(a)+" "+str(b)+" "+str(m)
    opened_file=os.popen(whole_command)
    my_result=opened_file.readlines()[0].strip()
    if(int(my_result)!=a*b%m):
        wrong_num=wrong_num+1
        print("wrong result: "+str(a)+"*"+str(b)+"%"+str(m)+"my_result:"+str(my_result)+" right result:"+str(a*b%m)+"\n")
    
print("in 1000 tests, wrong times are:"+str(wrong_num)+"\n")