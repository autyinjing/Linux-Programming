
## 学习笔记

### 一、知识点

##### 标准I/O库的三种缓冲
缓冲类型 | 说明
--- | ---
全缓冲 | 填满缓冲区后才进行实际的I/O操作
行缓冲 | 遇到换行符时执行I/O操作
不带缓冲 | 立即执行I/O操作

1. 通过文件描述符获取文件名？
- linux中每个被打开的文件都会记录在```/proc/self/fd/```目录中，```/proc/self/fd/fileno```就是```fileno```对应文件的符号链接，通过```readlink```函数就可以获得文件的完整路径
```
int get_filename_by_fd(int fd, char *buf, size_t bufsize)
{
    char linkbuf[1024] = {0};
    snprintf(linkbuf, 1024, "/proc/self/fd/%d", fd);
    return readlink(linkbuf, buf, bufsize - 1);
}
```

2. ```fflush()```将标准IO缓冲区的内容写入内核缓冲区，```fsync()```将内核缓冲区写至磁盘并等待磁盘操作结束才返回

### 二、相关API

```
//更改缓冲类型
setbuf()/setvbuf()

//强制冲洗一个流
fflush()

//创建临时文件
tempfile()/mkstemp()
```

### 三、练习题

5.2 ```fgets```读入数据直到行结束或缓冲区满，```fputs```只将缓冲区内容输出，并不考虑缓冲区是否包含换行符。所以，仍然会正常工作

5.3 输出的数据长度为0

5.4 ```EOF```为-1，```char```如果是无符号类型，则会进入死循环

5.5 前缀(5) + 进程内标识(4) + 系统标识(5) = UNIX传统文件长度限制(14)

5.6 先```fflush()```，然后```fsync()```

5.7 当程序交互运行时，标准输入和标准输出均为行缓冲，每次调用```fgets()```时标准输出设备将自动刷新