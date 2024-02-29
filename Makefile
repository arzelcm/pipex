# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: arcanava <arcanava@student.42barcelona.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/29 11:50:28 by arcanava          #+#    #+#              #
#    Updated: 2024/02/29 13:12:25 by arcanava         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

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
SRCS = pipex.c
OBJS = $(SRCS:%.c=%.o)
DEPS = $(OBJS:%.o=%.d)

#----BONUS----#
BSRCS = ft_printf_bonus.c basic_handle_helper_bonus.c complex_handle_helper_bonus.c padding_helper_bonus.c
BOBJS = $(BSRCS:%.c=%.o)
BDEPS = $(BOBJS:%.o=%.d)

#----RULES----#
all:
	@$(MAKE) --no-print-directory make_libft
	@$(MAKE) --no-print-directory $(NAME)

ifndef BONUS
$(NAME):: $(addprefix $(BIN_DIR), $(OBJS))
	@echo "$(BLUE)\nLinking objects and creating program...$(DEF_COLOR)"
	@cp $(LIBFT_LIB) $(NAME)
	@$(CC) $(CCFLAGS) $(addprefix $(BIN_DIR), $(OBJS)) $(LIBFT_LIB) -o $(NAME)
	@echo "$(GREEN)[✓] $(PINK)Pipex$(GREEN) created!!!$(DEF_COLOR)\n"
else
$(NAME):: $(addprefix $(BIN_DIR), $(BOBJS))
#@rm -rf $(addprefix $(BIN_DIR), $(OBJS)) $(addprefix $(BIN_DIR), $(DEPS))
	@echo "$(BLUE)\nLinking objects and creating binary program...$(DEF_COLOR)"
	@cp $(LIBFT_LIB) $(NAME)
	@$(CC) $(CCFLAGS) $(addprefix $(BIN_DIR), $(BOBJS)) -o $(NAME)
	@echo "$(GREEN)[✓] $(PINK)Pipex Bonus$(GREEN) created!!!$(DEF_COLOR)\n"
endif

$(NAME)::
	@echo "$(YELLOW)Nothing to be done for $(PINK)pipex$(DEF_COLOR)"

$(BIN_DIR)%.o: %.c Makefile
	@printf "$(CIAN)\rCompiling: $(PINK)$(notdir $<)...$(DEF_COLOR)                   \r"
	@mkdir -p $(BIN_DIR)
	@$(CC) $(CCFLAGS) -I $(INC_DIR) -MMD -g -c $< -o $@

clean:
	@rm -rf $(BIN_DIR)
	@echo "$(RED)bin/ deleted$(DEF_COLOR)"

fclean: libft_fclean clean mainclean
	@rm -f $(NAME)
	@echo "$(RED)Executable deleted$(DEF_COLOR)\n"

re: fclean all

bonus: 
	@$(MAKE) --no-print-directory BONUS=1

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
	@echo "\n$(YELLOW)COMPILING MAIN FOR TESTING..."

main: compmain
	@echo "$(GREEN)\n------------\nMain result:\n------------\n$(DEF_COLOR)"
	@./$(NAME)

m: main

n: norme

nm: norme main

mn: nm

leaks: compmain
	@echo "$(YELLOW)\n------------------------\nChecking leaks atExit...\n------------------------\n$(DEF_COLOR)"
	@-leaks -quiet -fullContent -atExit -- ./main

mainclean:
	@rm -f main

test: norme leaks

t: test

.PHONY: all clean fclean re bonus bonusre make_libft libft_clean libft_fclean norme main m n nm mn leaks compmain mainclean test t

-include $(DEPS)

-include $(BDEPS)
