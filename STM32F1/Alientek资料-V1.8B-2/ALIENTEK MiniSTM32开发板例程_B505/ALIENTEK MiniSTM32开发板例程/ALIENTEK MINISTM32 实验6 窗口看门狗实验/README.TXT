本实验将实现如下功能：程序一运行则开启WWDG,并使得DS0亮300ms后关闭，进入死循环。等待WWDG中断的到来，在中断里面，喂狗，并执行DS1的翻转操作。所以可以看到DS1不停的闪烁，而DS0只在刚启动的时候闪一下。 

该代码可以JTAG(SWD)下载,但是不支持仿真(仿真的时候，并没有停止WWDG的时钟，所以可能导致WWDG复位). 


               正点原子@ALIENTEK
               2010-12-29
	       购买：http://shop62103354.taobao.com
                     http://shop62057469.taobao.com
               技术支持论坛：www.openedv.com