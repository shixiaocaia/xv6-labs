Lab Util
===

## C

- static静态变量的定义和使用
- `int argc` 和`char *argc[]`
  - `argc` 是参数的个数
  - `argc[0]`是exe文件名，比如`test.exe`
  - 后面几个是以空格为间隔传入的参数名
- `echo > a` 会生成文件a，如果已有文件a，会删除后重建
  - `echo hello > a`输出hello到重建的a文件当中
  - `cat < a` 显示文件内容
- `open`函数会返回当前进程未使用的最小文件描述符序号
- 
## Sleep





## PingPong

### 管道

- 单向的，父子进程之间通信需要一对。
- 资源有限关闭用不到的管道端口

![](http://pic.shixiaocaia.fun//932246-20160909084013707-2039185528.png)

对于父进程中的pipefd[2]，在子进程中同样有这样一套，指向管道的两端，当我们封闭一段形成一个单向的管道时，因为管道是**单向**的，就可以进程间通信了。

如果需要进行双向通信，因为一个管道是单向的，需要两个管道。


> [参考:](https://www.cnblogs.com/MrListening/p/5858358.html)
> - 这里及时关闭一端管道，变成管道是只写只读，是为了节省资源，fd是有限的
> - close(fd)出于资源和安全

## Prime





## Find

### API

- int fstat （int filedes，struct ＊buf）；

  - fstat（）用来将参数filedes 所指向的文件状态复制到参数buf 所指向的结构中（struct stat）
  - 执行成功返回0，失败返回－1，错误代码保存在errno。
  - 与stat函数功能相同

- void *memmove(void *str1, const void *str2, size_t n)

  - 复制str2中n个字符到从str1位置处，会出现覆盖操作
  - 对比memcpy，更加安全

- struct dirent de
  - 读取当前文件 / 文件夹内对应的内容


- ls 可以看到整个路径包含了`.`,`..`,这两部分不会递归进入，de移动到下一个文件。


## Xrags

