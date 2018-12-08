#!/usr/bin/env python3
import numpy as np
import plot
import os
import sys

name_map = {
	"threeA": "collision",
	"threeB": "ejection",
	"threeC": "stable"
}
try:
	sys.argv[1] = name_map[sys.argv[1]]
except KeyError:
	pass
data = np.loadtxt(os.path.join("resources", sys.argv[1]+".txt"))
kwargs = {
	"butterfly" : {"max_r":150, "interval":30, "compare":[1,2]},
	"stable" : {"max_r":15},
	"collision" : {},
	"ejection" : {},
  "two_bodies" : {"max_r":50},
  "poincare" : {"max_r":120, "interval":1, "disabled_trajectories":[-1,-2], "energy":[0],
								 "poincare":True}
}[sys.argv[1]]
plot.plot(data, **kwargs)
