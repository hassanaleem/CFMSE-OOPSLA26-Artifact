import pandas as pd
from pandas import read_csv
import matplotlib.pyplot as plt

df = read_csv("output.csv")

input_size = df["input_size"]
cfm_true_error = df["cfm_true_error"] / 3600
no_cfm_error = df["no_cfm_error"] / 3600


# make a scatter plot
plt.scatter(input_size, cfm_true_error, label='CFM-SE')
plt.scatter(input_size, no_cfm_error, label='KLEE')
# add grid
plt.grid()

# output the y values
print("CFM-SE y values: ", cfm_true_error)
print("KLEE y values: ", no_cfm_error)

plt.xlabel('Input Size')
plt.ylabel('Time (hours)')
plt.title('Time Until Bug')
plt.legend()
plt.xticks(input_size)
# save the plot
plt.savefig('utf.png')
# I want the pdf file too
plt.savefig('utf.pdf')
# show the plot
plt.show()
#
