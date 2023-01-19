#变量
targets = main.exe
VPATH = src

#伪目标
.PHONY : all
all : $(targets) 

#规则
main.exe : main.cpp DES.cpp
	g++ -fexec-charset=GBK -o main.exe main.cpp DES.cpp

#伪目标
.PHONY : clean
clean :
	del $(targets)