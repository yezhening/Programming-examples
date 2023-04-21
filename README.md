# 编程实例（Programming-examples）

## 一、环境

- 操作系统：Windows
- 编译器：MinGW-w64

> 可使用Linux和make，替换（Makefile中）相应的编译命令即可。

- 工具：Go

## 二、内容

### 1. 数据结构：data_structure（11例）

（1）顺序表：sequence_list

- C语言，C++语言
- 顺序表的实现模板
- **有详细的步骤解析和使用示例**

（2）单链表：link_list

- C语言，C++语言
- 单链表的实现模板
- **有详细的步骤解析和使用示例**

（3）静态链表：static_link_list

- C语言，C++语言
- 静态链表的实现模板
- **有详细的步骤解析和使用示例**

（4）栈：stack

- C语言，C++语言
- 顺序栈的实现模板
- 链栈的实现模板
- **有详细的步骤解析和使用示例**

（5）队列：queue

- C语言，C++语言
- 顺序循环队列的实现模板
- 链队列的实现模板
- **有详细的步骤解析和使用示例**

（6）串的模式匹配：string_pattern_matching

- C语言，C++语言
- 暴力/简单/朴素算法的实现模板
- KMP算法的实现模板
- KMP改进算法的实现模板
- **有详细的步骤解析和使用示例**

（7）二叉树：binary_tree

- C语言，C++语言
- 二叉树的实现模板
- 线索二叉树的实现模板
- **有详细的步骤解析和使用示例**

（8）图：graph

- C语言，C++语言
- 图邻接矩阵的实现模板
- 图邻接表的实现模板
- **有详细的步骤解析和使用示例**

（9）线性查找：linear_search

- C语言，C++语言
- 线性查找的实现模板
- **有详细的步骤解析和使用示例**

（10）二叉排序树查找：binary_sort_tree_search

- C语言，C++语言
- 二叉排序树查找的实现模板
- **有详细的步骤解析和使用示例**

（11）排序：sort

- C语言，C++语言
- 排序的实现模板
- **有详细的步骤解析和使用示例**

### 2. 网络安全：network_security（3例）

（1）数据加密标准（DES）密码算法：DES

- **纯**C++语言
- **基于对象**编程范式
- 使用高级特性
- 考虑性能优化
- 相对规范和整洁
- 提示易错点
- **解析数据加密标准（DES）步骤**

（2）RSA密码算法：RSA

- **纯**C++语言
- **基于对象**编程范式
- 使用高级特性
- 考虑性能优化
- 相对规范和整洁
- 提示易错点
- **解析RSA步骤（网络上大部分实现代码的含义不明确，本代码相对明确）**
- **未使用大（素）数，但提供大（素）数实现的讨论**

（3）Diffie-Hellman密钥交换算法：DH

- **纯**C++语言
- **基于对象**编程范式
- 使用高级特性
- 考虑性能优化
- 相对规范和整洁
- 提示易错点
- **解析Diffie-Hellman步骤（网络上大部分实现代码的含义不明确，本代码相对明确）**

### 3. Node.js：Node.js（1例）

（1）简单Web服务端：simple_Web_server

- **详细解析创建http服务端的流程、URL的组成、请求消息的结构和响应消息的结构**

- 通过网络传输，浏览器客户端向该Web服务端发送“GET”请求，服务端依据URL响应本地相应的HTML、CSS和JavaScript文件，并在客户端渲染显示页面

### 4. Go：Go（3例）

（1）生产者消费者模型：producer_consumer_model

- 使用go关键字开启多协程goroutine，而不是多进程和多线程，实现并发

- 使用管道channal，而不是锁，实现同步互斥和数据通信

> 可联想进程间通信（IPC）中的管道pipe()、共享内存等方式

- 使用select{}语句，实现监听输入/输出（I/O）操作

> 可联想网络编程中的监听文件描述符select()函数

> 相比于C、C++和其他语言，使用Go实现并发编程的逻辑很简单

- **有详细的步骤解析**

（2）客户端/服务端（C/S）模型：client_server_model

- 实现服务端和客户端的简单通信：服务端接收，并原样发送所接收的数据给客户端

- 服务端使用多协程处理与多客户端的连接

- 客户端使用多协程处理终端用户输入和接收服务端数据

> 相比于C、C++和其他语言，使用Go实现网络编程的逻辑很简单


- **有详细的步骤解析**

（3）网络文件传输：network_file_transfer

- 使用服务端/客户端（C/S）模型
- 实现发送方（客户端）和接收方（服务端）的简单网络文件传输：发送方发送文件名，接收方回复响应，发送方再发送文件内容，接收方接收文件内容并保存在当前目录

> 网络传输文件的形式和本地传输文件类似，**本质是写读文件**

- 接续上一份代码实例“客户端/服务端（C/S）模型”，本章将传输的用户输入数据改为传输文件
- **有详细的步骤解析**

> 注意：关于网络编程的代码，上一份代码实例“客户端/服务端（C/S）模型”有详细的注释，本代码不再过多注释，只注释新增的网络文件传输相关内容

## 三、主要参考资料

### 1. 数据结构

- 《2023版数据结构高分笔记》主编：率辉
- 《2023年计算机组成原理考研复习指导》组编：王道论坛
- 《大话数据结构》作者：程杰

### 2. 网络安全

- 《密码编码学与网络安全——原理与实践(第五版)》作者：William Stallings

### 3. Node.js

- [Node.js (nodejs.org)](https://nodejs.org/en)
- [Node.js 中文网 (nodejs.cn)](https://nodejs.cn/)
- [黑马程序员Node.js全套入门教程，nodejs新教程含es6模块化+npm+express+webpack+promise等_Nodejs实战案例详解_哔哩哔哩_bilibili](https://www.bilibili.com/video/BV1a34y167AZ/?spm_id_from=333.337.search-card.all.click&vd_source=9ac1c0a6d496218112b60d49bc768cd7)
- [尚硅谷2023版Node.js零基础视频教程，nodejs新手到高手_哔哩哔哩_bilibili](https://www.bilibili.com/video/BV1gM411W7ex/?spm_id_from=333.337.search-card.all.click&vd_source=9ac1c0a6d496218112b60d49bc768cd7)

### 4.Go

- [20个小时快速入门go语言（中）_哔哩哔哩_bilibili](https://www.bilibili.com/video/BV1UW411x7Ve/?spm_id_from=333.337.search-card.all.click&vd_source=9ac1c0a6d496218112b60d49bc768cd7)
- [黑马程序员20个小时快速入门go语言（下）_哔哩哔哩_bilibili](https://www.bilibili.com/video/BV17W411W7hm/?spm_id_from=333.337.search-card.all.click)
