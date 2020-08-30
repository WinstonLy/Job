## TP -LINK（嵌入式软件工程师）

### 一面

1. C 语言中一个程序的编译过程：

    >- **预处理**：展开头文件、宏替换、去掉注释、条件编译，生成`.i`文件
    >- **编译**：检查语法，生成汇编代码，即`.s`文件
    >- **汇编**：汇编代码转换成机器码，生成`.o`文件
    >- **链接**：链接库文件和目标文件(`.o`文件)生成可执行文件

2. 定义一个指向整形数组的指针（理解错意思了）

    >利用数组指针：指向数组的指针 `类型名 (*p)[元素个数]`，一般利用于二维数组
    >
    >```c++
    >int a[10][20];
    >int (*p)[20] = a;
    >```
    >
    >指针数组的定义：元素是指针的数组，`类型名 *p[指针个数]`，一般对应于二级指针
    >
    >```c++
    >int *p[3];
    >int a[3][4];
    >for(int i = 0; i < 3; ++i)
    >{
    >p[i] = a[i];
    >++p;
    >}
    >```
    >
    >数组中 &a 和 &a[0] 的区别：
    >
    >```c++
    >int a[5] = {1, 2, 3, 4, 5};
    >int *ptr = (int *)(&a + 1);
    >printf("%d,%d",*(a+1), *(ptr-1));
    >
    >// 输出结果： 2 5
    >// 数组的名字 a：表示一个址项数组首地址的指针。a表示数组首地址（第一个元素地址），a+1表示第二个元素
    >// &a[0] : 表示数组的首地址，等于a
    >// &a: 表示存储指向数组首地址的指针的地址，类似一个二维指针。&a表示第一排数组，&a+1表示第二排数组
    >```
    >
    >
    >
    >[数组中的地址表示](https://blog.csdn.net/FX677588/article/details/74857473?utm_medium=distribute.pc_relevant.none-task-blog-BlogCommendFromMachineLearnPai2-2.nonecase&depth_1-utm_source=distribute.pc_relevant.none-task-blog-BlogCommendFromMachineLearnPai2-2.nonecase)

3. C语言关键字类型

    >```c
    >C语言
    >类型说明保字:int,long,short,float,double,char,unsigned,signed,const,void,volatile,enum,struct,union
    >语句定义保留字:if,else,goto,switch,case,do,while,for,continue,break,return,default,typedef
    >存储类说明保留字:auto,register,extern,static
    >长度运算符保留字:sizeof
    >enum：枚举参数值
    >extern：声明外部变量或函数，跨文件引用
    >static：指定静态变量或者静态函数，限定本文件使用
    >typedef：为数据类型定义别名
    >volatile：变量的值可能在程序的外部被改变，寄存器里的值可能来不及改变，允许直接从内存读取数据
    >C++
    >virtual、typename、template、private、public、protected、operator、delete等等
    >	包含有 C 中的关键字
    >explicit：当构造函数被指定时，将不会自动把构造函数作为转换构造函数
    >friend：允许类或者函数访问一个类中的私有数据，友元类/函数
    >inline：请求编译器扩张一个给定的函数，复制副本到相应位置，用空间换时间
    >```

    [关键字类型](https://blog.csdn.net/m0_38121874/article/details/82535129?utm_medium=distribute.pc_relevant.none-task-blog-searchFromBaidu-5.nonecase&depth_1-utm_source=distribute.pc_relevant.none-task-blog-searchFromBaidu-5.nonecase)

4. TCP 如何保证可靠性

    >- 报文中的校验和，检验报文头和数据
    >- 停止等待协议：利用序列号和确认应答来传输数据
    >- 超时重传机制：发送方在一定时间内没有收到确认，就重新发送数据
    >- 连接管理：三次握手和四次挥手，保证可靠连接
    >- 流量控制：根据接收端对数据的处理能力决定发送端的发送速度，防止丢包
    >- 拥塞控制：慢启动，拥塞避免，快重传，快恢复
    >- 窗口控制：滑动窗口

5. 介绍滑动窗口

    >停止等待协议要求每一次发送就停下来等待确认报文，然后再开始下一次发送，这样的效率很低。
    >
    >滑动窗口就是允许发送方在停止确认之前发送多个数据分组，在窗口内的数据分组分为以发送但未收到确认，和未发送的数据分组。接收端根据收到的数据分组序号，返回连续数据分组中序号最大的确认报文。发送方接收到确认之后，就像有滑动到确认报文对应的位置，开始下一次发送。这样能提高数据的传输速度，提高网络吞吐量。

6. TCP和UDP的区别

    >- TCP 面向连接，UDP 是无连接的；
    >- TCP 提供可靠的服务，也就是说，通过 TCP 连接传送的数据，无差错，不丢失，不重复，且按序到达；UDP 尽最大努力交付，即不保证可靠交付
    >- TCP 的逻辑通信信道是全双工的可靠信道；UDP 则是不可靠信道
    >- 每一条 TCP 连接只能是点到点的；UDP 支持一对一，一对多，多对一和多对多的交互通信
    >- TCP 面向字节流（可能出现黏包问题），实际上是 TCP 把数据看成一连串无结构的字节流；UDP 是面向报文的（不会出现黏包问题）
    >- UDP 没有拥塞控制，因此网络出现拥塞不会使源主机的发送速率降低（对实时应用很有用，如 IP 电话，实时视频会议等）
    >- TCP 首部开销20字节；UDP 的首部开销小，只有 8 个字节

7. 二叉树的遍历

    >前序遍历：根节点->左孩子->右孩子
    >
    >中序遍历：左孩子->根节点->右孩子
    >
    >后序遍历：左孩子->右孩子->根节点
    >
    >层序遍历：从根节点开始，依次遍历同一层的所有节点，遍历完之后在遍历

8. 深度优先和广度优先

    >深度优先：类似于前序遍历
    >
    >广度优先：类似于层序遍历

9. 专业和嵌入式的关系

    >AI 算法的落地实现，在硬件平台上的部署实现

### 二面 

1. 项目LVDS接口介绍

    [LVDS接口详解](https://blog.csdn.net/LinuxArmbiggod/article/details/83863479?utm_medium=distribute.pc_relevant.none-task-blog-BlogCommendFromMachineLearnPai2-4.nonecase&depth_1-utm_source=distribute.pc_relevant.none-task-blog-BlogCommendFromMachineLearnPai2-4.nonecase)

2. 项目QSPI接口介绍

    [QSPI介绍](https://www.cnblogs.com/commandNotFound/p/12663360.html)

3. 项目中遇到的问题以及如何解决（LVDS通信失败+调试）

4. QSPI、DMA、乒乓缓存介绍

5. C语言中的字节对齐

    >什么是对齐：计算机的内存空间是按 byte 划分的，从理论上讲对任何类型的变量都可以从特定地址开始访问，但实际上访问特定类型的变量都是从特定地址空间开始的，这就需要数据按一定规则在内存中排序，而不是顺序的一个一个排放。
    >
    >对齐的作用和原因：各个硬件平台对存储空间的处理有很大不同，有32位，64位等等，特定架构的 CPU 可能对一些数据类型只能从特定内存地址开始，如果没有字节对齐就可能读取出现错误；另外主要会对存取的效率会有影响，有的平台（例如32位系统）每次读都是从偶地址开始，对于从偶地址开始存放的 int 型数据，一个周期就能读取到，但对于从奇地址开始存放的 int 型数据，就需要读取两个周期，然后在开始拼凑才可以得到原始数据，这样读取效率就会下降很多。
    >
    >**字节对齐的原则**
    >
    >- 数据类型自身的对齐值：char 1、short 2、 int/float 4、单位字节
    >- 结构体或类的自身对齐值：其成员中自身对齐值最大的那个值
    >- 指定对齐值： `#pragma pack(value)`时的指定对齐值 value
    >- 数据成员、结构体和类的有效对齐值：自身对齐值和指定对齐值中小的那个值
    >
    >[字节对齐详解](https://blog.csdn.net/xhfwr/article/details/963793)
    >
    >[sizeof用法总结](https://blog.csdn.net/EVEcho/article/details/81115683?utm_medium=distribute.pc_relevant.none-task-blog-BlogCommendFromMachineLearnPai2-2.nonecase&depth_1-utm_source=distribute.pc_relevant.none-task-blog-BlogCommendFromMachineLearnPai2-2.nonecase)

6. int 与 unsigned int 的计算转换

    >**隐式类型转换**：内置数据类型有低精度向高精度转换、自定义数据类型？
    >
    >-  当不同类型的数据进行操作时，应当首先将其转换成相同的数据类型，然后进行操作，转换规则是由低级向高级转换，转换规则：(short/char)->int->unsigned->long->double、float->double
    >-  算术运算式中，低类型能够转换为高类型。
    >-  赋值表达式中，右边表达式的值自动隐式转换为左边变量的类型，并赋值给他。
    >-  函数调用中参数传递时，系统隐式地将实参转换为形参的类型后，赋给形参。
    >-  函数有返回值时，系统将隐式地将返回表达式类型转换为返回值类型，赋值给调用函数。
    >-  字符必须先转换为整数(C语言规定字符类型数据和整型数据之间可以通用) 
    >-  short型转换为int型(同属于整型) 。
    >-  float型数据在运算时一律转换为双精度(double)型，以提高运算精度(同属于实型)
    >
    >强制类型转换：`(type_name) expression`
    >
    >**当表达式中存在有符号类型和无符号类型时，所有的操作都将自动转换为无符号类型**
    >
    >```c
    >int a = 10;
    >int b = -20;
    >(a+b>0)?printf("a+b>0"):printf(a+b<0);
    >// 输出结果为 a+b>0
    >```
    >
    >[C 语言中数据类型自动转换原则](https://blog.csdn.net/u013498583/article/details/82899463)

7. 爱好