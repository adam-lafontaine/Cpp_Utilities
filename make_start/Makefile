#GPP   := g++-10 -std=c++17
GPP   := g++
build := ./build
code  := ./src

exe_name := my_program

program_exe := $(build)/$(exe_name)

main_c         := $(code)/main.cpp
main_o         := $(build)/main.o
object_files   := $(main_o)

math_h := $(code)/math.hpp

add_c        := $(code)/add.cpp
add_o        := $(build)/add.o
object_files += $(add_o)

subtract_c   := $(code)/subtract.cpp
subtract_o   := $(build)/subtract.o
object_files += $(subtract_o)


$(main_o): $(main_c) $(math_h)
	@echo "\n main"
	$(GPP) -o $@ -c $<

$(add_o): $(add_c)
	@echo "\n add"
	$(GPP) -o $@ -c $<

$(subtract_o): $(subtract_c)
	@echo "\n subtract"
	$(GPP) -o $@ -c $<

$(program_exe): $(object_files)
	@echo "\n $(exe_name)"
	$(GPP) -o $@ $+

build: $(program_exe)

run: build
	$(program_exe)
	@echo "\n"

setup:
	mkdir -p $(build)
	@echo "\n"

clean:
	rm -rfv $(build)/*
	@echo "\n"