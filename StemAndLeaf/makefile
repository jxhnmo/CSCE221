files = Driver.cpp Leaf.h Stem.cpp Stem.h StemAndLeaf.cpp StemAndLeaf.h
all:
	g++ $(files) -o run
	valgrind --tool=memcheck --track-origins=yes ./run

clean:
	rm -f run