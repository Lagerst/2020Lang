# DataBase

varchar(n)
    Capacity < 5.0.3 ? Unit = 字节 :(else) Unit = 字符

## 索引

    目录页 - 页目录 - 页 - 二分法
    根据 主键 - (is null) 唯一索引 - (if null) 默认生成rowid 建立 B+树

    建议自增id作为主键，提升存储效率（使用更少的页作为索引）

    建立过程

        第一页

        copy第一页 -> 开辟第二页，第一页改为目录页（起始页不变）

    辅助索引

        create index idx_t_bcd on t(b, c, d) 联合索引，按序排序
        辅助索引找到后回到主键索引取数据 或 全表暴力搜索

        explain关键字

    比较规则

        bin, 字符集......

    使用索引

        最左前缀原则

## 事务4大特性 mysql如何保证实现

    Atomicity 原子性
        一系列操作要么都成功，要么都失败

    Isolation 隔离型
        事务之间相互隔离，互不影响

    Consistency
        总数据的一致性，总数据保持既定的约束

    Durability
        记录永久保存

    事务

        autocommit 事务自动提交

        START TRANSACTION;
        ...
        commit;

    隐式提交

        特定语句执行会自动commit (定义或修改数据库对象的数据定义语言)
        ALTER TABLE, CREATE USER, DROP USER, GRANT, RENAME USER, SET PASSWORD,
        LOCK TABLES, UNLOCK TABLES,
        LOAD DATA,
        ANALYZE TABLE, CACHE INDEX, CHECK TABLE, FLUSH, LOAD INDEX INTO CACHE, OPTIMIZE TABLE

    保存点

        只回滚到保存点

        SAVEPOINT 保存点名称;
        ROLLBACK [WORK] TO [SAVEPOINT] 保存点名称;
        RELEASE SAVEPOINT 保存点名称;

## 事务隔离级别

## Mysql默认隔离级别与并发安全

## RR和RC如何实现 使用场景

## 隔离级别的单位

## 存储引擎Innodb和Myisam

Innodb page size default = 16384/1024 = 16KB
Row Format :
<<<<<<< HEAD
=======
<<<<<<< HEAD
=======

>>>>>>> 9f8948f (feat: add prep for interview)
>>>>>>> edeb160 (feat: add prep for interview)
    Dynamic
        完全的行溢出的方式，在数据页中只存放20个字节的指针，指向下一页地址

    Compact
        变长字段长度列表 NULL标志位 记录头信息 列1 列2 ...
        2 Bytes         1 Byte    max to 65532Bytes

        Optional:
            部分数据 + 下一页地址

## Innodb锁机制，行锁，表锁，意向锁

## MVCC

## 哈希索引

## B树索引为什么使用B+树，相对于B树有什么优点？为什么不能红黑树？

磁盘预读

## 聚簇索引和非聚簇索引

## 创建索引

## 使用索引避免全表扫描

## Explain语句各字段的意义

## 联合索引优化 最左前缀

## 数据库范式

## 数据库查询关键字

## mysql主从复制过程，binlog记录格式，复制的异步半同步同步模式区别

## 主从复制或读写分离等数据不一致性问题