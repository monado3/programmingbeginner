import numpy as np
import numpy.linalg as la


def make_mean_0(dataX):
   'perform linear conversion of every dataX[i] so that E[dataX[i]] = 0'
   meanarr = np.vstack(np.mean(dataX, axis=1))
   dataX = dataX - meanarr
   return (dataX, meanarr)


def whitening_data(mat_A):
   'make a matrix Z from a matrix X'
   cov_A = np.cov(mat_A, rowvar=1, bias=1)
   mat_D, mat_E = diag_with_orthomat(cov_A)
   mat_V = np.matrix(mat_D) * np.matrix(mat_E.T)
   return np.matrix(mat_V) * np.matrix(mat_A)


def make_W(mat_Z, num_sep):
   '''make a martix W.
      num_sep: a original number of signal source.'''

   num_n = len(mat_Z)  # the number of components of each time`s data

   # make a matrix W
   np.random.seed(0)
   epsilon = 1e-10  # this is the standard of convergence determination.
   mat_W = np.zeros((num_sep, num_sep))
   source_cnt = 0  # which component of the data this whileloop is finding then.

   while num_sep - source_cnt:
      vec_W = np.random.rand(num_sep) * 2 - 1  # -1 <= vec_W[i] < 1
      vec_W = normalize(vec_W)  # normalize vector W
      prev_vecW = vec_W.copy()  # prev_vecW contains the previous forloop`s vec_W

      # if vec_W don`t converge after 1000 loop, try another initial values
      for loop in range(1000):
         vec_W = make_Except_mat(vec_W, mat_Z, num_n) - 3 * vec_W
         vec_W = normalize(vec_W)

         # convergence determination
         if    la.norm(vec_W - prev_vecW) / num_n < epsilon \
            or la.norm(vec_W + prev_vecW) / num_n < epsilon:
            checker = 0

            # compare this vector W with matrix W(set of vector Ws already found)
            if    np.any(la.norm(vec_W - mat_W, axis=1) / num_n < epsilon * 1e3) \
               or np.any(la.norm(vec_W + mat_W, axis=1) / num_n < epsilon * 1e3):
               checker = 1  # if vec_W is already found, checker = 1

            if checker:
               break
            else:  # if new vec_W is found, it is added to mat_W
               mat_W[source_cnt] = vec_W.copy()
               source_cnt += 1
               break
         else:
            prev_vecW = vec_W.copy()

   return mat_W


def find_source(mat_W, dataZ):
   'return W*z'
   return np.array(np.matrix(mat_W) * np.matrix(dataZ))


def diag_with_orthomat(mat_A):
   'diagonalize a matrix A with orthogonal matrix E'
   mat_D, mat_E = la.eig(mat_A)
   mat_E, dump = la.qr(mat_E)
   mat_D = np.power(mat_D, -1 / 2)
   mat_D = np.diag(mat_D)
   return (mat_D, mat_E)


def normalize(vec_W):
   'normalize a vector W'
   norm = la.norm(vec_W)
   return vec_W / norm


def make_Except_mat(vec_W, mat_Z, num_n):
   'calculate Exceptation[z(w^T*z)^3]'
   mat_zT_W = np.power(np.array(np.matrix(vec_W) * np.matrix(mat_Z))[0], 3)
   return np.mean(np.array(mat_Z) * mat_zT_W, axis=1)
