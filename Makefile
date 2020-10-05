#-g -fsanitize=address
all:
	@clang -g *.c ./utils/*.c -o game -lmlx -lX11 -lXext -fPIC -lm
	@./game

build:
	@clang *.c ./utils/*.c -o game -lmlx -lX11 -lXext -fPIC -lm

run:
	@./game

clean:
	@rm -rf game  *.swp
