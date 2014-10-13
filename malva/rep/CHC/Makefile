include ../../environment

all: MainSeq MainLan

clean:
	rm -f MainLan MainSeq MainTest *.o *% *~

MainSeq: CHC.req.o CHC.pro.o MainSeq.o
	$(CXX) $(LDFLAGS) $^ $(LOADLIBES) $(CPPFLAGS) -o $@

MainLan: CHC.req.o CHC.pro.o MainLan.o
	$(CXX) $(LDFLAGS) $^ $(LOADLIBES) $(CPPFLAGS) -o $@

MainWan: CHC.req.o CHC.pro.o MainWan.o
	$(CXX) $(LDFLAGS) $^ $(LOADLIBES) $(CPPFLAGS) -o $@

LAN:
	$(RUN) -np 10 ./MainLan Config.cfg

WAN:
	$(RUN) -v  -p4pg pgfileWan MainWan

SEQ:
	./MainSeq CHC.cfg $(INSTANCES)/mt06.fjs res/sol_abz5.txt ./gantt/data/diffe.fjs

MainTest: CHC.req.o CHC.pro.o MainTest.o
	$(CXX) $(LDFLAGS) $^ $(LOADLIBES) $(CPPFLAGS) -o $@

TEST:
	./MainTest $(INSTANCES)/mt06.fjs
