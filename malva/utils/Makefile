include ../environment


all:	MainGantt

clean:
	rm -f MainGantt *.o *% *~

MainGantt: $(GA_DIR)/newGA.req.o $(GA_DIR)/newGA.pro.o GanttGenerator.o
	$(CXX) $(LDFLAGS) $^ $(LOADLIBES) $(CPPFLAGS) -o $@


