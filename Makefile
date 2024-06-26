# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: arcanava <arcanava@student.42barcel>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/29 11:50:28 by arcanava          #+#    #+#              #
#    Updated: 2024/04/08 18:10:20 by arcanava         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex
DEBUG_NAME = pipex_debug

#----COLORS----#
DEF_COLOR = \033[1;39m
WHITE_BOLD = \033[1m
BLACK = \033[1;30m
RED = \033[1;31m
GREEN = \033[1;32m
YELLOW = \033[1;33m
BLUE = \033[1;34m
PINK = \033[1;35m
CIAN = \033[1;36m

#----COMPILER----#
CC = cc
CCFLAGS = -Wall -Werror -Wextra

#----LIBFT----#
LIBFT_DIR = libft/
LIBFT_LIB = $(LIBFT_DIR)libft.a

#----DIRS----#
BIN_DIR = bin/

#----MANDATORY----#
SRCS =	pipex.c \
		utils.c \
		safe_utils.c \
		initiators.c
OBJS = $(SRCS:%.c=$(BIN_DIR)%.o)
DEPS = $(OBJS:%.o=%.d)

#----BONUS----#
BSRCS = pipex_bonus.c \
		utils_bonus.c \
		safe_utils_bonus.c \
		initiators_bonus.c
BOBJS = $(BSRCS:%.c=$(BIN_DIR)%.o)
BDEPS = $(BOBJS:%.o=%.d)

#----DEBUG----#
ifdef DEBUG
	OBJS = $(SRCS:%.c=$(BIN_DIR)%_debug.o)
	BOBJS = $(BSRCS:%.c=$(BIN_DIR)%_debug.o)
	NAME = $(DEBUG_NAME)
endif

#----EXEC----#
EXEC_PROGRAM = ./$(NAME) input date cat cat ls output

#----RULES----#
all:
	@$(MAKE) --no-print-directory make_libft
	@$(MAKE) --no-print-directory $(NAME)

ifndef BONUS
$(NAME):: $(OBJS)
	@printf "\r$(BLUE)Linking objects and creating program...$(DEF_COLOR)\n"
	@$(CC) $(CCFLAGS) $(OBJS) $(LIBFT_LIB) -o $(NAME)
	@echo "$(GREEN)[✓] $(PINK)Pipex$(GREEN) created!!!$(DEF_COLOR)"
else
$(NAME):: $(BOBJS)
	@echo "$(BLUE)\nLinking objects and creating binary program...$(DEF_COLOR)"
	@$(CC) $(CCFLAGS) $(BOBJS) $(LIBFT_LIB) -o $(NAME)
	@echo "$(GREEN)[✓] $(PINK)Pipex Bonus$(GREEN) created!!!$(DEF_COLOR)"
endif

$(NAME)::
	@printf "\r$(YELLOW)Nothing to be done for $(PINK)pipex$(DEF_COLOR)\n"

ifndef DEBUG
$(BIN_DIR)%.o: %.c Makefile
	@printf "$(CIAN)\rCompiling: $(PINK)$(notdir $<)...$(DEF_COLOR)\033[2K"
	@mkdir -p $(BIN_DIR)
	@$(CC) $(CCFLAGS) -MMD -c $< -o $@
else
$(BIN_DIR)%_debug.o: %.c Makefile
	@printf "$(CIAN)\rCompiling: $(PINK)$(notdir $<)...$(DEF_COLOR)\033[2K"
	@mkdir -p $(BIN_DIR)
	@$(CC) -g $(CCFLAGS) -MMD -c $< -o $@
endif

clean:
	@rm -rf $(BIN_DIR)
	@echo "$(RED)bin/ deleted$(DEF_COLOR)"

fclean: libft_fclean clean mainclean
	@rm -f $(NAME) $(DEBUG_NAME)
	@echo "$(RED)Executable deleted$(DEF_COLOR)\n"

re: fclean all

bonus: 
	@$(MAKE) --no-print-directory BONUS=1

b: bonus

bonusre: fclean bonus

make_libft:
	@$(MAKE) --no-print-directory -C $(LIBFT_DIR) bonus
	@echo ""

libft_clean:
	@$(MAKE) --no-print-directory -C $(LIBFT_DIR) clean

libft_fclean:
	@echo "$(RED)Cleaning $(PINK)Libft$(RED)...$(DEF_COLOR)"
	@$(MAKE) --no-print-directory -C $(LIBFT_DIR) fclean

norme:
	@echo "$(YELLOW)\n------------------------\nChecking norme errors...\n------------------------\n$(DEF_COLOR)"
	@-norminette $(INC_DIR) $(BONUS_INC_DIR) $(SRCS_DIR) $(BONUS_SRCS_DIR)

compmain: all
	@echo "\n$(GREEN)COMPILING MAIN FOR TESTING..."

main: compmain
	@echo "$(GREEN)\n------------\nMain result:\n------------\n$(DEF_COLOR)"
	@echo "see ./output\n"
	$(EXEC_PROGRAM)

m: main

n: norme

nm: norme main

mn: nm

leaks: compmain
	@echo "$(YELLOW)\n------------------------\nChecking leaks atExit...\n------------------------\n$(DEF_COLOR)"
	@-leaks -quiet -fullContent -atExit -- $(EXEC_PROGRAM)

mainclean:
	@rm -f main

test: norme leaks

t: test

debug:
	@$(MAKE) --no-print-directory all DEBUG=1

debug_bonus:
	@$(MAKE) --no-print-directory bonus DEBUG=1

.PHONY: all \
		clean \
		fclean \
		re \
		bonus \
		bonusre \
		make_libft \
		libft_clean \
		libft_fclean \
		norme \
		main \
		m \
		n \
		nm \
		mn \
		leaks \
		compmain \
		mainclean \
		test \
		t \
		debug \
		b

-include $(DEPS)
-include $(BDEPS)
