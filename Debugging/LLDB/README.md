# LLDB

    g++ sample.cpp -o sample.o -std=c++11

## Start

    lldb sample.o

## 断点

    设置断点
    (lldb) b base::AtomicRefCount::Decrement

    查看断点
    (lldb) breakpoint list
    (lldb) br l

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