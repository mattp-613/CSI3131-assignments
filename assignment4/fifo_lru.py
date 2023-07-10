import random


#essential functions for pages
def random_page_reference_string(size):
    page_reference = []
    for i in range(0,size):
        page_reference.append(random.randint(0,9))
    return page_reference

def fifo(string, num_page_frames):
    faults = 0
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

def lru(string, num_pages_frames):
    faults = 0
    page = dict()
    for i in range(0, num_page_frames):
        page[i] = ''
    fault = 0
    lru_value = 0
    last_accessed = []
    for i in range(0, num_page_frames):
        last_accessed.append(0)
    #last_accessed will have the index of the placement of the character in the string.
    #The lower the index in the string, the higher chance it has to be replaced.
    #Each index in this list corresponds to the key in the page dictionary.
    for i in range(0, len(string)):
        char = string[i]

        if char not in page.values(): #if it is not already in the dictionary (skip duplicates AND already existing)
            fault+=1
            for y in range(0, num_page_frames): #Find the last frame accessed in the list
                if lru_value < page.get(hmmmm): #TODO: Find hmmmm
                    lru_value = y
            page[lru_value] = char
            lru_value = 0


if __name__ == "__main__":
    string = random_page_reference_string(20)
    num_page_frames = 7
    print(lru(string, num_page_frames))