import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns

model_list = ['random_model', 'boarding_by_section', "boarding_by_section (10% disobey)", 'boarding_by_seat',
              "boarding_by_seat (10% disobey)", 'back_to_front']
iterations = 1000

data_files = [pd.read_csv(f"./model_outputs/{model_name}.csv") for model_name in model_list]

time_df = pd.concat(data_files, ignore_index=True)
names = []
for model_name in model_list:
    for i in range(iterations):
        names.append(model_name)

time_df['Method'] = pd.DataFrame(names)
plt.style.use('seaborn-dark')
plt.figure(figsize=(15, 5))
ax = sns.barplot(x='Method', y='Time', data=time_df)
ax.bar_label(ax.containers[0])
plt.xlabel('\nBoarding Methods')
plt.ylabel('Mean Time')
plt.grid()
plt.show()
