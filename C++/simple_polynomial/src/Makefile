.PHONY : all
all : main.exe main1.exe

main.exe : main.cpp polynomial.cpp
	g++ -o $@ $^

main1.exe : main1.cpp polynomial.cpp
	g++ -o $@ $^

.PHONY : clean
clean :
	del *.exe