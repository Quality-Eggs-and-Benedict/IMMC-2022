# IMMC-2022 - Quality Eggs and Benedict

The following repository contains the source code for models created for the 2022 IMMC by Quality Eggs and Benedict. <br>
The `IMMC_main_model.cpp` file is the main entry point, where you can select a model to run, where it will be iterated over and saved.

## Create Graphs
### KDE Plots
![KDE Plot Image](https://github.com/garv-shah/IMMC-2022/blob/main/images/kde_plot.png?raw=true) <br>
To generate a KDE plot, you can use the `generate_graph.py` python script. This takes the `data_output.csv` file and generates a graph.

### Bar Plots
![Bar Plot Image](https://github.com/garv-shah/IMMC-2022/blob/main/images/bar_plot.png?raw=true) <br>
To generate a bar plot, you can use the `generate_bar_graph.py` python script. This the csv files in `model_outputs` and creates a graph combining all of their values for comparison. <br>
As these graphs contain multiple models, you can specify which models you would like to be displayed using the model_list variable. Order matters, meaning the first string in the list corresponds to the first bar on the graph. All possible values currently are:

- 'random_model'
- 'boarding_by_section'
- "boarding_by_section (10% disobey)"
- 'boarding_by_seat'
- "boarding_by_seat (10% disobey)"
- 'back_to_front'
- 'steffen_method'
- 'random_model (30% capacity)'
- 'random_model (50% capacity)'
- 'random_model (70% capacity)'
- 'back_to_front (30% capacity)'
- 'back_to_front (50% capacity)'
- 'back_to_front (70% capacity)'

Iterations also needs to specified in this file to alter the size of the buckets. By default it is 1000, but should be changed if you wish to run more trials.
<br>
You can also edit the name of the csv file generated (and subsequently the name of the bar/plot) in the individual model files, by altering the csv string.

### Multiple Bivariate KDE Plots
![Multiple Bivariate KDE Plot](https://github.com/Quality-Eggs-and-Benedict/IMMC-2022/blob/main/images/final_kde_plot.png?raw=true) <br>
Similar to the Bar Plots, you can use `generate_multi_graph.py` to create multiple probability density plots on the same axes. In the same way, a model_list can be defined to display certain generated models, but unlike the Bar Plots, this doesn't impact the order of the graphs, as they are all on the same axes. Iterations also does not exist here, while the csv file name system is the same.
