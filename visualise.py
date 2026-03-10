import pandas as pd
import matplotlib.pyplot as plt

courbe = pd.read_csv("bezier.csv")
ctrl   = pd.read_csv("ctrl.csv")

fig, ax = plt.subplots(figsize=(8, 6))

ax.plot(courbe["x"], courbe["y"], color="royalblue", linewidth=2.5, label="Courbe Bézier")

ax.plot([ctrl["x"][0], ctrl["x"][1]], [ctrl["y"][0], ctrl["y"][1]], "--", color="gray", linewidth=1)
ax.plot([ctrl["x"][2], ctrl["x"][3]], [ctrl["y"][2], ctrl["y"][3]], "--", color="gray", linewidth=1)

couleurs = ["green", "orange", "orange", "red"]
for i, row in ctrl.iterrows():
    ax.plot(row["x"], row["y"], "o", color=couleurs[i], markersize=10, zorder=5)
    ax.annotate(f"  {row['label']}", xy=(row["x"], row["y"]), fontsize=9)

ax.set_title("Courbe de Bézier cubique")
ax.legend()
ax.grid(True, linestyle="--", alpha=0.5)
ax.set_aspect("equal")
plt.tight_layout()
plt.savefig("bezier.png", dpi=150)
print("OK — bezier.png sauvegardé")