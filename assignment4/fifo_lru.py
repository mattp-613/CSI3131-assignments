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

    return "given string:{}\nfinal page:{}\nfaults:{}.".format(string, page, fault)
if __name__ == "__main__":
    string = random_page_reference_string(20)
    num_page_frames = 7
    print(fifo(string, num_page_frames))