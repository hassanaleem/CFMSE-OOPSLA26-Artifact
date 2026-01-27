import pandas as pd
from pandas import read_csv
import matplotlib.pyplot as plt

df = read_csv("output.csv")

input_size = df["input_size"]
cfm_true_error = df["cfm_true_error"]
no_cfm_error = df["no_cfm_error"]

# make a scatter plot
plt.scatter(input_size, cfm_true_error, label='CFM-SE')
plt.scatter(input_size, no_cfm_error, label='KLEE')

plt.xlabel('Input Size')
plt.ylabel('Time (s)')
plt.title('JSON')
plt.legend()
# save the plot
plt.savefig('json.png')
# I want the pdf file too
plt.savefig('json.pdf')
# show the plot
plt.show()
#
