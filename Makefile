CXX = c++

CXXFLAGS = -Wall -Wextra -Werror -g -MMD

OBJS_DIR = obj

SRCS =	main.cpp

DEPS = $(OBJS:.o=.d)


OBJS = $(SRCS:%.cpp=$(OBJS_DIR)/%.o)

NAME = prog

$(NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@ -g
	
$(OBJS_DIR)/%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJS_DIR):
	mkdir -p $(OBJS_DIR)

all: $(NAME)

clean:
	rm -rf $(OBJS_DIR) $(DEPS)

fclean: clean
	rm -f $(NAME)

re: fclean all

-include $(DEPS)

.PHONY: all clean fclean re