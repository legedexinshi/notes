#AWK
####主体
	BEGIN {...}  
	/pattern/ {...}
	END {...}
####命令
	awk [options] file
	awk [options] -f command.awk file
####基础
$i 表示第i列  
$0 表示整行  
pattern 默认匹配  
action 默认 print  
下例输出长度大于18的行，length是内置函数

	awk 'length($0) > 18' marks.txt
####内置变量
ARGC => 命令行参数个数  
ARGV => 命令行数组  
ENVIRON => 环境变量  
FILENAME => 文件名  
NF => 域个数  
NR => 行数  
FNR => 当前文件行数  
OFS => 输出域分隔符，默认空格  
FS => 域分隔符，默认空格  
ORS => 输出记录分隔符，默认回车  
RS => 记录分隔符，默认回车
####正则表达式
. => 任意单字符  
^ => 行首  
$ => 行尾  
[ABC] => 匹配字符集  
[^ABC] => 不匹配字符集  
| => 逻辑或  
? => 零或1个字符  
* => 零或多个字符  
+ => 1或多个字符  
(aa|bb) => 匹配一个
####数组
arr[idx] = a   
delete arr[idx];
####控制语句
	if (cond)   
		{action}   
	else if (..)  
		{..}
		
	for (;;) {
	}
	
	whlie () {
	}
	
	break;
	continue;
	exit;
####函数
	function add(a, b) {
		return a+b;
	}
