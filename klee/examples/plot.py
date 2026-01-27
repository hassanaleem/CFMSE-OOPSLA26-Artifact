#!/usr/bin/python3
import matplotlib
matplotlib.use('Agg')
import matplotlib.pyplot as plt

# Read in the data from the text file
data = []
initial = True
initialX = 0
with open('echo_coverage_cfm.txt', 'r') as f:
    for line in f:
        x, y = line.strip().split()
        if initial:
          initialX = float(x)
          initial = False
        data.append((float(x) - initialX, float(y)))

# Create a plot of the data
fig, ax = plt.subplots()
ax.plot([d[0] for d in data], [d[1] for d in data])

# Set the plot title and axis labels
ax.set_title('Coverage for Coreutils Echo with CFM')
ax.set_xlabel('Time (seconds)')
ax.set_ylabel('Source Line Coverage (%)')

# Save the plot to a PNG file
plt.savefig('echo_with_cfm.png')