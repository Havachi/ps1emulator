NAME		:= ps1emulator
VERSION		:= 0.1

#Directories
SRCDIR		:= src
OBJDIR		:= obj
BINDIR		:= bin
LIBDIR		:= lib
INCDIR		:= include

#Files
FILES		= bios cpu interconnect range instruction opcode register main
SRCS		= $(addprefix $(SRCDIR)/, $(addsuffix .c, $(FILES)))
OBJS		= $(addprefix $(OBJDIR)/, $(addsuffix .o, $(FILES)))
INCS		= bios cpu interconnect instruction opcode register range

#Tools
CC			= gcc

#Flags
INCLFLAGS	:= -I$(INCDIR)
CFLAGS		:= -Wall -Wextra -Werror -ggdb

#Rules
all : clear $(BINDIR)/$(NAME)

$(BINDIR)/$(NAME): $(OBJS)
	@echo "\n Linking $@..."
	$(CC) $(CFLAGS) $(INCLFLAGS) $^ -o $@

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@echo "\n Compiling $<..."
	$(CC) $(CFLAGS) $(INCLFLAGS) -c $< -o $@

re: fclean all

clean:
	@echo "\n Cleaning..."
	@rm -f $(OBJS)

fclean: clean
	@echo "\n Full cleaning..."
	@rm -f $(BINDIR)/$(NAME)

clear:
	@clear