import pandas as pd
import numpy as np

def import_matrix(filename):
    return np.matrix(pd.read_csv(filename, delimiter = '\t', header = None))
    
def export_matrix(filename,mat):
    pd.DataFrame(np.array(mat)).to_csv(filename, sep='\t',header = False , index = False)