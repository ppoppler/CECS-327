# Makefile

OMNIORB_HOME=/usr

IDL=$(OMNIORB_HOME)/bin/omniidl
IDLFLAGS=-bcxx

INCLUDES=-I$(OMNIORB_HOME)/include -I$(OMNIORB_HOME)/include/omniORB4

LIBS=-L$(OMNIORB_HOME)/lib -lomnithread -lomniORB4

IDL_FILE = ../example.idl

.PHONY: all
all: server client

server: server.o MyExampleInterface_impl.o exampleSK.o
	$(CXX) -o $@ $^ $(LIBS)

server.o: server.cpp MyExampleInterface_impl.h

MyExampleInterface_impl.h: example.hh

client: client.o exampleSK.o
	$(CXX) -o $@ $^ $(LIBS)

MyExampleInterface_impl.o: MyExampleInterface_impl.cpp MyExampleInterface_impl.h example.hh

exampleSK.o: exampleSK.cc example.hh

exampleSK.cc example.hh: $(IDL_FILE)
	$(IDL) $(IDLFLAGS) $<

.PHONY: clean
clean:
	find . -maxdepth 1 -type f -name "*.bak" -exec rm -f {} \;
	find . -maxdepth 1 -type f -name "*.o" -exec rm -f {} \;
	find . -maxdepth 1 -type f -name "*.stackdump" -exec rm -f {} \;
	find . -maxdepth 1 -type f -name "*.exe" -exec rm -f {} \;
	find . -maxdepth 1 -type f -name "example.hh" -exec rm -f {} \;
	find . -maxdepth 1 -type f -name "exampleSK.cc" -exec rm -f {} \;

.cpp.o:
	$(CXX) $(CXXFLAGS) -o $@ -c $< $(INCLUDES)

.cc.o:
	$(CXX) $(CXXFLAGS) -o $@ -c $< $(INCLUDES)