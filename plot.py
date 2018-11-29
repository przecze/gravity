#!/usr/bin/env python3

import numpy as np
import matplotlib.animation as animation
import matplotlib.pyplot as plt

def main():
	data = np.loadtxt("evolution.txt")
	fig = plt.figure()
	ax = fig.add_subplot(111, autoscale_on=False, xlim=(-200, 200), ylim=(-200, 200))
	ax.grid()
	print(data[:10,0], data[:10,1])
	plt.scatter(data[:,0], data[:,1])
	plt.show()
	def animate(i):
		print("what!")
		coords = data[3*i:3*i+3]
		ax.scatter(coords[:][0], coords[:][1])
	ani = animation.FuncAnimation(fig, animate, np.arange(1, 11),
															  interval=25, blit=True)
	print("what!")


if __name__=="__main__":
	main()
