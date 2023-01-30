#变量
targets = sequence_queue.exe link_queue.exe

#伪目标
.PHONY : all
all : $(targets) 

#规则
sequence_queue.exe : sequence_queue.cpp
	g++ -fexec-charset=GBK -o sequence_queue.exe sequence_queue.cpp

link_queue.exe : link_queue.cpp
	g++ -fexec-charset=GBK -o link_queue.exe link_queue.cpp

#伪目标
.PHONY : clean
clean :
	del $(targets)