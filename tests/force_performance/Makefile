%.out : %.cc scenario.h point_type.hpp
	g++ -O3 -o $@ $< -I.

%.time : %.out
	time -p ./$<

	
all : vector_one_loop.time vector_separate_loops.time boost_point.time vector_reduced_loops.time valarray.time
