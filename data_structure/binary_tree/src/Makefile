#变量
targets = binary_tree.exe threaded_binary_tree.exe

#伪目标
.PHONY : all
all : $(targets) 

#规则
binary_tree.exe : binary_tree.cpp
	g++ -fexec-charset=GBK -o binary_tree.exe binary_tree.cpp

threaded_binary_tree.exe : threaded_binary_tree.cpp
	g++ -fexec-charset=GBK -o threaded_binary_tree.exe threaded_binary_tree.cpp

#伪目标
.PHONY : clean
clean :
	del $(targets)