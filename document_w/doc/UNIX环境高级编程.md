## 一 UNIX基础知识

**内核**：控制计算机硬件资源，提供程序运行环境，内核的接口称为系统调用

**登录名**：`cat /etc/passed`：登录名、加密口令、数值用户ID、数值组ID、注释字段、其实目录，shell程序

**shell**：命令解释器，读取用户输入，然后执行命令（`/bin/sh、/bin/bash`)

**文件系统**：UNIX文件系统是目录和文件组成的一种等次结构

- 目录的起点称为根，记作`/`
- 目录是一个包含许多目录项的文件，一个目录项包含文件名和说明文件属性的信息
- 文件名：目录的各个名字成为文件名，`./`表示当前目录，`../`表示上一目录

**输入和输出**：

- 文件描述符：非负整数，内核用它标识一个特定进程正在访问的文件
- 标准输入、输出和出错：所有的shell都为其打开三个文件描述符（标准输入、标准输出和标准出错）
- 不用缓冲的I/O：函数`open、read、write、lseek、close`都提供了不用缓冲的I/O
- 标准I/O：不用担心缓冲区大小，简化对输入行的处理

**程序和进程**：

- 程序：存放在磁盘上、处于某个目录中的一个可执行文件
- 进程和进程ID：程序的执行实例称为进程，UNIX系统确保每个进程都有一个唯一的数字表示符，总为非负整数`get_pid`
- 进程控制：`fork、exec、waitpid`
- 线程和线程ID：一个进程内的所有线程共享同一地址空间，文件描述符，栈以及进程相关的属性

**出错处理**：UNIX函数出错时，常返回一个负值，整型变量`errno`被设置为含附加信息的一个值

**用户标识**：

- 用户ID：向系统标识不同的用户，为0标识**根(root)**或**超级用户**
- 组ID：系统管理员在指定用户登录名时分配，允许同组各成员共享资源（`/etc/group`）

**信号**：通知进程已发生某种情况的一种技术，进程三种处理方式

- 忽略该信号
- 按系统默认方式处理
- 提供一个函数，信号发生时调用该函数

**时间值**：日历时间(time_t)和进程时间(clock_t)

- 时钟时间：进程运行的时间总量
- 用户CPU时间：执行用户指令所用的时间
- 系统CPU时间：为该进程执行内核程序所经历的时间

**系统调用和库函数**：内核提供服务的接口

## 二 文件与I/O

可用的文件I/O函数（打开文件、读文件、写文件等）：`open、read、write、lseek、close`

### 2.1 文件描述符

对内核而言，所有的文件都通过文件描述符引用，文件描述符是一个非负整数。

当打开一个现有文件或者创建一个新文件，内核向进程返回一个文件描述符。

文件描述符 0 关联进程的标准输入、文件描述符 1 关联标准输出、文件描述符 2 关联标准出错输出。

### 2.2 相关函数

**`open`函数**：打开或者创建一个文件

```shell
/* pathname: 打开或者创建文件的名字 */
/* flag: 说明此函数的多个选项 只读(O_RDONLY)、只写(O_WRONLY)、读写(O_RDWR) */
/* ...: 余下的参数数量及其类型根据具体调用会有所不同 */
/* 返回文件描述符，一定是最小的未用描述符数值 */
#include <fcntl.h>
int open(const char *pathname, int flag, ...)
```

**`creat`函数**：创建一个新文件

```shell
/* 返回值：若成功则返回只写打开的文件描述符，出错返回 -1 */
/* 等效于open(pathname, O_WRONLY | OCREAT | O_TRUNC, mode) */
#include <fcntl.h>
int creat(const char *pathname, mode_t mode);
```

**`close`函数**：关闭一个已打开的文件

```shell
/* 返回值：若成功返回 0，若出错返回 -1 */
/* 关闭一个文件还会释放该进程加在该文件上的所有记录锁 */
#include <unistd.h>
int close(int filedes);
```

**`lseek`函数**：显示地为一个打开的文件设置其偏移量

```Shell
/* 每个打开的文件都有一个相关联的当前文件偏移量，读写操作都是从当前文件偏移量开始的 */
/* 返回值：成功返回新的文件偏移量，出错返回 -1 */
/* 文件偏移量可大于文件当前长度，大于的部分形成空洞，空洞不占用存储区 */
#include <unistd.h>
off_t lseek(int filedes, off_t offset, int whence);
```

**`read`函数**：从打开的文件中读取数据

```shell
/* 返回值：若成功则返回读到的字节数，若到文件尾则返回 0，出错返回 -1 */
#include <unistd.h>
ssize_t read(int filedes, void *buf, size_t nbytes);
```

**`write`函数**：向已打开的文件写数据

```shell
/* 返回值：若成功则返回已写的字节数，若出错则返回 -1 */
/* 写文件在通常情况下从文件的当前偏移量处开始 */
#include <unistd.h>
ssize_t write(int filedes, cosnt void *buf, size_t nbytes);
```

### 2.3 文件共享

**表示已打开的文件的三种数据结构**：

1. 每个进程在进程表中都有一个记录项，记录项中包含一张打开文件描述符表（文件描述符标志、指向一个文件表项的指针）
2. 内核为所有打开文件维持一张文件表（文件状态标志、当前文件偏移量、指向该文件V节点表项的指针）
3. 每个打开文件都有一个V节点结构（文件类型和对此文件进行各种操作的函数的指针）

### 2.4 原子操作

一般而言，原子操作是指由多步组成的操作，要么执行完所有操作，要么一步也不执行。

**添写至一个文件**：打开文件时设置`O_APPEND`标志。使得内核每次对这种文件进行写之前，都将进程的当前偏移量设置到文件的尾端处。

**`pread`和`pwrite`函数**：允许原子性地定位搜索和执行I/O。

```shell
#include <unistd>
/* 返回读到的字节数 */
ssize_t pread(int filedes, void *buf, size_t nbytes, off_t offset);
/* 成功返回已写的字节数 */
ssize_t pwrite(int filedes, const void *buf, size_t nbytes, off_t offset);
```

- 调用`pread`相当于顺序调用`lseek`和`read`，但是调用`pread`时无法中断其定位和读操作；不更新文件指针
- 调用`pwrite`相当于顺序调用`lseek`和`write`

**创建一个文件**：检查该文件是否存在和创建该文件作为一个原子操作执行

### 2.5 `dup`和`dup2`函数

**用来复制一个现存的文件描述符**

```shell
/* 两函数的返回值：成功返回新的文件描述符，失败返回 -1 */
/* 由dup返回的一定是可用文件描述符中的最小值，dup2可用filedes执行新描述符的数值 */
/* 返回的新文件描述符与参数filedes共享同一个文件表项（文件状态标志） */
#include <unistd.h>
int dup(int filedes);
int dup2(int filedes, int filedes2);
```

### 2.6 sync、fsync和fdstasync函数

UNIX中大多数磁盘 I/O 都通过缓冲进行，将数据写入文件时，内核通常先将数据复制到其中一个缓冲区，然后再根据缓冲区情况决定是否排入输出队列，待其到达队首时进行实际的 I/O 操作。

**为保证磁盘上实际文件系统和缓冲区高速缓存中内容的一致性**

```shell
#include <unistd.h>
/* 返回值：成功返回 0，出错返回 -1 */
int fsync(int filedes);
int fdatasync(int filedes);

void sync(void);
```

- `sync`函数将所有修改过的块缓冲区排入写队列，然后就返回，并不等待实际写磁盘结束。通常`update`的系统守护进程会周期性地调用`sync`函数
- `fsync`只对由文件描述符`filedes`指定的单一文件起作用，并且等待写磁盘操作结束，然后返回
- `fdatasync`只影响文件的数据部分，`fsync`会同步更新文件的属性

### 2.7 `fcntl`函数

**改变已打开文件的性质，可以重新设置读、写、追加、阻塞等标识**

```shell
#include <fcntl.h>
int fcntl(int filedes, int cmd, .../* int arg */);
#返回值：成功则依赖于cmd，出错返回 -1
```

`fcntl`函数的5种功能

- 复制一个现有的文件描述符（cmd = F_DUPFD)
- 获得/设置文件描述符标记（cmd = F_GETFD 或 F_SETFD）
- 获得/设置文件状态标志（cmd = F_GETFL 或 F_SETFL)
- 获得/设置异步 I/O 所有权(cmd = F_GETOWN 或 F_SETOWN)
- 获得/设置记录锁（cmd = F_GETTLK、 F_SETTLK 或 F_SETLKW）

### 2.8 `ioctl`函数

`ioctl`函数是 I/O 操作的杂物箱，向设备发控制和配置命令

```shell
/* 返回值：出错返回 -1，成功返回其他值，依据request返回 */
int ioctl(int filedes, int request, ...);
```

每个设备驱动程序都可以定义自己专用的一组`ioctl`命令

| 类别       | 常量名 | 头文件              | ioctl数 |
| ---------- | ------ | ------------------- | ------- |
| 盘标号     | DIOxxx | `<sys/disklabel.h>` | 6       |
| 文件 I/O   | FIOxxx | `<sys/filio.h>`     | 9       |
| 磁带 I/O   | MTIxxx | `<sys/mtio.h>`      | 11      |
| 套接字 I/O | SIOxxx | `<sys/sockio.h>`    | 60      |
| 终端 I/O   | TIOxxx | `sys/ttycom.h>`     | 44      |

### 2.9 `/dev/fd`

较新的系统都提供名为`/dev/fd`的目录，其目录项是名为0，1,2等的文件，打开文件`/dev/fd/n`等效于赋值描述符n

调用格式如下：

```shell
`fd = open("/dev/fd/0",mode)` = `fd = dup(0)`
```

`/dev/fd`文件主要由`shell`使用，它允许使用路径名作为调用参数的程序，能用处理其他路径名的相同方式处理标准输入和输出

## 三 文件和目录

### 3.1 `stat、fstat和lstat`函数

```shell
/* 返回值：成功返回0，出错返回 -1 */
# include <sys/stat.h>
int stat(const char *restrict pathname, struct stat *restrict buf);
int fstat(int filedes, struct stat *buf);
int lstat(const char *restrict pathname, struct stat *restrict buf);
```

- `stat`返回与此命名文件有关的信息结构
- `fstat`获取描述符filedes上打开的文件的有关信息
- `lstat`类似于`stat`，当命名的文件是一个符号链接时，`lstat`返回该符号链接的有关信息

### 3.2 文件类型

- 普通文件：包含某种形式的数据
- 目录文件：包含了其他文件的名字以及指向与这些文件有关信息的指针
- 块特殊文件：提供对设备（如磁盘）带缓冲的访问，每次访问以固定长度为单位进行
- 字符特殊文件：对设备提供不带缓冲的访问，每次访问长度可变
- FIFO：用于进程间通信，有时也将其命名为管道
- 套接字：用于进程间的网络通信
- 符号链接：指向另一个文件

