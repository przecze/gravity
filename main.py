#!/usr/bin/env python3
import numpy as np
import plot
import io
import subprocess
import copy

class Planet:
	def __init__(self, pos, vel, mass, stationary=False):
		self.pos = pos
		self.vel = vel
		self.mass = mass
		self.stationary = stationary

def dump_planets(planets, time, active_planets=-1, one_over_r = False):
	size = len(planets)
	data = np.zeros((size + 1, 8))
	data[0][0] = size
	data[0][1] = size if active_planets==-1 else active_planets
	data[0][2] = 1. if one_over_r else 0.
	print("Dumping {} bodies".format(data[0][1]))
	data[0][3] = time
	for i in range(size):
		planet = planets[i]
		if len(planet.pos)==2:
				planet.pos = planet.pos + [0.]
		if len(planet.vel)==2:
				planet.vel = planet.vel + [0.]
		assert(len(planet.pos)==3)
		assert(len(planet.vel)==3)
		planet.mass = float(planet.mass)
		data[i+1] = planet.pos + planet.vel + [planet.mass, float(planet.stationary)]
	np.savetxt("system.txt", data, fmt='%.4f')

def run_simulation(debug=False):
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

def centralize(bodies):
	cm = np.array([0.,0.])
	M = 0.
	for b in bodies:
		cm += [b.pos[0]*b.mass, b.pos[1]*b.mass]
		M += b.mass
	for b in bodies:
		b.pos[0] -= cm[0]/M
		b.pos[1] -= cm[1]/M

def random3body():
	name = "random"
	r = 10.
	vel = .3
	mass = 1.
	rand = lambda : 2*(np.random.random() - 0.5)
	planets = []
	planets.append(Planet([r*rand(),r*rand(),0.],[vel*rand(),vel*rand()], 1.))
	planets.append(Planet([r*rand(),r*rand(),0.],[vel*rand(),vel*rand()], 1.))
	planets.append(Planet([r*rand(),r*rand(),1.],[vel*rand(),vel*rand()], 1.))
	remove_momentum(planets)
	centralize(planets)
	dump_planets(planets, 1000.)
	data = run_simulation()
	np.savetxt("random.txt", data, fmt='%.4f')
	plot.plot(data, 2*r, interval=10)

def triangle():
	name = "random"
	r = 10.
	vel = .3
	mass = 1.
	rand = lambda : 2*(np.random.random() - 0.5)
	planets = []
	planets.append(Planet([r*rand(),r*rand(),0.],[vel*rand(),vel*rand()], 1.))
	planets.append(Planet([r*rand(),r*rand(),0.],[vel*rand(),vel*rand()], 1.))
	planets.append(Planet([r*rand(),r*rand(),1.],[vel*rand(),vel*rand()], 1.))
	remove_momentum(planets)
	centralize(planets)
	dump_planets(planets, 1000.)
	data = run_simulation()
	np.savetxt("random.txt", data, fmt='%.4f')
	plot.plot(data, 2*r, interval=10)

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
	data = run_simulation()
	np.savetxt("two_bodies_all.txt", data, fmt='%.4f')
	plot.plot(data, 10*r, save_to=name, save_freq=10)

def initial_conditions(delta_x):
	name = "initital_conditions"
	r = 100.
	vel = 16.
	big_mass = 1000.
	planets = []
	planets.append(Planet([0.,0.],[0.,0.], big_mass, stationary=True))
	planets.append(Planet([1.2*r,0.],[0.,0.], big_mass, stationary=True))
	planets.append(Planet([.6*r,.6*r],[0.,0.], big_mass, stationary=True))
	probe = Planet([0.8*r,      0., 0.4*r],[-0.3*vel,-0.2*vel, 0.2*vel], 0.)
	probe2 = copy.deepcopy(probe)
	probe2.pos[0] *= (1+delta_x)
	probe3 = copy.deepcopy(probe)
	probe3.pos[0] *= (1+delta_x**2)
	planets.append(probe)
	planets.append(probe2)
	planets.append(probe3)
	remove_momentum(planets)
	centralize(planets)
	dump_planets(planets, 1000., active_planets=3, one_over_r=False)
	data = run_simulation(debug=False)
	#np.savetxt("butterfly.txt", data, fmt='%.4f')
	plot.plot(data, 1.5*r, interval=1, disabled_trajectories = (-1, -2))

if __name__=="__main__":
	initial_conditions(delta_x=0.01)	
	#two_bodies_all_solutions()
	#random3body()
	
