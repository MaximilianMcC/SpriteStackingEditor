default:
	mkdir -p ./bin
# 	g++ -g $(wildcard src/**/*.cpp) -o ./bin/main -lraylib
	g++ -g src/*.cpp -o ./bin/main -lraylib
