'''
Matthew Petrucci 300119235
This is a python implementation of Assignment 2 Question 2 that requires a multithreaded solution to
finding the fibonacci numbers of a given n interation.
As Fibonacci is quite hard to properly do concurrently with multiple processes since each thread will
require the next thread (either child or parallel) to finish, and thus wouldn't really work.
So for this implementation I have one thread that solves the fibonacci sequence and the other that prints
the values.
'''
fibonacciDone = False
fibonacciNumbers = []

import threading

def findFibonacci(n):

    global fibonacciDone
    # start the sequence
    f0, f1 = 0, 1
    # compute the nth number
    for _ in range(0, n):
        fibonacciNumbers.append(f0)
        f0, f1 = f1, (f1 + f0)
    fibonacciDone = True
    return f0

def main():
    
    global fibonacciNumbers
    maxThreads = 2 #Do not change
    maxNumber = int(input("Enter the n number for Fibonacci: "))

    for i in range(0, maxThreads):
        if i == 0: #first thread will solve fibonacci numbers and add them to an array
            thread = threading.Thread(target=findFibonacci, kwargs={'n':maxNumber})
            thread.start()
        if i == 1: #second thread will print every time the first thread creates a number
            while len(fibonacciNumbers) > 0 and fibonacciDone: #Check if there are no numbers left and first thread is done
                print(fibonacciNumbers.pop(0))

if __name__ == '__main__':
    main()