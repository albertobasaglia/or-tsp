import numpy as np
import matplotlib.pyplot as plt
import sys

def plot_loops(file_path):
    with open(file_path, 'r') as file:
        lines = file.readlines()

    current_loop = []
    all_loops = []

    for line in lines:
        if line.strip() == 'newloop':
            if current_loop:
                all_loops.append(current_loop)
                current_loop = []
        else:
            x, y = map(float, line.strip().split(','))
            current_loop.append((x, y))

    if current_loop:  # Add the last loop if not empty
        all_loops.append(current_loop)

    for loop in all_loops:
        loop = np.array(loop)
        plt.plot(loop[:, 0], loop[:, 1])

    plt.xlabel('X')
    plt.ylabel('Y')
    plt.title('Loops from File')
    plt.grid(True)
    plt.show()

# Example usage:
file_path = sys.argv[1]
plot_loops(file_path)