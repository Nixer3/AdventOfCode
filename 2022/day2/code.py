import os
# A/X rock; B/Y paper; C/Z scissors
path = "/workspaces/AdventOfCode/day2/input"
mapSame = {'X':'A','Y':'B','Z':'C'} 
mapWin = {'A':'B','B':'C','C':'A'}
rpsVal = {'A':1,'B':2,'C':3}
def A(opo:str, me:str) -> int:
    me = mapSame[me]
    if(opo == me): 
        return 3+rpsVal[me]
    if(mapWin[opo] == me):
        return 6+rpsVal[me]
    return 0+rpsVal[me]
def B(opo:str, outcome:str) -> int:
    if(opo == 'A' and outcome=='X'): return 0+3
    if(opo == 'A' and outcome=='Y'): return 3+1
    if(opo == 'A' and outcome=='Z'): return 6+2
    if(opo == 'B' and outcome=='X'): return 0+1
    if(opo == 'B' and outcome=='Y'): return 3+2
    if(opo == 'B' and outcome=='Z'): return 6+3
    if(opo == 'C' and outcome=='X'): return 0+2
    if(opo == 'C' and outcome=='Y'): return 3+3
    if(opo == 'C' and outcome=='Z'): return 6+1


#run code
points=0
with open(path) as f:
    for l in f:
        p = B(l[0],l[2])
        points+= p
print(points)