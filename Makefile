# ========== 变量定义 ==========
#已经进行变量定义了，很规范
# 编译器：使用 g++ (C++ 编译器)
CXX = g++
# 编译选项：
#   -g     生成调试信息（可用 GDB 调试）
#   -Wall  开启所有常用警告
CXXFLAGS = -g -Wall

# 最终生成的可执行文件名
TARGET = test
# 源文件列表（如果有多个文件用空格分隔，如 "a.cpp b.cpp"）
SRCS = test.cpp
# 目标文件列表：将 SRCS 中所有 .cpp 替换为 .o
# 即 test.cpp → test.o
OBJS = $(SRCS:.cpp=.o)


# ========== 规则 ==========

# 默认目标：直接执行 `make` 等价于 `make all`
all: $(TARGET)

# 链接规则：把 .o 文件链接成可执行文件
# $@ → 目标文件名（test）
# $^ → 所有依赖文件（test.o）
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# 编译规则：把 .cpp 编译成 .o 文件（模式匹配）
# %.o: %.cpp  → 匹配所有 .cpp → .o 的转换
# $< → 第一个依赖文件（如 test.cpp）
# -c → 只编译不链接
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# 清理：删除编译产生的 .o 文件和可执行文件
clean:
	rm -f $(OBJS) $(TARGET)

# 运行：先编译（如有需要），再执行程序
run: $(TARGET)
	./$(TARGET)

# .PHONY 声明：告诉 make 这些名字不是真正的文件名
# 即使当前目录下有叫 all/clean/run 的文件，也不会干扰规则
.PHONY: all clean run
