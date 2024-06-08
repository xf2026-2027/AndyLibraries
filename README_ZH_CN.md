# AndyLibraries

## 前言

这里收录了一些自己写的东西，以便不时之需。

总共分为两部分：库和模块

## 库

### FastIOS.h

你还在因背不下来快读快写而烦恼吗？

你还在因突然发现代码需要快读快写，然而改起来很麻烦而烦恼吗？

你还在因为普通快读快写难以获得最优解而烦恼吗？

快使用我们的封装快读，用仿 `cin cout` 的方式避免更改困难！！！

目前支持：**整形（你能想到的都可以），浮点数（你能想到的都可以），string，c风格字符串……**

#### 食用方法

需要使用 `using namespace FastIOS;`。

如果您需要本地调试，在代码编译选项里加入 `-DLOCAL`。

粘贴代码，更改您的 `cin cout`为 `qin qout`。

运行、调试、提交代码，祝您rp++，轻松AC，拿下最优解！！！

#### 高级

##### 使用自定义的快读类型

默认的 `qin qout` 是自动推断的产物，规则：

- 当定义 `LACAL`  宏时（编译代码选项里加入 `-DLOCAL`），使用  `qins qouts`。
- 当定义 `NORMAL`  宏时（编译代码选项里加入 `-DNORMAL`），使用  `qinn qoutn`。
- 否则使用  `qinf qoutf`。

其实有三对输入输出：`qins qouts`，`qinn qoutn`，`qinf qoutf`。只能任选一种，不能混用它们！！！

- `qins qouts` 是慢速快读，可以用于**OJ提交&本地调试&文件输入输出**。
- `qinn qoutn` 是普通快读，可以用于**OJ提交&文件输入输出**（本地调试困难，结束需要反复输入 `Ctrl+Z`)。
- `qinf qoutf` 是高速快读，可以用于**OJ提交&文件输入输出**（本地调试困难，结束需要反复输入 `Ctrl+Z`)。

快读的原理如出一辙，都是利用单个字符的输入。

慢速快读：使用 `<cstdio>`库中的 `std::getchar()`，`std::putchar()`。

普通快读：使用 `<cstdio>`库中的 `fread()`，`fwrite()`，先统一读入，再返回。

高速快读：使用 `<iostream>`库中的 `std::streambuf()`，直接访问cin，cout缓存。

#### 鸣谢

[hanmm81]([https://www.luogu.com.cn/user/748876](https://github.com/hanmm81)) [JSQ_]([https://www.luogu.com.cn/user/778847](https://github.com/Ji-Siqi))

### BigNumber.h

一个简单的封装整数高精度库。

### 食用方法

需要使用 `using namespace BigNumber;`

使用 `bignumber a`来定义一个高精度数字。

目前支持的运算符：

- `a+b`普通的加法
- `a-b`普通的减法
- `a*b`乘法(使用FFT加速)
- `a/b`普通的除法
- `a%b`普通的模法
- `abs(a)`返回绝对值
- `to_int(a)`转化为 `int`
- `to_long_long`转化为 `long long`

同时直接兼容 `cin cout`与 `FastIOS.h`中的快读快写！

### ExSort.h

一个对排序方法的追加。

#### 食用方法

类似于 `std::sort`（~~[你不知道？](https://zh.cppreference.com/w/cpp/algorithm/sort)~~）。

但是暂不支持自定义比较函数，想要排序结构体需要重载小于运算符（~~[你不知道？](https://zh.cppreference.com/w/cpp/language/overload_resolution)~~）。

## 模块

### Checker

一个简单的对拍实现。

#### 食用方法

#### 普通

命令行调用。

指令形如 `checker a1 a2 ... an rand judger`。

- `checker` 代表文件中的 `checker.exe`。
- `a1 a2 ... an` 为你要对拍的 $n$ 个 `cpp`文件（不用后缀名）。
- `rand` 代表数据生成器（exe文件，不用后缀名）。
- `judger` 为评测器。内置了一些在 `judgers` 文件夹下：
- `AllSame`：完全相同。
- `Normal`：正常评测器，忽略多余空格及换行。
- `Float_1e-3`：浮点误差小于 $10^{-3}$ 的评测器。
- `Float_1e-6`：浮点误差小于 $10^{-6}$ 的评测器。

执行后会输出结果，输入数据点存入 `tests` 文件夹。
输出数据存入 `answers`文件夹下对应程序名称的文件夹下。

#### 高级

##### 自定义数据生成器

请使用毫秒级随机数！！！

如果你要用 `rand()`，应使用：`srand(chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now().time_since_epoch()).count());` 以代替  `srand(time(0))`。

##### 自定义测评器

你应该实现的测评器应该能够使用如下命令行来调用：

```
judger a1 a2 ... an
```

其中 `judger` 为评测器exe，`a1 a2 ... an` 为检查是否相同的文件。

- 如果判定相同，应返回 $0$（`C++` 中 `return 0;`）；
- 如果判定不同，应返回 $1$（`C++` 中 `return 1;`）。
