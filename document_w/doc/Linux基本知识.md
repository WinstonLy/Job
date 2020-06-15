## 一 Bash Shell

`bash shell`的基本功能

- 命令记忆功能 `./bash_history`
- 命令别名功能 `alais`
- `shell scripts`功能 ：`sctipts`就是内涵多个复杂`command`的纯文本档案
- 命令与档案补全功能 `tab`键
- 工作控制功能 `jobs`

### 1.1 变量的取用与设定：echo，变量设定规则，ubset

利用`echo`这个指令来取用变量，在变量被取用的时候必须在前面加上`$`。

```shell
winston@Winstonly-Ly:~$ echo $PATH
/home/winston/bin:/home/winston/.local/bin:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/snap/bin
```

在修改变量的内容是，用`=`链接变量和他的内容即可，具体的设定规则如下：

- 变量与变量内容以一个等号`=`来连结；

- 等号两边不能直接接空格符，如`myname = Winston`为错误示例；

- 变量名称只能是英文字母或数字，开头不能为数字；

- 若该变量为扩增变量内容时，则可用“$变量名称”或者 ${变量}累加内容：

  `PATH=“$PATH”:/home/bin`

- 若该变量需要在其他子程序执行，则需要以`export`来使变量变成环境变量：`export PATH`
- 取消变量的方法为使用unset：`unset 变量名称`

### 1.2 环境变量的功能

- 用`env`观察环境变量与常见环境变量说明

  ```shell
  winston@Winstonly-Ly:~$ env
  XDG_VTNR=7
  LC_PAPER=zh_CN.UTF-8
  LC_ADDRESS=zh_CN.UTF-8
  XDG_SESSION_ID=c2
  XDG_GREETER_DATA_DIR=/var/lib/lightdm-data/winston
  LC_MONETARY=zh_CN.UTF-8
  CLUTTER_IM_MODULE=xim
  SESSION=ubuntu
  ```

  - 用`set`观察所有变量（包括环境变量与自定义变量）
  - `export`:自定义变量转为环境变量

### 1.3 变量键盘读取、数组与宣告：`read、array、declare`

## 二 开机流程、模块管理与loader

### 2.1 `linux`系统的开机流程

1. 加载`BIOS`的硬件信息与进行自我测试，并依据设定取得第一个可开机的装置；
2. 读取并执行第一个开机装置内`MBR`的`boot loader`（亦即是`grub，spfdisk`等程序）；
3. 一句`boot loader`的设定加载`Kernel`，`Kernel`会开始侦测硬件与加载驱动程序；
4. 在硬件驱动加载成功后，`Kernel`会主动呼叫`init`程序，而`init`会取得`run-level`信息；
5. `inti`执行`/etc/rc.d/rc.sysinit`档案来准备软件执行的作业环境（如网络、时区等）；
6. `init`执行`run-level`的各个服务之启动（`script`方式）；
7. `init`执行`/etc/rc.d/rc.local`档案；
8. `init`执行终端机仿真程序`mingetty`来启动`login`程序，最后就等待用户登入；

### 2.2 有关名词介绍

- `Loader`具有提供选单、加载核心档案、转交控制权给其他`loader`等功能
- `boot loader`可以安装在`MBR`或者是每个分割槽的`boot sector`区域中
- `initrd`可以提供核心在开机过程中所需要的最重要的模块，通常与磁盘以及文件系统有关

## 三 `Linux`下的原始码与`tarball`

### 3.1 `Tarball`与原始码

- `Tarball`档案是将软件的所有原始码档案先以`tar`打包，然后再以压缩技术来压缩，通常最常见的就是以`gzip`来压缩了。所以`Tarball`是一个软件包，解压之后档案通常会存在一下档案：
  - 源代码档案
  - 侦测程序档案（可能是`configure`或者`config`等档名）
  - 本软件的简易说明和安装说明（`INSTALL`或者`README`）


- 原始码大多都是文本档案，只有经过编译程序的编译之后，才能制作`linux`系统能够是别的二进制文件

### 3.2 `gcc`

- **查看`gcc`版本**
  `gcc -v`

- **编译单个文件**
  `gcc hello.cpp -o hello`

- **编译多个文件**

  ```shell
  - 如有头文件（header.h）,函数定义文件（func.cpp）,主函数文件（main.cpp）
    `gcc -c func.cpp`
    `gcc -c main.cpp`
    编译完成生成两个文件：func.o main.o
    通过链接可得到最终的可执行文件
    `gcc main.o func.o -o test
  
  `gcc -c func.cpp -I ../include`
  `gcc func.o main.o -o ../testOutput/test`
  ```

  

### 3.3 `make`进行宏编译

- make的优点

  1. 简化编译时所需要下达的指令

  2. 若在编译完成之后，修改了某个原始档案，则make仅会针对被修改了的档案进行编译，而其他的`object file`不会被更新

  3. 最后可以依照相依性来更新执行档

- makefile 的基本语法与变量

  makefile的规则是这样的：

  ```
  target ... : prerequisites ...
      command
      ...
      ...
  ```
  
  - target

    可以是一个object file（目标文件），也可以是一个执行文件，还可以是一个标签（label）。对 于标签这种特性，在后续的“伪目标”章节中会有叙述。

  - prerequisites
  
    生成该target所依赖的文件和/或target
  
  - command

    该target要执行的命令（任意的shell命令）

```shell
winston@Winstonly-Ly:~$ vim makefile
main：main.o haha.o sin_value.o cos_value.o
	gcc -o main main.o haha.o sin_value.o cos_value.o
	
clean:
	rm main haha.o sin_value.o cos_value.o
	
