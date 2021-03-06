
## 学习笔记

### 一、知识点

1. 由```open```返回的文件描述符一定是最小未被使用的描述符数值

2. 文件共享
![image](http://www.107zy.cn/aut/picture/i_file_sharing.png)

3. 如果用```O_APPEND```标识打开了一个文件，则每次对这个文件执行写操作时：首先将文件表项中的当前文件偏移量设置为i节点表项中的文件长度(文件最新的长度)，然后再执行写操作。相当于把```lseek```和```write```合并为一个原子操作

4. ```fcntl```函数的功能：
    - 复制文件描述符
    - 获得/设置文件描述符标志
    - 获得/设置文件状态标志
    - 获得/设置异步I/O所有权
    - 获得/设置记录锁

5. 执行完```fd2 = dup(fd1)```之后：
    - ```fd2```与```fd1```共享文件状态标志(```O_APPEND```等)
    - ```fd2```和```fd1```拥有自己独立的文件描述符标志(```FD_CLOEXEC```)

6. 习题3.4解释
```
问题：
在许多程序中都包含下面一段代码：

dup2(fd,0);
dup2(fd,1);
dup2(fd,2);
if(fd > 2)
    close(fd);

这里if的必要性是什么？

为什么最后要关闭文件描述符呢？

答案：
这里if的必要性是什么？ 为什么最后要关闭文件描述符呢？
两个问题的先后顺序得交换下。
为什么最后要关闭文件描述符呢？
——假定前三次 dup2() 函数调用均成功，那么 fd 与 0、1、2 等四个文件描述符将指向同个文件，fd 是否需继续保留由代码逻辑决定，你给出的代码片段缺少上下文，我只能假定无须继续使用 fd，为释放文件描述符资源，所以 close(fd)。
这里if的必要性是什么？
——dup2(old_fd, new_fd)，如果 old_fd == new_fd 且 old_fd 为有效文件描述符，那么函数调用也会成功且返回 new_fd（或，old_fd，都一样）。换言之，在三次调用 dup2() 时，fd 完全可能为 0、1、2 任一（如，2），这时再 close(fd) 将关闭刚获取的对应文件描述符（即，2），这势必与代码初衷“0、1、2 等三个文件描述符指向与 fd 相同文件”相悖（即，文件描述符 2 不再可用）。所以，fd 仅当不为 0、1、2 时才能 close(fd)，即，if (fd != 0 && fd != 1 && fd != 2) close(fd); 或 if (fd > 2) close(fd);
```

7. ```b>&a```等价于```dup2(a, b)```等价于```close(b) && set b = a```

### 二、相关API

```
/* 原子性地定位搜索和执行IO */
pread()/pwrite();
```