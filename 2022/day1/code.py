top = []
with open('input') as f:
    elf = 0
    for l in f:
        if(l != '\n'):
            elf+= int(l)
        else:
            top.append(elf)
            elf=0
        
top = sorted(top,reverse=True)
print(*top, sep='\n')

print(top[0]+top[1]+top[2])