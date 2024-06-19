#include "public.h"
#include "24c02.h"
#include "key.h"
#include "smg.h"


#define EEPROM_ADDRESS	0	//定义数据存入EEPROM的起始地址


void main()
{
	
	u8 key_temp = 0;
	u8 save_value = 0;
	
	while(1)
	{
		key_temp = key_scan(0);
		if(key_temp == 1)
		{
			at24c02_write_one_byte(EEPROM_ADDRESS,save_value);
		}
		else if(key_temp == 2)
		{
			save_value=at24c02_read_one_byte(EEPROM_ADDRESS);
		}
		else if(key_temp == 3)
		{
			save_value++;
			if(save_value==255)save_value=255;
		}
		else if(key_temp == 4)
		{
			save_value=0;	
		}
		
		smg(save_value);
	}
}


