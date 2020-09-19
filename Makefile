### Makefile for compilation of analysis macros
### to be copied into

FWK_BASE_DIR = ..
ROOOPT = 

%: %.cc $(FWK_BASE_DIR)
	@ g++ $(shell root-config --cflags --evelibs) -std=c++17 -O3 -Wall -Wextra -Wpedantic -Werror -Wno-float-equal -Wno-sign-compare -I $(FWK_BASE_DIR)/plugins/ -I $(FWK_BASE_DIR)/src/ $< -o $@
