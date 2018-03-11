def logistic(a,x0):
    if a<0 or 4<a:
        raise ValueError("'a' needs to be 0 <= a <= 4")
    elif x0<0 or 1<x0:
        raise ValueError("'x0' needs to be 0 <= x0 <= 1")
    else:
        x=x0
        while True:
            xnext=a*x*(1.0-x)
            yield xnext
            x=xnext

l=logistic(a=3.9,x0=0.23)
for i in range(1,101):
    print(str(i) + ' ' + str(next(l))) 