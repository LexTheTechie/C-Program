import re
import string


def printsomething():
    print("Hello from python!")

def PrintMe(v):
    print("You sent me: " + v)
    return 100;

def SquareValue(v):
    return v * v

def ReadLines():
    grocList = open("CS210_Project_Three_Input_File.txt", "r")
    dictionary = dict()
    for line in grocList:
        line = line.strip()
        grocItem = line.lower()
 
        if grocItem in dictionary:
            
            dictionary[grocItem] = dictionary[grocItem] + 1
        else:
          
            dictionary[grocItem] = 1
    for key in list (dictionary.keys()):
        print(key.capitalize(), ":", dictionary[key])
    grocList.close()



def SpecificItem(spefItem):
    spefItem = spefItem.lower()
    grocList = open("CS210_Project_Three_Input_File.txt", "r")
    itemCount = 0
    for line in grocList:
        line = line.strip()
        grocItem = line.lower()
        
        if grocItem == spefItem:
            itemCount = itemCount + 1

   
    return itemCount
    grocList.close()

def CreateData():
    grocList = open("CS210_Project_Three_Input_File.txt", "r")
    freqData = open("frequency.dat", "w")
    dictionary = dict()
    for line in grocList:
        line = line.strip()    
        grocItem = line.lower()
        if grocItem in dictionary:
           
            dictionary[grocItem] = dictionary[grocItem] + 1
        else:
           
            dictionary[grocItem] = 1
    for key in list (dictionary.keys()):
        freqData.write(str(key.capitalize()) + " " + str(dictionary[key]) + "\n")

    
    grocList.close()
    freqData.close()