# build helloworld executable when user executes "make" 

#helloworld: helloworld.o
#	$(GCC) $(LDFLAGS) helloworld.o -o helloworld

#helloworld.o: helloworld.c 
#	$(GCC) $(CFLAGS) -c helloworld.c 

# remove object files and executable when user executes "make clean"
#clean:
#	rm *.o helloworld 

helloworld: ipp_server.o op_action.o stringprocessor.o
	$(GCC) $(LDFLAGS) ipp_server.o op_action.o stringprocessor.o -o helloworld

ipp_server.o: ipp_server.c stringprocessor.h op_action.h
	$(GCC) $(CFLAGES) -c ipp_server.c

op_action.o: op_action.c op_action.h
	$(GCC) $(CFLAGES) -c op_action.c

stringprocessor.o: stringprocessor.c stringprocessor.h
	$(GCC) $(CFLAGES) -c stringprocessor.c

