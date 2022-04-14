---
date: 2022-04-13T22:06:32+08:00
author: "Rustle Karl"

title: "C++ 笔记目录"
url:  "posts/cpp/docs/CPP/README"  # 永久链接
tags: [ "C", "C++" ]  # 标签
series: [ "C 学习笔记" ]  # 系列
categories: [ "学习笔记" ]  # 分类

toc: true  # 目录
draft: false  # 草稿
---

## 🌋 C++ 发展历程

* C++ 编程语言的历史可以追溯到 **1979 年**，当时 Bjarne Stroustrup 为博士学位论文进行了一些开发。在 Stroustrup 可以使用的所有语言中，有一种被称为 Simula 的语言，顾名思义，它可能是一种主要为仿真而设计的语言。Simula 67 语言是 Stroustrup 使用的变体，被认为是支持面向对象编程范例的主要语言。Stroustrup 发现这种范例对包装开发很有帮助。但是，Simula 语言对于实践和实际使用而言太慢了。
随后不久，Bjarne Stroustrup 希望通过支持面向对象范例来增强 C。他深入研究了 Smalltalk 的 OO 实现，以获取有关实现的想法。但是他不愿意为此放弃性能，因此他开始从事 “C with Classes (带有类的 C）” 的工作，希望 C++ 代码运行时应具有与 C 代码相似（或更好）的性能。

* **1983 年**，语言的名称从 “带有类的 C” 更改为 C++。C 语言中的 ++ 运算符是用于递增变量的运算符，它使您可以深入了解 Stroustrup 如何看待该语言。在此期间添加了许多新功能，其中最引人注目的是虚函数，函数重载，带有＆符号的引用，const 关键字和使用两个正斜杠的单行注释。

* **1985 年**，Stroustrup 出版了名为*“C++ 编程语言” 的书籍*。同年，C++ 被实现为商业产品。该语言尚未正式标准化，因此使该书成为非常重要的参考。该语言在 1989 年再次进行了更新，以包括受保护的成员和静态成员，以及从多个类的继承。

* **1990 年**，发行了*《带注释的 C++ 参考手册*》。同年，Borland 的 Turbo C++ 编译器将作为商业产品发布。Turbo C++ 添加了许多其他库，这些库会对 C++ 的开发产生相当大的影响。尽管 Turbo C++ 的最后一个稳定版本是 2006 年，但该编译器仍被广泛使用。

* **1998 年**，C++ 标准委员会发布了第一个 C++ ISO / IEC 14882：1998 国际标准，其非正式名称为 C++ 98。据说*《带注释的 C++ 参考手册*》对标准的制定产生了很大的影响。还包括标准模板库，该模板库于 1979 年开始概念开发。2003 年，该委员会对 1998 年标准所报告的多个问题做出了回应，并对其进行了相应的修订。更改的语言称为 C++ 03。

* **2005 年**，C++ 标准委员会发布了一份技术报告（称为 TR1），详细介绍了他们计划添加到最新 C++ 标准中的各种功能。新标准被非正式地称为 C++ 0x，因为它有望在第一个十年结束之前的某个时间发布。具有讽刺意味的是，新标准要到 2011 年年中才会发布。直到那时为止，已经发布了几份技术报告，并且一些编译器开始为新功能添加实验性支持。

* **2011 年中**，新的 C++ 标准（称为 C++ 11）完成。Boost 库项目对新标准产生了重大影响，其中一些新模块直接来自相应的 Boost 库。一些新功能包括正则表达式支持，全面的随机化库，新的 C++ 时间库，原子支持，标准线程库 ，一种新的 for 循环语法，提供的功能类似于某些其他语言中的 foreach 循环，auto 关键字，新的容器类，对联合和数组初始化列表以及可变参数模板的更好支持。

* **2014 年**，C++ 14（也称为 C++ 1y）作为 C++11 的一个小扩展发布，主要功能是错误修复和小的改进，国际标准投票程序草案于 2014 年 8 月中完成，加强 lambda 函数，constexpr 和类型推导特性。

* **2017 年**，发布 C17 标准，C17 提供了很多东西。增强了核心语言和库。

* **2020 年**，发布 C++20 标准，推出了很多重量级功能，其中比较重要的有：

  - Concepts：概念改变了我们思考和编程模板的方式。它们是模板参数的语义类别。它们使您可以直接在类型系统中表达您的意图。如果出了什么问题，您会收到清晰的错误消息。
  - Ranges library：新的 ranges 库使它可以直接在容器上执行算法，用管道符号组成算法，并将其应用于无限数据流。
  - Coroutines：由于协程，C++ 中的异步编程成为主流。协程是协作任务，事件循环，无限数据流或管道的基础。
  - Modules：模块克服了头文件的限制。头文件和源文件的分离变得和预处理器一样过时了。最后，我们有更快的构建时间和更轻松的构建软件包的方法。
  - Concurrency：Atomic Smart Pointers,Joining & Cancellable Threads,The C20 Synchronization Library，增强了 C++ 并发编程能力；

## 🌰 干货铺

* [C++ Standard Library](http://en.wikipedia.org/wiki/C%2B%2B_Standard_Library) - 一系列类和函数的集合，使用核心语言编写，也是C++ISO自身标准的一部分
* [Standard Template Library](https://en.wikipedia.org/wiki/Standard_Template_Library) - 标准模板库
* [C POSIX library](https://en.wikipedia.org/wiki/C_POSIX_library) - POSIX系统的C标准库规范
* [ISO C++ Standards Committee](https://github.com/cplusplus) - C++标准委员会
* [C++ FAQ](https://isocpp.org/faq) − C++ 常见问题
* [Free Country](https://www.thefreecountry.com/sourcecode/cpp.shtml?spm=5176.10731542.0.0.4fc35bde2jHhz4) − Free Country 提供了免费的 C++ 源代码和 C++ 库，这些源代码和库涵盖了压缩、存档、游戏编程、标准模板库和 GUI 编程等 C++ 编程领域。
* [C and C++ Users Group](http://www.hal9k.com/cug/?spm=5176.10731542.0.0.4fc35bde2jHhz4) − C 和 C++ 的用户团体提供了免费的涵盖各种编程领域 C++ 项目的源代码，包括 AI、动画、编译器、数据库、调试、加密、游戏、图形、GUI、语言工具、系统编程等
* [LearnCpp](https://www.learncpp.com/) - 免费学习c++编程
* [CodeCogs](https://www.codecogs.com/) - CodeCogs是一项协作的开放源码库，C/C++的数值方面的组件
* [codeproject](https://www.codeproject.com/) - codeproject提供的C/C++资源代码项目
* [thoughtco](https://www.thoughtco.com/c-and-c-plus-programming-4133470) - 游戏有关的C++源代码
* [Free C/C++ Libraries](https://www.programmerworld.net/resources/c_library.htm) - 免费C++源代码和其它有用的工具
* [The C++ Standard Library](http://www.josuttis.com/libbook/examples.html) - 这是一个收集了数C/C++网站链接列表的网页
* [cplusplus](http://www.cplusplus.com/) - C++学习网站
* [C++ Source Codes](https://people.sc.fsu.edu/~jburkardt/cpp_src/cpp_src.html) - 这是一个全面的关于C++的345个源代码清单

## 🗜 框架

* [Apache C++ Standard Library](http://stdcxx.apache.org/) : 是一系列算法，容器，迭代器和其他基本组件的集合
* [ASL](http://stlab.adobe.com/) : Adobe源代码库提供了同行的评审和可移植的C++源代码库。
* [Boost](https://github.com/boostorg) : 大量通用C++库的集合。
* [BDE](https://github.com/bloomberg/bde) : 来自于彭博资讯实验室的开发环境。
* [Cinder](https://libcinder.org/) : 提供专业品质创造性编码的开源开发社区。
* [Bxxomfort](http://ryan.gulix.cl/fossil.cgi/cxxomfort/index) : 轻量级的，只包含头文件的库，将C++ 11的一些新特性移植到C++03中。
* [Dlib](http://dlib.net/) : 使用契约式编程和现代C++科技设计的通用的跨平台的C++库。
* [EASTL](https://github.com/paulhodge/EASTL) : EA-STL公共部分
* [ffead-cpp](https://github.com/sumeetchhetri/ffead-cpp) : 企业应用程序开发框架
* [Folly](https://github.com/facebook/folly) : 由Facebook开发和使用的开源C++库。
* [JUCE](https://github.com/WeAreROLI/JUCE) : 包罗万象的C++类库，用于开发跨平台软件
* [libphenom](https://github.com/facebookarchive/libphenom) : 用于构建高性能和高度可扩展性系统的事件框架。
* [LibSourcey](https://github.com/sourcey/libsourcey) : 用于实时的视频流和高性能网络应用程序的C++11 evented IO
* [Loki](http://loki-lib.sourceforge.net/) : C++库的设计，包括常见的设计模式和习语的实现。
* [MiLi](https://code.google.com/p/mili/) : 只含头文件的小型C++库
* [openFrameworks](https://openframeworks.cc/) : 开发C++工具包，用于创意性编码。
* [Qt](https://www.qt.io/developers/) : 跨平台的应用程序和用户界面框架
* [Reason](http://code.google.com/p/reason/) : 跨平台的框架，使开发者能够更容易地使用Java，.Net和Python，同时也满足了他们对C++性能和优势的需求。
* [ROOT](https://root.cern.ch/) : 具备所有功能的一系列面向对象的框架，能够非常高效地处理和分析大量的数据，为欧洲原子能研究机构所用。
* [STLport](http://www.stlport.org/) : 是STL具有代表性的版本
* [STXXL](http://stxxl.sourceforge.net/) : 用于额外的大型数据集的标准模板库。
* [Ultimate++](https://www.ultimatepp.org/) : C++跨平台快速应用程序开发框架
* [Windows Template Library](https://sourceforge.net/projects/wtl/) : 用于开发Windows应用程序和UI组件的C++库
* [Yomm11](https://github.com/jll63/yomm11) : C++11的开放multi-methods.

### 异步事件循环

* [Boost.Asio](https://think-async.com/Asio/) : 用于网络和底层I/O编程的跨平台的C++库。
* [libev](http://libev.schmorp.de/) : 功能齐全，高性能的时间循环，轻微地仿效libevent，但是不再像libevent一样有局限性，也修复了它的一些bug。
* [libevent](http://libevent.org/) : 事件通知库
* [libuv](https://github.com/joyent/libuv) : 跨平台异步I/O。
* [libco](https://github.com/Tencent/libco) : 协程，微信支持8亿用户同时在线的底层IO库。功能强大
* [libgo](https://github.com/yyzybb537/libgo) : golang风格的并发框架，C++11实现协程库

### 网络库

* [ACE](https://github.com/cflowe/ACE) : C++面向对象网络变成工具包
* [Casablanca](https://archive.codeplex.com/?p=casablanca) : C++ REST SDK
* [cpp-netlib](https://cpp-netlib.org/) : 高级网络编程的开源库集合
* [libCurl](https://curl.haxx.se/libcurl/) : 多协议文件传输库
* [Mongoose](https://github.com/cesanta/mongoose) : 非常轻量级的网络服务器
* [Muduo](https://github.com/chenshuo/muduo) : 用于Linux多线程服务器的C++非阻塞网络库
* [net_skeleton](https://github.com/cesanta/fossa) : C/C++的TCP 客户端/服务器库
* [POCO](https://github.com/pocoproject/poco) : 用于构建网络和基于互联网应用程序的C++类库，可以运行在桌面，服务器，移动和嵌入式系统。
* [RakNet](https://github.com/facebookarchive/RakNet) : 为游戏开发人员提供的跨平台的开源C++网络引擎。
* [Tufao](https://github.com/vinipsmaker/tufao) : 用于Qt之上的C++构建的异步Web框架。
* [WebSocket++](https://github.com/zaphoyd/websocketpp) : 基于C++/Boost Aiso的websocket 客户端/服务器库
* [ZeroMQ](http://zeromq.org/) : 高速，模块化的异步通信库

### TCP/IP协议栈

* [f-stack](https://github.com/f-stack/f-stack) : 腾讯开源的协议栈，基于DPDK的高性能用户态协议栈。
* [NtyTcp](https://github.com/wangbojing/NtyTcp) : 单线程的协议栈的，基于netmap,DPDK,rawSocket的实现。
* [LWIP](http://savannah.nongnu.org/projects/lwip/) : 针对 RAM 平台的精简版的 TCP/IP 协议栈实现。
* [mTCP](https://github.com/mtcp-stack/mtcp) : 针对多核系统的高可扩展性的用户空间 TCP/IP 协议栈。
* [4.4BSD](https://www.freebsd.org/zh_CN/copyright/license.html) : * nix的协议栈是源于4.4BSD的。

### WEB应用框架

* [Nginx](http://nginx.org/) : 一个高性能的HTTP和反向代理web服务器，同时也提供了IMAP/POP3/SMTP服务。
* [Lighttpd](http://www.lighttpd.net/) : 一款开源 Web 服务器软件，安全快速,符合行业标准,适配性强并且针对高配置环境进行了优化。
* [Libmicrohttpd](http://www.gnu.org/software/libmicrohttpd/) : GNU软件下的简单c库的Web服务器。API简单，快速。
* [shttpd](http://shttpd.sourceforge.net/) : 基于Mongoose的Web服务器框架。
* [CivetWeb](https://github.com/bel2125/civetweb) : 提供易于使用，强大的，C/C++嵌入式Web服务器，带有可选的CGI，SSL和Lua支持。
* [CppCMS](http://cppcms.com/wikipp/en/page/main) : 免费高性能的Web开发框架（不是 CMS）.
* [Crow](https://github.com/ipkn/crow) : 一个C++微型web框架（灵感来自于Python Flask）
* [Kore](https://kore.io/) : 使用C语言开发的用于web应用程序的超快速和灵活的web服务器/框架。
* [libOnion](https://www.coralbits.com/libonion/) : 轻量级的库，帮助你使用C编程语言创建web服务器。
* [QDjango](https://github.com/jlaine/qdjango/) : 使用C++编写的，基于Qt库的web框架，试图效仿Django API，因此得此名。
* [Wt](https://www.webtoolkit.eu/wt) : 开发Web应用的C++库。

### 标准库，算法与函数

* [C++ Standard Library](http://en.wikipedia.org/wiki/C%2B%2B_Standard_Library) : 是一系列类和函数的集合，使用核心语言编写，也是C++ISO自身标准的一部分。
* [Standard Template Library](https://en.wikipedia.org/wiki/Standard_Template_Library) : 标准模板库, STL
* [ISO C++ Standards Committee](https://github.com/cplusplus) : C++标准委员会

### 音频库

* [FMOD](https://www.fmod.com/) : 易于使用的跨平台的音频引擎和音频内容的游戏创作工具。
* [Maximilian](https://github.com/micknoise/Maximilian) : C++音频和音乐数字信号处理库
* [OpenAL](http://www.openal.org/) : 开源音频库—跨平台的音频API
* [Opus](http://opus-codec.org/) : 一个完全开放的，免版税的，高度通用的音频编解码器
* [Speex](https://www.speex.org/) : 免费编解码器，为Opus所废弃
* [Tonic](https://github.com/TonicAudio/Tonic) : C++易用和高效的音频合成
* [Vorbis](http://xiph.org/vorbis/) : Ogg Vorbis是一种完全开放的，非专有的，免版税的通用压缩音频格式。

### 生态学

* [lisequence](http://molpopgen.github.io/libsequence/) : 用于表示和分析群体遗传学数据的C++库。
* [SeqAn](http://www.seqan.de/) : 专注于生物数据序列分析的算法和数据结构。
* [Vcflib](https://github.com/vcflib/vcflib) : 用于解析和处理VCF文件的C++库
* [Wham](https://github.com/zeeev/wham) : 直接把联想测试应用到BAM文件的基因结构变异。

### 压缩

* [bzip2](http://www.bzip.org/) : 一个完全免费，免费专利和高质量的数据压缩
* [doboz](https://bitbucket.org/attila_afra/doboz/src) : 能够快速解压缩的压缩库
* [PhysicsFS](https://icculus.org/physfs/) : 对各种归档提供抽象访问的库，主要用于视频游戏，设计灵感部分来自于Quake3的文件子系统。
* [KArchive](https://projects.kde.org/projects/frameworks/karchive) : 用于创建，读写和操作文件档案（例如zip和 tar）的库，它通过QIODevice的一系列子类，使用gzip格式，提供了透明的压缩和解压缩的数据。
* [LZ4](https://code.google.com/p/lz4/) : 非常快速的压缩算法
* [LZHAM](https://code.google.com/p/lzham/) : 无损压缩数据库，压缩比率跟LZMA接近，但是解压缩速度却要快得多。
* [LZMA](http://www.7-zip.org/sdk.html) : 7z格式默认和通用的压缩方法。
* [LZMAT](http://www.matcode.com/lzmat.htm) : 及其快速的实时无损数据压缩库
* [Minizip](https://code.google.com/p/miniz/) : Zlib最新bug修复，支持PKWARE磁盘跨越，AES加密和IO缓冲。
* [Snappy](https://code.google.com/p/snappy/) : 快速压缩和解压缩
* [ZLib](http://zlib.net/) : 非常紧凑的数据流压缩库
* [ZZIPlib](http://zziplib.sourceforge.net/) : 提供ZIP归档的读权限。

### 并发性

* [Boost.Compute](https://github.com/boostorg/compute) : 用于OpenCL的C++GPU计算库
* [Bolt](https://github.com/HSA-Libraries/Bolt) :  针对GPU进行优化的C++模板库
* [C++React](https://github.com/schlangster/cpp.react) : 用于C++11的反应性编程库
* [Intel TBB](https://www.threadingbuildingblocks.org/) : Intel线程构件块
* [Libclsph](https://github.com/libclsph/libclsph) : 基于OpenCL的GPU加速SPH流体仿真库
* [OpenCL](https://www.khronos.org/opencl/) : 并行编程的异构系统的开放标准
* [OpenMP](https://www.openmp.org/) : OpenMP API
* [Thrust](http://thrust.github.io/) : 类似于C++标准模板库的并行算法库
* [HPX](https://github.com/STEllAR-GROUP/hpx/) : 用于任何规模的并行和分布式应用程序的通用C++运行时系统
* [VexCL](https://github.com/ddemidov/vexcl) : 用于OpenCL/CUDA 的C++向量表达式模板库。

### 密码学

* [Bcrypt](http://bcrypt.sourceforge.net/) : 一个跨平台的文件加密工具，加密文件可以移植到所有可支持的操作系统和处理器中。
* [BeeCrypt](https://github.com/klchang/beecrypt) : 快速的加密图形库，功能强大，接口方便。
* [Botan](https://botan.randombit.net/) : C++加密库
* [Crypto++](https://www.cryptopp.com/) : 一个有关加密方案的免费的C++库
* [GnuPG](https://www.gnupg.org/) : OpenPGP标准的完整实现
* [GnuTLS](https://www.gnutls.org/) : 实现了SSL，TLS和DTLS协议的安全通信库
* [Libgcrypt](https://gnupg.org/related_software/libgcrypt/) : 基于GnuPG的加密图形库。
* [Libmcrypt](https://github.com/winlibs/libmcrypt) : 线程安全，提供统一的API。
* [LibreSSL](http://www.libressl.org/) : 免费的SSL/TLS协议，属于2014 OpenSSL的一个分支
* [LibTomCrypt](https://github.com/libtom/libtomcrypt) : 一个非常全面的，模块化的，可移植的加密工具
* [libsodium](https://github.com/jedisct1/libsodium) : 基于NaCI的加密库，固执己见，容易使用
* [Nettle](http://www.lysator.liu.se/~nisse/nettle/) : 底层的加密库
* [OpenSSL](https://www.openssl.org/) : 一个强大的，商用的，功能齐全的，开放源代码的加密库。

### 数据库

* [hiberlite](https://github.com/paulftw/hiberlite) : 用于Sqlite3的C++对象关系映射
* [LevelDB](https://github.com/google/leveldb) : 快速键值存储库
* [LMDB](https://symas.com/lmdb/technical/) : 符合数据库四大基本元素的嵌入键值存储
* [MySQL++](https://tangentsoft.com/mysqlpp/home) : 封装了MySql的C API的C++ 包装器
* [RocksDB](https://github.com/facebook/rocksdb) : 来自Facebook的嵌入键值的快速存储
* [SQLite](https://www.sqlite.org/index.html) : 一个完全嵌入式的，功能齐全的关系数据库，只有几百KB，可以正确包含到你的项目中。
* [MongoDB](https://www.mongodb.com/) : 一个基于分布式文件存储的数据库

### 调试

* [Boost.Test](https://www.boost.org/doc/libs/master/libs/test/doc/html/index.html) : Boost测试库
* [Catch](https://github.com/catchorg/Catch2) : 一个很时尚的，C++原生的框架，只包含头文件，用于单元测试，测试驱动开发和行为驱动开发。
* [CppUnit](https://www.freedesktop.org/wiki/Software/cppunit/) : 由JUnit移植过来的C++测试框架
* [GoogleTest](http://code.google.com/p/googletest/) : 谷歌C++测试框架
* [ig-debugheap](https://github.com/deplinenoise/ig-debugheap) : 用于跟踪内存错误的多平台调试堆
* [MemTrack](http://www.almostinfinite.com/memtrack.html) : 用于C++跟踪内存分配
* [MicroProfile](https://bitbucket.org/jonasmeyer/microprofile/src/default/) : 跨平台的网络试图分析器
* [UnitTest++](http://unittest-cpp.sourceforge.net/) : 轻量级的C++单元测试框架

### 容器

* [C++ B-Tree](https://code.google.com/p/cpp-btree/) : 基于B树数据结构，实现命令内存容器的模板库
* [Hashmaps](https://github.com/goossaert/hashmap) : C++中开放寻址哈希表算法的实现

### 游戏引擎

* [Cocos2d-x](https://cocos2d-x.org/) : 一个跨平台框架，用于构建2D游戏，互动图书，演示和其他图形应用程序。
* [Grit](http://gritengine.com/) : 社区项目，用于构建一个免费的游戏引擎，实现开放的世界3D游戏。
* [lrrlicht](http://irrlicht.sourceforge.net/) : C++语言编写的开源高性能的实时#D引擎
* [PolyCode](http://polycode.org/) : C++实现的用于创建游戏的开源框架（与Lua绑定）。

### 图形库

* [bgfx](https://github.com/bkaradzic/bgfx) : 跨平台的渲染库
* [Cairo](http://www.cairographics.org/) : 支持多种输出设备的2D图形库
* [Horde3D](https://github.com/horde3d/Horde3D) : 一个小型的3D渲染和动画引擎
* [magnum](https://github.com/mosra/magnum) : C++11和OpenGL 2D/3D 图形引擎
* [Ogre 3D](https://www.ogre3d.org/) : 用C++编写的一个面向场景，实时，灵活的3D渲染引擎（并非游戏引擎）
* [OpenSceneGraph](http://www.openscenegraph.org/) : 具有高性能的开源3D图形工具包
* [Panda3D](https://www.panda3d.org/) : 用于3D渲染和游戏开发的框架，用Python和C++编写。
* [Skia](https://github.com/google/skia) : 用于绘制文字，图形和图像的完整的2D图形库
* [urho3d](https://github.com/urho3d/Urho3D) : 跨平台的渲染和游戏引擎。

### 图像处理

* [Boost.GIL](https://www.boost.org/doc/libs/1_56_0/libs/gil/doc/index.html) : 通用图像库
* [CImg](https://sourceforge.net/projects/cimg/) : 用于图像处理的小型开源C++工具包
* [FreeImage](http://freeimage.sourceforge.net/) : 开源库，支持现在多媒体应用所需的通用图片格式和其他格式。
* [GDCM](http://gdcm.sourceforge.net/wiki/index.php/Main_Page) : Grassroots DICOM 库
* [ITK](https://itk.org/) : 跨平台的开源图像分析系统
* [Magick++](http://www.imagemagick.org/script/api.php) : ImageMagick程序的C++接口
* [OpenCV](https://opencv.org/) : 开源计算机视觉类库
* [tesseract-ocr](https://code.google.com/p/tesseract-ocr/) : OCR引擎
* [VIGRA](https://github.com/ukoethe/vigra) : 用于图像分析通用C++计算机视觉库
* [VTK](https://vtk.org/) : 用于3D计算机图形学，图像处理和可视化的开源免费软件系统。

### 国际化

* [gettext](http://www.gnu.org/software/gettext/) :  GNU gettext
* [IBM ICU](http://site.icu-project.org/) : 提供Unicode 和全球化支持的C、C++ 和Java库
* [libiconv](http://www.gnu.org/software/libiconv/) : 用于不同字符编码之间的编码转换库

### Json库

* [frozen](https://github.com/cesanta/frozen) : C/C++的Jason解析生成器
* [Jansson](https://github.com/akheron/jansson) : 进行编解码和处理Jason数据的C语言库
* [jbson](https://github.com/chrismanning/jbson) : C++14中构建和迭代BSON data,和Json 文档的库
* [JeayeSON](https://github.com/jeaye/jeayeson) : 非常健全的C++ JSON库，只包含头文件
* [JSON++](https://github.com/hjiang/jsonxx) : C++ JSON 解析器
* [json-parser](https://github.com/udp/json-parser) : 用可移植的ANSI C编写的JSON解析器，占用内存非常少
* [json11](https://github.com/dropbox/json11) : 一个迷你的C++11 JSON库
* [jute](https://github.com/amir-s/jute) : 非常简单的C++ JSON解析器
* [ibjson](https://github.com/vincenthz/libjson) : C语言中的JSON解析和打印库，很容易和任何模型集成
* [libjson](https://sourceforge.net/projects/libjson/) : 轻量级的JSON库
* [PicoJSON](https://github.com/kazuho/picojson) : C++中JSON解析序列化，只包含头文件
* [Qt-Json](https://github.com/qt-json/qt-json) : 用于JSON数据和 QVariant层次间的相互解析的简单类
* [QJson](https://github.com/flavio/qjson) : 将JSON数据映射到QVariant对象的基于Qt的库
* [RepidJSON](https://github.com/Tencent/rapidjson) : 用于C++的快速JSON 解析生成器，包含SAX和DOM两种风格的API

### 日志

* [Boost.Log](http://www.boost.org/doc/libs/1_56_0/libs/log/doc/html/index.html) : 设计非常模块化，并且具有扩展性
* [easyloggingpp](https://github.com/zuhd-org/easyloggingpp) : C++日志库，只包含单一的头文件。
* [Log4cpp](http://log4cpp.sourceforge.net/) : 一系列C++类库，灵活添加日志到文件，系统日志，IDSA和其他地方。
* [templog](http://www.templog.org/) : 轻量级C++库，可以添加日志到你的C++应用程序中

### 机器学习，人工智能

* [btsk](https://github.com/aigamedev/btsk) : 游戏行为树启动器工具
* [Evolving Objects](http://eodev.sourceforge.net/) : 基于模板的，ANSI C++演化计算库，能够帮助你非常快速地编写出自己的随机优化算法。
* [Caffe](https://github.com/BVLC/caffe) : 快速的神经网络框架
* [CCV](https://github.com/liuliu/ccv) : 以C语言为核心的现代计算机视觉库
* [mlpack](http://www.mlpack.org/) :  可扩展的C++机器学习库
* [OpenCV](https://github.com/opencv/opencv) : 开源计算机视觉库
* [Recommender](https://github.com/GHamrouni/Recommender) : 使用协同过滤进行产品推荐/建议的C语言库。
* [SHOGUN](https://github.com/shogun-toolbox/shogun) : Shogun 机器学习工具
* [sofia-ml](https://code.google.com/p/sofia-ml/) : 用于机器学习的快速增量算法套件

### 数学库

* [Armadillo](http://arma.sourceforge.net/) : 高质量的C++线性代数库，速度和易用性做到了很好的平衡。语法和MatlAB很相似
* [blaze](https://code.google.com/p/blaze-lib/) : 高性能的C++数学库，用于密集和稀疏算法。
* [ceres-solver](http://ceres-solver.org/) : 来自谷歌的C++库，用于建模和解决大型复杂非线性最小平方问题。
* [CGal](http://www.cgal.org/) : 高效，可靠的集合算法集合
* [CML](https://github.com/demianmnave/CML/wiki/The-Configurable-Math-Library) : 用于游戏和图形的免费C++数学库
* [Eigen](http://eigen.tuxfamily.org/index.php?title=Main_Page) : 高级C++模板头文件库，包括线性代数，矩阵，向量操作，数值解决和其他相关的算法。
* [GMTL](http://ggt.sourceforge.net/) : 数学图形模板库是一组广泛实现基本图形的工具。
* [GMP](https://gmplib.org/) : 用于个高精度计算的C/C++库，处理有符号整数，有理数和浮点数。

### 多媒体库

* [GStreamer](https://gstreamer.freedesktop.org/) : 构建媒体处理组件图形的库
* [LIVE555 Streaming Media](http://www.live555.com/liveMedia/) : 使用开放标准协议(RTP/RTCP, RTSP, SIP) 的多媒体流库
* [libVLC](https://wiki.videolan.org/LibVLC) : libVLC (VLC SDK)媒体框架
* [QtAV](https://github.com/wang-bin/QtAV) : 基于Qt和FFmpeg的多媒体播放框架，能够帮助你轻而易举地编写出一个播放器
* [SDL](http://www.libsdl.org/) : 简单直控媒体层
* [SFML](http://www.sfml-dev.org/) : 快速，简单的多媒体库

### 物理学

* [Box2D](https://code.google.com/p/box2d/) : 2D的游戏物理引擎。
* [Bullet](https://github.com/bulletphysics/bullet3) : 3D的游戏物理引擎。
* [Chipmunk](https://github.com/slembcke/Chipmunk2D) : 快速，轻量级的2D游戏物理库
* [LiquidFun](https://github.com/google/liquidfun) : 2D的游戏物理引擎
* [ODE](http://www.ode.org/) : 开放动力学引擎-开源，高性能库，模拟刚体动力学。
* [ofxBox2D](https://github.com/vanderlin/ofxBox2d) : Box2D开源框架包装器。
* [Simbody](https://github.com/simbody/simbody) : 高性能C++多体动力学/物理库，模拟关节生物力学和机械系统，像车辆，机器人和人体骨骼。

### 机器人学

* [MOOS-Ivp](http://moos-ivp.org/) : 一组开源C++模块，提供机器人平台的自主权，尤其是自主的海洋车辆。
* [MRPT](https://www.mrpt.org/) : 移动机器人编程工具包
* [PCL](https://github.com/PointCloudLibrary/pcl) : 点云库是一个独立的，大规模的开放项目，用于2D/3D图像和点云处理。
* [Robotics Library](http://www.roboticslibrary.org/) : 一个独立的C++库，包括机器人动力学，运动规划和控制。
* [RobWork](http://www.robwork.dk/apidoc/nightly/rw/) : 一组C++库的集合，用于机器人系统的仿真和控制。
* [ROS](http://wiki.ros.org/) : 机器人操作系统，提供了一些库和工具帮助软件开发人员创建机器人应用程序。

### 脚本

* [ChaiScript](https://github.com/ChaiScript/ChaiScript/) : 用于C++的易于使用的嵌入式脚本语言。
* [Lua](http://www.lua.org/) : 用于配置文件和基本应用程序脚本的小型快速脚本引擎。
* [luacxx](https://github.com/dafrito/luacxx) : 用于创建Lua绑定的C++ 11 API
* [SWIG](http://www.swig.org/) : 一个可以让你的C++代码链接到JavaScript，Perl，PHP，Python，Tcl和Ruby的包装器/接口生成器
* [V7](https://github.com/cesanta/v7) : 嵌入式的JavaScript 引擎。
* [V8](http://code.google.com/p/v8/) : 谷歌的快速JavaScript引擎，可以被嵌入到任何C++应用程序中。

### 序列化

* [Cap'n Proto](https://capnproto.org/) : 快速数据交换格式和RPC系统。
* [cereal](https://github.com/USCiLab/cereal) : C++11 序列化库
* [FlatBuffers](https://github.com/google/flatbuffers) : 内存高效的序列化库
* [MessagePack](https://github.com/msgpack/msgpack-c) : C/C++的高效二进制序列化库，例如 JSON
* [ProtoBuf](http://code.google.com/p/protobuf/) : 协议缓冲，谷歌的数据交换格式。
* [SimpleBinaryEncoding](https://github.com/real-logic/simple-binary-encoding) : 用于低延迟应用程序的对二进制格式的应用程序信息的编码和解码。
* [Thrift](https://thrift.apache.org/) : 高效的跨语言IPC/RPC，用于C++，Java，Python，PHP，C#和其它多种语言中，最初由Facebook开发。

### 视频库

* [libvpx](http://www.webmproject.org/code/) : VP8/VP9编码解码SDK
* [FFMpeg](https://www.ffmpeg.org/) : 一个完整的，跨平台的解决方案，用于记录，转换视频和音频流。
* [libde265](https://github.com/strukturag/libde265) : 开放的h.265视频编解码器的实现。
* [OpenH264](https://github.com/cisco/openh264) : 开源H.364 编解码器。
* [Theora](https://www.theora.org/) : 免费开源的视频压缩格式。


### XML库

* [LibXml++](http://libxmlplusplus.sourceforge.net/) : C++的xml解析器
* [PugiXML](https://pugixml.org/) : 用于C++的，支持XPath的轻量级，简单快速的XML解析器。
* [RapidXML](http://rapidxml.sourceforge.net/) : 试图创建最快速的XML解析器，同时保持易用性，可移植性和合理的W3C兼容性。
* [TinyXML](https://sourceforge.net/projects/tinyxml/) : 简单小型的C++XML解析器，可以很容易地集成到其它项目中。
* [TinyXML2](https://github.com/leethomason/tinyxml2) : 简单快速的C++CML解析器，可以很容易集成到其它项目中。
* [TinyXML++](https://code.google.com/p/ticpp/) : TinyXML的一个全新的接口，使用了C++的许多许多优势，模板，异常和更好的异常处理。
* [Xerces-C++](http://xerces.apache.org/xerces-c/) : 用可移植的C++的子集编写的XML验证解析器。
