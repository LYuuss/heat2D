import pandas as pd
import matplotlib.pyplot as plt

data = pd.read_csv("build/heat_output.csv", header=None)

plt.imshow(data, cmap="hot")
plt.colorbar(label="Temperature")
plt.title("Heat2D simulation")
plt.show()