### 3.3 设置用户 ID 和 设置 组 ID

- 实际用户 ID 和实际组 ID：标识我们实际是谁，取自口令文件中的登录项
- 有效用户 ID、有效组 ID 和附加组 ID：决定文件的访问权限
- 保存的设置用户 ID 和保存的设置组 ID 在执行一个程序时包含有效用户 ID 和 有效组 ID 的副本

有效用户 ID 等于 实际用户 ID，有效组 ID 等于实际组 ID

### 3.4 文件访问权限

一个文件的访问权限信息如下，共分为9个访问权限位：

![](/home/winston/文档记录/工作准备/image/文件权限.png)

在`Linux`中第一个字符代表这个文件是目录(d)、文件(-)、或链接文件(l)等等；

在接下来的字符中，以三个为一组，且均为`rwx`的三个参数的组合，其中`r`代表可读(read)、`w`代表可写(write)、`x`代表可执行(execute)；

从第二个字符开始，三个字符为一组，分别表示，档案拥有者权限、同群组权限、其他非本群组权限。

**`access`函数**：按实际用户 ID 和实际组 ID 进行访问权限测试

```;shell
#include <unistd.h>
int access(const char *pathname, int mode)
/* mode 为 R_OK 测试读权限 */
/* mode 为 W_OK 测试写权限 */
/* mode 为 X_OK 测试执行权限 */
/* mode 为 F_OK 测试文件是否存在 */
```

**`umask`函数**：为进程设置文件模式创建屏蔽字，并返回以前的值

```shell
#include <sys/stat.h>
mode_t umask(mode_t cmask);
```

**`chgrp` 函数**：更改档案所属群组 

```shell
chgrp [-R] 档案名或目录名
```

**`chown`**函数：更改文件的用户 ID 和 组 ID

```shell
chown [-R] 账号名称 档案名或目录名
chown [-R] 账号名称：群组名 档案名或目录名
```

**`chmod`函数**:更改现有文件的访问权限

```shell
chmod [-R] xxx 档案名或目录 
# xxx表示数字类型的权限属性 rwx = 421
```

### 3.5 文件系统

**文件长度**：以字节为单位的文件长度，只对普通文件、目录文件和符号链接有意义

**文件空洞**：由于所设置的偏移量超过文件尾端，并写了某些数据后造成的

**文件截断**：在文件尾端处截去一些数据以缩短文件，利用`truncate`函数

把一个磁盘分为一个或多个文件，每个分区包含一个文件系统：

![](/home/winston/文档记录/工作准备/image/文件系统.png)

- 每个 i 节点都有一个链接计数，其值指向该 i 节点的目录项数，只有当其为 0 时，才可删除该文件释放数据块
- 符号链接包含了该符号链接所指向的文件的名字
- i 节点包含了大多数与文件有关的信息：文件类型、文件访问权限位、文件长度和指向该文件所占用的数据块的指针等

**`link`函数**：创建一个指向现有文件的链接

```shell
/* 成功返回0，出错返回 -1 */
int link(const char *existingpath, const char *newpath);
```

**`unlink`函数**：删除一个现有的目录项，并将所引用文件的链接计数减 1

```shell
/* 成功返回 0，出错返回 -1 */
/* 只有文件的链接计数为0时，才可以删除文件内容 */
int unlink(const char *pathname);
```

**`remove`函数**：解除对一个文件或目录的链接

```shell
/* 成功返回 0，出错返回 -1 */
int remove(const char *pathname);
```

**`rename`函数**：给文件或者目录更名

```shell
/* 成功返回 0，出错返回 -1 */
int remove(const char *oldname, const char *newname);
```

### 3.6 符号链接

符号链接是指向一个文件的间接指针，一般用于将一个文件或整个目录结构移到系统的另一个位置

open函数会跟随符号链接到连接的文件

而硬链接直接指向文件的 i 节点

- 硬链接要求链接和文件处于同一文件系统中
- 只有超级用户才能创建指向目录的硬链接

**`symlink`函数**：创建一个符号链接

```shell
int symlink(const char *actualpath, const char *sympath);
```

**`readlink`函数**：打开链接本身，不会跟随链接

```shell
ssize_t readlink(const char* restrict pathname, char *restrict buf, size_t bufsize);
# 此函数结合了open、read和close的所有操作
# 返回值：成功返回读入buf的字节数
```

### 3.7 文件的时间

每个文件保持有三个时间字段：

`st_atime`：文件数据的最后访问时间

`st_mtime`：文件数据的最后修改时间

`st_ctime`：i 节点状态的最后修改时间

**`utime`函数**：更改一个文件的访问和修改时间

```shell
/* 返回值：成功返回 0，出错返回 -1 */
#include <utime.h>
int utime(const char *pathname, const struct utimbuf *times)

# 若times为空指针，访问时间和修改时间设置为当前时间
# 若times为非空指针，访问时间和修改时间设置为times所指向的结构中的值
```

### 3.8 mkdir和rmdir函数

用 mkdir 函数创建目录，用 rmdir 函数删除目录

```shell
/* 成功返回 0，出错返回 -1 */
/* 创建的文件访问权限 mode 由进程的文件模式创建屏蔽字修改 */
#include <sys/stat.h>
int mkdir(const char *pathname, mode_t mode);
```

```shell
/* 成功返回 0，出错返回 -1 */
/* 删除一个空目录，空目录只包含 . 和 .. 这两项的目录 */
#include <unistd.h>
int rmdir(const char *pathname);
```

如果调用`rmdir`使目录的链接计数成为 0，并且也没有其他进程打开目录，则释放此目录占用的空间

### 3.9 VFS（虚拟文件系统）

Linux内核在各种不同的文件系统格式之上做了一个抽象层，使得文件、目录、读写访问等概念成为抽象层的概念，因此各种文件系统看起来用起来都一样，这个抽象层称为虚拟文件系统（VFS， Virtual Filesystem） 。

已打开的文件在内核中用file结构体表示，文件描述符表中的指针指向file结构体。

每个file结构体都指向一个file_operations结构体，这个结构体的成员都是函数指针，指向实现各种文件操作的内核函数。

每个file结构体都有一个指向dentry结构体的指针， “dentry”是directory entry（目录项）的缩写。

每个dentry结构体都有一个指针指向inode结构体。 inode结构体保存着从磁盘inode读上来的信息。

inode结构体有一个指向super_block结构体的指针。 super_block结构体保存着从磁盘分区的超级块读上来的信息，例如文件系统类型、块大小等。

## 四 标准 I/O 库

### 4.1 流和 FILE 对象

前面的 I/O 函数都是针对描述文件描述符的。对于标准 I/O 库，它们的操作是围绕流(stream)进行的。当用标准 I/O 库打开或者创建一个文件时，就使得一个流与一个文件相关联。

**流的定向**：

- 决定了所读、写的字符是单字节还是多字节的
- 标准 I/O 文件流可用单字节或多字节(宽)字符集
- 最初创建一个流时，没有定向，在后续的调用中决定是字节定向还是宽定向
- `fopen`函数清楚一个流的定向，`fwide`函数设置流的定向

当打开一个流时，标准 I/O 函数返回一个指向 FILE 对象的指针，包含：用于实际 I/O 的文件描述符、指向用于该留缓冲区的指针、缓冲区的长度、当前在缓冲区中的字符数以及出错标志等

### 4.2 标准输入、标准输出和标准出错

这三个流是一个进程预定义的，可以自动地被进程使用，这些流可与文件描述符`STDIN_FILENO、STDOUT_FILENO、STDERR_FILENO`所引用的文件相同

这三个标准 I/O 流通过预定义文件指针`stdin、stdout和stderr`加以引用，定义在`<stdio.h>`中

### 4.3 缓冲

标准 I/O 库提供缓冲的目的是尽可能减少使用`read`和`write`调用的次数。标准 I/O 提供三种类型的缓冲：

1. 全缓冲：在填满标准 I/O 缓冲区后才能进行实际 I/O 操作
2. 行缓冲：在输入和输出中遇到换行符时，标准 I/O 库执行操作
3. 不带缓冲：标准 I/O 库不对字符进行缓冲存储

很多系统默认标准出错是不带缓冲的。

**冲洗**：标准 I/O 缓冲区的写操作

```shell
/* 使该流所有未写的数据都被传送至内核 */
/* 返回值：成功返回 0，出错返回 EOF */
#include <stdio.h>
int fflush(FILE *fp);
```

### 4.4 关于流的操作

**打开流**

```shell
/* 打开一个标准 I/O 流 */
/* 返回值：成功返回文件指针，出错返回NULL */
/* restrict 关键字限定两个指针不会指向同一个数据 */
#include <stdio.h>
FILE *fopen(const char *restrict pathname, const char *restrict type);
FILE *freopen(const char *restrict pathname, const char *restrict type, FILE *restrict fp);
FILE *fdopen(int filedes, const char *type);

/* 关闭一个打开的流 */
/* 在文件被关闭之前，冲洗缓冲区的输出数据 */
int fclose(FILE *fp);
```

- `fopen`打开一个指定的文件
- `freopen`在一个指定的流上打开一个指定的文件
- `fdopen`获取一个现有的文件描述符，并将一个标准的 I/O 流与该描述符相结合

**读和写流**

```shell
/* 输入函数 */
/* 一次读一个字符 */
/* 返回值：成功返回下一个字符，出错或到达文件结尾返回 EOF */
#include <stdio.h>
int getc(FILE *fp);
int fgetc(FILE *fp);
int getchar(void);

/* 输出函数 */
/* 返回值：成功返回 c，出错返回 EOF */
int putc(int c, FILE *fp);
int fputc(int c, FILE *fp);
int putchar(int c);
```

**每次一行 I/O **

```shell
/* 提供每次输入一行的功能 */
/* 成功则返回 buf，到达文件结尾或出错返回 NULL */
#include <stdio.h>
char *fgets(char *restrict buf, int n, FILE *restrict fp);    /* 从指定流读 */
char *gets(char *buf);			/* 从标准输入读 */

/* 提供每次输出一行的功能 */
/* 返回值：成功返回非负值，出错返回 EOF */
int fputs(const char *restrict str, FILE *restrict fp);
int puts(const char *str);
```

**二进制 I/O **

```shell
/* 执行二进制 I/O 操作 */
/* 返回值：返回读或写的对象数 */
/* 用于读或写一个二进制数组或一个结构 */
/* size 为数组元素的长度或者结构的长度，nobj 为欲写的元素数或对象数 */
#include <stdio.h>
size_t fread(void *restrict ptr, size_t size, size_t nobj, FILE *restrict fp)；
size_t fwrite(cosnt void *restrict ptr, size_t size, size_t nobj, FILE *restrict fp);
```

​                                                                                                                                                                                                                                                                                                          **定位流**

