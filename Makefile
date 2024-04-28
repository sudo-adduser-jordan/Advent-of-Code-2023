VERSION="-std=c++23"
SOLUTION=01

run:
	mkdir -p bin

	# echo "Compiling Utilites..."
	# 	g++ packages/utilities/*.cpp -c $(VERSION)  

	# echo "Compiling Solutions..."
	# 	g++ source/solutions/*.cpp -c $(VERSION)

	echo "Compiling Solution..."
		g++ source/solutions/Solution$(SOLUTION)*.cpp -c $(VERSION) -Wall -Wextra

	echo "Compiling Source..."
		g++ source/*.cpp -c $(VERSION)

	mv *.o bin

	g++ bin/*.o -o bin/AdventOfCode.exe $(VERSION)

	# ./bin/AdventOfCode.exe
	# ./bin/AdventOfCode.exe --solution01 --sample
	./bin/AdventOfCode.exe --solution$(SOLUTION) --parta
	# ./bin/AdventOfCode.exe --solution$(SOLUTION) --partb


clean:
	rm -rf bin