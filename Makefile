all : main

GPP=g++

main : xmlParser.cpp xmlParser.h main.cpp
	$(GPP) -std=c++11 -g -Wall -o main \
                 xmlParser.cpp main.cpp

clean:
	-@rm main              >/dev/null 2>/dev/null