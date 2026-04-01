# Problem 046 - Mercenary

**ACMOJ Problem ID**: 1778

## Table of Contents

- [Problem 046 - Mercenary](#problem-046-mercenary)
  - [Table of Contents](#table-of-contents)
  - [Introduction](#introduction)
    - [Background](#background)
  - [Assignment Description](#assignment-description)
    - [Grade Composition](#grade-composition)
  - [Assignment Requirements](#assignment-requirements)
    - [Input Format](#input-format)
    - [Output Format](#output-format)
    - [Samples](#samples)
    - [Data Constraints](#data-constraints)
  - [Per-Testcase Resource Limits](#per-testcase-resource-limits)
  - [Test Data](#test-data)
  - [Submission Requirements](#submission-requirements)
    - [OJ Git Repository Compilation Process](#oj-git-repository-compilation-process)
    - [Git Configuration Requirements](#git-configuration-requirements)
    - [Submission Guidelines](#submission-guidelines)
    - [Evaluation Notes](#evaluation-notes)
    - [Academic Integrity](#academic-integrity)

## Introduction

### Background

Implement game character class hierarchy (Fighter/Protector/Caster) with battle system, damage calculation, type effectiveness.

## Assignment Description

### Grade Composition

| Grading Component | Percentage |
| :--: | :--: |
| Pass **1778. Mercenary** | 80% |
| Code Review | 20% |

Here are several points that need clarification:

- In the Code Review, we will **strictly examine your code style and repository organization structure, etc.**

- This assignment provides some sample data for testing, stored in the `/workspace/data/046/data_test/` directory. Note that these are not the test cases on the Online Judge. Passing all local test cases does not guarantee that you will pass the OJ tests.

- Besides the provided sample data, we also encourage you to design your own test data based on your program logic to assist debugging.

## Assignment Requirements

### Problem Description

**本题禁止在 hpp 中定义全局变量。**

在某游戏新推出的模式中，有三种不同的角色，*Fighter*、*Protector* 和 *Caster*。三种角色之间存在克制关系:

> *Fighters* deal double damage to *Casters*, *Casters* deal double damage to *Protectors*, and *Protectors* deal double damage to *Fighters*.

即 *Fighters* 对 *Casters* 造成双倍伤害, *Casters* 对 *Protectors* 造成双倍伤害, *Protectors* 对 *Fighters* 造成双倍伤害。

游戏机制是在回合制，每个回合开始前所有对象决定在下一回合中是否防御 `defend`，如果防御则不能发动进攻 `launch_attack`；在回合中，未防御的存活对象按照一定顺序发动进攻。采取防御的同时，*Fighter* 的生命值增加 3 点，攻击力增加 2 点；*Protector* 的生命值增加 7 点，攻击力增加 1 点；*Caster* 的生命值增加 5 点。

伤害结算：如果被进攻者未防御，则被进攻者生命值减少 **进攻者 attack × 克制倍数（克制为 2，不克制为 1）**；如果被进攻者防御，则被进攻者的生命值减少**进攻者 attack × 克制倍数 - 被进攻对象 attack** (攻击不会使被攻击者生命值增加，生命值减少量为负值则不造成伤害)，进攻者生命值减少 **被进攻者 attack × (1 - (进攻者 == Caster))** 。（即如果进攻者是 Caster 就不受反伤。）如果生命值归零（小于等于 0），则该角色阵亡。

正在玩此游戏的你突然卷入了时间漩涡，你成了此游戏的开发部门的一员，你需要应用所学的C++知识帮助完成此游戏的开发。

你接到的任务如下：

完成角色模块（`Role.hpp`）的代码设计，包括基类（`Base`）、三个派生类（`Fighter`, `Protector`, `Caster`）。

| 类     | 需求                                     |
| ------ | ---------------------------------------- |
| `Base` | 成员变量(`string` 参数属性 `name`，角色的名称；`int` 参数生命值 `health`，攻击力 `attack`，这两个参数只能由该类本身及其派生类修改；`bool` 参数 `alive` 表征该角色的存活状态(`true` 表示存活))；`bool` 参数 `defensive` 表征该角色是否采用防御策略；基类的构造析构函数，需要派生实现的函数 `launch_attack`, `defend`；状态表征类函数`isAlive`,  `isDefensive`；**特殊的 `int` 成员变量 `aliveNumber`** 用以表示当前存活的总角色数。 |
|`Fighter`|派生自基类 `Base`，实现需要派生实现的函数、构造函数、析构函数等|
|`Protector`|派生自基类 `Base`，实现需要派生实现的函数、构造函数、析构函数等|
|`Caster`|派生自基类 `Base`，实现需要派生实现的函数、构造函数、析构函数等|

需要实现的行为：

| 函数名及接口                         | 类   | 需求                               |
| ------------------------------------ | ---- | ---------------------------------- |
|构造函数|所有类|派生类需提供接口如 `ClassName (const string& name, const int health, const int attack)` 的构造函数，构造的对象默认 `alive = true`|
| `int getAliveNumber` | 基类 | 返回当前存活的总角色数 |
| `bool isAlive()` | 基类 | 返回对象是否存活 |
| `bool isDefensive()` | 基类 | 返回对象是否防御 |
| `void launch_attack( Base* target)` | 所有类 | 对 `target` 对象发动攻击，角色阵亡时需输出 `[role] [name] is killed\n`，`[role]` 同相应派生类名。当攻击发起者和被攻击者一同阵亡时，先输出**被攻击者**的阵亡信息。保证被攻击者存活。 |
| `void defend(bool flag)` | 所有类 | `flag = true` 表示下一回合中该角色将采取 `defend` 的行为；采取 defend 行为的同时，不同属性的角色会有不同的增益。 |

**你只需要为基类定义若干函数，以及实现各派生类的 `launch_attack` 函数**

**你的设计需要使声明一个基类 Base 对象是不合法的,不得定义额外的 public 函数和成员变量，良好的封装性是评分的标准之一。**

同样卷入时间漩涡的助教将给你提供测试的代码 `test.cpp`。

```cpp
//test.cpp
#include<iostream>
#include<string>
#include"Role.hpp"
using final::Base;
using final::Fighter;
using final::Protector;
using final::Caster;

Base* baseptrArray[1005];

int main() {
    int n, h, att, round=0, cnt=0;
    std::string roleInput, nameInput;
    std::cin >> n;
    for (int i = 0; i < n; ++i) {
        std::cin >> roleInput >> nameInput >> h >> att;
        if (roleInput == "Fighter") {
            baseptrArray[i] = new Fighter(nameInput, h, att);
        }
        if (roleInput == "Protector") {
            baseptrArray[i] = new Protector(nameInput, h, att);
        }
        if (roleInput == "Caster") {
            baseptrArray[i] = new Caster(nameInput, h, att);
        }
    }
    while (Base::getAliveNumber() > 1) {
        ++round;
        //before round begin
        for (int i = 0; i < n; ++i) {
            Base* &ptr = baseptrArray[i];
            if (ptr->isAlive()) {
                ++cnt;
                if (cnt == 7) {
                    ptr->defend(true);
                    cnt = 0;
                } else ptr->defend(false);
            }
        }
        //round begin
        for (int i = 0; i < n; ++i) {
            Base* &ptr = baseptrArray[i];
            if (ptr->isAlive() && !ptr->isDefensive()){
                for (int j = 0; j < n; ++j) {
                    if (j != i && baseptrArray[j]->isAlive()) {
                        ptr->launch_attack(baseptrArray[j]);
                        break;
                    }
                }
            }
        }
    }
    std::cout << round << '\n';
    for (int i = 0; i < n; ++i) {
        delete baseptrArray[i];
    }
}
```

Role.hpp:

```cpp
#include<string>
#include<iostream>
#ifndef ROLE_HPP
#define ROLE_HPP
namespace final{
    
    class Fighter;
    class Protector;
    class Caster;

    //uncompleted, you should add code into this class
    class Base{
        friend class Fighter;
        friend class Protector;
        friend class Caster;
    private:
        //WARNING: NO OTHER MEMBER VARIABLE IS ALLOWED TO BE ADDED HERE.
        std::string name;
        int health,attack;
        bool alive,defensive;
        //you only need to define aliveNumber here.
    public:
        //WARNING: NO OTHER PUBLIC FUNCTION IS ALLOWED TO BE ADDED.
        //WARNING: THIS CLASS(Base) CAN NOT BE INSTANTIATED（实例化）.
        //WARNING: THE FUNCTION PROVIDED NEED NO MODIFICATION
        //the function you need to implement or define is as follows.
        //(1) getAliveNumber
        //(2) Constructor
        //(3) launch_attack
        //(4) defend
        bool isAlive(){
            return alive;
        }

        bool isDefensive(){
            return defensive;
        }
    };

    class Fighter:public Base{
    public:
        //WARNING: NO OTHER PUBLIC FUNCTION IS ALLOWED TO BE ADDED.
        //WARNING: THE FUNCTION PROVIDED NEED NO MODIFICATION
        Fighter (const std::string& name, const int health,const int attack):Base(name,health,attack){}

        void launch_attack(Base* target);

        void defend(bool flag){
            if (flag) {
                defensive = 1;
                health += 3;
                attack += 2;
            } else {
                defensive = 0;
            }
        }
    };

    class Protector:public Base{
    public:
        //WARNING: NO OTHER PUBLIC FUNCTION IS ALLOWED TO BE ADDED.
        //WARNING: THE FUNCTION PROVIDED NEED NO MODIFICATION
        Protector (const std::string& name, const int health,const int attack):Base(name,health,attack){}

        void launch_attack(Base* target);

        void defend(bool flag){
            if (flag) {
                defensive = 1;
                health += 7;
                attack += 1;
            } else {
                defensive = 0;
            }
        }
    };

    class Caster:public Base{
    public:
        //WARNING: NO OTHER PUBLIC FUNCTION IS ALLOWED TO BE ADDED.
        //WARNING: THE FUNCTION PROVIDED NEED NO MODIFICATION
        Caster (const std::string& name, const int health,const int attack):Base(name,health,attack){}

        void launch_attack(Base* target);

        void defend(bool flag){
            if (flag) {
                defensive = 1;
                health += 5;
            } else {
                defensive = 0;
            }
        }
    };

    void Fighter::launch_attack(Base *target) {
        //your code here
    }

    void Protector::launch_attack(Base *target) {
        //your code here
    }

    void Caster::launch_attack(Base *target) {
        //your code here
    }
}
#endif //ROLE_HPP

```

### Input Format

第一行，整数 n，表示初始化的角色总数。

2~n+1 行：每行为 `role name health attack`，`role`, `name` 为字符串，保证 `role` 与三个派生类名字之一相同。

### Output Format

按题面描述，输出战斗时信息。角色阵亡时需输出 `[role] [name] is killed\n`，`[role]` 同相应派生类名。

战斗模拟结束后，输出总的回合数。

### Samples

#### Sample 1

**Input:**
```
```
3
Protector Uther 100 2
Caster Giana 50 10
Fighter Malfurion 70 4
```
```

**Output:**
```
```
Protector Uther is killed
Caster Giana is killed
13
```

#### 注释

战斗过程细节：

```
round 1
Uther 76 2 isAlive
Giana 48 10 isAlive
Malfurion 70 4 isAlive
round 2
Uther 52 2 isAlive
Giana 46 10 isAlive
Malfurion 70 4 isAlive
round 3
Uther 41 3 isAlive
Giana 46 10 isAlive
Malfurion 67 4 isAlive
round 4
Uther 17 3 isAlive
Giana 43 10 isAlive
Malfurion 67 4 isAlive
round 5
Uther 3 3 isAlive
Giana 48 10 isAlive
Malfurion 67 4 isAlive
Protector Uther is killed
round 6
Uther -17 3 dead
Giana 37 10 isAlive
Malfurion 67 4 isAlive
round 7
Uther -17 3 dead
Giana 29 10 isAlive
Malfurion 57 4 isAlive
round 8
Uther -17 3 dead
Giana 34 10 isAlive
Malfurion 47 4 isAlive
round 9
Uther -17 3 dead
Giana 26 10 isAlive
Malfurion 37 4 isAlive
round 10
Uther -17 3 dead
Giana 18 10 isAlive
Malfurion 27 4 isAlive
round 11
Uther -17 3 dead
Giana 18 10 isAlive
Malfurion 26 6 isAlive
round 12
Uther -17 3 dead
Giana 6 10 isAlive
Malfurion 16 6 isAlive
Caster Giana is killed
round 13
Uther -17 3 dead
Giana -6 10 dead
Malfurion 6 6 isAlive
```
```

### Data Constraints

$2\le n,attack,health \le 1000$

$\mathit{length\\;of\\;name}\le 20$

|check point|数据特征|
|---|---|
|1~3|只有 Protector|
|4~6|只有 Fighter|
|7~9|只有 Caster|
|10~12|只有 Protector&Fighter|
|13~15|只有 Protector&Caster|
|16~18|只有 Fighter&Caster|
|19~21|全职业|
|22~42|内容同上述 1~21，检查内存泄漏，每点 1 分，共 21 分|

|check point % 3|考察限制|
|---|---|
|1|无 getAliveNumber() 调用|
|2|无 defend(true) 调用|
|0|不限制|

## Per-Testcase Resource Limits

- **Time Limit (per test case)**: 50000 ms
- **Memory Limit (per test case)**: 200 MiB
- **Disk Usage**: No disk usage is permitted.

## Test Data

The test data for this problem is located at `/workspace/data/046/data_test/`.

## Submission Requirements

### OJ Git Repository Compilation Process

For Git compilation, we will first clone the repository using a command similar to:
```bash
git clone <repo_url> . --depth 1 --recurse-submodules --shallow-submodules --no-local
```

Then we check if there is a `CMakeLists.txt` file. If it exists, we run (if not, a warning message will be displayed):
```bash
cmake .
```

Finally, we check if there is any of `GNUmakefile`/`makefile`/`Makefile` (if cmake was run previously, this will be the generated Makefile). If it exists, we run (if not, a warning message will be displayed):
```bash
make
```

After this process is complete, we will use the `code` file in the project root directory as the compilation result.

A `CMakeLists.txt` file is provided in the project. You can use or modify it as needed. The local environment has gcc-13 and g++-13 available.

### Git Configuration Requirements

**IMPORTANT**: You must create a `.gitignore` file in your project root directory to avoid OJ evaluation conflicts.

The `.gitignore` file should include at least the following entries:

```gitignore
CMakeFiles/
CMakeCache.txt
```

### Submission Guidelines

- The submitted code must be able to compile successfully through the above compilation process
- The compiled executable file name must be `code`
- The program needs to be able to read data from standard input and write results to standard output
- Please ensure the code runs correctly within the given time and space limits
- **You must use C++ or C language** to implement this assignment

### Evaluation Notes

- The evaluation system will test your program using the provided test data
- The program output must exactly match the expected output (including format)
- Exceeding time or memory limits will be judged as the corresponding error type
- Please pay attention to the overall time performance of your code and the time complexity of each part of your algorithm.

### Academic Integrity

If any violations are found during evaluation or code review (including but not limited to using unconventional methods to pass test cases), your final score may be significantly reduced or become **0 points**.
