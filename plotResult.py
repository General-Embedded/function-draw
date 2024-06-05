import numpy as np
import matplotlib.pyplot as plt

def plot_matrix_from_file(filename):
    # Load the data from the file
    data = np.loadtxt(filename)
    
    # Plot the data
    plt.imshow(data, cmap='viridis', aspect='auto')
    plt.colorbar()
    plt.title('Matrix Plot')
    plt.xlabel('X-axis')
    plt.ylabel('Y-axis')
    plt.show()

# Replace 'result.txt' with the path to your file
plot_matrix_from_file('result.txt')
