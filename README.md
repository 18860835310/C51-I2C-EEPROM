# C51-I2C-EEPROM
利用IIC通信协议与EEPROM进行通信，实现写、读操作

四个按键负责输入，动态数码管负责输出，iic半双工负责读写EEPROM内部的数据。
1.四个按键：
key1负责将当前数码显示的数字写入EEPROM内。
key2负责读取EEPROM内的数据，并在数码管上显示出来。
key3按下一次则增加当前数码管数字，增加一位。
key4清空当前的数字为0。

# 公共函数文件Public
定义公共所需的延时、变量简写宏定义
```c
//详见文件Public.c与Public.h
```
# 按键扫描文件key
扫描并返回当前按下的按键
```c
//详见key.c与key.h
```
# 数码管显示模块smg
扫描并返回当前按下的按键
```c
//详见smg.c与smg.h
```
# iic通信协议与函数

## 起始信号 *iic_start()*
在SCL为高电平时，SDA产生一个下降沿即为开始。
在SCL为高电平时，SDA产生一个上降沿即为结束。
![Loading](I2C-EEPROM实验/image/(2)起始和停止信号.png "起始和停止信号")









