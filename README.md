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

- 字符串、字符串指针

  ```c
  char* p = "hello world"; //是把字符串的首地址给到p，不是直接把字符串给到p
  //所以这里hello world是字符串常量(放在常量区)，无法通过指针p进行改变
  
  char arr[10] = "hello world";
  char *pa = arr;
  *pa = 'H';
  //需要放到数组中进行修改
  
  char str1[] = "hello world";
  char str2[] = "hello world";
  //str1 != str2，因为创建数组开辟的内容空间位置是不同的
  //[] 优先级大于 *
  ```

## PingPong

- 管道是单向的，父子进程之间通信需要一对。
- 及时关闭一端管道，变成管道是只写只读，为了节省资源，fd是有限的，同时也更加安全。

## Prime

- 通过递归创建子进程，接受左进程传来的数字，打印接受的第一个数，经过素数筛，向右传递后续的数字。
- 注意在最后一个数（31），如果不判断是否为空，会导致`primes 0`无效输出。

## Find

- int fstat （int filedes，struct ＊buf）；

  - fstat（）用来将参数filedes 所指向的文件状态复制到参数buf 所指向的结构中（struct stat）
  - 执行成功返回0，失败返回－1，错误代码保存在errno。
  - 与stat函数功能相同

- void *memmove(void *str1, const void *str2, size_t n)

  - 复制str2中n个字符到从str1位置处，会出现覆盖操作
  - 对比memcpy，更加安全

- struct dirent de
  - 读取当前文件 / 文件夹内对应的内容


- ls 可以看到整个路径包含了`.`，`..`，这两部分不会递归进入，de移动到下一个文件。


## Xrags

- 管道符号

  ```c
  cmdA | cmdB
  
  cmdB | xargs cmdB
  ```

  - 将cmdA的输出作为cmdB的输入，但不是命令行参数
  - 加上xargs后，将输出作为命令行参数，那么想要读取前面的输出，从fd 0读入即可。
  - 此时argc和* argv[]参数指的是，xargs部分，管道后半部分内容。

- 主要思路是

  - 获取前一个命令的标准化输出，作为xargs的标准输入
  - 获取自己的命令行参数，argc，*argv[]
  - 使用exec执行参数（前面两部分参数需要进行拼接）