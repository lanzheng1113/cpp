# example of Fibonacci series
# using python3
import sys
import time

callCnt = 0

def fibr(n):
    """get the n-th Fibonacci series number,using recursion"""
    global callCnt
    callCnt += 1 # count how many time function called
    if n < 2:
       return n
    return fibr(n-1)+fibr(n-2)

if __name__ == "__main__":
    for n in list( map(int,sys.argv[1:]) ):
        callCnt = 0
        start_time = time.time() # record start time
        ret = fibr(n) 
        print("fib({})={}\n".format(n,ret),
         "\tcalled {} {} times\n".format("'recursive function fibr'",callCnt),
         "\tconsumed %s ms\n"% ((time.time()-start_time)*1000)  )
        print('*'*50)
