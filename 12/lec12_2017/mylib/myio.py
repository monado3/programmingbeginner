import pandas as pd
import numpy as np

def import_matrix(file_name):
    v = pd.read_csv(file_name, delimiter='\t', header = None)
    return np.matrix(v, dtype = 'float64')

def export_matrix(file_name, m):
    if isinstance(m, np.matrix):
        l = m.tolist()
    else:
        l = m
    df = pd.DataFrame(l)
    df.to_csv(file_name, sep='\t', header=False, index=False)

    