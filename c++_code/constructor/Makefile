app:delegateconstructor.cpp
	g++ -std=c++11 -o $@ $^


equaloperator:equaloperator.cpp
	g++ -std=c++11 -Wall -g $^ -o $@.out

.PHONY:
clean:
	rm -rf *.out app
