# ========== 变量定义 ==========
# 编译器：使用 gcc (C 编译器)
CC = gcc
# 编译选项：
#   -g     生成调试信息
#   -Wall  开启所有常用警告
CFLAGS = -g -Wall

# 最终生成的可执行文件名
TARGET = main
# 源文件列表
SRCS = main.c
# 目标文件列表：main.c → main.o
OBJS = $(SRCS:.c=.o)


# ========== 规则 ==========

# 默认目标
all: $(TARGET)

# 链接规则
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

# 编译规则：.c → .o
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# 清理
clean:
	rm -f $(OBJS) $(TARGET)

# 运行
run: $(TARGET)
	./$(TARGET)

.PHONY: all clean run
