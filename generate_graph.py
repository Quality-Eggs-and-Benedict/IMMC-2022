import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
import seaborn as sns

data = pd.read_csv(r"./data_output.csv")

recorded_time = []
for i in range(len(data)):
    recorded_time.append(data['Time'][i])
recorded_time = np.array(recorded_time)

sns.displot(recorded_time, kind='kde', height=5, aspect=18/9)
plt.axvline(recorded_time.mean(), color='red', label=f'mean time={recorded_time.mean():.2f} s')
plt.axvline(np.percentile(recorded_time, 5), color='green', label=f'5th percentile={np.percentile(recorded_time, 5):.2f} s')
plt.axvline(np.percentile(recorded_time, 95), color='green', label=f'95th percentile={np.percentile(recorded_time, 95):.2f} s')
plt.xlabel('Time (s)')
plt.ylabel('Probability')
plt.legend()
plt.show()
