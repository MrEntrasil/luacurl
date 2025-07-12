COMPILER=g++

all:
	$(COMPILER) -O2 -fPIC -shared -o luacurl.so ./src/main.cpp -I/usr/include -lcurl
