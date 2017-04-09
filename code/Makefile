CXX= g++ -std=c++11
CXXFLAGS= -pthread -Wall -Wextra -g

LDFLAGS= -lncurses -lpanel -L${OSPL_HOME}/lib/ -ldcpssacpp -lddskernel -lz
INCLUDES= -Iinclude/ -Isrc/ -Ibin/idl -I${OSPL_HOME}/include/dcps/C++/SACPP/

OBJDIR = obj
IDL_SRC= idl/SuperChat.idl
OSDDS_SRC= src/DDSEntityManager.cpp src/CheckStatus.cpp \
           src/chat_room.cpp src/message.cpp src/user.cpp src/osdds_io.cpp
OSDDS_IDL_GEN= bin/idl/SuperChat.cpp bin/idl/SuperChatSplDcps.cpp \
               bin/idl/SuperChatDcps.cpp bin/idl/SuperChatDcps_impl.cpp
INTERFACE_SRC= src/model.cpp src/main.cpp

BINDIR = bin
IDLBINDIR = bin/idl

all: bin/superchat

bin/superchat: $(OSDDS_IDL_GEN) osdds.o 
	@echo Final linking and compilation...
	$(CXX) $(CXXFLAGS) $(OBJDIR)/* $(INTERFACE_SRC) $(INCLUDES) $(LDFLAGS) -o $(BINDIR)/superchat

$(OSDDS_IDL_GEN): $(IDL_SRC)
	mkdir -p $(IDLBINDIR) $(OBJDIR)
	@echo Building IDL sources files...
	idlpp -I ${OSPL_HOME}/etc/idl -l cpp $(IDL_SRC) -d $(IDLBINDIR)/

osdds.o: $(OSDDS_SRC)
	@echo Compiling opensplice files...
	$(CXX) $(INCLUDES) $(OSDDS_SRC) $(OSDDS_IDL_GEN) $(LDFLAGS) -c
	@mv *.o $(OBJDIR)/

clean:
	@echo Deleting $(shell ls $(BINDIR))...
	rm -r $(BINDIR) 
	@echo Deleting object files $(shell ls $(OBJDIR))...
	rm -r $(OBJDIR)

test:
	@echo Test targets here...
