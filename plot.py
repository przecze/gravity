#!/usr/bin/env python3

import numpy as np
import matplotlib.animation as animation
import matplotlib.pyplot as plt
import os
import shutil
import time

def plot(data, max_r,save_to=None, save_freq=100):
	fig = plt.figure()
	N_BODIES = int(data[0][0])
	print(N_BODIES)
	print(data)
	colors = np.zeros(N_BODIES)
	colors[-1]= 100.
	colors[-2]= 50.
	data=data[1:]
	ax = fig.add_subplot(111,autoscale_on=False, xlim=(-max_r,max_r), ylim=(-max_r,max_r))
	ax.grid()
	scat = ax.scatter(data[0:N_BODIES,0], data[0:N_BODIES,1], c=colors, animated=True)
	history = [[[x,y]] for x,y in zip(data[0:N_BODIES,0], data[0:N_BODIES,1])]
	trajectories = [ax.plot([],[])[0] for i in range(N_BODIES)]
	if save_to!=None:
		dir = os.path.join("png",save_to)
		if os.path.exists(dir):
			print("WARNING removing {}".format(dir))
			time.sleep(1.)
			shutil.rmtree(dir)
	def animate(i):
		coords = data[N_BODIES*i:N_BODIES*i+N_BODIES]
		scat.set_offsets(coords[:,:2])
		for body in range(coords.shape[0]):
			history[body].append([coords[body][0], coords[body][1]])
			h_array = np.array(history[body])
			trajectories[body].set_data(h_array[:,0], h_array[:,1])
		if save_to!=None and i % save_freq == 0:
			path = os.path.join("png",save_to,"evolution{0:05d}.png".format(i))
			os.makedirs(os.path.dirname(path), exist_ok=True)
			fig.savefig(path)
		return trajectories + [scat]
	anim = animation.FuncAnimation(fig, animate, np.arange(1, data.shape[0]//N_BODIES),
															  interval=10, blit=True)
	#anim.save("evolution.gif", writer="imagemagick")
	plt.show()

def plot_from_file():
	data = np.loadtxt("evolution.txt")
	plot(data, np.max(data))


if __name__=="__main__":
	plot_from_file()
