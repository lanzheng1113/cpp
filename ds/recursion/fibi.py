
# example of Fibonacci series
# using python3
import sys
import time

def fibi(n):
    """ get n-th Fibnacci series number,using iteration"""
    if n < 2:
        return n
    else:
        last,cur = 0,1
        for i in range(1,n):
            last,cur = cur,last+cur
        return cur

if __name__ == "__main__":
    for n in list( map(int,sys.argv[1:]) ):
        start_time = time.time() # record start time
        ret = fibi(n) 
        print("fib({})={}\n".format(n,ret),
         "\tconsumed %s ms\n"% ((time.time()-start_time)*1000)  )
        print('*'*50)
