###清空shell里已经输入的内容
`Ctrl+u`	

###设置若有命令返回非0值，程序直接停止
`set -e`
###shell script
`
if [[ $1 == -psn_0_* ]] ; then #参数
	shift			#所有参数左移
fi
`
###pushd和popd是对一个目录栈进行操作，而dirs是显示目录栈的内容。该栈结构的顶端永远都存放着当前目录。
```
pushd [dir_name] 入栈
pushd 交换栈顶两元素
pushd +/-n 切换到第n个目录(以栈循环的方式)

popd 删除栈顶dir
popd +/-n 删除正数或者倒数第n个dir

dirs -v 列出当前栈中dirs（带序号）
其他dirs使用当法看mannual吧～

pushd . &> /dev/null 将当前dir入栈，但是不输出栈信息，输出全部重定向到/dev/null。
```

###进程中止的方式
`ctrl-c`: ( kill foreground process ) 发送 SIGINT 信号给前台进程组中的所有进程，强制终止程序的执行；
`ctrl-z`: ( suspend foreground process ) 发送 SIGTSTP 信号给前台进程组中的所有进程，常用于挂起一个进程，而并非结束进程，用户可以使用使用fg/bg操作恢复执行前台或后台的进程。fg命令在前台恢复执行被挂起的进程，此时可以使用ctrl-z再次挂起该进程，bg命令在后台恢复执行被挂起的进程，而此时将无法使用ctrl-z再次挂起该进程；
一个比较常用的功能：
正在使用vi编辑一个文件时，需要执行shell命令查询一些需要的信息，可以使用ctrl-z挂起vi，等执行完shell命令后再使用fg恢复vi继续编辑你的文件（当然，也可以在vi中使用！command方式执行shell命令， 但是没有该方法方便）。
`ctrl-d`: ( Terminate input, or exit shell ) 一个特殊的二进制值，表示 EOF，作用相当于在终端中输入exit后回车；

####还有以下几个：
`ctrl-/`    发送 SIGQUIT 信号给前台进程组中的所有进程，终止前台进程并生成 core 文件
`ctrl-s`  中断控制台输出
`ctrl-q`   恢复控制台输出
`ctrl-l`    清屏

其实，控制字符都是可以通过stty命令更改的，可在终端中输入命令"stty -a"查看终端配置

