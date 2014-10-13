include ../../environment

all: MainLan MainSeq

clean:
	rm -f MainLan MainSeq MainWan MainTest MainGantt *.o *% *~

MainLan: newGA.req.o newGA.pro.o MainLan.o
	$(CXX) $(LDFLAGS) $^ $(LOADLIBES) $(CPPFLAGS) -o $@

MainWan: newGA.req.o newGA.pro.o MainWan.o
	$(CXX) $(LDFLAGS) $^ $(LOADLIBES) $(CPPFLAGS) -o $@

MainSeq: newGA.req.o newGA.pro.o MainSeq.o
	$(CXX) $(LDFLAGS) $^ $(LOADLIBES) $(CPPFLAGS) -o $@

MainTest: newGA.req.o newGA.pro.o MainTest.o
	$(CXX) $(LDFLAGS) $^ $(LOADLIBES) $(CPPFLAGS) -o $@

LAN:
	$(RUN) -np 10 ./MainLan Config.cfg

WAN:
	$(RUN) -v  -p4pg pgfileWan MainWan

SEQ:
	./MainSeq newGA.cfg $(INSTANCES)/mt06.fjs res/sol_abz6.txt gantt/data/abz6.fjs

TEST:
	./MainTest $(INSTANCES)/mt06.fjs

MainGantt: newGA.req.o newGA.pro.o GanttGenerator.o
	$(CXX) $(LDFLAGS) $^ $(LOADLIBES) $(CPPFLAGS) -o $@

GANTT:
	./MainGantt ./instances/mt06.fjs ./gantt/data/best.txt ./gantt/latex/best.txt
