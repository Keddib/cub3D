#-g -fsanitize=address
all:
	@gcc -I /usr/local/include *.c ./utils/*.c -o game -L /usr/local/lib -lmlx -framework OpenGL -framework AppKit -lm
	@./game

build:
	@gcc -I /usr/local/include *.c ./utils/*.c -o game -L /usr/local/lib -lmlx -framework OpenGL -framework AppKit -lm

run:
	@./game

clean:
	@rm -rf game  *.swp
