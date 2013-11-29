CXX = /usr/bin/g++
DEBUG_FLAG = -g -Werror $(DEBUG_OPTIONS)
LIBS := -lpthread
#-I头文件所在目录，-L库文件所在目录
#DEBUG_FLAG = -O2 -Wall -g -I../base
#LDFLAGS = -s

OBJS = Global.o CThread.o zService.o MainLoop.o Service.o TCPServer.o TcpTask.o Log.o
PLIB = libpublic.a

all:$(PLIB)

$(OBJS):%.o:%.cpp
	$(CXX) -c $(DEBUG_FLAG) $< -o $@
#ar 打包多文件，ranlib相当于ar -s 不过为了兼容之前版本的Makefile 还是这么写
$(PLIB):$(OBJS)
	@rm -rf $(PLIB)
	@ar cru $(PLIB) $(OBJS)
	@ranlib $(PLIB)
clean:
	rm -f *.o $(PLIB)

