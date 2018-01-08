# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# First solution to problem without using dynamic programming
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

import sys;

def MakeChange(total, units):
    #Add precision to solution, return an empty solution under this condition
    if ( abs(total) < 1e-10 ):
        return [{}]
    #Not a solution if total becomes negative
    elif ( total < 0 ):
        return []
    #Cycle through units from i onwards
    else:
        n = len(units)
        ret = []
        for i in range(0,n):
            sols = MakeChange(total-units[i],units[i:n])
            for sol in sols:
                #If unit[i] has a key in the key value pair, then true
                if (units[i] in sol):
                    sol[units[i]] = sol[units[i]] + 1
                else:
                    sol[units[i]] = 1
                    ret.append(sol)
        return ret

#Convert input arguments to float and a list of floats
tot = float(sys.argv[1])
unit = [float(x) for x in sys.argv[2:len(sys.argv)]]

#Use function to find solutions
solutions = MakeChange(tot, unit)

#Print solutions
print("There are " + str(len(solutions)) + " ways to make change from "+str(tot) + " dollars")
for s in solutions:
    print(s)
