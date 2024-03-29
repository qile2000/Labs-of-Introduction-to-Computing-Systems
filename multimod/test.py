import random
import os

#p1, p2 or p3
choosen_func_no = "2 "

#run time
total_runtime = 0
MS_PER_SEC = 1000

#test instances number
test_num=10000

#generate test a b m
LIMIT=2**63-1
wrong_num=0

#for condition judge

wrong_result_condition_num=0
right_result_condition_num=0

for i in range(test_num):
    a=random.randint(0,LIMIT)
    b=random.randint(0,LIMIT)
    m=random.randint(1,LIMIT)

    whole_command ="/home/qile/ics-workbench/multimod/main -i "+\
                   choosen_func_no+str(a)+" "+str(b)+" "+str(m)
    opened_file=os.popen(whole_command)

    result_list=opened_file.readlines()
    
    run_time=result_list[1].strip()
    total_runtime+=int(run_time)
    
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
