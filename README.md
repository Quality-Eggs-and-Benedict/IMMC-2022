# IMMC-2022 - Quality Eggs and Benedict

The following repository contains the source code for models created for the 2022 IMMC by Quality Eggs and Benedict. <br>
The `IMMC_main_model.cpp` file is the main entry point, where you can select a model to run, where it will be iterated over and saved.

## Create Graphs
### KDE Plot
![KDE Plot Image](https://github.com/garv-shah/IMMC-2022/blob/main/images/kde_plot.png?raw=true) <br>
To generate a KDE plot, you can use the `generate_graph.py` python script. This takes the `data_output.csv` file and generates a graph.

### Bar Plot
![Bar Plot Image](https://github.com/garv-shah/IMMC-2022/blob/main/images/bar_plot.png?raw=true) <br>
To generate a bar plot, you can use the `generate_bar_graph.py` python script. This the csv files in `model_outputs` and creates a graph combining all of their values for comparison.
There are a few variables you might have to edit if you want to add more models or alter the number of iterations in this file. By default they are:

```python
model_list = ['random_model', 'boarding_by_section', 'boarding_by_seat']
iterations = 1000
```

You can also edit the name of the csv file generated in the individual model files, by altering the csv string.
