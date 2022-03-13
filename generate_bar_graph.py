import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns

model_list = ['random_model', 'boarding_by_section', 'boarding_by_seat']
iterations = 1000

data_files = [pd.read_csv(f"./model_outputs/{model_name}.csv") for model_name in model_list]
time_df = pd.concat(data_files, ignore_index=True)
names = []
for model_name in model_list:
    for i in range(iterations):
        names.append(model_name)

time_df['Method'] = pd.DataFrame(names)
plt.style.use('seaborn-dark')
plt.figure(figsize=(7, 5))
sns.barplot(x='Method', y='Time', data=time_df)
plt.xlabel('\nBoarding Methods')
plt.ylabel('Time (s)')
plt.grid()
plt.show()
