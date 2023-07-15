import random


#essential functions for pages
def random_page_reference_string(size):
    page_reference = []
    for i in range(0,size):
        page_reference.append(random.randint(0,9))
    return page_reference

def fifo(string, num_page_frames):
    page = dict()
    for i in range(0, num_page_frames):
        page[i] = ''

    FIFOcounter = 0 #pointer tracker
    fault = 0
    for char in string:
        if char not in page.values(): #if it is not already in the dictionary (skip duplicates AND already existing)

            fault+=1
            if(FIFOcounter == num_page_frames): #so it will reset
                FIFOcounter = 0
            page[FIFOcounter] = char
            FIFOcounter+=1

    return "--FIFO--\ngiven string:{}\nfinal page:{}\nfaults:{}.".format(string, page, fault)

def lru(string, num_page_frames):
    page = dict()
    for i in range(0, num_page_frames):
        page[i] = ''
    fault = 0
    lru_value = 0
    lru_list = []
    lru_index = 0
    for i in range(0, num_page_frames):
        lru_list.append(0)

    #This algorithm is sort of complicated so let me explain:
    #Instead of having each page frame have a number for the amount of "hits" it has,
    #It will instead correlate to the last index in the character string the same value appeared in.
    #Therefore it will require less strain on the system.
    #So we want to find the number in lru_list with the *lowest* value, so it correlates
    #With the lowest index in the string, aka, the last time in the string that value appeared
    for i in range(0, len(string)):
        char = string[i]

        if char not in page.values(): #if it is not already in the dictionary (skip duplicates AND already existing)
            print(page)
            print(char)
            fault+=1
            for y in range(0, len(lru_list)):
                if lru_value > lru_list[y] - 1:
                    lru_value = lru_list[y] - 1
                    lru_index = y
                    

            page[lru_index] = char

            #update LRU list
            lru_list[lru_index] = i + 1 #This +1 and the -1 above is entirely due to the first character having an index of 0
            #reset lru_value
            #print(lru_value)
            #print(lru_index)
            lru_value = len(string)

    return "--LRU--\ngiven string:{}\nfinal page:{}\nfaults:{}.".format(string, page, fault)


if __name__ == "__main__":
    string = random_page_reference_string(20)
    num_page_frames = 7
    print(lru(string, num_page_frames))
    print(fifo(string, num_page_frames))
