本实验将实现如下功能：开机的时候先检测W25X16中是否已经存在字库，如果存在，则按次序显示汉字。如果没有，则检测SD卡和文件系统，并查找SYSTEM文件夹下的FONT文件夹，在该文件夹内查找UNI2GBK.SYS和GBK16.FON（这两个文件是由我们自己生成的UNICODE转GBK码表文件和GBK字库（16*16）文件）。在检测到这些文件之后，就开始更新字库，更新完毕才开始显示汉字。同样我们也是用LED0来指示程序正在运行。
 
本实验可以SWD下载仿真.

               正点原子@ALIENTEK
               2011-1-1
	       购买：http://shop62103354.taobao.com
                     http://shop62057469.taobao.com
               技术支持论坛：www.openedv.com
           