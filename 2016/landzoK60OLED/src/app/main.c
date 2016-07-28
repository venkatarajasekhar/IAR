/******************** (C) COPYRIGHT 2011 蓝宙电子工作室 ********************
 * 文件名       ：main.c
 * 描述         ：工程模版实验
 *
 * 实验平台     ：landzo电子开发版
 * 库版本       ：
 * 嵌入系统     ：
 *
 * 作者         ：landzo 蓝电子
 * 淘宝店       ：http://landzo.taobao.com/

**********************************************************************************/

#include "include.h"


/*************************
设置系统的全局变量
*************************/


extern  u8  LPT_INT_count ;
extern  u8  DMA_Over_Flg ;            //采集完成标志位
extern  u8  LinADCout ;

extern double pwm_gain_temp;
int count_sin=0;
int group_id=3;
int Power_Flag=1;

int pwm_duty=10;

int pwm_gain=12;

double U0_Correct=(36/33+1.65)/3.3*4095;

int pwm_freq=40000;
double pwm_gain_temp=10;


double Kp_u=38.0;
double Ki_u=1.0;
double f0_set=99.0;


double U0_present_value=51.0;
double I0_present_value=2.8;
double U2_present_value=67.9;

int U0_sample=0;
int I0_sample=0;

double U0_present_max=0;
double I0_present_max=0;

int U0_sample_max=0;
int I0_sample_max=0;

int start_flag=0;

double Voltage_Error[2]={0,0};



int modeflag=0;
int ftm_flag=0;
int PID_flag=0;
int Freq_change_flag=0;

char buf[20];


int data_sin_1[555]=
{
500,504,508,513,517,521,525,530,534,538,542,547,551,555,559,563,568,572,576,580,584,588,592,597,601,605,609,613,617,621,625,629,633,637,641,645,649,653,656,660,664,668,672,675,679,683,687,690,694,698,701,705,708,712,715,719,722,726,729,732,736,739,742,745,749,752,755,758,761,764,767,770,773,776,779,782,784,787,790,792,795,798,800,803,805,808,810,812,815,817,819,822,824,826,828,830,832,834,836,838,839,841,843,845,846,848,850,851,853,854,855,857,858,859,860,862,863,864,865,866,867,867,868,869,870,870,871,872,872,873,873,874,874,874,874,875,875,875,875,875,875,875,875,875,874,874,874,873,873,872,872,871,871,870,869,869,868,867,866,865,864,863,862,861,860,859,857,856,855,853,852,850,849,847,846,844,842,840,839,837,835,833,831,829,827,825,823,820,818,816,814,811,809,806,804,801,799,796,794,791,788,786,783,780,777,774,771,769,766,763,759,756,753,750,747,744,741,737,734,731,727,724,720,717,713,710,706,703,699,696,692,688,685,681,677,674,670,666,662,658,654,651,647,643,639,635,631,627,623,619,615,611,607,603,599,594,590,586,582,578,574,570,565,561,557,553,549,544,540,536,532,528,523,519,515,511,506,502,498,494,489,485,481,477,472,468,464,460,456,451,447,443,439,435,430,426,422,418,414,410,406,401,397,393,389,385,381,377,373,369,365,361,357,353,349,346,342,338,334,330,326,323,319,315,312,308,304,301,297,294,290,287,283,280,276,273,269,266,263,259,256,253,250,247,244,241,237,234,231,229,226,223,220,217,214,212,209,206,204,201,199,196,194,191,189,186,184,182,180,177,175,173,171,169,167,165,163,161,160,158,156,154,153,151,150,148,147,145,144,143,141,140,139,138,137,136,135,134,133,132,131,131,130,129,129,128,128,127,127,126,126,126,125,125,125,125,125,125,125,125,125,126,126,126,126,127,127,128,128,129,130,130,131,132,133,133,134,135,136,137,138,140,141,142,143,145,146,147,149,150,152,154,155,157,159,161,162,164,166,168,170,172,174,176,178,181,183,185,188,190,192,195,197,200,202,205,208,210,213,216,218,221,224,227,230,233,236,239,242,245,248,251,255,258,261,264,268,271,274,278,281,285,288,292,295,299,302,306,310,313,317,321,325,328,332,336,340,344,347,351,355,359,363,367,371,375,379,383,387,391,395,399,403,408,412,416,420,424,428,432,437,441,445,449,453,458,462,466,470,475,479,483,487,492,496

};
int data_sin_2[333]=
{
500,507,514,521,528,535,542,549,556,563,570,577,584,591,598,605,611,618,625,632,638,645,651,658,664,670,677,683,689,695,701,707,713,719,724,730,736,741,746,752,757,762,767,772,777,782,786,791,795,799,804,808,812,816,819,823,827,830,833,836,839,842,845,848,851,853,855,858,860,862,863,865,867,868,869,870,871,872,873,874,874,875,875,875,875,875,874,874,873,873,872,871,870,869,867,866,864,862,861,859,856,854,852,849,847,844,841,838,835,832,828,825,821,817,814,810,806,801,797,793,788,784,779,774,770,765,759,754,749,744,738,733,727,722,716,710,704,698,692,686,680,674,667,661,654,648,641,635,628,622,615,608,601,594,588,581,574,567,560,553,546,539,532,525,518,511,504,496,489,482,475,468,461,454,447,440,433,426,419,412,406,399,392,385,378,372,365,359,352,346,339,333,326,320,314,308,302,296,290,284,278,273,267,262,256,251,246,241,235,230,226,221,216,212,207,203,199,194,190,186,183,179,175,172,168,165,162,159,156,153,151,148,146,144,141,139,138,136,134,133,131,130,129,128,127,127,126,126,125,125,125,125,125,126,126,127,128,129,130,131,132,133,135,137,138,140,142,145,147,149,152,155,158,161,164,167,170,173,177,181,184,188,192,196,201,205,209,214,218,223,228,233,238,243,248,254,259,264,270,276,281,287,293,299,305,311,317,323,330,336,342,349,355,362,368,375,382,389,395,402,409,416,423,430,437,444,451,458,465,472,479,486,493

};
int data_sin_3[199]=
{
500,512,524,535,547,559,571,582,594,605,616,628,639,650,660,671,681,692,702,712,721,731,740,749,758,766,774,782,790,797,804,811,818,824,830,835,840,845,849,854,857,861,864,867,869,871,872,874,874,875,875,875,874,873,872,870,868,865,862,859,856,852,847,843,838,832,827,821,814,808,801,794,786,778,770,762,753,745,735,726,717,707,697,687,676,666,655,644,633,622,611,599,588,576,565,553,541,530,518,506,494,482,470,459,447,435,424,412,401,389,378,367,356,345,334,324,313,303,293,283,274,265,255,247,238,230,222,214,206,199,192,186,179,173,168,162,157,153,148,144,141,138,135,132,130,128,127,126,125,125,125,126,126,128,129,131,133,136,139,143,146,151,155,160,165,170,176,182,189,196,203,210,218,226,234,242,251,260,269,279,288,298,308,319,329,340,350,361,372,384,395,406,418,429,441,453,465,476,488

};

