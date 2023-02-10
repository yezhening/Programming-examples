#变量
targets = graph_adjacency_matrix.exe graph_adjacency_list.exe

#伪目标
.PHONY : all
all : $(targets) 

#规则
graph_adjacency_matrix.exe : graph_adjacency_matrix.cpp
	g++ -fexec-charset=GBK -o graph_adjacency_matrix.exe graph_adjacency_matrix.cpp

graph_adjacency_list.exe : graph_adjacency_list.cpp
	g++ -fexec-charset=GBK -o graph_adjacency_list.exe graph_adjacency_list.cpp

#伪目标
.PHONY : clean
clean :
	del $(targets)