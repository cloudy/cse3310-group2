CXX= g++ -std=c++11
CXXFLAGS= -pthread

LDFLAGS= -lncurses -lpanel -L${OSPL_HOME}/lib/ -ldcpssacpp -lddskernel
INCLUDES= -Iinclude/ -Isrc/ -Ibin/ -I${OSPL_HOME}/include/dcps/C++/SACPP/

IDL_SRC= idl/SuperChat.idl
GUI_SRC= src/view.cpp
OSDDS_SRC= src/DDSEntityManager.cpp src/CheckStatus.cpp src/SuperChat.cpp
INTERFACE_SRC= src/chat_room.cpp  src/controller.cpp  \
                                     src/message.cpp src/user.cpp \
                                     src/model.cpp src/main.cpp
IDLPP_GEN_SRC= bin/SuperChatDcps_impl.h bin/SuperChat.cpp \
                                     bin/SuperChatSplDcps.cpp bin/SuperChatDcps.cpp \
                                     bin/SuperChatDcps_impl.cpp bin/ccpp_SuperChat.h \
                                     bin/SuperChatDcps.h bin/SuperChat.h bin/SuperChatSplDcps.h

all: idlpp.make view.o osdds.o
	@echo Final linking and compilation...
	$(CXX) $(CXXFLAGS) view.o $(INTERFACE_SRC) $(INCLUDES) $(LDFLAGS) -o bin/SuperChat
	@echo Deleting object files...
	rm *.o

idlpp.make: $(IDL_SRC)
	mkdir -p bin
	@echo Building IDL sources files...
	idlpp -I ${OSPL_HOME}/etc/idl -l cpp $(IDL_SRC) -d bin/

view.o: $(GUI_SRC)
	@echo Compiling gui files...
	$(CXX) $(GUI_SRC) $(INCLUDES) $(LDFLAGS) -c
 
osdds.o: $(OSDDS_SRC) $(IDLPP_GEN_SRC)
	@echo Compiling opensplice files...
	$(CXX) $(INCLUDES) $(OSDDS_SRC) $(IDLPP_GEN_SRC) $(LDFLAGS) -o bin/SuperChatDavis

clean:
	@echo Deleting $(shell ls bin/)...
	rm bin/*