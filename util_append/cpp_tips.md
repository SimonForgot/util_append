当在C++中使用C库时，要extern “C” 然后再include对应的C头文件，因为C库中的符号命名和C++的不一样（C++有重载）。

template头文件和cpp文件不能分离的原因是，如果这样做的话，cpp文件不知道它会被怎样使用，编译好的目标文件里面就没有具体的可以拿来用的实例化好的函数或者类。这时其他cpp文件想用的话，即使include了头文件，也会找不到实例化的符号。
______________________________________________________________________________________
typedef void (*fun)(int *node);
typedef const int* cip;
typedef的语法，就像声明一个普通的变量一样，只是把变量名替换成自己新起的名字。
还是using直观一些

#pragma pack (n)             作用：C编译器将按照n个字节对齐。
#pragma pack ()               作用：取消自定义字节对齐方式。

#pragma pack (push,1)     作用：是指把原来对齐方式设置压栈，并设新的对齐方式设置为一个字节对齐
#pragma pack(pop)            作用：恢复对齐状态

注：若不用#pragma pack(1)和#pragma pack()括起来，则sample按编译器默认方式对齐（成员中size最大的那个）。即按8字节（double）对齐，则sizeof(sample)==16.成员char a占了8个字节（其中7个是空字节）；若用#pragma pack(1)，则sample按1字节方式对齐sizeof(sample)＝＝9.（无空字节），比较节省空间啦，有些场和还可使结构体更易于控制。

1.第一个成员在结构体变量偏移量为0 的地址处，也就是第一个成员必须从头开始。
2.其他成员变量要对齐到某个数字（对齐数）的整数倍的地址处。对齐数 为编译器默认的一个对齐数与该成员大小中的较小值。mac 64位系统下默认应该是8字节（当然可以通过#pragma pack（）修改），但修改只能设置成1，2，4，8，16.
3.结构体总大小为最大对齐数的整数倍。（每个成员变量都有自己的对齐数）
4.如果嵌套结构体，嵌套的结构体的对齐数就是自己的最大对齐数，结构体的整体大小就是所有最大对齐数（包含嵌套结构体的对齐数）的整数倍。
https://juejin.cn/post/6844904025888931847
————————————————————————————————————————————————————————————————————————————————————————
_Pragma("message(\"_X86 macro activated !\")")等价于#pragma message("_X86 macro activated !")
—————————————————————————————————————————————————————————————————————————————————————————————
可见性设置：
-fvisibility=XXX 总体的可见性设置
__attribute__((visibility("default")))可用于具体的函数，变量，类,命名空间（linux only），可以覆盖掉上一条的总体的设置

[这项机制的价值在于它可以在不修改代码的前提下，尝试性的修改可见性，而不需要给代码加匿名namespace...]

cortex采用了这种方式，但是我看在gaffer里面，大量使用的是匿名namespace！第三方库也是直接用的，没有push，pop。
成片的设置可见性，可用于解决gnu和clang下，在第三方库的基础上写新库时，第三方库没有显式设置可见性导致的新库可见性也受到牵连。[这个设置相当于手动给这个header加-fvisibility=default]
#ifdef __GNUC__
#define IECORE_PUSH_DEFAULT_VISIBILITY _Pragma( "GCC visibility push(default)" )
#define IECORE_POP_DEFAULT_VISIBILITY _Pragma( "GCC visibility pop" )
#else
#define IECORE_PUSH_DEFAULT_VISIBILITY
#define IECORE_POP_DEFAULT_VISIBILITY
#endif
__________________________________________________________________
cortex的Refounted头文件boost::intrusive_ptr的宏声明有问题，boost::intrusive_ptr根本没有多个模板关键字的版本，只有一个的。
——————————————————————————————————————————————————————————————————————————————————————————
因为这个头文件既要被定义该函数的dll包含，也要被使用该函数的程序包含，当被前者包含时我们希望使用__declspec(dllexport)定义函数，当被后者包含时我们希望使用dllimport。于是我们使用
#ifdef _EXPORTING
#define CLASS_DECLSPEC __declspec(dllexport)
#else
#define CLASS_DECLSPEC __declspec(dllimport)
#endif
这种技巧，在定义该函数的dll中，其编译选项定义了_EXPORTING而使用该函数的程序则没有定义。
同理，在IECORE export.h中有：
#ifdef IECore_EXPORTS
	#define IECORE_API IECORE_EXPORT
#else
	#define IECORE_API IECORE_IMPORT
#endif
_____________________________________________________________________________________________
构造函数加explicit避免隐式转换(单参数多参数都适用)
类型转换https://zhuanlan.zhihu.com/p/27966225
当一个类没有定义构造函数，且所有成员都有无参构造函数时，编译器会自动生成一个无参构造函数，他会调用每个成员的无参构造函数（也就是说如果类中有成员没有默认构造函数，则该类也没有默认构造函数）

使用如下方式，进行默认构造函数的初始化，很方便：
class son
{
public:
    int a, b;
    son(int _a, int _b) : a(_b), b(_a) {}
};

class CC
{
public:
    int x{1}, y{2};
    son s{8, 9};
};

int main()
{
    CC c;
    std::cout << c.s.a << c.s.b;
    return 0;
}

###我觉得，编程语言这种东西就是用来解决编写汇编语言的复杂度问题的。目的是Make Life Easy
C++在解决该问题方面的态度是：向程序员尽可能提供全面的，具有【自行定制功能】的语言特性，用来作为连接底层机器和顶层试图MLE的程序员的桥梁。其他语言也类似，只是程度和方式不同。
MLE在coding的精髓就是重用，重用过程（函数），重用代码（template，micro），重用定义（库）
比如它继承了来自C语言的function功能，function解决重复使用代码。
面向对象则也是可以大量重用代码，比如子类可以继承使用父类的变量和函数定义。
重用往往意味着抽象，C++试图做到零代价抽象的，所以才需要库作者来照顾和付出众多的抽象的代价。

————————————————————————————————————————————————————————————————————————————————————————————————————
inline的目前含义是声明为weak符号

意思是，如果有其他同名符号，则weak符号的定义会被同名符号覆盖
（from小彭老师，他也没有指出C++11和17之间的变迁【看来，C++语言的含义只能信cppreference】）

###class的static成员可以看作是抽象出的type的数据的重复共享部分（交集）。
我认为他非常适合跟多线程一起使用，共享的那部分如果是指针的话，可以想象成类似钥匙，令牌一样的资源

在不考虑访问权限关键字的情况下，继承就是“is-a”关系，所以 “B继承A” 表示的就是 “B是一个A”加上访问关键字就是在继承的基础上增加访问限制：
public：所有人都知道 “B是一个A”，B对外界提供了A提供的所有方法
protected：只有继承B的人才知道 “B是一个A”，除了继承B的人，其他人无法通过B调用A提供的方法
private：只有B自己知道 “B是一个A”，外界无法通过B调用A提供的方法

protected:对外隐藏，private:对外隐藏+对子类隐藏。大多数情况下，其实要的是对外隐藏，不需要对子类隐藏。继承和重载是群众喜闻乐见的两大狗皮膏药，优先用private，是给群众和自己造成不便

###static void *operator new(size_t s)
operator new也是类的static成员函数


