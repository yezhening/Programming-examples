#变量
targets = main.exe

#伪目标
.PHONY : all
all : $(targets) 

#规则
main.exe : main.cpp DH.cpp
	g++ -fexec-charset=GBK -o main.exe main.cpp DH.cpp

#伪目标
.PHONY : clean
clean :
	del $(targets)