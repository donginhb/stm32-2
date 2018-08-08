本实验将实现如下功能：开机的时候先检测是否有DS18B20存在，如果没有，则提示错误。只有在检测到DS18B20之后才开始读取温度并显示在LCD上，如果发现了DS18B20，则程序每隔200ms左右读取一次数据，并把温度显示在LCD上。同样我们也是用LED0来指示程序正在运行。

本实验可以SWD下载仿真.

               正点原子@ALIENTEK
               2011-1-1
	       购买：http://shop62103354.taobao.com
                     http://shop62057469.taobao.com
               技术支持论坛：www.openedv.com
           