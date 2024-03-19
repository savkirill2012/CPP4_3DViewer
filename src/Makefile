.PHONY: all install uninstall clean dvi dist tests

UNAME:=$(shell uname -s)
ifeq ($(UNAME),Linux)
	LDFLAGS=-lcheck -lm -lrt -lpthread -lsubunit
	OPEN=xdg-open
endif
ifeq ($(UNAME),Darwin)
	LDFLAGS=-lcheck -lm
	OPEN=open
endif

all: clean install
default: all

install: clean
	cmake -B build
	make -C build

uninstall:
	rm build/Viewer_2_0

clean:
	rm -rf build Docs s21_test *.tar *.user

dvi: Doxyfile
	doxygen
	$(OPEN) Docs/html/index.html

dist:
	tar -cf Viewer_2_0.tar build/Viewer_2_0 

tests:
	g++ Tests/*.cpp Model/parser.cpp Model/transformation.cpp -lgtest -o s21_test
	./s21_test

valgrind: tests
	valgrind --leak-check=full ./s21_test

style_test:
	find . -name "*.cpp" -or -name "*.h" | xargs clang-format -n
	find . -name "*.cpp" -or -name "*.h" | xargs -I % sh -c 'echo Checking... %;'

style_edit:
	find . -name "*.cpp" -or -name "*.h" | xargs clang-format -i
	find . -name "*.cpp" -or -name "*.h" | xargs -I % sh -c 'echo Formatting... %;'

