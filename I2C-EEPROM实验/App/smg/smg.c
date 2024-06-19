#include "smg.h"
#include "public.h"

//�������������ʾ0~F�Ķ�������
u8 gsmg_code[17]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,
				0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71};

void smg_display(u8 w , u8 n)
{
		switch(w)//λѡ
	{
		case 0: LSC=1;LSB=1;LSA=1;break;
		case 1: LSC=1;LSB=1;LSA=0;break;
		case 2: LSC=1;LSB=0;LSA=1;break;
		case 3: LSC=1;LSB=0;LSA=0;break;
		case 4: LSC=0;LSB=1;LSA=1;break;
		case 5: LSC=0;LSB=1;LSA=0;break;
		case 6: LSC=0;LSB=0;LSA=1;break;
		case 7: LSC=0;LSB=0;LSA=0;break;
	}
	SMG_A_DP_PORT=gsmg_code[n];//���Ͷ�ѡ����
	delay_10us(100);//��ʱһ��ʱ�䣬�ȴ���ʾ�ȶ�
	SMG_A_DP_PORT=0x00;//����
}

void smg(u8  num)
{
    int i=0;
    for (i = 0; i < 10; i++) // ͨ��ѭ��ˢ����ʾ
	  { 
        smg_display( 7 , num % 10);
        smg_display( 6 , (num % 100) / 10);
        smg_display( 5 , (num % 1000) / 100);
    }
}
