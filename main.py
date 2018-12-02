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

def dump_planets(planets, time, active_planets=-1):
	size = len(planets)
	data = np.zeros((size + 1, 7))
	data[0][0] = size
	data[0][1] = size if active_planets==-1 else active_planets
	print(data[0][1])
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

def random3body():
	name = "random"
	r = 5.
	vel = .3
	mass = 1.
	rand = lambda : 2*(np.random.random() - 0.5)
	planets = []
	planets.append(Planet([r*rand(),r*rand()],[vel*rand(),vel*rand()], 1.))
	planets.append(Planet([r*rand(),r*rand()],[vel*rand(),vel*rand()], 1.))
	planets.append(Planet([r*rand(),r*rand()],[vel*rand(),vel*rand()], 1.))
	dump_planets(planets, 1000.)
	data = run_simulation()
	plot.plot(data, 2*r, save_to=name)

def main():
	name = "two_bodies_all"
	r = 5.
	vel = 4
	mass = 1.
	planets = []
	planets.append(Planet([0.,0.],[0.,0.], 100.))
	for i in range(10):
		planets.append(Planet([r,0.],[0.,vel+i/10.*vel], 1.))
	dump_planets(planets, 200., active_planets=1)
	data = run_simulation()
	plot.plot(data, 2*r, save_to=name, save_freq=10)
	
if __name__=="__main__":
	main()	
