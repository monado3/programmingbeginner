eulerproduct=1
for i in range(2,10000):
    for j in range(2,i//2+1):
        if i%j==0:
            break
    else:
        eulerproduct*=1-1/(i**2)
        
print((6/eulerproduct)**0.5)