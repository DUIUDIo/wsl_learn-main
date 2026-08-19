CC      = gcc
CFLAGS  = -Wall -g
LDFLAGS =

# 所有要编译的 .c 文件（不含后缀）
TARGETS = perror_test unname_test pipe_twoway fifo_write fifo_read

# 默认目标：编译所有程序
all: $(TARGETS)

# 通用规则：每个 .c 文件编译成同名可执行文件
%: %.c
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

# 运行特定程序，例如: make run TARGET=unname_test ARGS="hello"
run: $(TARGET)
	./$(TARGET) $(ARGS)

# 运行 perror_test（保留你原来的快捷方式）
run_perror_test: perror_test
	./$<

# 清理
clean:
	rm -f $(TARGETS)
.PHONY: all clean run run_perror_test
	rm -f perror_test unname_test
.PHONY:clean 
