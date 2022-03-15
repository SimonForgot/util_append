#switch gcc env
scl enable devtoolset-8 bash 
___________________________________________________________________________
包管理：
#yum install from specific rpm
yum --disablerepo="*" --enablerepo="<desired-repo-id>" install package-name

#rpm  通过包更新当前某软件
rpm -Uvh mypackage-<new-version>.rpm

#list available repo in yum
yum repolist

yum更改安装位置https://www.cnblogs.com/freeliver54/p/10021777.html
yum -c /etc/yum.conf --installroot=位置 --releasever=/  install 包名
该命令简单解释如下：

-c /etc/yum.conf                  表示指定yum配置文件地址

--installroot=/usr/local        表示指定自定义的安装目录


一个中间层类：所有的其他类成员都以它的成员的形式存放在其中，所以可以方便的管理内存排布，共享数据。
它可以通过重新布局内部成员来减少cache miss
(Data-oriented-Programming)


python中__init__.py意味着这是一个包，包里可以有其它模块和子包。有包才有A.B的用法，A为包名，B为模块名

请注意，每一个包目录下面都会有一个__init__.py的文件，这个文件是必须存在的，否则，Python就把这个目录当成普通目录，而不是一个包。__init__.py可以是空文件，也可以有Python代码，因为__init__.py本身就是一个模块，而它的模块名就是文件夹名

python里的from module import func并不是只看了func部分，而是把整个module执行了一遍，然后导入的名称

from pkg.module import func/var  同样也是在导入module的时候就会把它整个执行一遍

所以import的既可以是成员名变量/函数，也可以是module名

___________________________________
qtcreator当中在debug时,如果引用了外部的库文件,即使该库文件有debug信息,但是如果找不到h文件对应的cpp文件,仍然无法debug进去


可以手动修改时间！！！
touch -t 198901010000 hello.c


无法挂载服务器上的地址，使用sudo mount -a，就可以了，不用管报错
