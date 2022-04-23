GPP := g++-10 -std=c++17
build := ./build_files

tests_exe := $(build)/cpp_tests


# main
main_c         := test_main.cpp
main_o         := $(build)/test_main.o
object_files   := $(main_o)


host_h := host.hpp

host_c   := host.cpp
host_o   := $(build)/host.o
object_files   += $(host_o)


# flags
INCLUDES  :=
LIBRARIES :=

GPP += -O3 -DNDEBUG


# build rules

$(main_o): $(main_c) $(host_h)
	@echo "\n main"
	$(GPP) -o $@ -c $<

$(host_o): $(host_c) $(host_h)
	@echo "\n host"
	$(GPP) -o $@ -c $<

$(tests_exe): $(object_files)
	@echo "\n cpp_tests"
	$(GPP) -o $@ $+ $(LIBRARIES)


build: $(tests_exe)

run: build
	$(tests_exe)

clean:
	rm -rfv $(build)/*

setup:
	mkdir -p $(build)