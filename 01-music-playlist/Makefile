# make        : build ./run
# make demo   : run the programs on examples/ and compare with examples/expected_log.txt
# make clean  : remove build outputs
CXX      = g++
CXXFLAGS = -std=c++11 -Wall -O0 -g
SRCS     = $(wildcard *.cpp)
OBJS     = $(SRCS:.cpp=.o)
TARGET   = run

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp $(wildcard *.h)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# the program reads its input files from the current directory, so run it in a scratch folder
demo: $(TARGET)
	@rm -rf demo_out && mkdir demo_out
	@cp examples/*.txt $(TARGET) demo_out/
	@cd demo_out && ./$(TARGET) > /dev/null
	@diff demo_out/log.txt examples/expected_log.txt > /dev/null && echo "demo OK: log.txt matches examples/expected_log.txt" || (echo "demo FAILED: log.txt differs from examples/expected_log.txt"; exit 1)

clean:
	rm -rf $(OBJS) $(TARGET) log.txt demo_out

.PHONY: demo clean
