import pandas as pd
import matplotlib.pyplot as plt

courbe = pd.read_csv("bezier.csv")
ctrl   = pd.read_csv("ctrl.csv")

fig, (ax1, ax3) = plt.subplots(1, 2)

ax1.plot(courbe["x"], courbe["y"], color="royalblue", linewidth=2.5, label="Courbe Bézier")
# ax2.plot(courbe["x"], courbe["angleDeg"], color="red", linewidth=2.5)
ax3.plot(courbe["t"], courbe["angleDeg"], color="green", linewidth=2.5)

plt.show()