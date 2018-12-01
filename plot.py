#!/usr/bin/env python3

import numpy as np
import matplotlib.animation as animation
import matplotlib.pyplot as plt

N_BODIES = 0
def main():
	data = np.loadtxt("evolution.txt")
	fig = plt.figure()
	N_BODIES = int(data[0][0])
	print(N_BODIES)
	colors = np.zeros(N_BODIES)
	colors[-1]= 100.
	colors[-2]= 50.
	data=data[1:]
	max_r = 10.
	ax = fig.add_subplot(111,autoscale_on=False, xlim=(-max_r,max_r), ylim=(-max_r,max_r))
	ax.grid()
	scat = ax.scatter(data[0:N_BODIES,0], data[0:N_BODIES,1], c=colors, animated=True)
	history = [[[x,y]] for x,y in zip(data[0:N_BODIES,0], data[0:N_BODIES,1])]
	trajectories = [ax.plot([],[])[0] for i in range(N_BODIES)]
	def animate(i):
		coords = data[N_BODIES*i:N_BODIES*i+N_BODIES]
		scat.set_offsets(coords[:,:2])
		#for body in range(coords.shape[0]):
		#	history[body].append([coords[body][0], coords[body][1]])
		#	h_array = np.array(history[body])
		#	trajectories[body].set_data(h_array[:,0], h_array[:,1])
		return trajectories + [scat]
	ani = animation.FuncAnimation(fig, animate, np.arange(1, data.shape[0]//N_BODIES),
															  interval=50, blit=True)
	plt.show()
	#print("what!")


if __name__=="__main__":
	main()
