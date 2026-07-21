# 编译器
CXX = g++
# 编译选项
CXXFLAGS = -g -Wall

# 目标文件
TARGET = test
# 源文件
SRCS = test.cpp
# 目标文件（把 .cpp 替换成 .o）
OBJS = $(SRCS:.cpp=.o)

# 默认规则
all: $(TARGET)

# 链接生成最终可执行文件
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# 编译 .cpp 到 .o
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# 清理编译产物
clean:
	rm -f $(OBJS) $(TARGET)

# 运行程序
run: $(TARGET)
	./$(TARGET)

# 声明这些不是真正的文件名
.PHONY: all clean run
