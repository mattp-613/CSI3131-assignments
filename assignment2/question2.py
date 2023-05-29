'''
Matthew Petrucci 300119235
This is a python implementation of Assignment 2 Question 2 that requires a multithreaded solution to
finding the fibonacci numbers of a given n interation.
As Fibonacci is quite hard to properly do concurrently with multiple processes since each thread will
require the next thread (either child or parallel) to finish, and thus wouldn't really work.
So for this implementation I have one thread that solves the fibonacci sequence and the other that prints
the values.
'''

import threading
from time import sleep

def createThread(maxThreads):
    #Each thread

    pass

def findFibonacci(n):

    # start the sequence
    f0, f1 = 0, 1
    # compute the nth number
    for _ in range(0, n):
        fibonacciNumbers.append(f0)
        f0, f1 = f1, (f1 + f0)
    return f0

def main():
    
    global fibonacciNumbers
    fibonacciNumbers = []
    maxThreads = 2
    maxNumber = int(input("Enter the n number for Fibonacci: "))

    #allNumbers = list(range(0,maxNumber + 1)) #array of every single number 0->maxNumber
    #threads_to_multithread = createThread(maxThreads, allNumbers)

    for i in range(0, maxThreads):
        if i == 0: #first thread will solve fibonacci numbers and add them to an array
            thread = threading.Thread(target=findFibonacci, kwargs={'n':maxNumber})
            thread.start()
        if i == 1: #second thread will print every time the first thread creates a number
            while True:
                if len(fibonacciNumbers) > 0:
                    print(fibonacciNumbers.pop(0))

                #TODO: if condition to break the loop when thread 0 is done
if __name__ == '__main__':
    main()