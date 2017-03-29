CXX= g++ -std=c++11
CXXFLAGS= -pthread

LDFLAGS= -lncurses -lpanel
INCLUDES= -Iinclude/

IDL_SRC= idl/SuperChat.idl
GUI_SRC= src/view.cpp
OSDDS_SRC= //INSERT SRC HERE//
INTERFACE_SRC= src/chat_room.cpp  src/controller.cpp  \
									 src/message.cpp src/user.cpp \
									 src/model.cpp src/main.cpp
IDLPP_GEN_SRC= bin/SuperChatDcps_impl.h bin/SuperChat.cpp \
                                     bin/SuperChatSplDcps.cpp bin/SuperChatDcps.cpp \
                                     bin/SuperChatDcps_impl.cpp bin/ccpp_SuperChat.h \
                                     bin/SuperChatDcps.h bin/SuperChat.h bin/SuperChatSplDcps.h

all: idlpp.make view.o osdds.o
	@echo Final linking and compilation...
	$(CXX) $(CXXFLAGS) view.o $(INTERFACE_SRC) $(INCLUDES) $(LDFLAGS) -o ./bin/SuperChat
	@echo Deleting object files...
	rm *.o

idlpp.make: $(IDL_SRC)
	mkdir -p bin
	@echo Building IDL sources files...
	idlpp -I ${OSPL_HOME}/etc/idl -l cpp $(IDL_SRC) -d bin/

view.o: $(GUI_SRC)
	@echo Compiling gui files...
	$(CXX) $(GUI_SRC) $(INCLUDES) $(LDFLAGS) -c
 
osdds.o:
	@echo Compiling opensplice files...
	touch osdds.o

clean:
	@echo Deleting $(shell ls bin/)...
	rm bin/*