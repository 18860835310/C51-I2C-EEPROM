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

## 起始与结束信号 *iic_start()* 、 *iic_stop()*
在SCL为高电平时，SDA产生一个下降沿即为开始。
在SCL为高电平时，SDA产生一个上降沿即为结束。
![Loading](I2C-EEPROM实验/image/(2)起始和停止信号.png "起始和停止信号")
```c
void iic_start(void)
{
	IIC_SDA=1;//如果把该条语句放在SCL后面，第二次读写会出现问题
	delay_10us(1);
	IIC_SCL=1;
	delay_10us(1);
	IIC_SDA=0;	//当SCL为高电平时，SDA由高变为低
	delay_10us(1);
	IIC_SCL=0;//钳住I2C总线，准备发送或接收数据
	delay_10us(1);
}
```

```c
void iic_stop(void)
{	
	IIC_SDA=0;//如果把该条语句放在SCL后面，第二次读写会出现问题
	delay_10us(1);
	IIC_SCL=1;
	delay_10us(1);
	IIC_SDA=1;	//当SCL为高电平时，SDA由低变为高
	delay_10us(1);			
}
```

## 应答响应与非应答

![Loading](I2C-EEPROM实验/image/(3)应答响应.png "应答响应与非应答")

```c
void iic_ack(void)
{
	IIC_SCL=0;
	IIC_SDA=0;	//SDA为低电平
	delay_10us(1);
  IIC_SCL=1;
	delay_10us(1);
	IIC_SCL=0;
}
```

```c
void iic_nack(void)
{
	IIC_SCL=0;
	IIC_SDA=1;	//SDA为高电平
	delay_10us(1);
  IIC_SCL=1;
	delay_10us(1);
	IIC_SCL=0;	
}
```

## 等待应答
```c
u8 iic_wait_ack(void)
{
	u8 time_temp=0;
	
	IIC_SCL=1;
	delay_10us(1);
	while(IIC_SDA)	//等待SDA为低电平
	{
		time_temp++;
		if(time_temp>100)//超时则强制结束IIC通信
		{	
			iic_stop();
			return 1;	
		}			
	}
	IIC_SCL=0;
	return 0;	
}
```

## 读/写函数

### 写入函数
![Loading](I2C-EEPROM实验/image/(6)数据传输a.png "向EEPROM写数据")
```c
void iic_write_byte(u8 dat)
{                        
    u8 i=0; 
	   	    
    IIC_SCL=0;
    for(i=0;i<8;i++)	//循环8次将一个字节传出，先传高再传低位
    {              
			if((dat&0x80)>0) 
				IIC_SDA=1;
			else
				IIC_SDA=0;
			dat<<=1; 	  
			delay_10us(1);  
			IIC_SCL=1;
			delay_10us(1); 
			IIC_SCL=0;	
			delay_10us(1);
    }	 
}
```

### 读取函数
![Loading](I2C-EEPROM实验/image/(6)数据传输b.png "从EEPROM读取数据")
```c
u8 iic_read_byte(u8 ack)
{
	u8 i=0,receive=0;
   	
    for(i=0;i<8;i++ )	//循环8次将一个字节读出，先读高再传低位
		{
        IIC_SCL=0; 
        delay_10us(1);
				IIC_SCL=1;
        receive<<=1;
        if(IIC_SDA)receive++;   
				delay_10us(1); 
    }					 
    if (!ack)
        iic_nack();
    else
        iic_ack();  
		  
    return receive;
}
```










