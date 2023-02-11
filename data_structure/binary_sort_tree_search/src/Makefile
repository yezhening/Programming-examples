#变量
targets = binary_sort_tree_search.exe

#伪目标
.PHONY : all
all : $(targets) 

#规则
binary_sort_tree_search.exe : binary_sort_tree_search.cpp
	g++ -o binary_sort_tree_search.exe binary_sort_tree_search.cpp

#伪目标
.PHONY : clean
clean :
	del $(targets)