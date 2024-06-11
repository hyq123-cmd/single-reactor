这个项目使用单个epoll来管理多个IO事件，且引入线程池来处理客户端发送的请求。
程序运行的环境是ubuntu 16.04
运行的步骤如下：
1、使用cd指令进入single-reactor的目录，然后使用make指令使其自动生成两个可执行文件，分别是server.out和client.out。
2、"./sever.out"即可运行服务端，当然你也可以用"make run"来代替这个语句。
3、打开另一个终端，也是进入single-reactor目录，然后输入"./client.out"既可以运行客户端。

Epoll was used to manage multiply I/O events in this project, and I also used the thread pool to deal the client request.

In this project, my running enviornment is ubuntu 16.04.

Following these steps, you can run it successfully.
Step 1: open Linux's terminal and enter the directory of "single-reactor".
Step 2: using "make" to generate executable file.
Step 3: input "./server.out" or "make run" to start server.
Step 4: open another terminal, enter the same directory and input "./client.out" to start client.