int test_sin[5]=
{
  100,300,500,100,900
};

extern u16  TimeCount ;
int PID=1;

void Pot_Show(int x,int y,double final_adc);
void OLED_Light();
void Refresh_Present();
void Refresh_Key();
void PID_control();
void Curent_PID();
void Voltage_PID();
void PWM_Control();



void main()
{
  DisableInterrupts;                             //禁止总中断

  /*********************************************************
  初始化程序
  *********************************************************/

   uart_init (UART0 , 115200);                      //初始化UART0，输出脚PTA15，输入脚PTA14，串口频率 9600
   
   Init_Key_Port();
   
  
   
   OLED_Init();
   gpio_init (PORTB ,5, GPO,LOW); //B5 低电平开启
   
   adc_init(ADC0, AD9);  //B1  I0
   adc_init(ADC0,AD12);  //B2  U0
   
   pit_init_us(PIT0, 300);                                    //初始化PIT0，定时时间为： 300us

   FTM_Input_init(FTM1,CH0,Rising);  //A8输入捕捉初始化
   
   FTM0_Init(40000 ,500);  //C3、C4初始化
   
   EnableInterrupts; //开总中断

   OLED_Light();
   
   
   /******************************************
    执行程序
    ******************************************/
    while(1)
    {
        Key_Event(); 
        if(PID_flag==1)
        {
            I0_present_max=I0_sample_max*3.3/4095;
            I0_present_max=(I0_present_max*3-2.5)/0.185;
            U0_present_max=U0_sample_max*3.3/4095;
            U0_present_max=(U0_present_max-1.65)*50/1.41;
            if(PID==1)
            {
              Voltage_PID();
            }
            
            
            U0_sample_max=0;
            I0_sample_max=0; 
            PID_flag=0;
        }
    }

}