- `ftell`和`fseek`函数
- `ftello`和`fseeko`函数
- `fgetpos`和`fsetpos`函数

**格式化 I/O**

- 格式化输出（`printf`、`fprintf`、`sprintf`、`snprintf`）
- 格式化输入（`scanf`、`fscanf`、`sscanf`）

## 五 进程环境

**main 函数**：`int main(int argc, char *argv[])`

### 5.1 进程终止

8 种方式使进程终止，5 种为正常终止：

- 从` main `函数返回
- 调用` exit`
- 调用` _exit `或` _Exit`
- 最后一个线程从启动例程返回
- 最后一个线程调用 `pthread_exit`

异常终止有 3 种方式：

- 调用 `abort`
- 接到一个信号并终止
- 最后一个线程对取消请求做出响应

**`exit`函数**：有三个函数用于正常终止一个程序，`_exit`和`_Exit`立即进入内核，`exit`则先执行一些清理处理，然后进入内核，三个函数都带有一个整型参数，称之为终止状态（退出状态）

**`atexit`函数**：一个进程可以登记多达 32 个函数，这些函数由 `exit`自动调用，称这些函数为终止处理程序，并调用`atexit`函数登记这些函数，登记的顺序和`exit`调用函数的顺序相反

### 5.2 C程序的存储空间布局

- 正文段：代码段，由 CPU 执行的机器指令部分，可共享并且只读
- 初始化数据段：包含程序中需明确赋初值的变量
- 非初始化数据段：又称 bss 段，在程序执行开始之前，程序员未给该变量赋初值，内核将此段初始化为 0 或空指针
- 栈：自动变量以及每次调用时所需保存的信息都存放在此段中，新被调用的函数在栈上为其自动和临时变量分配存储空间，可实现递归调用
- 堆：通常在堆中进行动态存储分配，由`malloc`分配和`free`释放

>C++存储空间布局
>
>- 堆：由`new`动态分配内存，由`delete`释放空间
>- 栈：在函数内部局部变量都可以在栈上创建，函数执行完后，局部变量自动释放
>- 自由存储区：由`malloc`分配的内存，由`free`释放
>- 全局/静态存储区：全局变量和静态变量
>- 常量存储区：存放常量不允许修改

**共享库**：用动态链接方法将程序与共享库函数相链接，减少每个可执行文件的长度，可用新版本代替老版本，但增加了一些运行时间开销

### 5.3 存储器分配

- `malloc`：分配指定字节数的存储区，初始值不确定
- `calloc`：为指定数量和指定长度的对象分配存储空间，meiy8iwei都初始化为 0
- `realloc`：更改以前分配区的长度

这三个分配函数锁返回的指针一定是适当对齐的，使其可以用于任何数据对象，都返回通用指针 `void*`

函数`free`释放对应的存储空间

大多数分配的存储空间比要求的要大一些，额外的空间用来记录管理信息（分配块的长度，指向下一个分配块的指针）

**内存泄漏**：一个进程调用`malloc`函数，但忘记调用`free`函数，导致该进程占用的存储器会持续增加

### 5.4 环境变量

环境变量是系统运行时所需的一些参数，或运行应用程序，或运行系统程序，多需要相应的参数。

环境字符串的形式通常如下：`name=value`

内核并不查看这些字符串，解释完全取决于各个应用程序，可用`getenv`函数获取环境变量值，用`setenv`来设置环境变量

**环境表**：指向实际`name=value`字符串的指针数组

每个进程都有一个非负整型表示的唯一进程 

ID 为 0 的进程为调度进程，常常被称为交换进程(系统进程，不执行任何磁盘上的程序)

进程 ID 为 1 的是`init`进程，在自举过程结束时由内核调用，`init`通常读与系统有关的初始化文件，并将系统引导到一个状态

### 5.5 相关操作函数

**`fork`函数**：一个现有进程可以调用`fork`函数创建一个新进程

- `fork`函数创建的进程称为子进程
- `fork`函数调用一次，返回两次，子进程返回 0，父进程返回新子进程的进程 ID
- 子进程获得父进程数据空间、堆和栈的副本
- `fork`函数后一般跟随`exec`函数

在`fork`之后处理文件描述符：

- 父进程等待子进程完成，父进程无须对其描述符做任何处理
- 父、子进程各自执行不同的程序段，在`fork`之后都要关闭各自不需要使用的文件描述符

`fork`由下面两种用法：

- 一个父进程希望复制自己，使父、子进程同时执行不同的代码段
- 一个进程要执行一个不同的程序

**vfork函数**：用于创建一个新进程，该新进程的目的是`exec`一个新程序

`vfork`保证子进程先运行，在它调用`exec`或`exit`之后父进程才能被调度运行

**exit函数**：通过将其退出状态作为参数传递给函数(exit, _exit)

**wait 和 waitpid函数**：等待接受一个终止的子进程，并做相应处理

>调用 wait 和waitpid可能会发生的情况
>
>-  如果其所有子进程还在运行，则阻塞
>- 如果一个子进程已终止，正在等待父进程获取终止状态，则取得该子进程的终止状态后立即返回
>- 如果没有任何子进程，则立即出错返回
>
>wait 和 waitpid 的区别：
>
>- 在一个子进程终止前，wait 使其调用者阻塞，而 waitpid 有一个选项，可是调用者不阻塞
>- waitpid 并不等待在其调用之后第一个终止子进程，它有其它选项可以控制它所等待的进程

**waitid 函数**：取进程终止状态，允许一个进程指定要等待的子进程

**exec函数**：当进程调用一种`exec`函数时，该进程执行的程序完全替换为新程序。

### 5.6 解释器文件

解释器文件是文本文件，起始行的形式是：

`#! pathname [optional-argument]`

如：`#! /bin/sh`

`pathname`通常是绝对路径名，识别是由内核为`exec`系统调用处理的一部分来完成的

**exec执行解释器文件**：当执行`exec`"解释器"文件时，`exec`系统调用会识别这种文件，内核使调用`exec`函数的进程实际执行的并不是该"解释器文件",而是`pathname`指定的解释器

- `pathname`作为传递给解释器的第一个参数
- 解释器文件中`pathname`后的可选参数如果存在作为第二个参数
- 解释器文件名称作为第三个参数
- exec程序出入的第二个参数作为传入解释器的第四个参数

**命令行执行解释器文件**：

- 通过执行解释且文件执行解释器，传递给解释器的第一个参数是解释器文件的`pathname`
- ``pathname`后的可选参数如果存在作为第二个参数传递给解释器
- 解释器文件名称会作为下一个参数传递给解释器

**解释器**：解释器文件第一行中`pathname`指定的程序，

## 六 调试

调试的方法：

1. 在程序中打印语句，优点是能显示程序的动态过程，容易检查源程序的有关信息；但是效率低，可能输入大量无关数据
2. 获取有关文件系统支持，可用内存，CPU，运行程序的内核状态等信息 - 查询 /proc 文件系统
3. 最初的问题诊断，系统调用或库调用的相关问题，了解程序流程 – strace / ltrace
4. 应用程序内存空间的问题 – valgrind
5. 检查应用程序运行时的行为，分析应用程序崩溃 – gdb

### 6.1 strace

Linux系统的架构如下图所示：

![](..\image\Linux系统架构.png)

>从宏观上来讲，Linux操作系统的体系架构分为用户态和内核态（用户空间和内核空间）
>
>1. Linux内核：从技术层面讲，内核是硬件和软件之间的一个中间层，作用是将应用层程序的请求传递给硬件，并充当底层驱动程序，对系统中的各种设备和组件进行寻址；本质上内核可以看做一种控制计算机的硬件资源的软件，并提供上层应用程序运行的环境（驱动）；由微内核和宏内核之分。
>
>2. 用户空间。用户态即上层应用程序的活动空间，应用程序的执行必须依托于内核提供的资源，包括CPU资源、存储资源、I/O资源等。
>
>3. **运行在用户态下的程序不能直接访问操作系统内核空间的数据结构和程序**，两者最大区别在于特权级不同，也就是权力的不同。（特权级是一种有效管理和控制程序执行的手段，在硬件上会对特权级作出相应支持）
>
>4. 一般而言程序都是运行在用户态下的，在其需要操作系统帮助完成某些它没有权力和能力完成的工作时就会切换到内核态，在三种情况下可以切换到内核态：系统调用，异常，外围设备的中断。
>   - 系统调用：为了能使上层应用访问到依托于内核提供的资源，内核为上层应用提供访问的接口：系统调用。系统调用是操作系统的最小功能单位。是用户态进程主动要求切换到内核态的一种方式，通过系统调用申请使用操作系统提供的服务程序完成工作。
>   - 用户态程序在执行时发生事先不可知的异常，就会切换到内核中处理该异常的相关程序中，如缺页异常
>   - 外围设备完成用户请求的操作时，会向CPU发出相应中断信号，CPU会停止当前执行指令去处理中断处理程序。

**系统调用**：

- 应用程序不能直接访问Linux内核，但可以跳转到`system_call`的内核位置，内核会检查系统调用号，查看系统调用表找到所调用的内核函数入口地址，调用该函数后返回到应用程序；
- 系统调用不直接返回错误码，而是将错误码放入一个名为errno的全局变量中。

#### 6.1.1 strace介绍

`strace`常用来跟踪进程执行时的系统调用和接受的信号，可以跟踪到一个进程产生的系统调用，包括参数、返回值、执行消耗的时间。

对于一个简单的程序`text.cpp`

```shell
#include <iostream>
using namespace std;

