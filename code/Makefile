CXX= g++ -std=c++11
CXXFLAGS= -pthread -Wall -Wextra -g

LDFLAGS= -lncurses -lpanel -L${OSPL_HOME}/lib/ -ldcpssacpp -lddskernel
INCLUDES= -Iinclude/ -Isrc/ -Ibin/idl -I${OSPL_HOME}/include/dcps/C++/SACPP/

OBJDIR = obj/
IDL_SRC= idl/SuperChat.idl
OSDDS_SRC= src/DDSEntityManager.cpp src/CheckStatus.cpp \
                                     src/chat_room.cpp \
                                     src/message.cpp src/user.cpp
OSDDS_IDL_GEN= bin/idl/SuperChatDcps_impl.h bin/idl/SuperChat.cpp \
                                     bin/idl/SuperChatSplDcps.cpp bin/idl/SuperChatDcps.cpp \
                                     bin/idl/SuperChatDcps_impl.cpp bin/idl/ccpp_SuperChat.h \
                                     bin/idl/SuperChatDcps.h bin/idl/SuperChat.h bin/idl/SuperChatSplDcps.h
INTERFACE_SRC= src/model.cpp src/main.cpp

all: idlpp.make osdds.o 
	@echo Final linking and compilation...
	$(CXX) $(CXXFLAGS) $(OBJDIR)* $(INTERFACE_SRC) $(INCLUDES) $(LDFLAGS) -o bin/superchat

idlpp.make: $(IDL_SRC) $(OSDDS_SRC)
	mkdir -p bin/idl obj
	@echo Building IDL sources files...
	idlpp -I ${OSPL_HOME}/etc/idl -l cpp $(IDL_SRC) -d bin/idl

osdds.o: $(OSDDS_SRC) $(IDLPP_GEN_SRC)
	@echo Compiling opensplice files...
	$(CXX) $(INCLUDES) $(OSDDS_SRC) $(OSDDS_IDL_GEN) $(LDFLAGS) -c
	@mv *.o $(OBJDIR)/

clean:
	@echo Deleting $(shell ls bin/)...
	rm -rf bin/* 
	@echo Deleting object files $(shell ls obj/)...
	rm obj/*