`基本语法`
# 在makefile中 # 代表注释
# gcc编译语法的一行开始必须以“tab”键开始
# taget 与 目标文件必须以“：”隔开
```

### 3.4 makefile的工作方式

GNU的make工作时的执行步骤如下：（想来其它的make也是类似）

- 读入所有的Makefile。

- 读入被include的其它Makefile。

- 初始化文件中的变量。

- 推导隐晦规则，并分析所有规则。

- 为所有的目标文件创建依赖关系链。

- 根据依赖关系，决定哪些目标要重新生成。

- 执行生成命令。

### 3.5 函式库管理

- 动态与静态函式库

  ```
  静态函式库的特点
  1. 扩展名： 扩展名为 .a
  2. 编译行为： 这类函式库在编译的时候会直接整合到程序当中
  3. 独立执行的状态： 编译成功的可执行文件可独立的运行
  4. 升级难易度： 只要函数库更新升级，所有此函数库纳入的程序都要重新编译
  ```

  ```
  动态函式库的特点
  1. 扩展名： 扩展名一般为 .so
  2. 动态函式库的内容并没有整合到执行档中，当执行档使用函式库的机制时，程序才会去读取函式库来使用
  3. 独立执行的状态： 编译出来的程序不能独立执行，调用函式库的机制时去指定路径读取函式库
  4. 升级难易度：　函式库更新，编译的执行档会自动到新的函式库来读取
  ```

  **可以利用`ldconfig`和`/etc/ld.so.conf`来制作动态函式库的链接和快取**

- 软件安装机制

  | distribution代表 | 软件管理机制 | 使用指令      | 在线升级机制(指令) |
  | ---------------- | ------------ | ------------- | ------------------ |
  | Red Hat/Fedora   | RPM          | rpm、rpmbuild | YUM(yum)           |
  | Debian/Ubuntu    | DPKG         | dpkg          | APT(apt-get)       |

## 四 GDB工具使用

### 4.1 单步调试与跟踪

`linux`的调试工具为`gdb`,调试的基本思想仍然是“分析现象->假设错误原因->产生新的现象去验证假设.在编译的时候加上`-g`选项就能使用`gdb`调试工具了.

```shell
winston@Winstonly-Ly:~/TestProject$ g++ -g main.c -o main
winston@Winstonly-Ly:~/TestProject$ gdb main
GNU gdb (Ubuntu 7.11.1-0ubuntu1~16.5) 7.11.1
Copyright (C) 2016 Free Software Foundation, Inc.
License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>
This is free software: you are free to change and redistribute it.
There is NO WARRANTY, to the extent permitted by law.  Type "show copying"
and "show warranty" for details.
This GDB was configured as "x86_64-linux-gnu".
Type "show configuration" for configuration details.
For bug reporting instructions, please see:
<http://www.gnu.org/software/gdb/bugs/>.
Find the GDB manual and other documentation resources online at:
<http://www.gnu.org/software/gdb/documentation/>.
For help, type "help".
Type "apropos word" to search for commands related to "word"...
Reading symbols from main...done.
(gdb) 