int main()
{
	int a;
	cin >> a;
	cout << a << endl;
	
	return 0;
}
```

用`strace`调用执行后的结果如下：

```shell
winston@Winstonly-Ly:/media/winston/本地磁盘/Job/TestProject/Debug$ strace ./test
execve("./test", ["./test"], [/* 70 vars */]) = 0
brk(NULL)                               = 0xd19000
access("/etc/ld.so.nohwcap", F_OK)      = -1 ENOENT (No such file or directory)
access("/etc/ld.so.preload", R_OK)      = -1 ENOENT (No such file or directory)
open("/etc/ld.so.cache", O_RDONLY|O_CLOEXEC) = 3
fstat(3, {st_mode=S_IFREG|0644, st_size=111759, ...}) = 0
mmap(NULL, 111759, PROT_READ, MAP_PRIVATE, 3, 0) = 0x7f339a9ab000
close(3)                                = 0
access("/etc/ld.so.nohwcap", F_OK)      = -1 ENOENT (No such file or directory)
open("/usr/lib/x86_64-linux-gnu/libstdc++.so.6", O_RDONLY|O_CLOEXEC) = 3
read(3, "\177ELF\2\1\1\3\0\0\0\0\0\0\0\0\3\0>\0\1\0\0\0 \235\10\0\0\0\0\0"..., 832) = 832
fstat(3, {st_mode=S_IFREG|0644, st_size=1566440, ...}) = 0
mmap(NULL, 4096, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0) = 0x7f339a9aa000
mmap(NULL, 3675136, PROT_READ|PROT_EXEC, MAP_PRIVATE|MAP_DENYWRITE, 3, 0) = 0x7f339a420000
mprotect(0x7f339a592000, 2097152, PROT_NONE) = 0
mmap(0x7f339a792000, 49152, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x172000) = 0x7f339a792000
mmap(0x7f339a79e000, 13312, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_FIXED|MAP_ANONYMOUS, -1, 0) = 0x7f339a79e000
close(3)                                = 0
access("/etc/ld.so.nohwcap", F_OK)      = -1 ENOENT (No such file or directory)
open("/lib/x86_64-linux-gnu/libc.so.6", O_RDONLY|O_CLOEXEC) = 3
read(3, "\177ELF\2\1\1\3\0\0\0\0\0\0\0\0\3\0>\0\1\0\0\0P\t\2\0\0\0\0\0"..., 832) = 832
fstat(3, {st_mode=S_IFREG|0755, st_size=1868984, ...}) = 0
mmap(NULL, 3971488, PROT_READ|PROT_EXEC, MAP_PRIVATE|MAP_DENYWRITE, 3, 0) = 0x7f339a056000
mprotect(0x7f339a216000, 2097152, PROT_NONE) = 0
mmap(0x7f339a416000, 24576, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x1c0000) = 0x7f339a416000
mmap(0x7f339a41c000, 14752, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_FIXED|MAP_ANONYMOUS, -1, 0) = 0x7f339a41c000
close(3)                                = 0
access("/etc/ld.so.nohwcap", F_OK)      = -1 ENOENT (No such file or directory)
open("/lib/x86_64-linux-gnu/libm.so.6", O_RDONLY|O_CLOEXEC) = 3
read(3, "\177ELF\2\1\1\3\0\0\0\0\0\0\0\0\3\0>\0\1\0\0\0\0V\0\0\0\0\0\0"..., 832) = 832
fstat(3, {st_mode=S_IFREG|0644, st_size=1088952, ...}) = 0
mmap(NULL, 3178744, PROT_READ|PROT_EXEC, MAP_PRIVATE|MAP_DENYWRITE, 3, 0) = 0x7f3399d4d000
mprotect(0x7f3399e55000, 2093056, PROT_NONE) = 0
mmap(0x7f339a054000, 8192, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x107000) = 0x7f339a054000
close(3)                                = 0
access("/etc/ld.so.nohwcap", F_OK)      = -1 ENOENT (No such file or directory)
open("/lib/x86_64-linux-gnu/libgcc_s.so.1", O_RDONLY|O_CLOEXEC) = 3
read(3, "\177ELF\2\1\1\0\0\0\0\0\0\0\0\0\3\0>\0\1\0\0\0p*\0\0\0\0\0\0"..., 832) = 832
fstat(3, {st_mode=S_IFREG|0644, st_size=89696, ...}) = 0
mmap(NULL, 4096, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0) = 0x7f339a9a9000
mmap(NULL, 2185488, PROT_READ|PROT_EXEC, MAP_PRIVATE|MAP_DENYWRITE, 3, 0) = 0x7f3399b37000
mprotect(0x7f3399b4d000, 2093056, PROT_NONE) = 0
mmap(0x7f3399d4c000, 4096, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x15000) = 0x7f3399d4c000
close(3)                                = 0
mmap(NULL, 4096, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0) = 0x7f339a9a8000
mmap(NULL, 8192, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0) = 0x7f339a9a6000
arch_prctl(ARCH_SET_FS, 0x7f339a9a6740) = 0
mprotect(0x7f339a416000, 16384, PROT_READ) = 0
mprotect(0x7f339a054000, 4096, PROT_READ) = 0
mmap(NULL, 4096, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0) = 0x7f339a9a5000
mprotect(0x7f339a792000, 40960, PROT_READ) = 0
mprotect(0x600000, 4096, PROT_READ)     = 0
mprotect(0x7f339a9c7000, 4096, PROT_READ) = 0
munmap(0x7f339a9ab000, 111759)          = 0
brk(NULL)                               = 0xd19000
brk(0xd4b000)                           = 0xd4b000
fstat(0, {st_mode=S_IFCHR|0620, st_rdev=makedev(136, 2), ...}) = 0
read(0, 8"8\n", 1024)                    = 2
fstat(1, {st_mode=S_IFCHR|0620, st_rdev=makedev(136, 2), ...}) = 0
write(1, "8\n", 28)                      = 2
lseek(0, -1, SEEK_CUR)                  = -1 ESPIPE (Illegal seek)
exit_group(0)                           = ?
+++ exited with 0 +++
```

对于命令行下执行的程序 ， execve （或 exec 系列调用中的某一个）均为 strace 输出系统调用中的第一个 

打印出来的每一行都是一次系统调用，等号左边是系统调用的函数名和参数，右边是该调用的返回值，首先装载被执行程序，载入`libc`函数库，设置内存映射等初始化操作的系统调用，然后执行`read`和`write`两个系统调用。

#### 6.1.2 常用用法介绍

**用`strace`跟踪信号传递**：例如上面先执行`strace ./test`后，另开一个窗口执行`killall test`后会在执行`test`下的窗口下观察进程接收信号的情况

```shell
--- SIGTERM {si_signo=SIGTERM, si_code=SI_USER, si_pid=4061, si_uid=1000} ---
+++ killed by SIGTERM +++
```

**统计系统调用**：通过使用参数 -c ，将进程所有的系统调用做一个同一分析并返回。

```shell
winston@Winstonly-Ly:/media/winston/本地磁盘/Job/TestProject/Debug$ strace -c  ./test
8
8
% time     seconds  usecs/call     calls    errors syscall
------ ----------- ----------- --------- --------- ----------------
 26.99    0.000166          10        16           mmap
 16.75    0.000103          11         9           mprotect
 13.98    0.000086          17         5           read
  9.43    0.000058           8         7           fstat
  8.13    0.000050          10         5           open
  7.15    0.000044           9         5           close
  6.67    0.000041           7         6         6 access
  3.74    0.000023          23         1           write
  3.09    0.000019          19         1           munmap
  1.79    0.000011          11         1         1 lseek
  1.63    0.000010           3         3           brk
  0.65    0.000004           4         1           arch_prctl
  0.00    0.000000           0         1           execve
------ ----------- ----------- --------- --------- ----------------
100.00    0.000615                    61         7 total
```

**常见参数**

| -c            | 统计每一次系统调用的执行时间、次数和出错的次数等             |
| ------------- | ------------------------------------------------------------ |
| -o            | 将strace的结果输出到文件中，默认输出设备是STDERR             |
| -T            | 将每个系统调用所花费的时间打印出来                           |
| -t、-tt、-ttt | 记录每次系统调用发生的时间                                   |
| -p            | 追踪现有的进程`strace -p pid`                                |
| -d            | 输出`strace`关于标准错误的调试信息                           |
| -f            | 跟踪由`fork`调用所产生的子进程                               |
| -i            | 输出系统调用的入口指针，即每行首输出代码地址，利于GDB设置断点调试 |

其他常见参数可通过`strace -h`查看，会列出常用命令参数及使用方法。

>**strace的用途**
>
>- 用`strace`调试程序
>- `strace`解决动态依赖库
>- 限制`strace`只跟踪特定的系统调用
>
>[`strace`调试详解]https://blog.csdn.net/yangrendong/article/details/17716603

### 6.2 GDB

#### 6.2.1 gdb简介

​	`gdb`是`gcc`的调试工具，主要用于 C 和 C++ 的调试。主要应用体现：

- 启动程序，按照用户自定义要求运行程序；
- 用断点进行调试；
- 程序停住时，可以检查此时程序运行的状态；
- 动态改变程序的执行环境。

>- **Linux下GCC将单个`.cpp`文件编译成可执行文件的步骤**
>
>  1. 预编译(生成`.i`文件)
>
>     ```shell
>     // -E 让GCC早与处理结束后停止编译 
>     g++ -E hello.cpp -o hello.i
>     ```
>
>  2. 编译(生成`.s`文件)
>
>     ```shell
>     // -S 对.i文件进行语法分析,语义分析以及生成汇编代码文件 
>     g++ -S hello.i -o hello.s
>     ```
>
>  3. 汇编(生成`.o`文件)
>
>     ```shell
>     // -c 将汇编代码文件转换成中间目标文件
>     g++ -c hello.s -o hello.o
>     ```
>
>  4. 链接(生成可执行文件)
>
>     ```shell
>     // 连接器 ld 将目标文件与动态/静态链接库连接起来称为可执行文件
>     g++ hello.o -o hello
>     ```
>
>  5. 运行可执行文件
>
>     ```shell
>     ./hello
>     ```
>
>  **也可以一步实现**
>
>```shell
>g++ hello.cpp -o hello
>```
>
>- **编译多个文件**
>
>  ```shell
>  g++ hello1.cpp hello2.cpp -o hello
>  ```
>
>详细用法在终端输入`g++ -h`可查看

**为了能够使用GDB调试工具,在编译的时候要加上 `-g`选项**

>`gcc -g hello.c -o hello`
>
>`g++ -g hello.cpp -o hello`

**启动gdb的方法**

- `gdb program` : program 就是可执行文件
- `gdb program core`:用`gdb`同时调试一个程序和core文件(程序非法执行后产生的文件)
- `gdb program pid`:如果程序是一个服务程序,可以指定程序运行时的进程id

`gdb`调试的基本思想仍然是“分析现象->假设错误原因->产生新的现象去验证假设.在编译的时候加上`-g`选项就能使用`gdb`调试工具了.

加入选项 -q 不会打印版本信息

```shell
winston@Winstonly-Ly:~/TestProject$ g++ -g main.c -o main
winston@Winstonly-Ly:~/TestProject$ gdb -q ./main
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

**`-g`**选项的作用是在可执行文件中加入源代码的信息,比如可执行文件中的第几条机器指令对应源代码的第几行,但不是把整个源文件嵌入到可执行文件中.确保`gdb`能够找到相应的源文件.如果没有`-g`,将看不见函数名\变量名,所替代的全是运行时的内存地址.

`gdb`提供一个类似`Shell`的命令环境,输入`help`可以查看命令的类别.

`gdb`在提示符下直接敲回车表示重复上一条命令.

#### 6.2.2 `gdb`基本命令

