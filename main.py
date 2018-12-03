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
	print("Plotting {} bodies".format(data[0][1]))
	data[0][2] = time
	for i in range(size):
		planet = planets[i]
		assert(len(planet.pos)==2)
		assert(len(planet.vel)==2)
		planet.mass = float(planet.mass)
		data[i+1] = planet.pos + [0] + planet.vel + [0, planet.mass]
	np.savetxt("system.txt", data, fmt='%.4f')
	print(data)

def run_simulation(true_gravity=False, debug=False):
	if true_gravity:
		simulation_output = subprocess.Popen(["./true_main"], stdout=subprocess.PIPE).communicate()[0]
	else:
		simulation_output = subprocess.Popen(["./main"], stdout=subprocess.PIPE).communicate()[0]
	if debug:
		for line in simulation_output.split(b'\n'):
			print(line)
	data = np.loadtxt(io.BytesIO(simulation_output))
	return data

def remove_momentum(bodies):
	total_p = np.array([0.,0.])
	M = 0.
	for b in bodies:
		total_p += [b.vel[0]*b.mass, b.vel[1]*b.mass]
		M += b.mass
	for b in bodies:
		b.vel[0] -= total_p[0]/M
		b.vel[1] -= total_p[1]/M
		print(b.vel)

def centralize(bodies):
	cm = np.array([0.,0.])
	M = 0.
	for b in bodies:
		cm += [b.pos[0]*b.mass, b.pos[1]*b.mass]
		M += b.mass
	for b in bodies:
		b.pos[0] -= cm[0]/M
		b.pos[1] -= cm[1]/M
		print(b.vel)

def random3body():
	name = "random"
	r = 10.
	vel = .3
	mass = 1.
	rand = lambda : 2*(np.random.random() - 0.5)
	planets = []
	planets.append(Planet([r*rand(),r*rand()],[vel*rand(),vel*rand()], 1.))
	planets.append(Planet([r*rand(),r*rand()],[vel*rand(),vel*rand()], 1.))
	planets.append(Planet([r*rand(),r*rand()],[vel*rand(),vel*rand()], 1.))
	remove_momentum(planets)
	centralize(planets)
	dump_planets(planets, 1000.)
	data = run_simulation(true_gravity=True)
	plot.plot(data, 2*r, save_to=name)

def two_bodies_all_solutions():
	name = "two_bodies_all"
	r = 5.
	vel = 4
	mass = 1.
	planets = []
	planets.append(Planet([0.,0.],[0.,0.], 100.))
	for i in range(10):
		planets.append(Planet([r,0.],[0.,vel+i/10.*vel], 1.))
	dump_planets(planets, 200., active_planets=1)
	data = run_simulation(true_gravity=True)
	plot.plot(data, 10*r, save_to=name, save_freq=10)

def initial_conditions_pos():
	name = "initital_conditions"
	r = 40.
	vel = 2.
	mass = 1.
	planets = []
	planets.append(Planet([0.,0.],[0.,0.], 100.))
	planets.append(Planet([r,0.],[0.,vel], 100.))
	planets.append(Planet([0.7*r+0.001,      0.],[0.,-0.01*vel], 0.))
	planets.append(Planet([0.7*r,      0.],[0.,-0.01*vel], 0.))
	remove_momentum(planets)
	centralize(planets)
	dump_planets(planets, 100., active_planets=2)
	data = run_simulation(debug=True)
	plot.plot(data, 1.5*r)
	
def initial_conditions_vel():
	name = "initital_conditions"
	r = 40.
	vel = 2.
	mass = 1.
	planets = []
	planets.append(Planet([0.,0.],[0.,0.], 100.))
	planets.append(Planet([r,0.],[0.,vel], 100.))
	planets.append(Planet([0.7*r,      0.],[0.,-0.01*vel], 0.))
	planets.append(Planet([0.7*r,      0.],[0.,-0.0101*vel], 0.))
	remove_momentum(planets)
	centralize(planets)
	dump_planets(planets, 100., active_planets=2)
	data = run_simulation(debug=True)
	plot.plot(data, 1.5*r)

if __name__=="__main__":
	#initial_conditions_pos()	
	initial_conditions_vel()	
	#two_bodies_all_solutions()
	#random3body()
	