```

**`-g`**选项的作用是在可执行文件中加入源代码的信息,比如可执行文件中的第几条机器指令对应源代码的第几行,但不是把整个源文件嵌入到可执行文件中.确保`gdb`能够找到相应的源文件.

`gdb`提供一个类似`Shell`的命令环境,输入`help`可以查看命令的类别.

`gdb`在提示符下直接敲回车表示重复上一条命令.

### 4.2 `gdb`基本命令

| 命令              | 描述                                                  |
| ----------------- | ----------------------------------------------------- |
| `backtrace`(`bt`) | 查看各级函数调用及参数                                |
| `finish`          | 连续运行到当前函数返回为止,然后停下来等待命令         |
| `frame(f) 帧编号` | 选择栈帧                                              |
| `info(i) locals`  | 查看当前栈帧局部变量的值                              |
| `list 行号`       | 列出从第几行开始的源代码                              |
| `list(l) 函数名`  | 列出某个函数的源代码                                  |
| `list(l)`         | 列出源代码,接着上次的为止往下列,每次列10行            |
| `next(n)`         | 执行下一行语句                                        |
| `print(p)`        | 打印表达式的值,通过表达式可以修改变量的值或者调用函数 |
| `quit(q)`         | 退出`gdb`调试环境                                     |
| `set var 变量=x`  | 修改变量的值                                          |
| `starts`          | 开始执行程序,停在`main`函数第一行语句前面等待命令     |
| `step(s)`         | 执行下一行语句,如果有函数调用则进入到函数中           |
|                   |                                                       |

### 4.3 有关断点的操作命令

**当程序执行到某一行代码时中断**

| 命令                         | 描述                                    |
| ---------------------------- | --------------------------------------- |
| `break(b) 行号`              | 在某一行设置断点                        |
| `break 函数名`               | 在某个函数开头设置断点                  |
| `break ... if ...`           | 设置条件断点,满足条件时中断             |
| `continue(c)`                | 从当前位置开始连续运行程序至断点处      |
| `delete breakpoints 断点号`  | 删除断点                                |
| `display 变量名`             | 跟踪查看某个变量,每次停下来都显示它的值 |
| `disable breakpoints 断点号` | 禁用断点                                |
| `enable 断点号`              | 启用断点                                |
| `info(i) breakpoints`        | 查看当前设置了哪些断点                  |
| `undisplay 跟踪显示号`       | 取消跟踪显示                            |
| `run(r)`                     | 从头开始连续运行程序                    |

### 4.4 观察点

**当程序访问某个存储单元时中断**

| 命令                  | 描述                                                         |
| --------------------- | ------------------------------------------------------------ |
| `watch`               | 设置观察点                                                   |
| `x`                   | 从某个位置开始打印存储单元的内容,全部当成字节来看,而不区分哪个字节属于哪个变量 |
| `info(i) watchpoints` | 查看当前设置了哪些观察点                                     |

### 4.5 段错误

程序运行时出现段错误,`gdb`很容易定位到哪一行发生错误

> 如果某个函数的局部变量发生访问越界，有可能并不立即产生段错误，而是在函
> 数返回时产生段错误。

**段错误产生的过程**：

>1. 用户程序要访问的一个VA，经过MMU检查无权访问
>
>2. MMU产生一个异常，CPU从用户模式切换到特权模式，跳转到内核代码中执行异常服务程序
>3. 内核把这个异常解释为段错误，把引发异常的进程终止掉

## 五 计算机体系结构

冯·诺依曼结构的计算机：CPU（中央处理器）和内存是计算机的两个主要组成部分，内存中保存着数据和指令，CPU从内存中取指令执行。

每个内存单元有一个地址，内存地址都是从0开始编号的证书，CPU通过地址找到相应的内存单元，取其中的指令或者读写其中的数据。

### 5.1 CPU

- 寄存器（Register）：CPU内部的高速存储器，向内存一样可以存取数据，但比访问内存快的多

- 程序计数器（PC）：一种特殊寄存器，保存着CPU取下一条指令的地址

- 指令译码器：负责解释指令的含义，然后调用相应的执行单元去执行它

- 算术逻辑单元（ALU）：负责加减乘除、位运算、逻辑运算的单元

- 地址和数据总线（BUS）：CPU和内存之间用地址总线、数据总线和控制总线连接起来U寄存器的位数通常是一致的，处理器的位数也称为字长

### 5.2 设备

- CPU执行指令也需要访问很多设备，如键盘、鼠标、硬盘、显示器等
- 设备中可供读写的单元成为设备寄存器，操作设备的过程就是读写这些寄存器的过程
- 内存映射I/O：无论是CPU外部接总线的设备还是CPU内部接总线的设备都有各自地址范围，可像访问内存一样访问
- 端口I/O：设备有独立的端口地址空间，CPU需要额外的地址线连接片内设备，访问时也有专用的指令（in/out）
- 操作系统核心功能：管理进程调度、管理内存的分配使用和管理各种设备（内核、Kernel）

### 5.3 内存管理单元（MMU）

- 虚拟地址和物理地址

- 具有地址转换的功能：

  - 操作系统在初始化或分配、释放内存时会执行一些指令在物理内存中填写页表，然后用指令设置MMU，告诉MMU页表在物理内存中的什么位置。

  - 设置好之后， CPU每次执行访问内存的指令都会自动引发MMU做查表和地址转换操作，地址转换操作由硬件自动完成，不需要用指令控制MMU去做。

- 内存保护机制：操作系统可在页表中设置权限，通过页面权限是否符合来判断是否能够访问

### 5.4 ELF文件

ELF文件格式是一个开放标准，各种UNIX系统的可执行文件都采用ELF格式

- 可重定位的目标文件（Object File）
- 可执行文件（Executable）
- 共享库（Shared Library）

## 六 Linux系统编程

### 6.1 文件与I/O

所有I/O操作最终都是在内核中实现的，以前用过的C标准I/O库函数最终也是通过系统调用I/O操作从用户空间传给内核，然后让内核去操作。

每个进程在Linux内核中都有一个`task_struct`结构体来维护进程相关的信息，成为进程描述符（在操作系统理论中称为进程控制块），`task_struct`中有一个指针指向`file_struct`结构体，称为文件描述符表，其中每个表项包含一个指向已打开的文件指针。

用户程序是不能直接访问内核中的文件描述符表，而只能使用文件描述符表的索引（即0、1、2、3这些数字），这些索引就是文件描述符，用`int`型变量表示。当调用`open`打开一个文件或创建一个新的文件时，内核分配一个文件描述符并返回给用户程序。

- `open/close`

  ```c
  /* 打开或者创建一个文件 */
  /* 返回值: 成功返回新分配的文件描述符，出错返回-1并设置errno */
  int open(const char *pathname, int flags, ...);
  
  /* 关闭一个已打开的文件 */
  /* 返回值:　成功返回0，出错返回-1并设置errno*/
  int close(int fd);
  ```

- `read/write`

  ```c
  /* 从打开的设备或者文件中读取数据　*/
  /* 返回值: 成功返回读取的字节数，出错返回-1并设置errno */
  ssize_t read(int fd, void *buf, size_t count);
  
  /* 向打开的设备或者文件中写数据 */
  /* 返回值： 成功返回写入的字节数，出错返回-1并设置errno */
  ssize_t write(int fd, const void *buf, size_t count);
  ```

- `lseek`

  ```c
  /* 移动当前读写为止或者叫做偏移量 */
  /* 成功返回新的偏移量 */
  off_t lseek(int fd, off_t offset, int whence);
  ```

- `fcntl`

  ```c
  /* 改变一个已打开的文件的属性，可以重新设置读、写、追加、阻塞等标识 */
  int fcntl(int fd, int cmd);
  int fcntl(int fd, int cmd, long arg);
  int fcntl(int fd, int cmd, struct flock *lock);
  ```

- `ioctl`

  ```c
  /* 向设备发控制和配置命令 */
  /* d: 某个设备的文件描述符 */
  /* request: ioctl的命令，可变参数取决于request */
  /* 返回值： 成功返回值取决于request，出错返回-1 */
  int ioctl(int d, int request, ...);
  ```

- `mmap`

  ```c
  /* 把磁盘文件的一部分直接映射到内存，这样文件中的位置就有对应的内存地址 */
  void *mmap(void *addr, size_t len, int prot, int flag, int filedes, off_t off);
  int munmap(void *addr, size len);
  ```

### 6.2 文件系统

- **ext2文件系统**

格式化的过程会在磁盘上写一些管理存储的信息，进行一个存储布局。

文件系统中存储的最小单位是块（block），存储布局中有`Boot Block`，这个启动块的大小是确定的，由PC标准规定，用来存储磁盘分区信息和启动信息。启动块之后才是ext2文件系统，ext2文件系统将整个分区划分成块组（Block Group），每个块组由以下部分组成：

- 超级块：整个分区的文件系统信息
- 块组描述符表：块描述符存储一个块组的描述信息
- 块位图：描述整个块组中哪些已用哪些空闲，本身占一个块
- `inode`位图：每个bit表示一个`inode`是否空闲可用
- `inode`表：每个文件都有一个inode，一个块组的所有inode组成inode表
- 数据块：
  - 常规文件，文件数据存储在数据块中
  - 对于目录，该目录下的所有文件名和目录名存储在数据块中
  - 对于符号链接，路径名较长则分配一个数据块来保存
  - 设备文件、FIFO和socket等特殊文件没有数据块
- `df`：统计整个磁盘的已用空间
- `du`：查看一个目录的已用空间
- `dd`：把一个文件的一部分拷贝成另一个文件

利用`dumpe2fs`工具可查看分区的超级块和块组描述符表中的信息

- **文件与目录**

  1. `Linux`文件简介

     在`linux`我们可以用`ls -l`来显示一个文件目录下文件的属性和所属用户组

     ```shell
     winston@Winstonly-Ly:~$ ls -l
     total 504
     drwxrwxr-x 2 winston winston   4096 2月  11 13:36 bin
     drwxr-xr-x 2 winston winston   4096 2月  13 13:26 Desktop
     ... ...
     drwxr-xr-x 2 winston winston   4096 2月  10 17:32 Templates
     drwxr-xr-x 2 winston winston   4096 2月  10 17:32 Videos
     drwxrwxr-x 2 winston winston   4096 2月  18 16:56 学习资料
     drwxrwxr-x 4 winston winston   4096 2月  13 13:32 文档记录
     ```

     ![image-20200221123617696](/home/winston/文档记录/工作准备/image/文件权限.png)

     在`Linux`中第一个字符代表这个文件是目录(d)、文件(-)、或链接文件(l)等等；

     在接下来的字符中，以三个为一组，且均为`rwx`的三个参数的组合，其中`r`代表可读(read)、`w`代表可写(write)、`x`代表可执行(execute)；

     从第二个字符开始，三个字符为一组，分别表示，档案拥有者权限、同群组权限、其他非本群组权限。

  2. 文件操作

     - 更改档案所属群组 `chgrp` 

       ```shell
       chgrp [-R] 档案名或目录名
       ```

     - 更改档案拥有者 `chown`

       ```shell
       chown [-R] 账号名称 档案名或目录名
       chown [-R] 账号名称：群组名 档案名或目录名
       ```

     - 更改档案的权限 `chmod`

       ```shell
       chmod [-R] xxx 档案名或目录 
       # xxx表示数字类型的权限属性 rwx = 421
       ```

  3. 目录管理常用命令

     ```shell
     ls ： 列出目录
     cd ： 切换目录
     pwd ：　先当前目录
     mkdir ： 创建一个新的目录
     rmdir ： 删除一个空的目录
     cp ： 复制文件或者目录
     rm ： 一出文件或者目录
     mv ： 移动文件与目录，或者修改文件或者目录的名称
     cat ：　由第一行开始显示文件内容
     nl ： 显示的时候顺道输出文件内容
     more ：　一页一页的显示文件内容
     ```

- **VFS（虚拟文件系统）**

   Linux内核在各种不同的文件系统格式之上做了一个抽象层，使得文件、目录、读写访问等概念成为抽象层的概念，因此各种文件系统看起来用起来都一样，这个抽象层称为虚拟文件系统（VFS， Virtual Filesystem） 。

  已打开的文件在内核中用file结构体表示，文件描述符表中的指针指向file结构体。

  每个file结构体都指向一个file_operations结构体，这个结构体的成员都是函数指针，指向实现各种文件操作的内核函数。

  每个file结构体都有一个指向dentry结构体的指针， “dentry”是directory entry（目录项）的缩写。

  每个dentry结构体都有一个指针指向inode结构体。 inode结构体保存着从磁盘inode读上来的信息。

  inode结构体有一个指向super_block结构体的指针。 super_block结构体保存着从磁盘分区的超级块读上来的信息，例如文件系统类型、块大小等。

### 6.3 正则表达式

规定一些特殊语法表示字符类、数量限定符和位置关系，然后用这些特殊语法和普通字符一起表示一个模式，这就是正则表达式（Regular Expression） 。

- 基本语法

  | 字符      | 含义                                                     | 举例                                                         |
  | --------- | -------------------------------------------------------- | ------------------------------------------------------------ |
  | .         | 匹配任意一个字符                                         | abc.可以匹配abcd、 abc9等                                    |
  | []        | 匹配括号中的任意一个字符                                 | [abc]d可以匹配ad、 bd或cd                                    |
  | -         | 在[]括号内表示字符范围                                   | [0-9a-fA-F]可以匹配一位十六进制数字                          |
  | ^         | 位于[]括号内的开头，匹配除括号中的字符之外的任意一个字符 | [^xy]匹配除xy之外的任一字符，因此`[^xy]1`可以匹配a1、 b1但不匹配x1、 y1 |
  | [[:xxx:]] | grep工具预定义的一些命名字符类                           | [[:alpha:]]匹配一个字母， [[:digit:]]匹配一个数字            |
  | ?         | 紧跟在它前面的单元应匹配零次或一次                       | [0-9]\.[0-9]匹配0.0、 2.3、 .5等，由于.在正则表达式中是一个特殊字符，所以需要用\转义一下，取字面值 |
  | +         | 紧跟在它前面的单元应匹配一次或多次                       | `[a-zA-Z0-9_.-]+@[a-zA-Z0-9_.-]+\.[a-zA-Z0-9_.-]+`匹配email地址 |
  | *         | 紧跟在它前面的单元应匹配零次或多次                       | `[0-9][0-9]*`匹配至少一位数字，等价于[0-9]+， [azA-Z_]+[a-zA-Z_0-9]*匹配C语言的标识符 |
  | {N}       | 紧跟在它前面的单元应精确匹配N次                          | `[1-9][0-9]{2}`匹配从100到999的整数                          |
  | {N,}      | 应匹配至少N次                                            | `[1-9][0-9]{2,}`匹配三位以上（含三位）的整数                 |
  | {,M}      | 紧跟在它前面的单元应匹配最多M次                          | [0-9]{,1}相当于[0-9]?                                        |
  | {N,M}     | 紧跟在它前面的单元应匹配至少N次，最多M次                 | [0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}匹配IP地址     |
  | ^         | 匹配行首的位置                                           | ^Content匹配位于一行开头的Content                            |
  | $         | 匹配行末的位置                                           | ;$匹配位于一行结尾的;号， ^$匹配空行                         |
  | <         | 匹配单词开头的位置                                       | \<th匹配... this，但不匹配ethernet、 tenth                   |
  | >         | 匹配单词结尾的位置                                       | p\>匹配leap ...，但不匹配parent、 sleepy                     |
  | \b        | 匹配单词开头或结尾的位置                                 | \bat\b匹配... at ...，但不匹配cat、 atexit、 batch           |
  | \B        | 匹配非单词开头和结尾的位置                               | \Bat\B匹配battery，但不匹配... attend、 hat...               |

## 七 TCP/IP协议栈和数据包封装

### 7.1  TCP/IP协议基础

TCP/IP网络协议栈分为应用层、传输层、网络层、链路层四层。

- 应用层：

  - 应用层为操作系统或网络应用程序提供访问网络服务的接口。

  - Telnet、FTP、e-mail等，应用层数据通过协议栈发到网络上时，每层协议都要加上一个数据首部（header），称为封装（Encapsulation）。

- 传输层：

  - 管理两个节点之间的数据传输。负责可靠传输（确保数据被可靠地传送到目标地址）

  - TCP、UDP

- 网络层：

  - 地址管理与路由选择, 在这一层，数据的单位称为数据包(packet)(路由器）

  - IP、ICMP和IGMP

  - 网络层的IP协议是构成Internet的基础。Internet上的主机通过IP地址来标识，Internet上的路由器负责根据IP地址选择合适的路径转发数据包。

- 链路层：

  - 互连设备之间传送和识别数据帧（交换机）。

  - 设备驱动程序及接口卡，链路层下还有物理层，指的是电信号的传递方式。链路层有以太网、令牌环网等标准，链路层负责网卡设备的驱动、帧同步、冲突检测、数据差错校验等工作。

不同的协议层对数据包有不同的称谓，在传输层叫做段（segment），在网络层叫做数据报（datagram），在链路层叫做帧（frame）。网络层负责点到点的传输，而传输层负责端到端的传输。

### 7.2 IP地址与路由

- Internet被各种路由器和网关设备分隔成很多网段，为了标识不同的网段，需要把32位的IP地址划分成网络号和主机号两部分，网络号相同的各主机位于同一网段，相互间可以直接通信，网络号不同的主机之间通信则需要通过路由器转发。

- 网络号和主机号的划分需要用一个额外的子网掩码（subnet mask）来表示，IP地址与子网掩码做与运算可以得到网络号，主机号从全0到权益就是子网地址范围。

- 路由：数据包从原地址到目的地址所经过的路径，有一系列路由节点组成
- 路由：某个路由节点为数据报选择投递方向的选路过程

### 7.3 TCP协议

- TCP（Transmission Control Protocol，传输控制协议）是 面向连接的协议，也就是说在收发数据之前，必须先和对方建立连接。它的主要任务是**在可靠传输数据的基础之上，尽可能的提高传输的效率**。
- 三次握手，建立连接
  - 客户端向服务器发送一个SYN J
  - 服务器向客户端响应一个SYN K，并对SYN J进行确认ACK J+1
  - 客户端再想服务器发一个确认ACK K+1
- 四次挥手，释放连接
  - 客户端向服务器发送一个FIN M
  - 服务器接收到FIN M后，执行被动关闭，对这个FIN M进行确认。它的接收也作为文件结束符传递给应用进程，向客户端发送ACK M+1
  - 一段时间后，接收到文件结束符的应用程序主动调用close关闭它的socket，向客户端发送FIN N
  - 客户端接收到ACK FIN N之后进行确认，向服务器发送ACK N+1，释放连接。

## 八 socket编程

### 8.1 预备知识

- 网络数据流的地址规定：先发出的数据是低地址，后发出的数据是高地址，发送方将缓冲区的数据按内存地址从低到高发出，接收方按内存地址从低到高的顺序保存在缓冲区。

- TCP/IP协议规定，网络数据流采用大端字节序，即低地址高字节。

- socket API是一层抽象的网络编程接口，适用于各种底层网络协议，各种协议的地址格式并不相同：

  | struct sockaddr | struct sockaddr_in              | struct sockaddr_un    |
  | --------------- | ------------------------------- | --------------------- |
  | 16位地址类型    | 16位地址类型：AF_INET           | 16位地址类型：AF_UNIX |
  | 14字节地址数据  | 16位端口号+32位IP地址+8字节填充 | 108字节路径名         |

  各种socket地址结构体的开头都是相同的，前16位表示整个结构体的长度，后16位表示地址类型。

### 8.2 网络之间通信

网络中进程之间通信首先要解决的问题是**如何唯一标识一个进程**，TCP/IP协议栈的解决办法是**网络层的ip地址可以唯一标识网络中的主机，而传输层的协议+端口可以唯一标识主机中的应用程序（进程）**，这样利用三元组（ip地址，协议，端口）就可以标识网络中的进程了。

使用TCP/IP协议的应用程序是通过采用编程接口：socket（套接字）来实现网络进程之间的通信。

### 8.3 socket的基本操作

Linux的基本哲学之一就是一切皆是文件，都可以**打开open-->读写write/read-->关闭close**模式来操作。socket就提供了这些操作对应的接口函数。

- socket()函数

  socket函数对应于普通文件的打开操作，socket()返回一个socket描述符，唯一标识一个socket。

  ```cpp
  int socket(int domain, int type, int protocol);
  # dimain：协议族，AN_INET,AF_INET6,AF_LOCAL
  # type：	 指定socket类型，SOCK_STREAM,SOCK_DGRAM,SOCK_RAW,SOCK_PACKET
  # protocol： 指定协议，IPPROTO_TCP,IPPTOTO_UDP,IPPROTO_SCTP，IPPROTO_TIPC 
  ```

- bind()函数

  bind()函数将一个地址族中的特定地址赋给socket

  ```shell
  
  ```
  
  服务器启动的时候会绑定一个众所周知的地址，客户端通过它来连接服务器，而客户端就不用指定，由系统自动分配一个端口号和自身的ip地址组合。
  
>

- listen()、connect()函数

  作为一个服务器，在调用socket(),bind()之后就会调用listen()来监听这个socket，如果客户端这个时候调用connetc()发出连接请求，服务器就会收到这个请求。

  ```cpp
  int listen(int sockfd, int backlog);
  # listen的第一个参数为socket描述字，第二个参数为socket可以排队的最大连接个数
  # socket()创建的socket默认是一个主动类型，listen将socket变为被动类型，等待客户连接
  int connect(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
  # connect函数的第一个参数为socket描述字，第二个参数为服务器的socket地址，第三个参数为socket地址的长度
  ```

- accept()函数

  TCP服务器监听收到请求之后，调用accept()函数来接受请求。这样建立好连接之后就可以开始网络I/O操作。

  ```cpp
  int accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen);
  # sockfd：socket描述字
  # addr： 指向struct sockaddr×的指针，用于返回客户端的协议地址
  # addrlen： 协议地址的长度
  # 如果accept成功，返回值是内核自动生成的一个全新的描述字，代表与返回客户的TCP连接
  ```

- read()、write()函数

  调用网络I/O进行读写操作，实现网络中不同进程之间的通信。read函数负责从fd中读取内容，成功返回读的字节数；write将缓冲区的内容写入fd，返回值大于0，表示写了部分或者全部的数据，返回的值小于0，出现错误。

  ```cpp
  read()/write()
  recv()/send()
  readv()/wrtiev()
  `recvmsg()/sendmsg()
  recvfrom()/sendto()
  ```