| 命令              | 命令缩写 | 描述                                                         |
| :---------------- | :------: | :----------------------------------------------------------- |
| `start`           |   `st`   | 开始执行程序,停在`main`函数第一行语句前面等待命令            |
| `run`             |   `r`    | 完整运行程序或者直到运行到第一个断点停止等待命令             |
| `list(l)`         |   `l`    | 列出源代码,接着上次的为止往下列,每次列10行,可接行数或者函数名,以此为中心打印 |
| `backtrace`       |   `bt`   | 查看各级函数调用及参数(堆栈)                                 |
| `finish`          |          | 运行到当前函数返回为止,并打印函数返回时的堆栈地址和返回值及参数值等信息； |
| `frame(f) 帧编号` |          | 选择栈帧                                                     |
| `info(i) locals`  |   `i`    | 查看当前栈帧局部变量的值                                     |
| `break`           |   `b`    | 设置断点,程序运行到断点的位置会停下来                        |
| `step(s)`         |   `s`    | 执行下一行语句,如果有函数调用则进入到函数中                  |
| `next(n)`         |   `n`    | 执行下一行语句,如果有函数不会进入函数内部,直接跳过           |
| `continue`        |   `c`    | 继续程序的运行,直到遇到下一个断点或者结束                    |
| `until`           |          | 可运行程序到退出循环体,加入行号运行到某一行                  |
| `watch`           |          | 监视变量值的变化                                             |
| `print(p)`        |   `p`    | 打印表达式的值,通过表达式可以修改变量的值或者调用函数        |
| `whatis`          |          | 查看变量类型或者函数类型                                     |
| `quit(q)`         |   `q`    | 退出`gdb`调试环境                                            |
| `set var 变量=x`  |          | 修改变量的值                                                 |
| `file`            |          | 装入需要调试的程序                                           |
| `kill`            |   `k`    | 终止正在调试的程序                                           |
| `dispaly`         |  `disp`  | 跟踪查看某个变量,每次停下来都显示它的值                      |

#### 6.2.3 有关断点的操作命令

**当程序执行到某一行代码时中断**

| 命令                       | 描述                                    |
| -------------------------- | --------------------------------------- |
| `break(b) 行号`            | 在某一行设置断点                        |
| `break 函数名`             | 在某个函数开头设置断点                  |
| `break ... if ...`         | 设置条件断点,满足条件时中断             |
| `break 文件名:行号/函数名` | 对指定文件的指定行/指定函数设置断点     |
| `continue(c)`              | 从当前位置开始连续运行程序至断点处      |
| `delete breakpoints`       | 删除所有断点                            |
| `delete 断点号n`           | 删除第n个断点                           |
| `enable 断点号n`           | 启用断点n                               |
| `disable 断点号n`          | 禁用断点n                               |
| `display 变量名`           | 跟踪查看某个变量,每次停下来都显示它的值 |
| `info breakpoints/info b`  | 查看当前设置了哪些断点                  |
| `undisplay 跟踪显示号`     | 取消跟踪显示                            |
| `run(r)`                   | 从头开始连续运行程序                    |



#### 6.2.4 打印信息/显示信息

| 命令                    | 描述                                                         |
| ----------------------- | ------------------------------------------------------------ |
| `watch 表达式`          | 设置观察点,一旦被监视的表达式的值改变,将强行终止被调试的程序 |
| `awatch 表达式`         | 表达式被访问\改变时暂停运行                                  |
| `rwatch 表达式`         | 表达式被访问时暂停运行                                       |
| `print(p) 变量名s`      | 打印变量s的值                                                |
| `dispaly 表达式/变量名` | 设置之后每次单步执行后会输出x的值                            |
| `info(i) watchpoints`   | 查看当前设置了哪些观察点                                     |
| `x /NFU 内存地址`       | 打印指定内存地址中的数据,N表示打印的单元数,F表示前面的显示格式U表示每个单元大小 |

#### 6.2.5 查看栈帧信息

| 命令                             | 缩写 | 描述                                 |
| -------------------------------- | ---- | ------------------------------------ |
| `backtrace`=`where`=`info stack` | `bt` | 查看函数调用的顺序(函数调用栈的信息) |
| `frame N`                        |      | 切换到栈编号为N的上下文中            |
| `info frame`                     |      | 查看当前函数调用的栈帧信息           |
| `info registers`                 |      | 查看当前寄存器的值                   |
| `info args`                      |      | 查看当前函数参数的值                 |
| `info locals`                    |      | 查看当前局部变量的值                 |
| `info variables`                 |      | 查看程序中的变量符号                 |
| `info functions`                 |      | 查看程序中的函数符号                 |
| `where`=`bt`                     |      | 查看当前运行的堆栈列表               |
| `info program`                   |      | 查看程序是否运行,进程号,被暂停的原因 |

注：*由程序产生每个函数调用和局部变量，传递的参数，调用位置等信息一起存储在堆栈内的数据块，被称为一帧*

#### 6.2.6 分割窗口

| 命令           | 描述                             |
| -------------- | -------------------------------- |
| `layout src`   | 显式源代码窗口                   |
| `layout asm`   | 显式反汇编窗口                   |
| `layout regs`  | 显式源代码/反汇编和CPU寄存器窗口 |
| `layout split` | 显式源代码和反汇编窗口           |

更多详细的调试方法见以下链接

[linux下gdb调试方法与技巧整理]https://blog.csdn.net/niyaozuozuihao/article/details/91802994

[Linux环境下的GDB调试方法]https://blog.csdn.net/horotororensu/article/details/82256832

[gdb 调试 ncurses 全过程]https://blog.csdn.net/luguifang2011/article/details/78182689?utm_medium=distribute.pc_relevant.none-task-blog-BlogCommendFromMachineLearnPai2-2.nonecase&depth_1-utm_source=distribute.pc_relevant.none-task-blog-BlogCommendFromMachineLearnPai2-2.nonecase

#### 6.2.7 用gdb分析coredump文件

**段错误(Segmentation Fault)**

程序运行时出现段错误,`gdb`很容易定位到哪一行发生错误

> 如果某个函数的局部变量发生访问越界，有可能并不立即产生段错误，而是在函
> 数返回时产生段错误。
>
> 产生段错误的原因：
>
> - 访问不存在的地址
> - 访问系统保护的内存地址
> - 数组访问越界

段错误产生的过程：

>1. 用户程序要访问的一个VA，经过MMU检查无权访问
>
>2. MMU产生一个异常，CPU从用户模式切换到特权模式，跳转到内核代码中执行异常服务程序
>3. 内核把这个异常解释为段错误，把引发异常的进程终止掉

当程序运行的过程中异常终止或崩溃，操作系统会将程序当时的内存状态记录下来，保存在一个文件中，这种行为就叫做Core Dump（中文有的翻译成“核心转储”),除了内存信息之外,还有些关键信息会保存下来,如寄存器信息,(程序指针\栈指针),内存管理信息,其他处理器和操作系统状态和信息.

>1. core 文件开关
>
> - 使用` ulimit -c `查看core开关，如果为0表示关闭，不会生成core文件；
> - 使用 `ulimit -c [filesize] `设置core文件大小，当最小设置为4之后才会生成core文件；
> - 使用 `ulimit -c unlimited `设置core文件大小为不限制，这是常用的做法；
> - 如果需要开机就执行，则需要将这句命令写到 /etc/profile 等文件。
>
> 缺省情况下，内核在coredump时所产生的core文件放在与该程序相同的目录中，并且文件名固定为core
>
>2. core文件命名和保存路径
> - 通过修改**`/proc/sys/kernel/core_pattern`**设置core文件名和保存路径
>
>   ```shell
>   echo "/home/winston/CoreFile/core-%e-%p-%t" > /proc/sys/kernel/core_pattern
>   打印可执行文件名+进程id+时间
>   这样的方式只是暂时有效，永久设置的方法如下：
>   
>   编辑 /etc/sysctl.conf 文件
>   sudo vi /etc/sysctl.conf 
>   添加以下两行：
>   	kernel.core_uses_pid = 1
>   	kernel.core_pattern = /home/winston/CoreFile/core-%e-%p-%t
>   sudo sysctl -p
>   ```
>
>- 通过修改**`/etc/profile`**来使得关于core dump的配置永久生效
>
> ```shell
> sudo vi /etc/profile
> 在打开文件的末尾添加以下命令:
> ulimit -c unlimited
> ```
>
> **当前用户，即执行对应程序的用户具有对写人 core 目录的写权限以及有足够的空间**
>
>3. 产生coredump文件的原因
>  - 内存访问越界
>  - 多线程使用了线程不安全的函数
>  - 多线程读写的数据未加锁保护
>  - 非法指针(包括空指针和随意使用指针转换)
>  - 堆栈溢出

1. 采用命令**`gdb 可执行文件 core文件`**就可以进入gdb环境查看程序出错原因.

2. 在进入 gdb 后，查找段错误位置，使用 where 或者bt。

3. 可定位源程序中具体文件的位置出现段错误

   ```shell
   winston@Winstonly-Ly:/media/winston/本地磁盘/Job/TestProject/Debug$ ./test
   32765
   Segmentation fault (core dumped)
   
   winston@Winstonly-Ly:/media/winston/本地磁盘/Job/TestProject/Debug$ gdb -q ./test core-test-5956-1591844997
   Reading symbols from ./test...done.
   [New LWP 5956]
   Core was generated by `./test'.
   Program terminated with signal SIGSEGV, Segmentation fault.
   #0  0x00000000004009db in test () at test.cpp:41
   41	    *p1 = 1; // 非法指针  
   (gdb) where
   #0  0x00000000004009db in test () at test.cpp:41
   #1  0x0000000000400a1c in main () at test.cpp:48
   (gdb) bt
   #0  0x00000000004009db in test () at test.cpp:41
   #1  0x0000000000400a1c in main () at test.cpp:48
   (gdb) 
   ```

### 6.3 top和ps

**`top`**指令是Linux下的性能分析工具,能实时显示系统中各个进程的资源占用情况.类似于Windows下的任务管理器.

```shell
winston@Winstonly-Ly:/media/winston/本地磁盘/Job/TestProject/Debug$ top

top - 17:20:52 up  1:28,  1 user,  load average: 0.79, 0.49, 0.51
Tasks: 248 total,   2 running, 189 sleeping,   0 stopped,   0 zombie
%Cpu(s):  2.1 us,  1.2 sy,  0.0 ni, 96.1 id,  0.5 wa,  0.0 hi,  0.1 si,  0.0 st
KiB Mem :  3937204 total,   173300 free,  2581096 used,  1182808 buff/cache
KiB Swap:  7999484 total,  7916796 free,    82688 used.   491292 avail Mem 

  PID USER      PR  NI    VIRT    RES    SHR S  %CPU %MEM     TIME+ COMMAND                                                                      
 1065 root      20   0  471064  99688  71708 R   7.0  2.5   4:11.51 Xorg                                                                         
 1989 winston   20   0 1527880 147084  55244 S   5.0  3.7   4:04.03 compiz                                                                       
 4755 winston   20   0  616572  38264  28632 S   4.0  1.0   0:04.75 gnome-terminal-                                                              
 7187 winston   20   0 4941628 185664 104868 S   1.3  4.7   1:04.42 chrome                                                                       
  912 root      20   0    4396   1160   1160 S   1.0  0.0   0:10.75 acpid                                                                        
 2931 winston   20   0 3004604 375520  20656 S   1.0  9.5   6:14.78 WeChat.exe                                                                   
 2936 winston   20   0    8692   4860    764 S   0.7  0.1   2:32.73 wineserver.real                                                              
