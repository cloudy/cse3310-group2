CXX= g++ -std=c++11
CXXFLAGS= -pthread -Wall -Wextra -g

LDFLAGS= -lncurses -lpanel -L${OSPL_HOME}/lib/ -ldcpssacpp -lddskernel -lz
INCLUDES= -Iinclude/ -I$src/ -Ibin/idl -I${OSPL_HOME}/include/dcps/C++/SACPP/

OBJDIR= obj
BINDIR= bin
SRCDIR= src
IDLBINDIR= $(BINDIR)/idl
OUTPUT= $(BINDIR)/superchat

IDL_SRC= idl/SuperChat.idl
OSDDS_SRC= $(SRCDIR)/DDSEntityManager.cpp $(SRCDIR)/CheckStatus.cpp \
           $(SRCDIR)/chat_room.cpp $(SRCDIR)/message.cpp $(SRCDIR)/user.cpp $(SRCDIR)/osdds_io.cpp
OSDDS_IDL_GEN= $(IDLBINDIR)/SuperChat.cpp $(IDLBINDIR)/SuperChatSplDcps.cpp \
               $(IDLBINDIR)/SuperChatDcps.cpp $(IDLBINDIR)/SuperChatDcps_impl.cpp
INTERFACE_SRC= $(SRCDIR)/model.cpp
all : MAIN_SRC= $(SRCDIR)/main.cpp
test: MAIN_SRC= $(SRCDIR)/test.cpp

all: bin/superchat

bin/superchat: $(OSDDS_IDL_GEN) OSDDS_OBJ 
	@echo Final linking and compilation...
	$(CXX) $(CXXFLAGS) $(OBJDIR)/* $(INTERFACE_SRC) $(MAIN_SRC) $(INCLUDES) $(LDFLAGS) -o $(OUTPUT)

$(OSDDS_IDL_GEN): $(IDL_SRC)
	mkdir -p $(IDLBINDIR) $(OBJDIR)
	@echo Building IDL sources files...
	idlpp -I ${OSPL_HOME}/etc/idl -l cpp $(IDL_SRC) -d $(IDLBINDIR)/

OSDDS_OBJ: $(OSDDS_SRC)
	@echo Compiling opensplice files...
	$(CXX) $(INCLUDES) $(OSDDS_SRC) $(OSDDS_IDL_GEN) $(LDFLAGS) -c
	@mv *.o $(OBJDIR)/

clean:
	@echo Deleting $(shell ls $(BINDIR))...
	rm -r $(BINDIR) 
	@echo Deleting object files $(shell ls $(OBJDIR))...
	rm -r $(OBJDIR)

test:  bin/superchat
	./bin/superchat