- 8.4 socket中TCP的三次握手连接和四次挥手详情

**三次握手**

![](/media/winston/本地磁盘/Job/document/image/TCP三次握手.png)

- 首先客户端调用connect，发送连接请求，向服务器发送SYN J包，然后connect进入阻塞状态；
- 服务器监听到连接请求，收到SYN J包，调用accept函数接受请求并向客户端发送SYN K，ACK J+1，然后accept进入阻塞状态；
- 客户端收到SYN K，ACK J+1之后，这是connect返回，并对SYN K进行确认，发送ACK K+1；
- 服务器收到ACK K+1后，accept返回，此时三次握手完成连接建立

**四次挥手**

![](/media/winston/本地磁盘/Job/document/image/TCP四次挥手.png)

- 某个应用进程首先调用close主动关闭连接，这时TCP发送一个FIN M；
- 另一端接收到FIN M之后，执行被动关闭，对这个FIN进行确认。它的接收也作为文件结束符传递给应用进程，因为FIN的接收意味着应用进程在相应的连接上再也接收不到额外数据；
- 一段时间之后，接收到文件结束符的应用进程调用close关闭它的socket。这导致它的TCP也发送一个FIN N；
- 接收到这个FIN的源发送端TCP对它进行确认。

## Socket编程

### Linux中的socket介绍