16311 winston   20   0 2964680 157812  99076 S   0.7  4.0   0:25.07 FoxitReader                                                                  
 2145 winston   20   0 3753440 116688  52848 S   0.3  3.0   0:40.74 sogou-qimpanel                                                               
 2651 winston   20   0  537012  49652  11224 S   0.3  1.3   0:08.76 plugin_host                                                                  
 5924 winston   20   0 1357476 275376 100412 S   0.3  7.0   2:15.04 chrome                                                                       
 5990 winston   20   0 4931524 189168 109092 S   0.3  4.8   0:24.10 chrome                                                                       
 6066 winston   20   0 4809028 107112  73728 S   0.3  2.7   0:18.69 chrome                                                                       
12570 winston   20   0 1031040 212432  95324 S   0.3  5.4   2:34.48 Typora                                                                       
23431 winston   20   0   48980   4172   3456 R   0.3  0.1   0:01.21 top           
```

>top 会依次打印出系统运行时间和平均负载, 任务进程, CPu状态, 内存使用情况, 各进程的状态监控
>
>**top**的使用方法:
>
>```shell
>top [-] [d] [p] [q] [c] [C] [S] [s] [n]
>参数说明：
>
>d：指定每两次屏幕信息刷新之间的时间间隔。当然用户可以使用s交互命令来改变之。
>
>p:通过指定监控进程ID来仅仅监控某个进程的状态。
>
>q:该选项将使top没有任何延迟的进行刷新。如果调用程序有超级用户权限，那么top将以尽可能高的优先级运行。
>
>S：指定累计模式。
>
>s：使top命令在安全模式中运行。这将去除交互命令所带来的潜在危险。
>
>i：使top不显示任何闲置或者僵死进程。
>
>c:显示整个命令行而不只是显示命令名。
>
>```
>
>更多交互命令见:
>
>[Linux top的命令详解]https://www.cnblogs.com/zhoug2020/p/6336453.html
>
> [Linux top的交互指令]https://www.cnblogs.com/haoxiaoyu/p/3933924.html	

**ps (process status ）**命令列出的是当前在运行的进程的快照，就是执行 ps 命令的那个时刻的那些进程，如果想要动态地显示进程信息，就可以使用 top 命令 。ps指令最常用的还是用于监控后台进程的工作情况,不和键盘屏幕等通信

> Linux上进程的5种状态和 ps 对应的5种状态码
>
> - 运行(正在运行或者运行队列中对待) ---------R
> - 中断(休眠中,受阻,在等待某个条件的形成或接收信号)-----------S
> - 不可中断(收到信号不唤醒或者不可运行,必须等待直到有中断发生)-----------D
> - 停止（进程收到 SIGSTOP, SIGSTP, SIGT肘， SIGTOU 信号后停止运行运行） --------------T
> - 僵死（进程已终止，但进程描述符存在，直到父进程调用 wait4（）系统调用后释放）--------------Z
>
> ps指令的命令格式:` ps [参数]`,常用参数如下:
>
> | 参数   | 功能                         |
> | ------ | ---------------------------- |
> | `a`    | 显示终端的所有进程           |
> | `-a`   | 显示同一终端下的所有程序     |
> | `-A`   | 显示所有进程                 |
> | `c`    | 显示进程的真实名称           |
> | `-e`   | `-e`等于`-A`                 |
> | `e`    | 显示环境变量                 |
> | `f`    | 显示程序间的关系             |
> | `-H`   | 显示树状结构                 |
> | `r`    | 显示当前终端下的进程         |
> | `T`    | 显示当前终端的所有程序       |
> | `-aux` | 显示所有包含其他使用者的行程 |
>
> 更详细的ps指令介绍参考: 
>
> [Linux ps命令详解与示例说明]https://blog.csdn.net/lsbhjshyn/article/details/18549869?utm_medium=distribute.pc_relevant.none-task-blog-BlogCommendFromMachineLearnPai2-6.nonecase&depth_1-utm_source=distribute.pc_relevant.none-task-blog-BlogCommendFromMachineLearnPai2-6.nonecase

### 6.4 Valgrind

#### 6.4.1 Valgrind概述

Valgrind是一款内存分析工具,由内核和基于内核的其他调试工具组成,其体系结构如下图:

![](D:\Job\document\image\Valgrind体系结构图.png)

Valgrind包括以下工具:

- **Memcheck**:应用最广泛的工具,重量级的内存检查器,能检查使用未初始化的内存,使用已经释放了的内存,内存访问越界等

  >主要检测下面的程序错误：
  >
  >- 使用未初始化的内存
  >- 使用已经释放了的内存
  >- 使用超过malloc分配的内存空间
  >- 对堆栈的非法访问
  >- 申请的空间是否有释放
  >- `malloc/free/new/delete`申请和释放内存的匹配
  >- ` strcpy, strncpy, memcpy, strcat, memcpy`相关函数中的`dst`和`src`指针重叠
  >
  >注：*Valgrind 不检查静态分配数组的使用情况*

- **Callgrind**:用来检查程序中函数调用过程中出现的问题

- **Cachegrind**:用来检查程序中缓存使用出现的问题

- **Helgrind**:用来检查多线程程序中出现的竞争问题

  >用来检测下面三类错误
  >
  >- POSIX pthreads API的错误使用
  >- 由加锁和解锁顺序引起的潜在的死锁‘
  >- 数据竞态--在没有锁或者同步机制下访问内存
  >
  >

- **Massif**:堆栈分析器,能测量程序在堆栈中使用的内存大小

- **Extension**:利用Core提供的功能,编写特定的内存调试工具

#### 6.4.2 Linux内存空间布局

**程序内存空间布局概述**

![](D:\Job\document\image\Linux程序内存布局.png)

>1. 代码段(`.text segment`)：通常是指用来存放程序执行代码的一块内存区域，程序运行前就已经确定
>2. 初始化数据段(`data segment`)：通常是指用来存放程序中已经初始化的全局变量的一块内存
>3. 未初始化数据段(`.bss segment`)：用来存放程序中未初始化的全局变量的一块内存区域
>4. 堆(`heap`)：用来存放进程运行中被动态分配的内存段，大小补丁，可动态扩张或缩减
>5. 栈(`stack`)：又称为堆栈，存放的局部变量（但不包括`static`声明的变量，`static`意味着在数据段中存放变量)；除此以外函数被调用时，栈用来传递参数和返回值。

**堆栈的区别**

- 申请方式不同：栈由系统自动分配；堆由程序员自己申请（`malloc、new等`）
- 申请后系统响应不同：栈只要剩余空间大于所申请空间，系统将为程序提供内存，否则将报异常提示栈溢出；堆会遍历系统中记录空闲地址的链表，寻找第一个空间中大于所申请空间的堆结点，然后删除该结点，并将结点空间分配给程序
- 申请大小的限制不同：栈是向低地址扩展的数据结构，是一块连续的内存的区域，即栈顶地址和栈最大容量预先设定好了；堆是向高地址扩展的数据结构，不连续的内存区域，因为系统用链表来存储空闲内存地址的。
- 申请效率不同：栈由系统分配，速度较快，但程序员无法控制；堆由程序员分配，一般较慢，易产生内存碎片
- 存储内容不同：栈存储主函数的下一条指令的地址，参数，局部变量等；堆的头部用一个字节存放堆的大小，具体内容由程序员指定

#### 6.4.3 内存检查原理

Memcheck检测内存问题原理如下：

![](D:\Job\document\image\Valgrind内存检查原理.png)

>关键之处在于建立了两个全局表：
>
>- Valid-Value表：对于进程的整个地址空间中的每一个字节（Byte），都有与之对应的8 bit；对于CPU的每个寄存器，也有一个与之对应的 bit 向量。这些 bit 向量负责记录该字节或者寄存器值是否具有有效的，已初始化的值
>- Valid-Address表：对于进程整个地址空间的每一个字节（Byte），还有与之对应的 1 bit，负责记录改地址是否能够被读写。
>
>检测原理：
>
>- 当要读写内存中某个字节时，首先检查这个字节对应的A bit，如果该 A bit 显示该位置是无效位置，Memcheck则报告读写错误。
>- 内 核（ core ） 类似于一个虚拟的 CPU 环境 ，这样当内存中的某个字节被加载到真实的CPU 中时，该字节对应的 V bit 也被加载到虚拟的 CPU 环境中 。一旦寄存器中的值，被用来产生内存地址， 或者该值能够影响程序输出，则 Memcheck 会检查对应的 V bit ，如果该值尚未初始化，则会报告使用未初始化内存错误。
>
>    Memcheck将内存泄露分为两种
> - 可能的内存泄露（Possibly lost），指仍然存在某个指针能够访问某块内存，但该指针指向的已经不是该内存首地址。
> - 确定的内存泄露（Definitely lost），指已经不能够访问这块内存。分为直接的（direct）和间接的（indirect）。直接和间接的区别就是，直接是没有任何指针指向该内存，间接是指指向该内存的指针都位于内存泄露处。

#### 6.4.4 Valgrind安装与使用

**安装**

>1. 首先去 [官网]https://www.valgrind.org/downloads/old.html 下载Valgrind的压缩包
>
>2. 解压安装包：`tar xvf valgrind-3.16.0.tar.bz2`
>
>3. 进入安装文件夹：`cd valgrind-3.16.0`
>
>4. 配置和生成 makefile：`./configure`
>
>5. 从makefile中读取指令，然后编译并安装到指定位置
>
>   ```shell
>   make
>   make install
>   ```

**使用**

>命令格式：`valgrind [options] program-and-args`
>
>```shell
>常用选项介绍：
>--tool=<name> 最常用的选项。运行 valgrind中名为toolname的工具。默认memcheck。
>-h –help 显示帮助信息。
>--version 显示valgrind内核的版本，每个工具都有各自的版本。
>-q –quiet 安静地运行，只打印错误信息。
>-v –verbose 更详细的信息, 增加错误数统计。
>--trace-children=no|yes 跟踪子线程? [no]
>--track-fds=no|yes 跟踪打开的文件描述？[no]
>--time-stamp=no|yes 增加时间戳到LOG信息? [no]
>--log-fd=<number> 输出LOG到描述符文件 [2=stderr]
>--log-file=<file> 将输出的信息写入到filename.PID的文件里，PID是运行程序的进行ID
>--log-file-exactly=<file> 输出LOG信息到 file
>--log-file-qualifier=<VAR> 取得环境变量的值来做为输出信息的文件名。 [none]
>--log-socket=ipaddr:port 输出LOG到socket ，ipaddr:port
>
>LOG信息输出
>-xml=yes 将信息以xml格式输出，只有memcheck可用
>-num-callers=<number> show <number> callers in stack traces [12]
>-error-limit=no|yes 如果太多错误，则停止显示新错误? [yes]
>-error-exitcode=<number> 如果发现错误则返回错误代码 [0=disable]
>-db-attach=no|yes 当出现错误，valgrind会自动启动调试器gdb。[no]
>-db-command=<command> 启动调试器的命令行选项[gdb -nw %f %p]
>
>适用于Memcheck工具的相关选项：
>--leak-check=no|summary|full 要求对leak给出详细信息? [summary]
>--leak-resolution=low|med|high how much bt merging in leak check [low]
>--show-reachable=no|yes show reachable blocks in leak check? [no]
>
>```
>
>下面进行实例分析：
>
>```shell
>对于一个main.cpp
>#include <stdlib.h>
>#include <malloc.h>  
>#include <string.h>  
>using namespace std;
>
>void test()  
>{  
>    int *ptr = (int *)malloc(sizeof(int)*10);  
>  
>    ptr[10] = 7; // 数组下标访问越界  
>  
>    memcpy(ptr +1, ptr, 5); // dst和src地址重叠  
>  
>  
>    free(ptr);   
>    free(ptr);// 重复释放  
>  
>    int *p1;  
>    *p1 = 1; // 非法指针  
>}  
>  
>int main(void)  
>{  
>    test();  
>    return 0;  
>}  
>```
>
>运行`g++ -g test.cpp -o tes`t,成功生成可执行文件 test ；
>
>然后利用 memcheck 调试：`valgrind --tool=memcheck --leak-chenck=full ./test`
>
>```shell
>winston@Winstonly-Ly:/media/winston/本地磁盘/Job/TestProject/Debug$ valgrind --tool=memcheck --leak-check=full ./test
>==17357== Memcheck, a memory error detector
>==17357== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
>==17357== Using Valgrind-3.16.0 and LibVEX; rerun with -h for copyright info
>==17357== Command: ./test
>==17357== 
>//`======================= 内存越界======================// 
>==17357== Invalid write of size 4			
>==17357==    at 0x400825: test() (test.cpp:32)
>==17357==    by 0x400874: main (test.cpp:46)
>==17357==  Address 0x5ab7ca8 is 0 bytes after a block of size 40 alloc'd
>==17357==    at 0x4C2DF66: malloc (vg_replace_malloc.c:307)
>==17357==    by 0x400818: test() (test.cpp:30)
>==17357==    by 0x400874: main (test.cpp:46)
>==17357== 
>//`========踩内存，memcpy()相关函数中的dst和src指针重叠==========`
>==17357== Source and destination overlap in memcpy(0x5ab7c84, 0x5ab7c80, 5)
>==17357==    at 0x4C32784: memcpy@@GLIBC_2.14 (vg_replace_strmem.c:1033)
>==17357==    by 0x400846: test() (test.cpp:34)
>==17357==    by 0x400874: main (test.cpp:46)
>==17357== 
>//`==================== 重复释放 ============================`
>==17357== Invalid free() / delete / delete[] / realloc()
>==17357==    at 0x4C2F060: free (vg_replace_malloc.c:538)
>==17357==    by 0x40085E: test() (test.cpp:38)
>==17357==    by 0x400874: main (test.cpp:46)
>==17357==  Address 0x5ab7c80 is 0 bytes inside a block of size 40 free'd
>==17357==    at 0x4C2F060: free (vg_replace_malloc.c:538)
>==17357==    by 0x400852: test() (test.cpp:37)
>==17357==    by 0x400874: main (test.cpp:46)
>==17357==  Block was alloc'd at
>==17357==    at 0x4C2DF66: malloc (vg_replace_malloc.c:307)
>==17357==    by 0x400818: test() (test.cpp:30)
>==17357==    by 0x400874: main (test.cpp:46)
>==17357== 
>//`================= 使用未初始化的内存 =====================`
>==17357== Use of uninitialised value of size 8
>==17357==    at 0x400863: test() (test.cpp:41)
>==17357==    by 0x400874: main (test.cpp:46)
>==17357== 
>==17357== 
>==17357== Process terminating with default action of signal 11 (SIGSEGV): dumping core
>==17357==  Bad permissions for mapped region at address 0x4006B0
>==17357==    at 0x400863: test() (test.cpp:41)
>==17357==    by 0x400874: main (test.cpp:46)
>==17357== 
>==17357== HEAP SUMMARY:
>==17357==     in use at exit: 72,704 bytes in 1 blocks
>==17357==   total heap usage: 2 allocs, 2 frees, 72,744 bytes allocated
>==17357== 
>==17357== LEAK SUMMARY:
>==17357==    definitely lost: 0 bytes in 0 blocks
>==17357==    indirectly lost: 0 bytes in 0 blocks
>==17357==      possibly lost: 0 bytes in 0 blocks
>==17357==    still reachable: 72,704 bytes in 1 blocks
>==17357==         suppressed: 0 bytes in 0 blocks
>==17357== Reachable blocks (those to which a pointer was found) are not shown.
>==17357== To see them, rerun with: --leak-check=full --show-leak-kinds=all
>==17357== 
>==17357== Use --track-origins=yes to see where uninitialised values come from
>==17357== For lists of detected and suppressed errors, rerun with: -s
>==17357== ERROR SUMMARY: 4 errors from 4 contexts (suppressed: 0 from 0)
>Segmentation fault
>
>```
>
>

### 6.5 几个常用的调试命令

**file**

>`file`命令可查看文件的确切类型
>
>```shell
>winston@Winstonly-Ly:/media/winston/本地磁盘/Job/TestProject/Debug$ file test
>test: ELF 64-bit LSB executable, x86-64, version 1 (SYSV), dynamically linked, interpreter /lib64/ld-linux-x86-64.so.2, for GNU/Linux 2.6.32, BuildID[sha1]=49026291f98ab29ee9c6b71766f5940f3cc75b2d, not stripped
>```

**ldd**

>针对动态链接的二进制文件运行`ldd`命令会显示其所有依赖的库及路劲
>
>```shell
>winston@Winstonly-Ly:/media/winston/本地磁盘/Job/TestProject/Debug$ ldd test
>	linux-vdso.so.1 =>  (0x00007ffe3a570000)
>	libstdc++.so.6 => /usr/lib/x86_64-linux-gnu/libstdc++.so.6 (0x00007f5b36a91000)
>	libc.so.6 => /lib/x86_64-linux-gnu/libc.so.6 (0x00007f5b366c7000)
>	libm.so.6 => /lib/x86_64-linux-gnu/libm.so.6 (0x00007f5b363be000)
>	/lib64/ld-linux-x86-64.so.2 (0x00007f5b36e13000)
>	libgcc_s.so.1 => /lib/x86_64-linux-gnu/libgcc_s.so.1 (0x00007f5b361a8000)
>```

**ltrace**

>`ltrace`命令可以追踪命令运行的时候跑了哪些函数，可以作为堆栈调用跟踪调试。它能够跟踪进程的库函数调用，会显示哪个库函数被调用

**readelf**

>一般用于查看ELF格式的文件信息，如查看Linux下的可执行文件，动态库(*.so)或者静态库(*>a)，等
>
>```shell
>// `查看可执行文件test的头信息`
>winston@Winstonly-Ly:/media/winston/本地磁盘/Job/TestProject/Debug$ readelf -h test
>ELF Header:
>  Magic:   7f 45 4c 46 02 01 01 00 00 00 00 00 00 00 00 00 
>  Class:                             ELF64
>  Data:                              2's complement, little endian
>  Version:                           1 (current)
>  OS/ABI:                            UNIX - System V
>  ABI Version:                       0
>  Type:                              EXEC (Executable file)
>  Machine:                           Advanced Micro Devices X86-64
>  Version:                           0x1
>  Entry point address:               0x400840
>  Start of program headers:          64 (bytes into file)
>  Start of section headers:          20536 (bytes into file)
>  Flags:                             0x0
>  Size of this header:               64 (bytes)
>  Size of program headers:           56 (bytes)
>  Number of program headers:         9
>  Size of section headers:           64 (bytes)
>  Number of section headers:         36
>  Section header string table index: 33
>```

**nm**

>`nm`命令可以看到链接库的地址
>
>```shell
>winston@Winstonly-Ly:/media/winston/本地磁盘/Job/TestProject/Debug$ g++ test.cpp -o test.o
>winston@Winstonly-Ly:/media/winston/本地磁盘/Job/TestProject/Debug$ nm test.o
>0000000000601078 B __bss_start
>0000000000601190 b completed.7594
>                 U __cxa_atexit@@GLIBC_2.2.5
>0000000000601068 D __data_start
>0000000000601068 W data_start
>0000000000400870 t deregister_tm_clones
>00000000004008f0 t __do_global_dtors_aux
>0000000000600e08 t __do_global_dtors_aux_fini_array_entry
>0000000000601070 D __dso_handle
>0000000000600e18 d _DYNAMIC
>0000000000601078 D _edata
>0000000000601198 B _end
>0000000000400b04 T _fini
>0000000000400910 t frame_dummy
>0000000000600df8 t __frame_dummy_init_array_entry
>0000000000400d00 r __FRAME_END__
>0000000000601000 d _GLOBAL_OFFSET_TABLE_
>
>```

**查询命令**

>相关的查询命令可以显示一个运行在内核中的进程的状态和内存映射，主要是利用`/proc`文件系统，系统已启动就会收集运行时的系统信息（CPU信息，内存容量等）
>
>```shell
>ls -l /proc的输出结果，通过对系统中运行的每一个进程在/proc文件系统中有一个以进程id命名的项。每个进程的细节信息可以在进程id对应的目录下的文件中获得。也可以'ls /proc/pid'的输出
>// 获取进程id
>winston@Winstonly-Ly:/media/winston/本地磁盘/Job/TestProject/Debug$ ps -ef | grep test
>winston   2956 23216  0 10:57 pts/19   00:00:00 grep --color=auto test
>// 查看test进程在proc文件系统下的信息
>winston@Winstonly-Ly:/media/winston/本地磁盘/Job/TestProject/Debug$ ls /proc/23216
>attr        cmdline          environ  io         mem         ns             pagemap    sched       smaps_rollup     syscall            wchan
>autogroup   comm             exe      limits     mountinfo   numa_maps      patch_state  schedstat  stack         task
>auxv        coredump_filter  fd       loginuid   mounts      oom_adj        personality  sessionid  stat          timers
>cgroup      cpuset           fdinfo   map_files  mountstats  oom_score      projid_map   setgroups  statm         timerslack_ns
>clear_refs  cwd              gid_map  maps       net         oom_score_adj  root      smaps      status        uid_map
>然后可以利用cat 等命令查看具体文件的内容
>```
>
>
>
>

## 七 网络分析工具

### 7.1 ping

**简介**

> **ping**（Packet Internet Groper，因特网包探索器）是Windows、Unix和Linux下的一个命令，ping也属于TCP/IP协议的一部分。ping命令可以检查网络是否连通，可以很好地帮助分析和判定网络故障。
>
> ping 发送一个 ICMP (Internet Control Messages Protocol ，因特网信报控制协议），请求消息给目的地并报告是否收到所希望的 ICMP echo ( ICMP 回声应答）。工作原理是：利用网络机器上IP地址的唯一性，给目标IP地址发送一个数据包，再要求对方返回一个同样大小的数据包来确定两台网络机器是否连接相通以及时延是多少。

**ping的使用**

>网络连通问题是由许多原因引起，如本地配置错误、远程主机协议失效，设备故障等，用 ping 命令检查连通性有以下 6 个步骤：
>
>1. 使用 `ifconfig/all `观察本地网络设置是否正确 ；
>2.  `ping 127.0.0.1`，来检查本地的 TCP/IP 协议有没有设置好；
>3. `ping 本机 IP 地址`，这样是为了检查本机的 IP 地址是否设置有误；
>4. `ping 本网网关或本网 IP 地址`，这样的是为了检查硬件设备是否有问题，也可以检查本机与本地网络连接是否正常  （在非局域网中这一步骤可以忽略）；
>5. ` ping 本地 DNS 地址`，这样做是为了检查本地 DNS 服务器是否工作正常 ；
>6. ` ping 远程 IP 地址`，这主要是检查本网或本机与外部的连接是否正常 。 ping 远程 IP
>    地址还可以用来测试网络延时。 
>
>Linux下 ping 命令发送的数据包是 64 Byte，Windows则是 32 Byte；Windows下默认发送 4 次数据包后结束，Linux下 ping 默认不停发送数据包，直到手动停止。
>
>```shell
>ping [options]
>-c<完成次数>：设置完成要求回应的次数
>-i<时间间隔>：指定收发信息的间隔时间
>```
>
>

### 7.2 telnet

`telnet`命令常用语远程连接与管理目标主机，或者测试某个目标主机的某个TCP端口是否开放。

`telnet`命令常用来探测指定 ip 是否开放指定 port。

`telnet`因为采用明文传送报文，安全性不好，很多Linux服务器都不开放telnet服务，而改用更安全的ssh方式了

命令格式：`telnet ip_address port`

### 7.3 tcpdump

tcpdump 可以将网络中传送的数据包的“头”完全截获下来提供分析，它支持针对协议、主机、网络或端口的过滤，并提供`and、or、not`等逻辑语句来帮助去掉无用信息。

命令格式：

```shell
tcpdump [参数]
tcpdump 表达式
```

>- 表达式：正则表达式，满足表达式条件就会捕获报文，表达式中的关键字有关于类型（host、net、port），关于传输方向（src、dst、dst or src、dst、src），关于协议（fddi、ip、arp、rarp、tcp、udp，还有gateway、broadcast等关键字，另外提供三种逻辑运算：取非运算（not/!)，与运算（and/&&)，或运算(or/||).
>
>  ```shell
>  # 截取某主机相关的包
>  // a 截获host收到和发出的所有的数据包
>  tcpdump host 210.17.48.1	
>  // b 截获xxx.1和xxx.2或xxx.3的通信（命令行使用括号要添加 "\"
>  tcpdump host 210.17.48.1 and \ (210.17.18.2 or 210.17.18.3 \)
>  // c 截获主机接受或者发出的telnet包
>  tcpdump tcp port 23 host 210.27.480.1
>  # 截取某端口相关的包
>  tcpdump port 6666
>  # 截取某网卡的包
>  tcpdump -ieth1
>  ```
>
>  - 参数
>
>    ```shell
>    -c<数据包数目>：收到指定的数据包数目后，就停止进行倾倒操作；
>    -i<网络界面>：使用指定的网络截面送出数据包；
>    -r<数据包文件>：从指定的文件读取数据包数据；
>    -s<数据包大小>：设置每个数据包的大小；
>    -w<数据包文件>：把数据包数据写入指定的文件。
>    更多详细参数使用命令tcpdump -h 查看
>    ```

### 7.4 netstat

netstat 用于显式与 IP、TCP、UDP 和 ICMP协议相关的统计数据，一般用于检测本机各端口的网络连接情况。netstat 是在内核中访问网络及相关信息的程序，它能提供 TCP 连接、对 TCP 和 UDP 的监听及获取进程内存管理的相关报告 。

命令格式：`netstat [参数]`

```shell
-a或–all：显示所有连线中的Socket；
-A<网络类型>或–<网络类型>：列出该网络类型连线中的相关地址；
-c或–continuous：持续列出网络状态；
-l或–listening：显示监控中的服务器的Socket；
-n或–numeric：直接使用ip地址，而不通过域名服务器；
-p或–programs：显示正在使用Socket的程序识别码和程序名称；
-t或–tcp：显示TCP传输协议的连线状况；
-u或–udp：显示UDP传输协议的连线状况；

