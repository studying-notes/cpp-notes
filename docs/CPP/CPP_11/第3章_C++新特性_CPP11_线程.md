---
date: 2022-04-13T22:20:05+08:00
author: "Rustle Karl"

title: "第3章_C++新特性_CPP11_线程"
url:  "posts/cpp/docs/CPP/CPP_11/第3章_C++新特性_CPP11_线程"  # 永久链接
tags: [ "C", "C++" ]  # 标签
series: [ "C 学习笔记" ]  # 系列
categories: [ "学习笔记" ]  # 分类

toc: true  # 目录
draft: false  # 草稿
---

- [std::thread相关](#stdthread相关)
- [std::mutex相关](#stdmutex相关)
- [std::lock相关](#stdlock相关)
- [std::atomic相关](#stdatomic相关)
- [std::call_once相关](#stdcall_once相关)
- [volatile相关](#volatile相关)
- [std::condition_variable相关](#stdcondition_variable相关)
- [std::future相关](#stdfuture相关)
- [std::promise与std::future配合使用](#stdpromise与stdfuture配合使用)
- [std::packaged_task与std::future配合使用](#stdpackaged_task与stdfuture配合使用)
- [三者之间的关系](#三者之间的关系)
- [async相关](#async相关)
- [C++11 使用 std::async创建异步程序](#c11-使用-stdasync创建异步程序)
- [std::future](#stdfuture)
- [std::promise](#stdpromise)
- [std::packaged_task](#stdpackaged_task)
- [std::promise、std::packaged_task和std::future的关系](#stdpromisestdpackaged_task和stdfuture的关系)
- [为什么要用`std::async`代替线程的创建](#为什么要用stdasync代替线程的创建)
- [`std::async`基本用法](#stdasync基本用法)
- [总结](#总结)

## std::thread相关

c++11之前可能使用pthread_xxx来创建线程，繁琐且不易读，c++11引入了std::thread来创建线程，支持对线程join或者detach。直接看代码：

```c++
#include <iostream>
#include <thread>

using namespace std;

int main() {
    auto func = []() {
        for (int i = 0; i < 10; ++i) {
            cout << i << " ";
        }
        cout << endl;
    };
    std::thread t(func);
    if (t.joinable()) {
        t.detach();
    }
    auto func1 = [](int k) {
        for (int i = 0; i < k; ++i) {
            cout << i << " ";
        }
        cout << endl;
    };
    std::thread tt(func1, 20);
    if (tt.joinable()) { // 检查线程可否被join
        tt.join();
    }
    return 0;
}
```

上述代码中，函数func和func1运行在线程对象t和tt中，从刚创建对象开始就会新建一个线程用于执行函数，调用join函数将会阻塞主线程，直到线程函数执行结束，线程函数的返回值将会被忽略。如果不希望线程被阻塞执行，可以调用线程对象的detach函数，表示将线程和线程对象分离。

如果没有调用join或者detach函数，假如线程函数执行时间较长，此时线程对象的生命周期结束调用析构函数清理资源，这时可能会发生错误，这里有两种解决办法，一个是调用join()，保证线程函数的生命周期和线程对象的生命周期相同，另一个是调用detach()，将线程和线程对象分离，这里需要注意，如果线程已经和对象分离，那就再也无法控制线程什么时候结束了，不能再通过join来等待线程执行完。

这里可以对thread进行封装，避免没有调用join或者detach可导致程序出错的情况出现：

```c++
class ThreadGuard {
    public:
    enum class DesAction { join, detach };

    ThreadGuard(std::thread&& t, DesAction a) : t_(std::move(t)), action_(a){};

    ~ThreadGuard() {
        if (t_.joinable()) {
            if (action_ == DesAction::join) {
                t_.join();
            } else {
                t_.detach();
            }
        }
    }

    ThreadGuard(ThreadGuard&&) = default;
    ThreadGuard& operator=(ThreadGuard&&) = default;

    std::thread& get() { return t_; }

    private:
    std::thread t_;
    DesAction action_;
};

int main() {
    ThreadGuard t(std::thread([]() {
        for (int i = 0; i < 10; ++i) {
            std::cout << "thread guard " << i << " ";
        }
        std::cout << std::endl;}), ThreadGuard::DesAction::join);
    return 0;
}
```

c++11还提供了获取线程id，或者系统cpu个数，获取thread native_handle，使得线程休眠等功能

```c++
std::thread t(func);
cout << "当前线程ID " << t.get_id() << endl;
cout << "当前cpu个数 " << std::thread::hardware_concurrency() << endl;
auto handle = t.native_handle();// handle可用于pthread相关操作
std::this_thread::sleep_for(std::chrono::seconds(1));
```

## std::mutex相关

std::mutex是一种线程同步的手段，用于保存多线程同时操作的共享数据。

mutex分为四种：

- std::mutex：独占的互斥量，不能递归使用，不带超时功能
- std::recursive_mutex：递归互斥量，可重入，不带超时功能

- std::timed_mutex：带超时的互斥量，不能递归
- std::recursive_timed_mutex：带超时的互斥量，可以递归使用

拿一个std::mutex和std::timed_mutex举例，别的都是类似的使用方式：

std::mutex:

```c++
#include <iostream>
#include <mutex>
#include <thread>

using namespace std;
std::mutex mutex_;

int main() {
    auto func1 = [](int k) {
        mutex_.lock();
        for (int i = 0; i < k; ++i) {
            cout << i << " ";
        }
        cout << endl;
        mutex_.unlock();
    };
    std::thread threads[5];
    for (int i = 0; i < 5; ++i) {
        threads[i] = std::thread(func1, 200);
    }
    for (auto& th : threads) {
        th.join();
    }
    return 0;
}
```

std::timed_mutex:

```c++
#include <iostream>
#include <mutex>
#include <thread>
#include <chrono>

using namespace std;
std::timed_mutex timed_mutex_;

int main() {
    auto func1 = [](int k) {
        timed_mutex_.try_lock_for(std::chrono::milliseconds(200));
        for (int i = 0; i < k; ++i) {
            cout << i << " ";
        }
        cout << endl;
        timed_mutex_.unlock();
    };
    std::thread threads[5];
    for (int i = 0; i < 5; ++i) {
        threads[i] = std::thread(func1, 200);
    }
    for (auto& th : threads) {
        th.join();
    }
    return 0;
}
```

## std::lock相关

这里主要介绍两种RAII方式的锁封装，可以动态的释放锁资源，防止线程由于编码失误导致一直持有锁。

c++11主要有std::lock_guard和std::unique_lock两种方式，使用方式都类似，如下：

```c++
#include <iostream>
#include <mutex>
#include <thread>
#include <chrono>

using namespace std;
std::mutex mutex_;

int main() {
    auto func1 = [](int k) {
        // std::lock_guard<std::mutex> lock(mutex_);
        std::unique_lock<std::mutex> lock(mutex_);
        for (int i = 0; i < k; ++i) {
            cout << i << " ";
        }
        cout << endl;
    };
    std::thread threads[5];
    for (int i = 0; i < 5; ++i) {
        threads[i] = std::thread(func1, 200);
    }
    for (auto& th : threads) {
        th.join();
    }
    return 0;
}
```

std::lock_gurad相比于std::unique_lock更加轻量级，少了一些成员函数，std::unique_lock类有unlock函数，可以手动释放锁，所以条件变量都配合std::unique_lock使用，而不是std::lock_guard，因为条件变量在wait时需要有手动释放锁的能力，具体关于条件变量后面会讲到。

## std::atomic相关

c++11提供了原子类型std::atomic<T>，理论上这个T可以是任意类型，但是平时只存放整形，别的还真的没用过，整形有这种原子变量已经足够方便，就不需要使用std::mutex来保护该变量啦。看一个计数器的代码：

```c++
struct OriginCounter { // 普通的计数器
    int count;
    std::mutex mutex_;
    void add() {
        std::lock_guard<std::mutex> lock(mutex_);
        ++count;
    }

    void sub() {
        std::lock_guard<std::mutex> lock(mutex_);
        --count;
    }

    int get() {
        std::lock_guard<std::mutex> lock(mutex_);
        return count;
    }
};

struct NewCounter { // 使用原子变量的计数器
    std::atomic<int> count;
    void add() {
        ++count;
        // count.store(++count);这种方式也可以
    }

    void sub() {
        --count;
        // count.store(--count);
    }

    int get() {
        return count.load();
    }
};
```

是不是使用原子变量更加方便了呢？

## std::call_once相关

c++11提供了std::call_once来保证某一函数在多线程环境中只调用一次，它需要配合std::once_flag使用，直接看使用代码：

```c++
std::once_flag onceflag;

void CallOnce() {
    std::call_once(onceflag, []() {
        cout << "call once" << endl;
    });
}

int main() {
    std::thread threads[5];
    for (int i = 0; i < 5; ++i) {
        threads[i] = std::thread(CallOnce);
    }
    for (auto& th : threads) {
        th.join();
    }
    return 0;
}
```

## volatile相关

貌似把volatile放在并发里介绍不太合适，但是貌似很多人都会把volatile和多线程联系在一起，一起介绍下。

volatile通常用来建立内存屏障，volatile修饰的变量，编译器对访问该变量的代码通常不再进行优化，看下面代码：

```c++
int *p = xxx;
int a = *p;
int b = *p;
```

a和b都等于p指向的值，一般编译器会对此做优化，把*p的值放入寄存器，就是传说中的工作内存(不是主内存)，之后a和b都等于寄存器的值，但是如果中间p地址的值改变，内存上的值改变啦，但a,b还是从寄存器中取的值(不一定，看编译器优化结果)，这就不符合需求，所以在此对p加volatile修饰可以避免进行此类优化。

注意：volatile不能解决多线程安全问题，针对特种内存才需要使用volatile，它和atomic的特点如下：• std::atomic用于多线程访问的数据，且不用互斥量，用于并发编程中• volatile用于读写操作不可以被优化掉的内存，用于特种内存中

## std::condition_variable相关

条件变量是c++11引入的一种同步机制，它可以阻塞一个线程或者个线程，直到有线程通知或者超时才会唤醒正在阻塞的线程，条件变量需要和锁配合使用，这里的锁就是上面介绍的std::unique_lock。

这里使用条件变量实现一个CountDownLatch：

```c++
class CountDownLatch {
    public:
    explicit CountDownLatch(uint32_t count) : count_(count);

    void CountDown() {
        std::unique_lock<std::mutex> lock(mutex_);
        --count_;
        if (count_ == 0) {
            cv_.notify_all();
        }
    }

    void Await(uint32_t time_ms = 0) {
        std::unique_lock<std::mutex> lock(mutex_);
        while (count_ > 0) {
            if (time_ms > 0) {
                cv_.wait_for(lock, std::chrono::milliseconds(time_ms));
            } else {
                cv_.wait(lock);
            }
        }
    }

    uint32_t GetCount() const {
        std::unique_lock<std::mutex> lock(mutex_);
        return count_;
    }

    private:
    std::condition_variable cv_;
    mutable std::mutex mutex_;
    uint32_t count_ = 0;
};
```

关于条件变量其实还涉及到通知丢失和虚假唤醒问题，因为不是本文的主题，这里暂不介绍，大家有需要可以留言。

## std::future相关

c++11关于异步操作提供了future相关的类，主要有std::future、std::promise和std::packaged_task，std::future比std::thread高级些，std::future作为异步结果的传输通道，通过get()可以很方便的获取线程函数的返回值，std::promise用来包装一个值，将数据和future绑定起来，而std::packaged_task则用来包装一个调用对象，将函数和future绑定起来，方便异步调用。而std::future是不可以复制的，如果需要复制放到容器中可以使用std::shared_future。

## std::promise与std::future配合使用

```c++
#include <functional>
#include <future>
#include <iostream>
#include <thread>

using namespace std;

void func(std::future<int>& fut) {
    int x = fut.get();
    cout << "value: " << x << endl;
}

int main() {
    std::promise<int> prom;
    std::future<int> fut = prom.get_future();
    std::thread t(func, std::ref(fut));
    prom.set_value(144);
    t.join();
    return 0;
}
```

## std::packaged_task与std::future配合使用

```c++
#include <functional>
#include <future>
#include <iostream>
#include <thread>

using namespace std;

int func(int in) {
    return in + 1;
}

int main() {
    std::packaged_task<int(int)> task(func);
    std::future<int> fut = task.get_future();
    std::thread(std::move(task), 5).detach();
    cout << "result " << fut.get() << endl;
    return 0;
}
```

## 三者之间的关系

std::future用于访问异步操作的结果，而std::promise和std::packaged_task在future高一层，它们内部都有一个future，promise包装的是一个值，packaged_task包装的是一个函数，当需要获取线程中的某个值，可以使用std::promise，当需要获取线程函数返回值，可以使用std::packaged_task。

## async相关

async是比future，packaged_task，promise更高级的东西，它是基于任务的异步操作，通过async可以直接创建异步的任务，返回的结果会保存在future中，不需要像packaged_task和promise那么麻烦，关于线程操作应该优先使用async，看一段使用代码：

```c++
#include <functional>
#include <future>
#include <iostream>
#include <thread>

using namespace std;

int func(int in) { return in + 1; }

int main() {
    auto res = std::async(func, 5);
    // res.wait();
    cout << res.get() << endl; // 阻塞直到函数返回
    return 0;
}
```

使用async异步执行函数是不是方便多啦。

async具体语法如下：

```c++
async(std::launch::async | std::launch::deferred, func, args...);
```

第一个参数是创建策略：

- std::launch::async表示任务执行在另一线程
- std::launch::deferred表示延迟执行任务，调用get或者wait时才会执行，不会创建线程，惰性执行在当前线程。

如果不明确指定创建策略，以上两个都不是async的默认策略，而是未定义，它是一个基于任务的程序设计，内部有一个调度器(线程池)，会根据实际情况决定采用哪种策略。

若从 std::async 获得的 std::future 未被移动或绑定到引用，则在完整表达式结尾， std::future的析构函数将阻塞直至异步计算完成，实际上相当于同步操作：

```c++
std::async(std::launch::async, []{ f(); }); // 临时量的析构函数等待 f()
std::async(std::launch::async, []{ g(); }); // f() 完成前不开始
```

注意：关于async启动策略这里以cppreference为主。

有时候如果想真正执行异步操作可以对async进行封装，强制使用std::launch::async策略来调用async。

```c++
template <typename F, typename... Args>
inline auto ReallyAsync(F&& f, Args&&... params) {
    return std::async(std::launch::async, std::forward<F>(f), std::forward<Args>(params)...);
}
```

## C++11 使用 std::async创建异步程序

C++11中增加了线程，可以非常方便的创建线程，它的基本用法是这样的：

```c++
void f(int n);
std::thread t(f, n + 1);
t.join();
```

但是线程毕竟是属于比较低层次的东西，有时候使用有些不便，比如希望获取线程函数的返回结果的时候，就不能直接通过 `thread.join()`得到结果，这时就必须定义一个变量，在线程函数中去给这个变量赋值，然后join，最后得到结果，这个过程是比较繁琐的。

c++11还提供了异步接口`std::async`，通过这个异步接口可以很方便的获取线程函数的执行结果。`std::async`会自动创建一个线程去调用线程函数，它返回一个`std::future`，这个future中存储了线程函数返回的结果，当需要线程函数的结果时，直接从future中获取，非常方便。

其实std::async提供的便利可不仅仅是这一点，它首先解耦了线程的创建和执行，可以在需要的时候获取异步操作的结果；其次它还提供了线程的创建策略（比如可以通过延迟加载的方式去创建线程），可以以多种方式去创建线程。在介绍`async`具体用法以及为什么要用`std::async`代替线程的创建之前，先看看`std::future`、`std::promise`和 `std::packaged_task`。

## std::future

std::future是一个非常有用也很有意思的东西，简单说std::future提供了一种访问异步操作结果的机制。从字面意思来理解， 它表示未来，因为一个异步操作是不可能马上就获取操作结果的，只能在未来某个时候获取，但是可以以同步等待的方式来获取结果，可以通过查询future的状态（future_status）来获取异步操作的结果。future_status有三种状态：

- deferred：异步操作还没开始
- ready：异步操作已经完成

- timeout：异步操作超时

```c++
//查询future的状态
std::future_status status;
do {
    status = future.wait_for(std::chrono::seconds(1));
    if (status == std::future_status::deferred) {
        std::cout << "deferred\n";
    } else if (status == std::future_status::timeout) {
        std::cout << "timeout\n";
    } else if (status == std::future_status::ready) {
        std::cout << "ready!\n";
} while (status != std::future_status::ready);
```

获取future结果有三种方式：get、wait、wait_for，其中get等待异步操作结束并返回结果，`wait`只是等待异步操作完成，没有返回值，`wait_for`是超时等待返回结果。

## std::promise

std::promise为获取线程函数中的某个值提供便利，在线程函数中给外面传进来的promise赋值，当线程函数执行完成之后就可以通过promis获取该值了，值得注意的是取值是间接的通过promise内部提供的future来获取的。它的基本用法：

```c++
std::promise<int> pr;
std::thread t([](std::promise<int>& p){
    p.set_value_at_thread_exit(9);
},std::ref(pr));
std::future<int> f = pr.get_future();
auto r = f.get();
```

## std::packaged_task

std::packaged_task它包装了一个可调用的目标（如function, lambda expression, bind expression, or another function object）,以便异步调用，它和promise在某种程度上有点像，promise保存了一个共享状态的值，而`packaged_task`保存的是一 个函数。它的基本用法：

```c++
std::packaged_task<int()> task([](){ return 7; });
std::thread t1(std::ref(task)); 
std::future<int> f1 = task.get_future(); 
auto r1 = f1.get();
```

## std::promise、std::packaged_task和std::future的关系

看了`std::async`相关的几个对象`std::future`、`std::promise`和`std::packaged_task`，其中 `std::promise`和`std::packaged_task`的结果最终都是通过其内部的future返回出来的，看看他们之间的关系到底是怎样的，`std::future`提供了一个访问异步操作结果的机制，它和线程是一个级别的属于低层次的对象，在它之上高一层的是`std::packaged_task`和`std::promise`，他们内部都有future以便访问异步操作结果，`std::packaged_task`包装的是一个异步操作，而`std::promise`包装的是一个值，都是为了方便异步操作的，因为有时需要获取线程中的某个值，这时就用`std::promise`，而有时需要获一个异步操作的返回值，这时就用`std::packaged_task`。

那 `std::promise`和`std::packaged_task`之间又是什么关系呢？说他们没关系也没关系，说他们有关系也有关系，都取决于如何使用他们了，可以将一个异步操作的结果保存到`std::promise`中。

## 为什么要用`std::async`代替线程的创建

`std::async`是为了让开发者的少费点脑子的，它让这三个对象默契的工作。大概的工作过程是这样的：`std::async`先将异步操作用`std::packaged_task`包 装起来，然后将异步操作的结果放到`std::promise`中，这个过程就是创造未来的过程。外面再通过`future.get/wait`来获取这个未来的结果！

现在来看看`std::async`的原型

`async(std::launch::async | std::launch::deferred, f, args...)` 第一个参数是线程的创建策略，有两种策略，默认的策略是立即创建线程：

`std::launch::async`：在调用async就开始创建线程。

`std::launch::deferred`：延迟加载方式创建线程。调用async时不创建线程，直到调用了`future`的`get`或者`wait`时才创建线程。

第二个参数是线程函数，第三个参数是线程函数的参数。

## `std::async`基本用法

```c++
std::future<int> f1 = std::async(std::launch::async, []() {
    return 8;
    });
cout << f1.get() << endl; //output: 8
std::future<void> f2 = std::async(std::launch::async, []() {
    cout << 8 << endl;
    //return 8;
    });
f2.wait(); //output: 8
std::future<int> future = std::async(std::launch::async, []() {
    std::this_thread::sleep_for(std::chrono::seconds(3));
    return 8;
    });
std::cout << "waiting...\n";
//Test12();
std::future_status status;
Sleep(3000);
do {
    status = future.wait_for(std::chrono::seconds(1));
    if (status == std::future_status::deferred) {
        std::cout << "deferred\n";
    }
    else if (status == std::future_status::timeout) {
        std::cout << "timeout\n";
    }
    else if (status == std::future_status::ready) {
        std::cout << "ready!\n";
    }
} while (status != std::future_status::ready);
std::cout << "result is " << future.get() << '\n';
```

可能的结果：waiting... timeout timeout ready! result is 8

`std::async`是更高层次上的异步操作，它的存在可以使开发者不用关注线程创建内部细节，就能方便的获取异步执行状态和结果，还可以指定线程创建策略，应该用`std::async`替代线程的创建，让它成为做异步操作的首选。

## 总结

• std::thread使线程的创建变得非常简单，还可以获取线程id等信息。
• std::mutex通过多种方式保证了线程安全，互斥量可以独占，也可以重入，还可以设置互斥量的超时时间，避免一直阻塞等锁。
• std::lock通过RAII技术方便了加锁和解锁调用，有std::lock_guard和std::unique_lock。
• std::atomic提供了原子变量，更方便实现实现保护，不需要使用互斥量
• std::call_once保证函数在多线程环境下只调用一次，可用于实现单例。
• volatile常用于读写操作不可以被优化掉的内存中。
• std::condition_variable提供等待的同步机制，可阻塞一个或多个线程，等待其它线程通知后唤醒。
• std::future用于异步调用的包装和返回值。
• async更方便的实现了异步调用，异步调用优先使用async取代创建线程。
