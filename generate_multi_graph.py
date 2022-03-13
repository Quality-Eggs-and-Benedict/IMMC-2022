import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
import seaborn as sns

model_list = ['random_model', 'boarding_by_section', 'boarding_by_seat', 'back_to_front', 'steffen_method']

iterations = 1000

data_files = [pd.read_csv(f"./model_outputs/{model_name}.csv") for model_name in model_list]

for x in range(len(data_files)):
    recorded_time = []
    for i in range(len(data_files[x])):
        recorded_time.append(data_files[x]['Time'][i])
    recorded_time = np.array(recorded_time)

    ax = sns.kdeplot(recorded_time, label=model_list[x], shade=True, thresh=False)
    plt.axvline(recorded_time.mean(), color='red')
    trans = ax.get_xaxis_transform()
    ax.text(recorded_time.mean() - 25, 0.5, f'{recorded_time.mean():.2f}s', rotation=90, transform=trans)

plt.xlabel('Time (in seconds)')
plt.ylabel('Probability (no. occurrences)')
plt.legend(loc='upper right')
plt.show()