// 实例
netstat -a   		// 列出所有端口
netstat -at			// 列出所有 tcp 端口
netstat -au			// 列出所有 udp 端口
netstat -l			// 列出所有处于监听状态的socket
netstat -c 			// 持续输出netstat信息
```

输入 netstat 之后的打印信息

```shell
winston@Winstonly-Ly:/usr/local/bin$ netstat
Active Internet connections (w/o servers)
Proto Recv-Q Send-Q Local Address           Foreign Address         State      
tcp        0      0 192.168.0.101:39806     109.244.23.245:http     ESTABLISHED
tcp        0      1 192.168.0.107:54820     162.245.239.68:customs  FIN_WAIT1  
tcp        0      0 192.168.0.107:34100     112.53.36.18:http       ESTABLISHED
... ...
Active UNIX domain sockets (w/o servers)
Proto RefCnt Flags       Type       State         I-Node   Path
unix  2      [ ]         DGRAM                    27374    /run/user/1000/systemd/notify
unix  2      [ ]         DGRAM                    269853   /run/wpa_supplicant/wlp3s0
unix  3      [ ]         DGRAM                    750      /run/systemd/notify
unix  2      [ ]         DGRAM                    751      /run/systemd/cgroups-agent

```

>- netstat 的输出结果可以分为两个部分 ： ① Active Internet connections,称为有源 TCP 连接，其中 Recv-Q 和 Send-Q 指的是接收队列和发送队列，这些数字一般都应该是 0 ，如果不是则表示请求包和回包正在队列中堆积； ② Active UNIX domain sockets,称为有源 UNIX 域套接口（和 网络套接字一样 但是只能用于本机通信，性能可以提高一倍）。
>- Proto 显示连接使用的协议， RefCnt 表示连接到本套接口上的进程号， Types 显示套接口的类型， State 显示套接口当前的状态， Path 表示连接到套接口的其他进程使用的路径名 。
>

### 7.5 lsof

lsof ( list open file ） 是一个列出当前系统打开文件的工具。 因为 lsof需要访问核心内存和各种文件 ，所以必须以 root 用户的身份运行才能够充分地发挥其功能 。

执行 `lsof`命令后，输出结果如下 ：

```shell
winston@Winstonly-Ly:~$ lsof
COMMAND     PID   TID   USER   FD      TYPE    DEVICE  SIZE/OFF       NODE NAME
systemd       1        root   cwd    unknown     /proc/1/cwd (readlink: Permission denied)
systemd       1        root  rtd   unknown       /proc/1/root (readlink: Permission denied)
systemd       1        root  txt   unknown       /proc/1/exe (readlink: Permission denied)
systemd       1        root NOFD                 /proc/1/fd (opendir: Permission denied)
kthreadd      2        root  cwd   unknown       /proc/2/cwd (readlink: Permission denied)
```

- COMMAND ：进程的名称。
- PID ：进程标识符 。
- USER：进程所有者 。
- FD ：文件描述符，应用程序通过文件描述符识别该文件如 cwd 、 txt 等 。
- TYPE ：文件类型，如 DIR 、 阻G 等 。
- DEVICE ：指定磁盘的名称。
- SIZE ：文件的大小。
- NODE ：索引节点（文件在磁盘上的标识） 。
-  NAME ：打开文件的确切名称 。

**命令格式**：

```shell
lsof [options] filename

