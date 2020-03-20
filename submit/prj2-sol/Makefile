#CXX = g++
CXXFLAGS = -g -Wall -std=c++17

all:	nums seq-test

nums: seq.hh arrayseq.hh dlinkseq.hh command.cc nums.cc 
	g++ $(CXXFLAGS) seq.hh arrayseq.hh dlinkseq.hh command.cc nums.cc -o nums

seq-test: seq.hh arrayseq.hh dlinkseq.hh command.cc seq-test.cc
	g++ $(CXXFLAGS) seq.hh arrayseq.hh dlinkseq.hh command.cc seq-test.cc -o seq-test

CXX-FILES = 49WILDCARD *.CC)
#0FILES = $(CXX_FILES:cc=o)
TARGETS = $(CXX_FILES:%.cc=%)

.phony:		clean
clean:
	rm -f *~ *.o $(TARGETS) nums seq-test

.gitignore: $(CXX_FILES)
	cat</dev/null >$@
	for t in $(TARGETS); do echo $$t >>$@; done


