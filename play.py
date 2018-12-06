#!/usr/bin/env python3
import numpy as np
import plot
import os
import sys

data = np.loadtxt(os.path.join("resources", sys.argv[1]+".txt"))
kwargs = {
	"butterfly" : {"max_r":150, "interval":10, "compare":[1,2]},
	"stable" : {},
	"collision" : {},
	"ejection" : {},
  "two_bodies" : {"max_r":50}
}[sys.argv[1]]
plot.plot(data, **kwargs)
