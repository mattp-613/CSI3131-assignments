import random
#from queue import Queue #Use queue for FIFO?

#essential functions for pages
def random_page_reference_string(size):
    page_reference = []
    for i in range(0,size):
        page_reference.append(random.randint(0,9))
    return page_reference

def fifo(string, num_page_frames):
    faults = 0
    page = list()
    for i in range(0, num_page_frames):
        page.append([[None],[i]]) #First index of the list is string value, second is index of the frame in the page
    print(page)

if __name__ == "__main__":
    string = random_page_reference_string(20)
    num_page_frames = 7
    fifo(string, num_page_frames)