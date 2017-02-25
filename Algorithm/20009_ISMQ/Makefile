all:
	g++ -std=c++11 -O2 main.cpp ISMQ.cpp -o ISMQ
	g++ -std=c++11 -O2 main.cpp ISMQ_djSet.cpp -o ISMQ_djSet
	g++ -std=c++11 -O2 main.cpp ISMQ_djSet_BS.cpp -o ISMQ_djSet_BS
	g++ -std=c++11 -O2 main.cpp ISMQ_djSet_BS_fast.cpp -o ISMQ_djSet_BS_fast
special:
	g++ -std=c++11 -O2 main-special.cpp ISMQ_djSet.cpp -o ISMQ_djSet
	g++ -std=c++11 -O2 main-special.cpp ISMQ_djSet_BS.cpp -o ISMQ_djSet_BS
clean:
	rm a.out
