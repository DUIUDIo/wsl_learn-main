CC = gcc
CFLAGS = -Wall -g

# 默认目标
all: system_test

system_test: system_test.c
	$(CC) $(CFLAGS) -o $@ $<

fork: fork.c
	$(CC) $(CFLAGS) -o $@ $<

fork__fd_test: fork_fd_test.c
	$(CC) $(CFLAGS) -o $@ $<	

execve_test: execve_test.c
	$(CC) $(CFLAGS) -o $@ $<

execve_test2: execve_test2.c
	$(CC) $(CFLAGS) -o $@ $<
fork_execve_test: fork_execve_test.c
	$(CC) $(CFLAGS) -o $@ $<

wait_pid_test: wait_pid_test.c
	$(CC) $(CFLAGS) -o $@ $<

# 单独运行
run: system_test
	./$<

run-fork: fork
	./$<

run-fork_fd_test: fork__fd_test
	./$<

run-execve_test: execve_test
	./$<

run-execve_test2: execve_test2
	./$<

run-fork_execve_test: fork_execve_test
	./$<

run-wait_pid_test: wait_pid_test
	./$<



clean:
	rm -f system_test fork fork__fd_test execve_test execve_test2 fork_execve_test wait_pid_test

.PHONY: all clean run run-fork run-fork_fd_test run-execve_test run-execve_test2 run-fork_execve_test run-wait_pid_test
