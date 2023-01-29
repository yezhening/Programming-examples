#变量
targets = sequence_stack.exe link_stack.exe

#伪目标
.PHONY : all
all : $(targets) 

#规则
sequence_stack.exe : sequence_stack.cpp
	g++ -fexec-charset=GBK -o sequence_stack.exe sequence_stack.cpp

link_stack.exe : link_stack.cpp
	g++ -fexec-charset=GBK -o link_stack.exe link_stack.cpp

#伪目标
.PHONY : clean
clean :
	del $(targets)