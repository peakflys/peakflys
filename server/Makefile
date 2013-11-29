CXX = /usr/bin/g++
#-I头文件所在目录，-L库文件所在目录
DEBUG_FLAG = -I../public -L../public -g -Werror $(DEBUG_OPTIONS)
DEBUG_FLAGS = -I../public -L../public -lpublic -lpthread -g -Werror $(DEBUG_OPTIONS)
LIBS := ../public/libpublic.a

OBJS = MainServer.o 
PRJNAME = MyServer

all:$(PRJNAME)
$(OBJS):%.o:%.cpp
	$(CXX) -c $(DEBUG_FLAG) $< -o $@
$(PRJNAME):$(OBJS) $(LIBS)
	$(CXX) $(OBJS)  -o $@ $(DEBUG_FLAGS) 
clean:
	rm -f *.o core.* $(PRJNAME) 

#   有core文件时不编译
#	@if [-f core.*];then\
		echo "有core文件需要处理:";\
		ls core.*;\
	else\
		$(CXX) -c $(LIB_PATH) $< -o $@\
	fi
