def legendre(n,x):
    if n==0:
        return 1
    elif n==1:
        return x
    else:
        return ((2*n-1)*x*legendre(n-1,x)-(n-1)*legendre(n-2,x))/n

print(legendre(16,0.5))
print(legendre(32,0.7))