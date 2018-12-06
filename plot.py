#!/usr/bin/env python3

import numpy as np
import matplotlib.animation as animation
import matplotlib.pyplot as plt
import os
import shutil
import time
import sys

save_count = 0
def plot(data, max_r=10,save_to=None, save_freq=100, interval=20, disabled_trajectories=[], compare=None):
	fig = plt.figure()
	N_BODIES = int(data[0][0])
	disabled_trajectories = {x%N_BODIES for x in disabled_trajectories}
	colors = np.zeros(N_BODIES)
	colors[-1]= 100.
	colors[-2]= 50.
	data=data[1:]
	if compare:
		ax = fig.add_subplot(211,autoscale_on=False, xlim=(0,20), ylim=(-40,-20))
		ax2 = fig.add_subplot(212,autoscale_on=False, xlim=(0, 10))
		dx = []
		dx_plot = ax2.plot([],[])[0]
	else:
		ax = fig.add_subplot(111,autoscale_on=False, xlim=(-max_r,max_r), ylim=(-max_r,max_r))
	ax.grid()
	scat = ax.scatter(data[0:N_BODIES,0], data[0:N_BODIES,1], c=colors, animated=True)
	history = [[state] for state in data[0:N_BODIES]]
	trajectories = [ax.plot([],[])[0] for i in range(N_BODIES)]
	if save_to!=None:
		dir = os.path.join("png",save_to)
		if os.path.exists(dir):
			print("WARNING removing {}".format(dir))
			time.sleep(1.)
			shutil.rmtree(dir)
	def animate(i):
		global save_count
		coords = data[N_BODIES*i:N_BODIES*i+N_BODIES]
		scat.set_offsets(coords[:,:2])
		for body in range(coords.shape[0]):
			if body in disabled_trajectories:
				continue
			history[body].append(list(coords[body]))
			h_array = np.array(history[body][:])
			trajectories[body].set_data(h_array[-1000:,0], h_array[-1000:,1])
		if save_to!=None and i % save_freq == 0:
			path = os.path.join("png",save_to,"evolution-{}.png".format(save_count))
			save_count+=1
			os.makedirs(os.path.dirname(path), exist_ok=True)
			fig.savefig(path, dpi=100)
		if compare:
			dx.append(np.linalg.norm(coords[compare[0]] - coords[compare[1]]))
			dx_plot.set_data(range(len(dx)), dx/dx[0])
			ax2.set_ylim(min(dx[:10])/dx[0], max(dx[:10])/dx[0])
			if(i==10): plt.show()
			return trajectories + [scat, dx_plot]
		return trajectories + [scat]
	anim = animation.FuncAnimation(fig, animate, np.arange(1, data.shape[0]//N_BODIES),
															  interval=interval, blit=True)
	#anim.save("evolution.gif", writer="imagemagick")
	plt.show()

def plot_from_file(file_name = "evolution.txt", **kwargs):
	data = np.loadtxt(file_name)
	plot(data, 10., **kwargs)


if __name__=="__main__":
	if len(sys.argv)==2:
		plot_from_file(sys.argv[1])
	else:
		plot_from_file()
