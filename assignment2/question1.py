'''
Matthew Petrucci 300119235

'''

import threading

def createThread(maxThreads, allNumbers):
        #Takes a number of threads and an array with all the numbers to be distributed equally amongst the threads
        #Allocates all numbers from 0 to maxNumber equally amongst all the threads in an array.
        #The array will consist of maxThreads numbers of array that contains all the numbers that each individual thread needs to solve.
        #Basically, each array in the array is a thread and the numbers it must find for the prime number
        
    threadList = []
    numbersPerThread = len(allNumbers) // maxThreads #calculate the number of numbers each thread will have to check
    for i in range(maxThreads):
        start = i * numbersPerThread #calculate the starting index for this thread
        end = start + numbersPerThread #calculate the ending index for this thread

        if i == maxThreads - 1: #the last thread will have to check any remaining numbers
            end = len(allNumbers)
            threadList.append(allNumbers[start:end]) #add the array of numbers for this thread to the threadList

        else:
            threadList.append(allNumbers[start:end])

    return threadList

def findPrimes(numbers):
    #Finds the prime numbers in the given array and prints them
    #That's it.
    #Pretty simple

    for num in numbers:
        for i in range(2, num):
            if (num % i) == 0:
                break
        else:
            print(num)

def main():
    
    maxThreads = 4
    maxNumber = int(input("Enter the largest number: "))

    allNumbers = list(range(0,maxNumber + 1)) #array of every single number 0->maxNumber

    #print(allNumbers)
    threads_to_multithread = createThread(maxThreads, allNumbers)

    for i in range(0, maxThreads):
        thread = threading.Thread(target=findPrimes, kwargs={'numbers':threads_to_multithread[i]})
        thread.start()
    
if __name__ == '__main__':
    main()