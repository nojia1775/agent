CXX = c++

CXXFLAGS = -Wall -Wextra -Werror -g -MMD

OBJS_DIR = obj

SRCS =	src/Agent.cpp \
	src/main.cpp \
	src/Map.cpp \
	src/Server.cpp

DEPS = $(OBJS:.o=.d)

OBJS = $(SRCS:%.cpp=$(OBJS_DIR)/%.o)

NAME = agent

$(NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@ -g
	
$(OBJS_DIR)/%.o: %.cpp
	mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

all: $(NAME)

clean:
	rm -rf $(OBJS_DIR) $(DEPS)

fclean: clean
	rm -f $(NAME)

re: fclean all

-include $(DEPS)

.PHONY: all clean fclean re