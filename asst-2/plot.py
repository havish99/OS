import pandas as pd
import matplotlib.pyplot as plt 

df = pd.read_csv("plots.csv")
plt.plot(df['n'],df[' process'],label='process')
plt.plot(df['n'],df[' thread'],label='thread')
plt.xlabel('Size')
plt.ylabel('Time(in sec)')
plt.legend()
plt.show()
# l1 = df[' thread'].values.tolist()
# print(l1)