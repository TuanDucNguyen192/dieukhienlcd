#include <regx52.h>
//------------Khoi tao bien va cac gia tri gan-------------//
sbit RS_LCD = P2^5;
sbit RW_LCD = P2^6;
sbit E_LCD = P2^7;
sbit qn = P3^2;
sbit qt = P3^3;
sbit tt = P3^4;
sbit gt = P3^5;
sbit stop  = P3^6;
sbit start = P3^7;  

unsigned char M[] = {0,0x0c,0x04,0x06,0x02,0x03,0x01,0x09,0x08};
unsigned int v,vt,d1,d0;
unsigned char a,i,n,j,xungdelay,h; 

//-------------------------

 void delay_short()
{
unsigned int x;
for(x=0;x<10;x++);
}//--------------****------------------//
void delay(unsigned int time) 
{
unsigned int q;
unsigned char e;
for (q=1; q<=time; q++)
{
for (e=1; e<=150; e++)
{;}
}
}
//các ham lcd
//----Ham kiem tra co ban-----
void kt_ban()
{
unsigned char x;
P0 = 0xff;
RS_LCD = 0;
RW_LCD = 1;
do
{
E_LCD = 1;
delay(3);
E_LCD = 0;
x=P0;
x=x&0x80;
}
while(x!=0x80);
}
//---Ham ghi lenh giao tiep voi LCD---//
void ghi_lenh(unsigned char lenh)
{
kt_ban();
delay(50);
P0 = lenh;
RS_LCD = 0; // Chon thanh ghi lenh
RW_LCD = 0; // Chon che do ghi du lieu tu 8051 vao LCD
E_LCD = 1;
delay_short();
E_LCD = 0;
}
//---Ham ghi ky tu ra LCD---//
void ghi_kytu(unsigned char kytu)
{
kt_ban();
delay(50);
P0 = kytu;
RS_LCD = 1; // Chon che do doc du lieu tu 8051
RW_LCD = 0;
E_LCD =1;
delay_short();
E_LCD = 0;
}
//---Ham ghi nhanh ky tu ra LCD---//
void ghi_nhanh ( unsigned char kytu)
{
kt_ban();
P0 = kytu;
RS_LCD = 1;
RW_LCD = 0;
E_LCD = 1;
delay_short();
E_LCD = 0;
}
//---Ham ghi chuoi ky tu ra LCD----//
void ghi_chuoi(char *str)
{
while(*str)
{  
ghi_kytu(*str);
str++;
}
}
void ghi_chuoi1(char *str)
{
while(*str)
{  
ghi_kytu(*str);
str++;
ghi_lenh(0x07);
}
}
//---Ham ghi nhanh chuoi ky tu ra LCD---//
void ghi_nhanh_chuoi(char *str)
{
while(*str){
ghi_nhanh(*str);
str++;
}
}
//---Ham ghi so nguyen ra LCD---//
void hienthiso(unsigned char n){
int  c1, d1;  
c1=n/10; n=n-c1*10;
d1=n;
ghi_lenh(0xc0);
//ghi_lenh(0x0c);
if((a<1)||(a>2)||(h==1)) ghi_nhanh_chuoi(" STOP -> START!");
else{
if(a==1)ghi_nhanh_chuoi("QT : ");
else if(a==2) ghi_nhanh_chuoi("QN : ");
if(c1!=0) ghi_nhanh(c1+48); // Doi ra hang chuc, ma ascii
ghi_nhanh(d1+48); // Doi ra hang don vi, ma ascii
ghi_nhanh_chuoi(" V/Phut  ");
}
}
//---Ham khoi tao LCD---//
void setting_LCD()
{
ghi_lenh(0x38);
ghi_lenh(0x01); // Xoa man hinh
ghi_lenh(0x0f); // Co dich hien thi
}
//ham gioi thieu
void gioi_thieu()
{ 
ghi_lenh(0x01);
ghi_lenh(0x0c);
ghi_chuoi("MACH DIEU KHIEN   ");
delay(300);
ghi_lenh(0xC0);
ghi_lenh(0x0c);
ghi_chuoi("DONG CO BUOC ");
ghi_lenh(0xC0);
ghi_lenh(0x0c);
ghi_chuoi("    VDK 8051    ");
delay(2000);
delay(2000);
ghi_lenh(0x01);
ghi_lenh(0x0c);
ghi_chuoi(" START ");
delay(2000);
}
//--------------------------

//-------------------------
//---Ham tre khoang thoi gian rat ngan phuc vu viec kiem tr co ban---//

void khoitao(void){// Ham khoi tao
TMOD=0x01; 
IE=0x82;         //chon timer0
TH1=0x3c; 
TL1=0xb0; 
TH0=0xfc; 
TL0=0x18; 
    TR1=1;                       //khoi dong timer1
TR0=1;      
n=0;
   

}//----------------------------------------//


void ktphim()
{
if(tt==0)
{ while (tt==0) {;}
if(vt>=15) vt=15;
else vt++;
if(xungdelay<2) xungdelay=1;
else xungdelay=xungdelay-1;
}
if(gt==0)
{ while (gt==0) {;}
if(vt<=1) vt=1;
else vt--;
if( xungdelay>=16) xungdelay=16;
else xungdelay=xungdelay+1;
}
if(qt==0)
if(a==3) {a=1; h=1;}
else a=1;
if(qn==0)
if(a==3) {a=2; h=1;}
else a=2;
if(stop==0) a=3;
if(start==0)
{
vt=8;
if(a==3) a=1;
h=0;
xungdelay=8;
}
}
void  dich()
{
if((a==1)&&(h==0)) i++;
if((a==2)&&(h==0))i--;
if(i==9) i=1;
if(i==0) i=8;
P1 = M[i];
}  

void main()
{
P1=0;
khoitao();
setting_LCD();
gioi_thieu();
ghi_lenh(0x01);
ghi_lenh(0x0c);
ghi_chuoi("TOC DO HIEN TAI:");
xungdelay=8;
 d0=0;
 a=3;
while(1)
{
ktphim();
P1 = M[i];
ghi_lenh(0xc0);
hienthiso(vt);
}
 
} 
void timer0(void) interrupt 1
{
TR0=0;
d0=d0+1;
if(d0==xungdelay)  
{
P3_1=P3_1 ^1;
    d0=0;
dich();        
    }
if(d0>18) d0=0;
TL0=0x18;               
    TH0=0xfc;               
   TR0=1;   
}

