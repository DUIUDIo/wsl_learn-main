CC      = gcc
CFLAGS  = -Wall -g -pthread

# 递归找出所有 .c（去掉开头的 ./，让目标名干净）
SRCS    = $(patsubst ./%,%,$(shell find . -name '*.c'))
# 每个 .c 生成同目录下的同名可执行文件
TARGETS = $(SRCS:.c=)

# 默认目标：全部编译（含子目录）
all: $(TARGETS)

# 静态模式规则：每个 .c 精确映射到自己的可执行文件
# 例：sync/mutex_test 依赖 sync/mutex_test.c
$(TARGETS): %: %.c
	$(CC) $(CFLAGS) -o $@ $<

# 运行指定程序：make run TARGET=thread_sum
run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGETS)

.PHONY: all run clean
