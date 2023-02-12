#变量
targets = sort.exe

#伪目标
.PHONY : all
all : $(targets) 

#规则
sort.exe : sort.cpp
	g++ -fexec-charset=GBK -o sort.exe sort.cpp

#伪目标
.PHONY : clean
clean :
	del $(targets)