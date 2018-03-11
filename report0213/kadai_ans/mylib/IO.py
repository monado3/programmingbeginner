import matplotlib.pyplot as plt
import numpy as np


def plot_graph(vec, title, xlabel):
   'show the graph of vec'
   x_axis = np.arange(len(vec))
   plt.plot(x_axis, vec)
   plt.title(title)
   plt.xlabel(xlabel)
   plt.ylabel('value')
   plt.grid()


def standardize_wav(mat_X):
   'make max(each row of abs(mat_X)) 32767 and dtype = int16'
   mat_X = np.array(mat_X)
   maxarr = np.vstack(np.max(np.absolute(mat_X), axis=1))
   mat_X = np.array((mat_X / maxarr) * 32767, dtype='int16')
   if np.max(np.absolute(mat_X)) > 32767:
      raise ValueError("The maximum value is greater than 32767")
   else:
      return mat_X


def standardize_png(mat_X):
   'make max(each row of mat_X) 255 and min(each row of mat_X) 0 and dtype uint8'
   mat_X = np.array(mat_X)
   minarr = np.vstack(np.min(mat_X, axis=1))
   mat_X = mat_X - minarr
   maxarr = np.vstack(np.max(mat_X, axis=1))
   mat_X = np.array((mat_X / maxarr) * 255, dtype='uint8')
   if np.max(mat_X) > 255:
      raise ValueError("The maximum value is greater than 255")
   elif np.min(mat_X) < 0:
      raise ValueError("The minimum value is less than 0")
   else:
      return mat_X