在计算机通信领域，socket被翻译成**套接字**，通过socket这种约定，计算机之间棵通信同时计算机内部也可通信，是一种网络进程间通信。

socket的典型应用是Web服务器和浏览器

在Linux下可以认为一切皆文件，每个文件都有对应的ID（文件描述符），Linux程序在执行任何形式的I/O操作时，都是在读取或者写入一个文件描述符。

网络连接也可以认为是一个文件，也有文件描述符，可以通过`socket()`函数创建一个网络连接，`socket()`的返回值就是文件描述符，有了文件描述符就可以用普通文件操作函数来传输数据：

- 用`read()`读取从远程计算机传来的数据
- 用`write()`向远程计算机写入数据



### TCP/IP 协议

**OSI模型（开放式系统互联）**：将网络通信的工作分为7层，**从上到下**依次是：物理层、数据链路层、网络层、传输层、会话层、表示层和应用层；精简之后的模型如下：**从下到上依次是接口层、网络层、传输层和应用层**

![网络模型](/media/winston/本地磁盘/Job/document/image/网络模型.png)

网络模型的每一层都是在进行数据封装。

**TCP/IP协议**对OSI模型进行简化，从上到下依次是**应用层、传输层、网络层和数据链路层（网络接口层）**，每一层都包含了若干协议。

