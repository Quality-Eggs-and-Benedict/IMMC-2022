import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
import seaborn as sns

model_list = ['random_model', 'boarding_by_section', "boarding_by_section (10% disobey)", 'boarding_by_seat',
              "boarding_by_seat (10% disobey)", 'back_to_front', 'steffen_method', 'random_model (30% capacity)',
              'random_model (50% capacity)', 'random_model (70% capacity)', 'back_to_front (30% capacity)',
              'back_to_front (50% capacity)', 'back_to_front (70% capacity)']

iterations = 1000

data_files = [pd.read_csv(f"./model_outputs/{model_name}.csv") for model_name in model_list]

for x in range(len(data_files)):
    recorded_time = []
    for i in range(len(data_files[x])):
        recorded_time.append(data_files[x]['Time'][i])
    recorded_time = np.array(recorded_time)

    ax = sns.kdeplot(recorded_time, label=model_list[x], shade=True, thresh=False)
    plt.axvline(recorded_time.mean(), color='red')

plt.xlabel('Time (s)')
plt.ylabel('Probability')
plt.legend(loc='upper right')
plt.show()
