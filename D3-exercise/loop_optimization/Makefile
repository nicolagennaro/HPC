CXX=gcc
CFLAGS=-lm
STR= avoid_avoidable avoid_avoidable_loop0 avoid_avoidable_loop1 avoid_avoidable_loop2 \
	avoid_avoidable_loop3  avoid_avoidable_loop4 avoid_avoidable_loop5 avoid_avoidable_loop6 \
	avoid_avoidable_loop7 avoid_avoidable_loop7b avoid_avoidable_loop8 avoid_avoidable_loop8b \
        avoid_avoidable_loop8pref


 
  
  


all: $(STR)

$(STR): %: %.c
	$(CXX) $< -o $@ $(CFLAGS)

