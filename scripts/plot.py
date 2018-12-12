#!/usr/bin/env python3

import numpy as np
import matplotlib.animation as animation
import matplotlib.pyplot as plt
import os
import shutil
import time
import sys

save_count = 0
def plot(data, max_r=10,save_to=None, save_freq=100, interval=20,
				disabled_trajectories=[], compare=None, energy=None, poincare=False):
	fig = plt.figure()
	N_BODIES = int(data[0][0])
	disabled_trajectories = {x%N_BODIES for x in disabled_trajectories}
	colors = np.zeros(N_BODIES)
	colors[-1]= 100.
	colors[-2]= 50.
	data=data[1:]
	print("Preparing plots")
	if compare:
		compare_len = data.shape[0]//N_BODIES
		ax = fig.add_subplot(211,autoscale_on=False, xlim=(-max_r, max_r), ylim=(-max_r, max_r))
		ax2 = fig.add_subplot(212,autoscale_on=False, xlim=(0, compare_len), ylim=(0,.005))
		dx = []
		dx_plot = ax2.plot([],[])[0]
	if poincare:
		ax = fig.add_subplot(211,autoscale_on=False, xlim=(-max_r, max_r), ylim=(-max_r, max_r))
		ax2 = fig.add_subplot(212,autoscale_on=False, xlim=(-max_r, max_r), ylim=(-np.pi,np.pi))
		ax.plot(np.linspace(-max_r,max_r, num=10), np.zeros(10), linestyle="--")
		sections = []
		sections_colors = []
		poincare_section = ax2.scatter([],[],s=10,cmap=plt.get_cmap("seismic"))
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
		if energy:
			for body in energy:
				e_kin = np.linalg.norm(coords[body][3:])**2/2.
				#e_pot = -100./np.linalg.norm(coords[body][:3] - coords[1][:3])
				#e_pot+= -100./np.linalg.norm(coords[body][:3] - coords[2][:3])
				e_pot = 0
				e_pot+= 50.*np.log(np.linalg.norm(coords[body][:3] - coords[1][:3]))
				e_pot+= 100.*np.log(np.linalg.norm(coords[body][:3] - coords[1][:3]))
				#print(e_kin+e_pot,e_kin,e_pot)
		if poincare and len(history[0])>=2:
			if history[0][-2][1]*history[0][-1][1]<0:
				angle = np.angle(np.complex(history[0][-1][3], history[0][-1][4]))
				sections.append([history[0][-1][0], angle])
				print(sections[-1])
				poincare_section.set_offsets(sections)
			return trajectories + [scat, poincare_section]
		if compare:
			dx.append(np.linalg.norm(coords[compare[0]] - coords[compare[1]]))
			dx_plot.set_data(range(len(dx)), dx/dx[0]-1.)
			if len(dx)==compare_len: plt.savefig("compare_short.png")
			#if(len(dx)>=10): raise KeyboardInterrupt
			return trajectories + [scat, dx_plot]
		return trajectories + [scat]
	print("Starting animation")
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
