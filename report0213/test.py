# import sys
# ans=0
# inp = sys.stdin.readlines()
# cnt = 0
# for i in inp:
#    if cnt < 10:
#       print(float(i))
#    ans+= float(i)
#    cnt+=1
# print(ans/len(inp))

# a='1'
# if a:
#    print("True")
# if not a:
#    print("false")

import numpy as np
M = np.matrix([[2,1],[3,4]])
N = np.power(np.array(M),-1/2)
print(f'M**-1/2 = {N}')
l,v = np.linalg.eig(M)
print(f'l = {l}')
print(f'v = {v}')
# print(f'v0 = {v[0]}') #固有ベクトルではなくPの一行目
# print(f'v1 = {v[1]}')

#covtest
# In[]:
import numpy as np
x = np.ones((2,3142))
covx = np.cov(x, rowvar=1)
covx

# In[]:
import numpy as np
import numpy.linalg as la
x = np.array([1,10,100,1000])
((x**2).sum())**0.5
la.norm(x)

x = np.array([[1,10],[100,1000],[1,1]])
((x[0]**2).sum())**0.5
la.norm(x,axis = 1)

a = np.array([[1,2],[3,4]])
la.norm(a)
(1+2**2+3**2+4**2)**0.5

# In[]:
a = np.array([1,2,3])
b = a.copy()
a[0] = 10
b

# In[]:
a = np.array([[1,2,3],[4,5,6]])
a
a.T

# In[]:
a = np.array([[1,-1],[-3,-4]])
a
abs(a)
abs(a).sum()
a.T

# In[]:
import numpy as np
a = np.array([[1,2],[3,4]])
np.power(a,2)

# In[]:
import numpy as np
import numpy.linalg as la
a = np.array([[1,10],[100,0]])
a
b = np.array([10,1])
b = np.vstack(b)
b
a/=b
a

# In[]:
def normalize(mat_A, axis):
   'normalize a matrix A'
   norm = la.norm(mat_A, axis=axis)
   mat_A =/np.vstack(norm)
   return mat_A
a = np.array([[1,10],[100,0]])
a
normalize(a,1)
# In[]:
a = np.array([[1,2,3],[4,6,8]])
def make_mean_0(data):
   meanarr = np.vstack(np.mean(data, axis=1))
   data = data - meanarr
   return (data,meanarr)

a, mean = make_mean_0(a)
print(a,mean,sep = '\n')

# In[]:
a = np.array([1,10])
np.matrix(a)
la.norm(a)

b = np.array([[1,2,3],[4,5,6]])
b
c = np.array(np.matrix(a)*np.matrix(b))[0]
c
np.power(c,3)
d = np.array([0,0,1])
d
np.mean(c*d)
d - np.array([10,5,0])

# In[]:
a = np.array([[1,-5,4],[-7,6,3]])
a = np.absolute(a)
a
b = np.vstack(np.max(a, axis = 1))
b
a/b

# In[]:
a = np.array([[1,2,3],[4,5,6]])
b = np.array([1,0,1])
np.mean(a*b, axis = 1)

# In[]:
a = np.array([1,2,3])
b = np.array([[1,1,1],[2,2,2]])
a-b
la.norm(a-b, axis = 1)
la.norm(a-b, axis = 1) /2  < 2
np.any(la.norm(a-b, axis = 1) < 2) or \
np.any(np.array([False, False]))
