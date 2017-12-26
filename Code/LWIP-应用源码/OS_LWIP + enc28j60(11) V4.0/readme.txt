1、该例程为RTC例程。

2、使用说明
    (1)工程文件路径：例程目录\USART+RTC\MDK-ARM\Project.uvproj
	(2)请将串口线(直连串口线)插在板子COM1口及电脑机箱，并打开超级终端或串口助手，配置波特率115200，8位，一个停止位，无校验位。
	(3)请使用MDK 4.0以上版本打开,MDK版本过低会导致无法识别工程。
    (4)使用调试工具为ULINK
	(5)HEX文件下载到板子里后，串口将打印一些信息，表明例程运行成功，打印信息如下：
	 **************************************************************
 	 *                                                            *
 	 *   Thank you for using Multi Media Development Board！^_^   *
 	 *                                                            *
 	 **************************************************************
  	 =======================Time Settings==========================
	 Please Set Years between 1970 to 2037 
 	 Please Set Months between 1 to 12
	 Please Set Days between 1 to 31
     Please Set Hours between 1 to 23
     Please Set Minutes between 1 to 59
     Please Set Seconds between 1 to 59

	 若拿掉纽扣电池，则会提示进行时间设置。

3、注意事项
	请务必在下载、调试、运行过程中，保持板子上电、ULINK连接并插在电脑机箱上。
