#变量
targets = brute_force.exe kmp.exe kmp_improvement.exe

#伪目标
.PHONY : all
all : $(targets) 

#规则
brute_force.exe : brute_force.cpp
	g++ -fexec-charset=GBK -o brute_force.exe brute_force.cpp

kmp.exe : kmp.cpp
	g++ -fexec-charset=GBK -o kmp.exe kmp.cpp

kmp_improvement.exe : kmp_improvement.cpp
	g++ -fexec-charset=GBK -o kmp_improvement.exe kmp_improvement.cpp

#伪目标
.PHONY : clean
clean :
	del $(targets)