**协议**：网络通信过程中的约定或者合同，通信的双方都必须遵守才能正常收发数据，如TCp、UDP、IP等。TCP/IP模型包含了TCP、IP、UDP、Telnet、FTP等互为相关的协议，TCP、IP是两种底层协议，所以统称为TCP/IP协议族。

socket编程是基于TCP和UDP协议的，层级关系如下：

![scoket层级关系](/media/winston/本地磁盘/Job/document/image/socket层级关系.png)

**网络中确认身份信息的三要素**：IP地址，MAC地址和端口号

- *IP地址*：网际协议地址，常用IPv4地址，IPv6也在逐渐使用，数据包中附带iP地址，路由器接收后，根据IP地址和智能的算法找到对方的地理位置，完成一次数据传输。
- *MAC地址*：往往是一个局域网才拥有一个独立的IP地址，真正能**唯一标识一台计算机的是MAC地址**，每个网卡的MAC地址都是独一无二的，数据包中也会附带对方的MAC地址。
- *端口号*：一台计算机有多种网络服务，计算机为每个网络程序分配一个独一无二的端口号，通过端口号才能完成特定的数据通信。

### 寻址

- 字节序(一个处理器架构特性)

  >网络数据流的地址规定：先发出的数据是低地址，后发出的数据是高地址，发送方将缓冲区的数据按内存地址从低到高发出，接收方按内存地址从低到高的顺序保存在缓冲区。
  >
  >**主机字节序**：平常说的大端和小端模式
  >
  >- Little-Endian：低字节低地址，高字节高地址
  >- Big-Endian：高字节低地址，低字节高地址
  >
  >**网络字节序**：
  >
  >- 4个字节的32bit值以下面的次序传输：
  >
  > 首先是0~7bit、其次是8~15bit、然后16~23bit、最后是24~31bit，这种传输次序称为大端字节序
  >
  >**网络协议会指定字节序，如TCP/IP 协议采用大端字节序，而地址表示是网络字节序；所以将一个地址绑定到socket的时候，应现将主机字节序转换为网络字节序**
  >
  >
  >
  >下面是几个处理器字节序和网络字节序之间的转换
  >
  >```cpp
  >#include <arpa/inet.h>
  >uint32_t htonl(uint32_t hostint32);		// 返回值：以网络字节序表示的32位整型数
  >uint32_t htons(uint16_t hostint16);		// 返回值：以网络字节序表示的16位整型数
  >uint32_t ntohl(uint32_t netint32);		// 返回值：以主机字节序表示的32位整型数
  >uint16_t ntohs(uint16_t netint16);		// 返回值：以主机字节序表示的16位整型数
  >```

- 地址格式

  地址标识了特定通信领域中的套接字类型，地址格式与特定的通信域有关，传入套接字函数的时候地址被强制转换为通用结构`sockaddr`：

  ```cpp
  struct sockaddr{
  	sa_family_t sa_family;		// address family
  	char 		sa_data[];		// variable-length address
  };
  ```

  套接字实现可以自由地添加额外的成员并定义`sa_data`成员的大小

  ```cpp
  // IPv4因特网域（AF_INET)中套接字地址结构：
  struct in_addr
  {
  	in_addr_t s_addr;	// IPv4 address
  };
  struct sockaddr_in
  {
  	sa_family_t		sa_family;
  	in_port_t		sin_port;		// port number > 1023,用htons()转换格式
  	struct in_addr 	sin_addr;		// IPV4 address
  	char			size_zero[8];	// 不使用，一般用 0 填充
  }
  
  // Linux下套接字地址结构定义：
  struct sockaddr
  {
  	sa_family_t 	sa_family;
  	char			sa_data[14];
  }
  ```

  有时需要答应能被人理解的地址格式：提供下面两个函数在二进制地址格式和点分十进制字符串表示(a.b.c.d)之间转换：

  ```cpp
  #include <arpa/inet.h>
  # 将网络字节序的二进制地址转换成文本字符串格式
  // 返回值：成功返回地址字符串指针，出错返回NULL
  const char *inet_ntop(int domain, const void *restrict addr, char *restrict str, socklen_t size);
  
  # 将文本字符串格式转换成网络字节序的二进制地址
  // 返回值：成功返回 1，格式无效返回 0，出错返回 -1
  int inet_pton(int domain, const char *restrict str, void *restrict addr);
  
  #domain 支持两个值：AF_INET AF_INET6
  #size   用于指定保存文本字符串的缓冲区(str)的大小
  ```

