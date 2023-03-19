import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
# import seaborn as sns

data = pd.read_csv('build1/output.csv', names=["x_acc", "y_acc", "x_vel", "y_vel", "x_pos", "y_pos"])


y = []
for i in range(len(list(data.x_acc))):
    value = i * (1/60)   # Calculate the value as a multiple of 1/60
    y.append(value)  # Add the value to the y

# print(y)
fig, axes = plt.subplots(nrows=3, ncols=2, figsize=(10, 9.5))
for i in range(6):
    axes.flat[i].set_xlabel("time")
    axes.flat[i].set_title(f"Plot {i+1}")

axes.flat[0].set_ylabel("position x direction")
axes.flat[1].set_ylabel("position y direction")
axes.flat[2].set_ylabel("velocity x direction")
axes.flat[3].set_ylabel("velocity y direction")
axes.flat[4].set_ylabel("acceleration x direction")
axes.flat[5].set_ylabel("acceleration y direction")
axes.flat[0].plot(y, list(data.x_pos))
axes.flat[1].plot(y, list(data.y_pos))
axes.flat[2].plot(y, list(data.x_vel))
axes.flat[3].plot(y, list(data.y_vel))
axes.flat[4].plot(y, list(data.x_acc))
axes.flat[5].plot(y, list(data.y_acc))
plt.tight_layout()
plt.show()
