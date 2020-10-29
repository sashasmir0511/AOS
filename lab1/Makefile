CC = gcc
CFLAGS = -Wall -Werror -Wextra

SRC = lab_1_1.c lab_1_2.c lab_1_4.c lab_1_6.c lab_1_7.c lab_1_8.c lab_1_9.c \
		lab_1_10.c lab_1_11.c
NAME = $(SRC:.c=)

all: $(NAME)

$(NAME): $(SRC)
	$(CC) $(CFLAGS) $< -o $@

clean:
	@/bin/rm -rf $(NAME)

re: fclean all