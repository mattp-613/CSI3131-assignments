'''
Matthew Petrucci 300119235

'''

import threading

def createThread(maxThreads):
    pass

def findFibonacci(n):
    if n <= 1:
       return n
    else:
       return(findFibonacci(n-1) + findFibonacci(n-2))


def main():
    
    maxThreads = 4
    maxNumber = int(input("Enter the largest number: "))

    allNumbers = list(range(0,maxNumber + 1)) #array of every single number 0->maxNumber

    #print(allNumbers)
    threads_to_multithread = createThread(maxThreads, allNumbers)

    for i in range(0, maxThreads):
        thread = threading.Thread(target=findFibonacci, kwargs={'numbers':threads_to_multithread[i]})
        thread.start()
    
if __name__ == '__main__':
    main()