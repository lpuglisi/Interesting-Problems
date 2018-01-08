import sys
import random as rd

#Fixing issue with between input() and raw_input() for python 2/3
try:
    input = raw_input
except NameError: pass

#Defining function to find all correct words
def findall(dic,l,wrd):
    #Setting up list for checks
    allWrds = list(dic[l])
    sortedWrds = [list(i) for i in dic[l]]
    for i in range(len(sortedWrds)):
        sortedWrds[i].sort()
    #Find all correct matches based on random word
    crrt = list()
    crrtWrd = list(wrd)
    crrtWrd.sort()
    for i in range(len(sortedWrds)):
        if sortedWrds[i] == crrtWrd:
            crrt.append(i)
        else:
            continue
    otherCorrect = [allWrds[i] for i in crrt]
    return otherCorrect

#Simple function to check input is numeric
def numcheck(s):
    try:
        int(s)
        return True
    except ValueError:
        return False

#Read the file given, each word is an entry in the list
with open(sys.argv[1]) as fl:
    wrd = fl.readlines()
wrd = [i.strip() for i in wrd]

# Find max word length and store words of similar length in a dictionary
maxwrd = len(max(wrd,key=len))
fnldict = dict()
for i in range(maxwrd+1):
    if i==0:
        continue
    else:
        fnldict[i] = [x for x in wrd if len(x)==i]



#~~~~~~~~~~~~~~~~~~Game Start~~~~~~~~~~~~~~~~~~#
print("-------------------------------------------")
print("Welcome to the word unscrambler!")
print("-------------------------------------------")

#Get all possible lengths for random lengths
wrdlengths = list(range(maxwrd+1))[1:]
#Set default
length = "blah"

#Let the games begin
while (length != 'q') | (numcheck(length)==False):
    guess = 'dumdum'
    otherCorrect = list()
    length = str(input("Pick the length of the word you want to unscramble (type 'q' to quit or hit Enter for a random word): "))
    if length == "":
        length = rd.SystemRandom().choice(wrdlengths)
        rndwrd = rd.SystemRandom().choice(fnldict[length])
        rndwrd_shuf = list(rndwrd)
        rd.shuffle(rndwrd_shuf)
        rndwrd_shuf = "".join(rndwrd_shuf)
        otherCorrect = findall(fnldict,length,rndwrd)
        while (guess != 'q') & (length != 'q'):
            guess = str(input("Unscramble the word %s : " % rndwrd_shuf))
            if (guess == rndwrd) | (guess in otherCorrect):
                print("Correct!")
                print("Correct answer(s): %s" % otherCorrect)
                guess='q'
                break
            else:
                print("Sorry, wrong answer. Correct answer(s): %s" % otherCorrect)
                break
    elif (numcheck(length)==True):
        length = int(length)
        if length <= maxwrd:
            rndwrd = rd.SystemRandom().choice(fnldict[length])
            rndwrd_shuf = list(rndwrd)
            rd.shuffle(rndwrd_shuf)
            rndwrd_shuf = "".join(rndwrd_shuf)
            otherCorrect = findall(fnldict,length,rndwrd)
            while (guess != 'q') & (length != 'q'):
                guess = str(input("Unscramble the word %s : " % rndwrd_shuf))
                if (guess == rndwrd) | (guess in otherCorrect):
                    print("Correct!")
                    print("Correct answer(s): %s" % otherCorrect)
                    guess='q'
                    break
                else:
                    print("Sorry, wrong answer. Correct answer(s): %s" % otherCorrect)
                    break
            continue
        else:
            print("Please enter a smaller number!")
            continue
    elif length == 'q':
        break
    else:
        print("Incorrect input! Please enter an integer, hit Enter, or type 'q' to quit")
        continue
    continue