void OLED_Light()
{
  OLED_Fill(0x00);  //液晶屏全黑
  Dly_ms(50);
  
  OLED_P6x8Str(0,0,"U0:");
  Pot_Show(20,0,U0_present_value);
  OLED_P6x8Str(65,0,"I0:");
  Pot_Show(85,0,I0_present_value);
  
  OLED_P6x8Str(0,1,"U2:");
  Pot_Show(20,1,U2_present_value);  
  
  OLED_P6x8Str(0,2,"f0:");
  Pot_Show(20,2,f0_set);  
  OLED_P6x8Str(65,2,"Pow:");
  Pot_Show(90,2,Power_Flag);
  
  
  OLED_P6x8Str(0,3,"Kp:");
  Pot_Show(20,3,Kp_u);
  
  OLED_P6x8Str(0,4,"Ki:");
  Pot_Show(20,4,Ki_u);
 
  OLED_P6x8Str(0,6,"gain:");
   Pot_Show(28,6,pwm_gain);
}


void Refresh_Key()
{

  Pot_Show(20,2,f0_set);  
  
  Pot_Show(20,3,Kp_u);
  
  Pot_Show(20,4,Ki_u);
  
  if(f0_set>=34 && f0_set<=60)
  {
    group_id=2;
    pwm_freq=(int)(2*333*f0_set);
  }
  else if(f0_set>=20 && f0_set<36)
  {
    group_id=1;
    pwm_freq=(int)(2*555*f0_set);
  }
  else if(f0_set>58 && f0_set<=100)
  {
    group_id=3;
    pwm_freq=(int)(2*199*f0_set);
  }
  
  FTM0_Freq_Change(pwm_freq);
  
}

void Refresh_Present()
{

   Pot_Show(90,2,Power_Flag);
  Pot_Show(20,0,U0_present_max);

  Pot_Show(85,0,I0_present_max);

  //Pot_Show(20,1,U2_present_value); 
  
  Pot_Show(28,6,pwm_gain_temp);
  
}



void Pot_Show(int x,int y,double final_adc)
{
  u8  adc_num[]="00.00" ;
  
  int int_adc_1=0;
  int int_adc_2=0;
  int pot_adc_1=0;
  int pot_adc_2=0;
  int adc_temp=0;
  
  adc_temp=final_adc*100;
  int_adc_1=adc_temp/1000;
  int_adc_2=adc_temp/100-int_adc_1*10;
  pot_adc_1=adc_temp/10-int_adc_1*100-int_adc_2*10;
  pot_adc_2=adc_temp-int_adc_1*1000-int_adc_2*100-pot_adc_1*10;
        
  sprintf(adc_num, "%d%d.%d%d",int_adc_1,int_adc_2,pot_adc_1,pot_adc_2); 
  
  OLED_P6x8Str(x,y,adc_num);  
}


void PID_control()
{
  
}


void Voltage_PID()
{
  Voltage_Error[1]=Voltage_Error[0];
  Voltage_Error[0]=55-U0_present_max;
  
  pwm_gain_temp=(Voltage_Error[0]-Voltage_Error[1])*Kp_u/100+Voltage_Error[0]*Ki_u+pwm_gain_temp;
  
  if(pwm_gain_temp>=12) pwm_gain_temp=12;
  if(pwm_gain_temp<=8) pwm_gain_temp=8;
  
  //pwm_gain=pwm_gain_temp;
}


void PWM_Control()
{  
  if(start_flag==1)
  {
    if(group_id==1)
    {
      if(count_sin>554)
      {
        count_sin=0;
        PID_flag=1;
      }
      pwm_duty=pwm_gain*data_sin_1[count_sin]/10;
      if(pwm_duty>=1000)
      {
        pwm_duty=999;
      }
      FTM0_Duty_Change(pwm_duty);
      count_sin++;
    }
    
    if(group_id==2)
    {
      if(count_sin>332)
      {
        count_sin=0;
        PID_flag=1;
      }
      pwm_duty=pwm_gain*data_sin_2[count_sin]/10;
      if(pwm_duty>=1000)
      {
        pwm_duty=999;
      }
      FTM0_Duty_Change(pwm_duty);
      count_sin++;
    }
  
    if(group_id==3)
    {
      if(count_sin>198)
      {
        count_sin=0;
        PID_flag=1; 
      }
      pwm_duty=pwm_gain*data_sin_3[count_sin]/10;
      if(pwm_duty>=1000)
      {
        pwm_duty=999;
      }
      FTM0_Duty_Change(pwm_duty);
      count_sin++;
    }
    
    
  }
      
}

