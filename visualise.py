import pandas as pd
import matplotlib
matplotlib.use("Agg")  # pas de fenêtre — export direct
import matplotlib.pyplot as plt
import matplotlib.gridspec as gridspec

# ── Chargement ──────────────────────────────────────────────────────────────
df = pd.read_csv("bezier.csv")

# colonnes : x, y, dot, cross, angleDeg, t, qx, qy, bestCoordonatesx, bestCoordonatesy
courbe   = df[["x", "y"]]
q        = (df["qx"].iloc[0], df["qy"].iloc[0])
best     = (df["bestCoordonatesx"].iloc[-1], df["bestCoordonatesy"].iloc[-1])

# ── Figure ───────────────────────────────────────────────────────────────────
fig = plt.figure(figsize=(14, 10))
fig.suptitle("Analyse de la courbe de Bézier", fontsize=15, fontweight="bold")

gs = gridspec.GridSpec(2, 2, figure=fig, hspace=0.4, wspace=0.35)

# ── Ax1 : courbe Bézier + point Q + point le plus proche ────────────────────
ax1 = fig.add_subplot(gs[0, 0])
ax1.plot(courbe["x"], courbe["y"], color="royalblue", linewidth=2.5, label="Courbe Bézier")
ax1.scatter(*q,    color="crimson",     zorder=5, s=80, label=f"Q ({q[0]:.3f}, {q[1]:.3f})")
ax1.scatter(*best, color="limegreen",   zorder=5, s=80, marker="*",
            label=f"Plus proche ({best[0]:.3f}, {best[1]:.3f})")
ax1.set_title("Courbe Bézier")
ax1.set_xlabel("x")
ax1.set_ylabel("y")
ax1.legend(fontsize=7)
ax1.grid(True, linestyle="--", alpha=0.5)
ax1.set_aspect("equal", adjustable="datalim")

# ── Ax2 : angle en degrés le long de t ──────────────────────────────────────
ax2 = fig.add_subplot(gs[0, 1])
ax2.plot(df["t"], df["angleDeg"], color="darkorange", linewidth=1.8)
ax2.axhline(0, color="gray", linewidth=0.8, linestyle="--")
ax2.set_title("Angle local (degrés) en fonction de t")
ax2.set_xlabel("t  (index)")
ax2.set_ylabel("Angle (°)")
ax2.grid(True, linestyle="--", alpha=0.5)

# ── Ax3 : dot product ────────────────────────────────────────────────────────
ax3 = fig.add_subplot(gs[1, 0])
ax3.plot(df["t"], df["dot"], color="steelblue", linewidth=1.8, label="dot")
ax3.set_title("Produit scalaire (dot) en fonction de t")
ax3.set_xlabel("t  (index)")
ax3.set_ylabel("dot")
ax3.grid(True, linestyle="--", alpha=0.5)

# ── Ax4 : cross product ──────────────────────────────────────────────────────
ax4 = fig.add_subplot(gs[1, 1])
ax4.plot(df["t"], df["cross"], color="mediumpurple", linewidth=1.8, label="cross")
ax4.axhline(0, color="gray", linewidth=0.8, linestyle="--")
ax4.set_title("Produit vectoriel (cross) en fonction de t")
ax4.set_xlabel("t  (index)")
ax4.set_ylabel("cross")
ax4.grid(True, linestyle="--", alpha=0.5)

# ── Export ───────────────────────────────────────────────────────────────────
output = "bezier_analysis.png"
fig.savefig(output, dpi=150, bbox_inches="tight")
print(f"Figure exportée → {output}")