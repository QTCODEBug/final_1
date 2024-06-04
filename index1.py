import matplotlib.pyplot as plt
import matplotlib.patches as patches

# Create a figure and axis
fig, ax = plt.subplots(figsize=(10, 7))

# Add FRDM-KL46Z board
ax.add_patch(patches.Rectangle((2, 6), 4, 2, edgecolor='black', facecolor='lightgrey', lw=2))
ax.text(4, 7, 'FRDM-KL46Z', horizontalalignment='center', verticalalignment='center', fontsize=12)

# Add MAG3110
ax.add_patch(patches.Rectangle((0.5, 4), 2, 1, edgecolor='black', facecolor='lightblue', lw=2))
ax.text(1.5, 4.5, 'MAG3110', horizontalalignment='center', verticalalignment='center', fontsize=10)
ax.plot([2, 2.5], [6, 4.5], 'k-', lw=2)  # Connection line
ax.plot([2, 2.5], [6, 4], 'k-', lw=2)  # Connection line

# Add LCD
ax.add_patch(patches.Rectangle((5.5, 4), 3, 1.5, edgecolor='black', facecolor='lightgreen', lw=2))
ax.text(7, 4.75, 'LCD', horizontalalignment='center', verticalalignment='center', fontsize=10)
ax.plot([6, 6], [6, 5.5], 'k-', lw=2)  # Connection line
ax.plot([6.5, 6.5], [6, 5.5], 'k-', lw=2)  # Connection line

# Add Green LED
ax.add_patch(patches.Circle((1, 1), 0.2, edgecolor='black', facecolor='green', lw=2))
ax.text(1, 0.5, 'Green LED\nGPIOB Pin 5', horizontalalignment='center', verticalalignment='center', fontsize=10)
ax.plot([2, 1], [6, 1.2], 'k-', lw=2)  # Connection line

# Add Red LED
ax.add_patch(patches.Circle((3, 1), 0.2, edgecolor='black', facecolor='red', lw=2))
ax.text(3, 0.5, 'Red LED\nGPIOE Pin 29', horizontalalignment='center', verticalalignment='center', fontsize=10)
ax.plot([4, 3], [6, 1.2], 'k-', lw=2)  # Connection line

# Add SW1
ax.add_patch(patches.Circle((6, 1), 0.2, edgecolor='black', facecolor='yellow', lw=2))
ax.text(6, 0.5, 'SW1\nGPIOC Pin 3', horizontalalignment='center', verticalalignment='center', fontsize=10)
ax.plot([6.5, 6], [6, 1.2], 'k-', lw=2)  # Connection line

# Add SW2
ax.add_patch(patches.Circle((8, 1), 0.2, edgecolor='black', facecolor='yellow', lw=2))
ax.text(8, 0.5, 'SW2\nGPIOC Pin 12', horizontalalignment='center', verticalalignment='center', fontsize=10)
ax.plot([7.5, 8], [6, 1.2], 'k-', lw=2)  # Connection line

# Add power and ground lines
ax.plot([4, 4], [6, 5], 'k-', lw=2)  # Power line
ax.plot([4, 4], [2, 3], 'k-', lw=2)  # Ground line
ax.text(4.2, 5.5, 'Power', verticalalignment='center', fontsize=10)
ax.text(4.2, 2.5, 'Ground', verticalalignment='center', fontsize=10)

# Set limits and hide axes
ax.set_xlim(0, 10)
ax.set_ylim(0, 8)
ax.axis('off')

# Save the diagram
diagram_path = "/mnt/data/hardware_schematic_diagram.png"
plt.savefig(diagram_path)
plt.show()

# Provide the file path for the user
diagram_path