- 创建套接字

  套接字描述符在Unix系统中用文件描述符实现，用**`socket`**函数创建一个套接字：

  ```cpp
  #include <sys/socket.h>
  /*
   *返回值：成功返回文件（套接字）描述符，失败返回 -1
   */
  int socket(int domain, int type, int protocol);
  
  // TCP 套接字
  int tcp_socket = socket(AF_INET, SOCK_STREAM, 0/IPPROTO_UDP)
  ```

  - 参数介绍

    > *domain（域）*：确定通信的特性，包括地址格式，各个域的常数以AF_开头，意指地址族,套接字通信域如下：
    >
    > | 域        | 描述          |
    > | --------- | ------------- |
    > | AF_INET   | IPv4 因特网域 |
    > | AF_INET6  | IPv6 因特网域 |
    > | AF_UNIX   | UNIX 域       |
    > | AF_UNSPEC | 未指定        |
    >
    > *type*：套接字类型，下表是一些常见的定义：
    >
    > 1. SOCK_STREAM（TCP协议）
    >
    >    - 有序：按顺序传输
    >    - 可靠：出现问题阻塞重传，数据不会丢失
    >    - 数据的发送和接收不同步，接收方存在缓冲区（数据没有边界）
    >    - 面向连接：在交换数据之前在本地套接字和与之通信的远程套接字之间建立逻辑连接
    >
    > 2. SOCK_DGRAM（UDP协议）
    >
    >    - 强调传输速度而非传输顺序
    >    - 传输的数据可能丢失或损毁
    >    - 长度固定：限制每次传输的数据大小
    >    - 存在数据边界：数据的发送和接收是同步的
    >    - 无连接的套接字，只管传输不做数据校验
    >
    > 3. SOCK_RAW 
    >
    >    socket类型提供单一的网络访问，这个socket类型使用IP协议。（ping、traceroute使用该协议） 
    >
    > 4. SOCK_SEQPACKET
    >
    >    该协议是双线路的、可靠的连接，发送固定长度的数据包进行传输。必须把这个包完整的接受才能进行读取。
    >
    > *protocol*：通常为0，表示按给定的域和套接字类型选择默认协议，IPPROTO_TCP(TCP)、IPPTOTO_UDP(UDP)
    >
    > [面向连接和无连接的套接字的区别] http://c.biancheng.net/view/2125.html

  - 处理套接字时的行为

    | 函数            | 处理套接字时的行为                      |
    | --------------- | --------------------------------------- |
    | `close`         | 释放套接字                              |
    | `dup、dup2`     | 和一般文件描述符一样复制                |
    | `fchdir`        | 失败，并且将errno设置为ENOTDIR          |
    | `fchmod`        | 未规定                                  |
    | `fcntl`         | 支持一些命令，如F_DUPFD,F_GETFD,F_GETFL |
    | `ioctl`         | 支持部分命令，依赖于底层设备驱动        |
    | `read，readv`   | 与没有任何标志位的recv等价              |
    | `write，writev` | 与没有任何标志位的send等价              |
    | `shutdown`      | 禁止套接字上的输入输出                  |

    >```cpp
    >#incldue <sys/socket.h>
    >int shutdown(int socket, int how);
    >
    >// how：SHUT_RD（关闭读端），SHUT_WR（关闭写端）
    ># shutdown允许一个套接字处于不活动状态，无论引用它的文件描述符数目多少
    >```

- 将套接字和地址绑定

  对于客户端，与之关联的套接字的地址没有多大意义，系统会自动分配一个默认地址；但是对于服务器，需要给一个接收客户端请求的套接字绑定一个众所周知的地址，客户端有一种方法来发现用以连接服务器的地址。

  可用**`bind`**函数将地址绑定到一个套接字,

  ```cpp
  #include <sys/socket.h>
  // 成功返回 0 ，失败返回 -1
  // 指定的地址必须有效，地址和套接字的地址族格式匹配，端口号大于1024（除非为超级用户）
  int bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
  # sockfd: socket描述字，通过socket()函数创建，唯一标识一个socket
  # addr: 一个const struct sockaddr*指针，指向要绑定给sockfd的协议地址
  # addrlen： 对应的地址长度
  
  // getsockname来发现绑定到一个套接字的地址
  int getsockname(int sockfd, struct sockaddr *restrict addr, socklen_t *restrict alenp);
  # alenp 为一个指向整数的指针，该整数指定缓冲区sockaddr的大小
  
  // 如果套接字和对方建立连接，getpeername来发现对方的地址
  int getpeername(int sockfd, struct sockaddr *restrict addr, socklen_t *restrict alenp);
  ```

- 建立连接

  对于面向连接的网络服务（SOCK_STREAM\SOCK_SEQPACKET)，在开始交换数据以前，需要在请求服务的进程套接字（客户端）和提供服务的进程套接字（服务器）之间建立一个连接
  
  客户端利用`connect`建立一个连接：
  
  ```cpp
  #include <sys/socket.h>
  int connect(int sockfd, struct sockaddr *restrict addr, socklen_t len);
  
  // 返回值：成功返回 0，出错返回 -1
  # 在connect中所指定的地址是想与之通信的服务器地址，如果sockfd没有绑定到一个地址，系统会给调用者绑定一个默认地址
  ```
  
  服务端利用`listen`来宣告可以接受连接请求，这时使得套接字进入被动监听状态（无客户端请求，套接字处于睡眠，有客户端请求，套接字唤醒）
  
  ```cpp
  #include <sys/socket.h>
  int listen(int sockfd, int backlog);
  
  // backlog：提供一个提示，用于表示该进程所要入队的连接请求数量，其实际值由系统决定，但上限由		
     <sys/socket.h>中的SOMAXCONN决定。队列满就会拒绝多余连接请求，这时客户端会收到ECONNREfUSED错误
  # socket()创建的socket默认是一个主动类型，listen将socket变为被动类型，等待客户连接
  # 请求队列，当套接字正在处理客户端请求，无法处理新进来的请求，会将新的请求存在缓冲区中，按照先后顺序在缓冲区排队，知道缓冲区满，这个缓冲区就是请求队列
  ```
  
  一旦服务器调用了`listen`，套接字就能接收连接请求，使用`accept`获得连接请求并建立连接：
  
  ```cpp
  #include <sys/socket.h>
  int accpet(int sockfd, struct sockaddr *restrict addr, socklen_t *restrict len);
  
  // 返回值：成功返回文件（套接字）描述符，出错返回 -1
  // addr 用来缓存地址的缓冲区，保存客户端的IP地址和端口号，len所指向的整数为该地址的长度
  # 返回的文件描述符是套接字描述符，该描述符连接到调用`connect`的客户端
  # 新的套接字描述符和原始套接字（socket）具有相同的套接字类型和地址族，传给accpet的原始服务器端的套接字没有关联到这个连接，而是继续保持可用状态并接受其他连接请求
  # 如果没有连接请求等待处理，accept会阻塞到下一个请求到来
  ```
  
  **作为一个服务器，在调用`socket(),bind()`之后就会调用`listen()`来监听这个socket，如果客户端这个时候调用connetc()发出连接请求，服务器就会收到这个请求，然后服务器调用`accept（)`来建立连接。**

### 数据传输

建立连接之后就可以向操作文件描述那样进行`read`和`write`来交换数据。下面的函数可以指定选项，从多个客户端接收数据包或发送数据。

**`write和read`**

```cpp
ssize_t write(int fd, const void *buf, size_t nbytes);
// fd 要写入的文件描述符，buf 要写入的数据的缓冲区地址， nbytes 要写入的数据的字节数

ssize_t read(int fd, void *buf, size_t nbytes);
// 从fd文件中读取nbytes个字节数据并保存到缓冲区buf
```

用于发送数据的函数：

**send**

```cpp
#include <sys/socket.h>
ssize_t send(int sockfd， const void *buf, size_t nbytes, int flags);
// 成功返回发送的字节数，出错返回 -1
# send和write类似，但可以指定标志来改变处理传输数据的方式，使用send时套接字必须已经建立连接 
# send成功不代表另一端进程接收数据，仅表示数据已经无错发送到网络；对于字节流协议send会阻塞直到整个数据被传输
```

>![套接字调用标志](/media/winston/本地磁盘/Job/document/image/套接字调用标志.png)

**sendto**:

