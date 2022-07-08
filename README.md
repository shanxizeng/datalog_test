## DataLog

### [Souffle](https://github.com/souffle-lang/souffle)

### 简介

datalog是prolog的一个子集，主要表达数据及其关系。

Datalog 是一种（声明式）基于逻辑的查询语言，允许用户执行递归查询。Datalog 语法的规范没有统一的标准，通常采用 Prolog 风格的语法。Soufflé 的语法受到 Datalog 实现的启发，即 Z3 中的 bddbddb(BDD-Based Deductive DataBase) 和 muZ。

Soufflé 为大规模面向逻辑的编程提供了软件工程功能（例如组件），对于实际使用，Soufflé 通过算术函子（arithmetic functors）扩展了 Datalog 使其图灵等价，让程序员能够编写非终止的程序。

Soufflé 中的主要语言元素是关系声明（relation declarations）、事实（facts）、规则（rules）和指令（directives）。

### 类型

datalog中有两种基本类型：symbol和number。其中symbol包含了所有的字符串，而number中包含了所有的整数。datalog内部使用序数表示字符串，```ord(str)```表示其序数。

souffle中另外还有两种类型：float和unsigned。其中float包含了浮点数，unsigned包含了无符号整数。

souffle中支持各种基本代数运算（包括取余和取幂）以及位运算和逻辑运算（同C语言一样，1为true，0为false）。同时还有 autoinc()运算。autoinc()每次使用时产生一个新的值（从零开始）。autoinc不能在递归关系中使用。（参考autoincTest.dl）

### 关系

souffle中的关系必须声明。关系由一个列表```(x1,x2,...,xk)```组成。每个部分声明各自的类型。

使用`.decl <rel-name>(x1:type1, x2:type2, ..., xk:typek)`定义关系。

### 输入输出

使用`.input <rel-name>`和`.output <rel-name>`进行输入输出。从`<rel-name>.facts`中读取输入，并将输出存在`<rel-name>.csv`中。注意数据要用制表符分隔。

使用`.printsize <rel-name>`输出集合基数。

### 规则

规则是条件逻辑语句，由规则头和规则体组成。如```path(x,y) :- path(x,z),edge(z,y)```

使用$!$对某个语句取非。注意为了保证单调性，在循环的定义中不能使用not。

### Functor

#### 聚合

Soufflé 中的聚合是指使用特定的函子来汇总有关查询的信息，聚合类型包括计数、求最小值/最大值、求和。在 Soufflé 中，信息通常不能从子目标（聚合函子的参数）流到外部作用域。例如，如果希望找到关系 Cost(x) 的最小值，无法找到使成本最小化的特定 x 值，因为这样的 x 值可能不是唯一的。

计数：```count:{<sub-goal>}```

最小：```max <var>:{<sub-goal(<var>)>}```

最大：```min <var>:{<sub-goal(<var>)>}```

求和：```sum <var>:{<sub-goal(<var>)>}```

参考countingTest.dl

#### 字符串函数

字符串拼接：`cat(x,y)`

字符串长度：`strlen(x)`

求子串：`substr(x,idx,len)`

转化函数：`to_string(x)`

Constraints:

子串：`contains(sub,str)`

正则表达式：`match(regexpr,str)`

### 类型系统

使用`.type`定义新的类型。如：

```datalog
.type Mytype = number
.decl A(x:Mytype)
```

#### Records

使用`[x1:type1,...,xk:typek]`定义Records，如

```datalog
.type IntPair = [l:number, r:number]
.type IntList = [x:number, xs:IntList]
.decl edge(e:IntPair)
.decl len(len:number, xs:IntList)
```

Records可以定义一些递归类型。使用nil表示递归结束。

#### 子类

使用符号 `<:`定义子类，如

```datalog
.type City <: symbol
.type Town <: symbol
.type Village <: symbol 
```

 使用$|$创建子类的union，如

```datalog
.type Position = City | Town | Village
```

使用`as(expr,type)` 进行类型转换

#### 抽象数据类型ADT

union只能表示由同一个基类生成的子类的并。如果要表示不同基类生成的子类，就必须使用ADT。

定义：`.type name = bname1 { name11:type11, ..., name1k1:type1k1 } | bname2 { name21:type21, ..., name2k2:type2k2} | ...`

`bnamei`表示一个`branch`的名字。使用`$bname(...)`选择一个分支。

```datalog
.type T = N {a:number} | S {b:symbol} // Either a number or a symbol
.decl A(p: T)  // set of numbers or symbols
A($N(1)). 
A($S(“hello world”)).
// Flatten relation A
.decl Flatten(a:number, b:symbol) 
Flatten(a, ””) :- A($N(a)).
Flatten(0, b) :- A($S(b)).  
```

### 组件

Soufflé 有组件这个概念，可用于模块化大型逻辑程序。一个组件可能包含其他组件、关系、类型声明、事实、规则和指令；组件必须声明和实例化后才可以使用，每个组件都有自己的命名空间；组件可以继承一个或多个超级组件。

声明组件使用```.comp```，使用`.init`初始化组件。如：

```datalog
.comp TestComponent {
	.type MyType = number
	.decl Rel(x: MyType)
	Rel(0).
}
.init TestInstance = TestComponent
TestInstance.Rel(10).
.output TestInstance.Rel
```

组件的定义可以进行嵌套。

#### 组件参数传递

可以使用类似泛型的概念。

```datalog
.comp ParamComponent<myType> {
    .decl TheAnswer(x:myType)    // component relation
    TheAnswer(42).               // component fact
    .output TheAnswer            // component output directive
}
.init numberInstance = ParamComponent<number>
.init floatInstance = ParamComponent<float>
```

```datalog
.decl R(x:number)
.comp Case<Selector> {
   .comp One { 
     R(1). 
   } 
   .comp Two { 
     R(2).
   } 
   .init selection = Selector // instantiation depending on type parameter "Selector" 
} 
.init myCase = Case<One> 
.output R
```

#### 继承

一个组件可以继承其他的组件，这样可以包含其他组件中的内容。

```datalog
.comp Base1 {
    .type myNumber = number
    .decl TheAnswer(x:myNumber)
    TheAnswer(42).
}
.comp Base2 { 
    TheAnswer(41). 
}
.comp Sub  : Base1, Base2 { // inherit from Base1 and Base2
    .decl WhatIsTheAnswer(n:myNumber)
    WhatIsTheAnswer(n) :- TheAnswer(n).
    .output WhatIsTheAnswer
}
.init mySub = Sub
```

#### 可重写关系

使用overridable声明关系使其在继承时可以被覆盖。

```datalog
.comp Base {
    .decl R(x:number) overridable
    R(1).
    R(x+1) :- R(x), x < 5. 
    .output R
}
.comp Sub : Base {
    .override R
    R(2).
    R(x+1) :- R(x), x < 4. 
}
.init mySub = Sub
```



## 参考

[Tutorial | Soufflé](https://souffle-lang.github.io/tutorial)

[Datalog 引擎 Soufflé 指南 - Jckling's Blog](https://jckling.github.io/2021/11/22/Other/Datalog%20%E5%BC%95%E6%93%8E%20Souffl%C3%A9%20%E6%8C%87%E5%8D%97/)

