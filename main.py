#!/usr/bin/env python3
import numpy as np
import plot
import io
import subprocess

class Planet:
	def __init__(self, pos, vel, mass):
		self.pos = pos
		self.vel = vel
		self.mass = mass

def dump_planets(planets, time):
	size = len(planets)
	data = np.zeros((size + 1, 7))
	data[0][0] = size
	data[0][1] = size
	data[0][2] = time
	for i in range(size):
		planet = planets[i]
		assert(len(planet.pos)==2)
		assert(len(planet.vel)==2)
		planet.mass = float(planet.mass)
		data[i+1] = planet.pos + [0] + planet.vel + [0, planet.mass]
	np.savetxt("system.txt", data, fmt='%.3f')
	print(data)

def run_simulation():
	simulation_output = subprocess.Popen(["./main"], stdout=subprocess.PIPE).communicate()[0]
	data = np.loadtxt(io.BytesIO(simulation_output))
	return data

def main():
	r = 10.
	vel = 10.
	mass = 1.
	p1 = Planet([r,0.],[0.,vel], 1.)
	p2 = Planet([0.,0.],[0.,0.], 1.)
	dump_planets([p1,p2], 1.)
	data = run_simulation()
	plot.plot(data, 2*r)
	
if __name__=="__main__":
	main()	