```cpp
#include <sys/socket.h>
ssize_t sendto(int sockfd, const void *buf, size_t nbytes, int falgs, 
				csont struct sockaddr *destaddr, socklen_t destlen);
// 成功返回发送的字节数，出错返回 -1
# sendto允许在无连接的套接字上指定一个目标地址
```

**sendmsg**：

```cpp
#include <sys/socket.h>
ssize_t sendmsg(int sockfd, const strcut msghdr *msg, int flags);
// 成功返回发送的字节数，出错返回 -1
# 可指定多重缓冲区传输数据，和wrtiev很相似
```

用于接收数据的函数

**recv**:

```cpp
#include <sys/socket.h>
ssize_t recv(int sockfd, void *buf, sizt_t nbytesm int flags);
// 返回值：以字节计数的消息长度，若无消息或对方已按序结束则返回0，出错返回 -1
# 允许指定选项来控制如何接收数据：MSG_OOB(如果协议支持，接收带外数据)，MSG_PEEK(返回报文内容而不取走报文)，MSG_WAITALL(等待直到所有的数据可用)，MSG_TRUNC(即使报文截断，要求返回报文的实际长度)
```

**recvfrom**：

```cpp
#include <sys/socket.h>
ssize_t recvfrom(int sockfd, void *restrict buf, size_t len, int flags,
					struct sockaddr * restrict addr, socklen_t 8restrict addrlen);
// 返回值，以字节计数的消息长度，若无可用消息或对方已按序结束返回 0，出错返回 -1
# addr非空就会包含数据发送者的套接字地址，可用于无连接套接字
```

**recvmsg**：

```cpp
#include <sys/socket.h>
ssize_t recvmsg(int sockfd, struct msghdr *msg, int flags);
// 返回值：以字节计数的消息长度，若无可用消息或对方已按序结束返回 0，出错返回 -1
```

**close**

完成读写操作之后就要关闭相应的socket描述字

```cpp
#include <unistd.h>
int close(int fd);
# 把该socket标记为已关闭，然后立即返回到调用进程
```

演示程序：客户端从服务器读取一个字符串并打印出来

```cpp
// 服务器端代码
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
int main(){
    //创建套接字
    int serv_sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    //将套接字和IP、端口绑定
    struct sockaddr_in serv_addr;
    memset(&serv_addr, 0, sizeof(serv_addr));  //每个字节都用0填充
    serv_addr.sin_family = AF_INET;  //使用IPv4地址
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");  //具体的IP地址
    serv_addr.sin_port = htons(1234);  //端口
    bind(serv_sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
    //进入监听状态，等待用户发起请求
    listen(serv_sock, 20);
    //接收客户端请求
    struct sockaddr_in clnt_addr;
    socklen_t clnt_addr_size = sizeof(clnt_addr);
    int clnt_sock = accept(serv_sock, (struct sockaddr*)&clnt_addr, &clnt_addr_size);
    //向客户端发送数据
    char str[] = "http://c.biancheng.net/socket/";
    write(clnt_sock, str, sizeof(str));
   
    //关闭套接字
    close(clnt_sock);
    close(serv_sock);
    return 0;
}

// 客户端代码
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
int main(){
    //创建套接字
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    //向服务器（特定的IP和端口）发起请求
    struct sockaddr_in serv_addr;
    memset(&serv_addr, 0, sizeof(serv_addr));  //每个字节都用0填充
    serv_addr.sin_family = AF_INET;  //使用IPv4地址
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");  //具体的IP地址
    serv_addr.sin_port = htons(1234);  //端口
    connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
   
    //读取服务器传回的数据
    char buffer[40];
    read(sock, buffer, sizeof(buffer)-1);
   
    printf("Message form server: %s\n", buffer);
   
    //关闭套接字
    close(sock);
    return 0;
}
```

>代码解读：
>
>- 先运行服务器程序，代码运行到`accpet`函数就会阻塞等待客户端发起请求
>- 在运行客户端程序，通过`connect`函数向服务器发起请求，处于监听状态的服务器被激活，利用`write`发送数据，客户端通过`read`函数读取数据

### socket缓冲区和阻塞

- socket缓冲区

  **每个 socket 被创建后，都会分配两个缓冲区，输入缓冲区和输出缓冲区**

  `write()/send()`函数并不立即向网络中传输数据，而是先将数据写入到缓冲区中，再由TCP/IP协议将数据从缓冲区发送到目标机器。一旦将数据写入到缓冲区，函数就可以成功返回，不管它们有没有到达目标机器，也不管它们何时被发送到网络，这些都是TCP协议负责的事情

  `read()/recv() `函数也是如此，也从输入缓冲区中读取数据，而不是直接从网络中读取。下面是TCP/IP套接字的I/O缓冲区示意图：

  ![TCP套接字IO缓冲区示意图](/media/winston/本地磁盘/Job/document/image/TCP套接字IO缓冲区示意图.png)

  >这些缓冲区特性如下：
  >
  >- I/O缓冲区在每个TCP套接字中单独存在；
  >- I/O缓冲区在创建套接字时自动生成；
  >- 即使关闭套接字也会继续传送输出缓冲区中遗留的数据；
  >- 关闭套接字将丢失输入缓冲区中的数据；
  >- 利用`getsockopt`可获得缓冲区大小，默认为8K。

- 阻塞模式

  当使用` write()/send() `发送数据时：

  1. 首先会检查缓冲区，如果缓冲区的可用空间长度小于要发送的数据，那么` write()/send()` 会被阻塞（暂停执行），直到缓冲区中的数据被发送到目标机器，腾出足够的空间，才唤醒` write()/send()` 函数继续写入数据。
  2.  如果TCP协议正在向网络发送数据，那么输出缓冲区会被锁定，不允许写入，`write()/send() `也会被阻塞，直到数据发送完毕缓冲区解锁，write()/send() 才会被唤醒。
  3. 如果要写入的数据大于缓冲区的最大长度，那么将分批写入。
  4. 直到所有数据被写入缓冲区` write()/send() `才能返回。

  当使用 `read()/recv() `读取数据时：

  1. 首先会检查缓冲区，如果缓冲区中有数据，那么就读取，否则函数会被阻塞，直到网络上有数据到来。
  2. 如果要读取的数据长度小于缓冲区中的数据长度，那么就不能一次性将缓冲区中的所有数据读出，剩余数据将不断积压，直到有` read()/recv() `函数再次读取。
  3.  直到读取到数据后 `read()/recv()` 函数才会返回，否则就一直被阻塞。MDPXBLIXRXSDXYRM

TCP协议的粘包问题（数据的无便捷性）：

​	客户端发送的多个数据包存在服务器的输入缓冲区，服务器端可能会分一次或者多次接收数据，这叫数据的粘包，也叫数据的无边界性。