# 参数
lsof filename 显示打开指定文件的所有进程
lsof - a 表示两个参数都必须满足时才显示结果
lsof -c string 显示 COMMAND 列中包含指定字符的进程所有打开的文件
lsof -u username 显 示所属 user 进程打开的文件
lsof -g gid 显示归属 gid 的进程情况
lsof +d /DIR／显示目录下被进程打开的文件
lsof +D /DIR／同上 ， 但是会搜索目录下 的所有目录，时 间相对较长
lsof -d FD 显示指定文件描述符的进程
lsof -n 不将工P 转换为 hostname ， 缺省是不加上－n 参数
lsof -i 用以显示符合条件的进程情况

lsof -i ：6666			// 查看6666端口运行情况
lsof -a -u root -d txt 	// 查看root用户进程所打开的文件，文件类型为.txt
lsof /dev/tty1			// 监控打开的文件和设备
```

### 7.6 其他常用命令

[Linux中与网络相关的命令及常见用法]https://blog.csdn.net/flat0809/article/details/103148690

**ifconfig**

>网卡配置工具，可用来查看网卡信息（IP地址、发送包的个数、丢包个数）以及配置网卡（开启关闭网卡、修改网络、修改ip地址）
>
>命令格式 ：`ifconfig [options]`
>
>```shell
>option选项为：
>up，激活指定网卡；
>down，关闭指定网卡；
>netmask，设置子网掩码；
>media，设置网卡速度类型；
>pointopoint，设置当前主机以点对点方式通信时，对方主机的网络地址；
>address，设置指定网卡的IP地址。
>
>ifconfig eth0	// 查看查看系统中第一块以太网卡信息
>ifconfig eth0 up	// 激活网卡eth0
>ifconfig eth0 192.168.0.22 netmask 255.255.255.0	// 设置etho的ip地址和子网掩码 
>```

**service**

>`service`能够将目录`/etc/init.d/`中有关网络服务或系统服务脚本以一种统一的格式执行。
>
>命令格式：`service 脚本程序 [选项]`
>
>```shell
>service network-manager status	// 查看网络的工作状况
>service network-manager stop	// 关闭当前主机的网卡。关闭主机的对外网络连接
>service network-manager start	// 打开当前主机网卡，使主机获取ip地址，进行对外网络连接
>service network-manager restart	// 先stop，再start的功能
>```

**route**

>`route`命令可以显示或管理Linux系统的路由表，`route`设置的路由主要是静态路由
>
>```shell
>route -n：查看路由列表（可以看到当前计算机的网关）。
>route add default gw 192.168.1.1：临时设定网关。　
>route del default gw 192.168.1.1：删除设定的网关。
>```
>

