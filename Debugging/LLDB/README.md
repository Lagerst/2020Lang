# LLDB

    g++ -g sample.cpp -o sample.o -std=c++11

## Start

    调试可执行文件
    lldb sample.o

    调试运行时带参数的可执行文件
    lldb -- sample.o 1 2 3

    调试某个正在运行中的进程
    lldb
    (lldb) process attach --pid 9939
    or
    (lldb) process attach --name Safari

## 断点

    设置断点
    (lldb) breakpoint set --file sample.cpp --line 82
    (lldb) b base::AtomicRefCount::Decrement

    根据函数名下断点
    # C函数
    (lldb) breakpoint set --name main
    # C++类方法
    (lldb) breakpoint set --method foo
    # Objective-C选择器
    (lldb) breakpoint set --selector alignLeftEdges:

    根据某个函数调用语句下断点(Objective-C比较有用)
    # lldb有一个最小子串匹配算法，会知道应该在哪个函数那里下断点
    (lldb) breakpoint set -n "-[SKTGraphicView alignLeftEdges:]"

    查看断点
    (lldb) breakpoint list
    (lldb) br l

    禁用断点
    (lldb) breakpoint disable 2

    启用断点
    (lldb) breakpoint Enable 2

    删除断点
    (lldb) breakpoint delete x
    (lldb) br del x

    单步进入
    (lldb) thread step-in
    (lldb) step
    (lldb) s

    单步跳过
    (lldb) thread step-over
    (lldb) step
    (lldb) n

    继续运行
    (lldb) thread continue
    (lldb) continue
    (lldb) c

## 观察点

    设置观察点
    (lldb) watchpoint set variable b
    (lldb) wa s v b

    查看观察点
    (lldb) watchpoint list
    (lldb) watch l

    删除观察点
    (lldb) watchpoint delete 观察点编号
    (lldb) watch del 观察点编号

## 变量

    查看本地变量 (查看当前堆栈帧的所有本地变量)
    (lldb) frame variable
    (lldb) fr v
    查看本地变量 (查看某个具体变量，其中bar为变量名)
    (lldb) frame variable bar
    (lldb) fr v bar
    (lldb) p bar
    (lldb) po &bar

    查看全局变量 (全部)
    (lldb) target variable
    (lldb) ta v
    查看全局变量 (某个具体变量)
    (lldb) target variable baz
    (lldb) ta v baz

    计算基本数据类型表达式
    (lldb) expr (int) i * i
    (lldb) expr i * i
    (lldb) print i * i
    (lldb) p i * i

    计算对象数据类型表达式
    (lldb) expr -o --对象.属性
    (lldb) po 对象.属性

# frame 帧

    切换帧
    (lldb) frame select 4

# 线程

    查看所有线程
    (lldb) thread backtrace all

    切换线程
    (lldb) thread select 3

# 查看代码

    查看当前代码段
    (lldb) l or list

    查看某一函数的代码
    (lldb) list main