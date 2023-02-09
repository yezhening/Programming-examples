#变量
targets = linear_search.exe

#伪目标
.PHONY : all
all : $(targets) 

#规则
linear_search.exe : linear_search.cpp
	g++ -fexec-charset=GBK -o linear_search.exe linear_search.cpp

#伪目标
.PHONY : clean
clean :
	del $(targets)