.PHONY: all clean build rebuild

all: build
	@cd build && $(MAKE)

build:
	@mkdir -p build
	@cd build && cmake ..

clean:
	@rm -rf build

rebuild: clean all 