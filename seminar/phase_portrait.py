import matplotlib.pyplot as plt
import numpy as np
def phys_osc(x):
	return (x[1], np.sin(x[0]))
x_lim = (0, 2*np.pi)
y_lim = (-3,3)
x,y = np.meshgrid(np.linspace(*x_lim, num=20), np.linspace(*y_lim, num=20))
X,Y = phys_osc([x,y])
plt.quiver(x,y,X,Y)
plt.savefig("phase_portait.png")
