默认情况下：字符集为abc（改main的chs可以更改字符集），*表闭包，|表选择。

直接输入正则表达式如：abca*(b|c)*a((a|b)*b|c*)

会输出NFA的各状态的情况

最后会输出DFA的转移函数矩阵