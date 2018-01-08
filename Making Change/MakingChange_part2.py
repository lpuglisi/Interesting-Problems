# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
# Second solution to problem using dynamic programming
# ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

import sys
import copy

#Modifying code from part 1 solution
def dpMakeChange(total, units, stored):
    #Store solutions in a dictionary with the key as a concatenation of total and units
    dictky = ":".join(map(str, [total]+units))
    #Check if solution has already been found, if it has, don't continue
    if dictky not in stored.keys():
        if ( abs(total) < 1e-10 ):
            return [{}]
        elif ( total < 0 ):
            return []
        else:
            n = len(units)
            ret = []
            for i in range(0,n):
                sols = copy.deepcopy(dpMakeChange(total-units[i], units[i:n], stored))
                for sol in sols:
                    if ( units[i] in sol ):
                        sol[units[i]] = sol[units[i]] + 1
                    else:
                        sol[units[i]] = 1
                    ret.append(sol)
            #Store solution using key created earlier
            stored[dictky] = ret
    return stored[dictky]


#Convert input arguments to float and a list of floats
tot = float(sys.argv[1])
unit = [float(x) for x in sys.argv[2:len(sys.argv)]]

#Use function to find solutions
solutions = dpMakeChange(tot, unit, {})

#Print solutions
print("There are " + str(len(solutions)) + " ways to make change from "+str(tot) + " dollars")
for s in solutions:
    print(sorted(s.items()))
