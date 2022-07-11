/*
 * GccApplication3.cpp
 *
 * Created: 7/3/2022 7:18:28 PM
 * Author : ali
 */ 

#include <avr/io.h>

#include <avr/interrupt.h>

#define F_CPU 16000000	
void delay(int ms );
void delay(int ms );
void Lcd_init();
void write_char1(char c);
void write_char2(char c);
void movto(int r,int col);
void write_String1(char* s);
void write_String2(char* s);
void clear_screen();
void func3(char* a);
char s1='0';
char s2='0';
char m1='0';
char m2='0';
char h1='0';
char h2='0';
char ts1='0';
char ts2='0';
char tm1='0';
char tm2='0';
char th1='0';
char th2='0';
char* tmp;
bool edit=false;
bool t_active=true;
char* Tm="  ";
bool mode_24=true;
int ms;
	void func2(char* a,char *b,char c,char d,char e){
		if(*a == c){
			*a='0';
			*b=++*b;
			
			
		}
		if(*a==d){
			--*b;
			*a=e;
			
			
		}
	}

class ScrollMenu{
	public:
	char* title;
	char* clear;
	char** Options;
	int l=0;
	int selected =0;
	
	void next(){
		selected=(selected+1)%(l-2);
	}
	void back(){
		
		selected=(selected-1)%(l-2);
		
	}
	

	
	 ScrollMenu(char** op,int L){
		l=L;
		title=*op;
		clear=*(op+1);
		char *tmp[L-2];
		for(int i=0;i<L-2;i++){
		*(tmp+i)=*(op+i+2);
		
		}
	  Options=tmp;
		
	}
	void display(){
		movto(1,20);
		write_String1(title);
		movto(2,20);
		
			write_String1(*(Options+selected%(l-2)));
		
		movto(3,20);
		
		write_String2(*(Options+(selected+1)%(l-2)));
	}
	
};
ISR(TIMER2_OVF_vect){
	ms++;
	if(ms==3000){
		s1++;
		if(t_active){
			
			if(th2 =='0'&&th1=='0'&&tm2=='0'&&tm1=='0'&&ts2=='0'&&ts1=='0'){
				t_active=0;
			}  else {
				ts1--;
			}                             
		}
		TCNT2 = 0;
	ms=0;
	}
}

int main(void)
{
	int selected_menu=0;
	char* menu0="press to enter menu";
	TCNT2 = 0; 
	TCCR2A = 0x00; 
	TCCR2B = 0x01;
	TIMSK2 = 0x01;
	sei();

	char * menu1[]={"       Menu1       ","                    ","      Set time      "," Set stopwatch time ","      Settings      ","       Exit         "};
	char * menu2[]={"       Menu2       ","                    ","      Set hour      ","     Set minute     ","     Set second     ","       Exit         "};
	char * menu3[]={"       Menu3       ","                    ","      Set hour      ","     Set minute     ","     Set second     ","       Exit         "};
	char * menu4[]={"       Menu4       ","                    "," Select 12 display  "," Select 24 display  ","       Exit         "};
	ScrollMenu Menu1(menu1,6);
	ScrollMenu Menu2(menu2,6);
	ScrollMenu Menu3(menu3,6);
	ScrollMenu Menu4(menu4,5);
	PORTB = 0x00;
	DDRD= 0xff;
	DDRB = 0x00;
	DDRC = 0x07;
	
	delay(40);
	Lcd_init();
	

	 
while(true){
func2(&s1,&s2,':','/','9');
func2(&s2,&m1,'6','/','5');
func2(&m1,&m2,':','/','9');
func2(&m2,&h1,'6','/','5');

func2(&ts1,&ts2,':','/','9');
func2(&ts2,&tm1,'6','/','5');
func2(&tm1,&tm2,':','/','9');
func2(&tm2,&th1,'6','/','5');
func2(&th1,&th2,':','/','9');

if(th2==':'){
	th2='0';
	
}
if(h1==':'){
h1='0';
h2++;
}	
	if((h1=='/'&& h2 =='1') ||(h1=='/'&& h2 =='2')){
		h2--;
		h1='9';
	}
	if(h1=='/'&& h2 =='0'){
	h2--;
	h1='3';
}
	if(h2=='/'){
		
		h2='2';
	}

	
if(h2=='2'&& h1=='4'){
	
	h1='0';
	h2='0';
	
}


	movto(1,0);
	write_char1(th2);
	write_char1(th1);
	write_char1(':');
	write_char1(tm2);
	write_char1(tm1);
	write_char1(':');
	write_char1(ts2);
	write_char1(ts1);
	
	
	movto(2,0);
	if(mode_24){
		write_char1(h2);
		write_char1(h1);
	}else{
		if(h1=='0'&&h2=='0'){
			write_char1('1');
			write_char1('2');
			Tm="PM";
			
		}
			
		else if(h1>'2'&&h2>'0'){
		write_char1(h2-1);
		write_char1(h1-2);	
		Tm="PM";
			
		}
		else{
			write_char1(h2);
			write_char1(h1);
			Tm="AM";
		}
	
	}
	write_char1(':');
	write_char1(m2);
	write_char1(m1);
	write_char1(':');
	write_char1(s2);
	write_char1(s1);
	write_String1(Tm);
	
	
if(selected_menu==0 && !edit){
	movto(1,20);
	write_String1(menu0);
	movto(2,20);
	write_String1("                    ");
	movto(3,20);
	write_String2("                    ");
	
	if(PINB==0x06){
		th2='0';
		th1='0';
		tm2='0';
		tm1='0';
		ts2='0';
		ts1='0';
		t_active=false;
		
	}
	if(PINB==0x04){
		t_active=0;
		
		delay(500);
	}
     if(PINB==0x02){
		t_active=1;
		
		delay(500);
	}
	if(PINB==0x01){
		selected_menu=1;
		
		delay(500);
	}
			
	
}else if (selected_menu==1&& !edit){
Menu1.display();
if(PINB==0x01){
	switch(Menu1.selected){
		case 0:
		selected_menu= 2;
		break;
		case 1:
		selected_menu= 3;
		break;
		case 2:
		selected_menu= 4;
		break;
		case 3:
		selected_menu= 0;
		break;
	}
	
	delay(500);
}
if(PINB==0x02){
	Menu1.next();
	
	delay(500);
}
if(PINB==0x04){
Menu1.back();

delay(500);
}

}else if(selected_menu==2 && !edit){
Menu2.display();
if(PINB==0x01){
	switch(Menu2.selected){
		case 0:
		edit=true;
		tmp=&h1;
		break;
		case 1:
		edit=true;
		tmp=&m1;
		break;
		case 2:
		edit=true;
		tmp=&s1;
		break;
		case 3:
		selected_menu= 0;
		break;
	}
	
	delay(500);
}
if(PINB==0x02){
	Menu2.next();
	
	delay(500);
}
if(PINB==0x04){
Menu2.back();

delay(500);
}

}else if(selected_menu==3 && !edit){
Menu3.display();
if(PINB==1){
		switch(Menu3.selected){
			case 0:
			edit=true;
			tmp=&th1;
			break;
			case 1:
			edit=true;
			tmp=&tm1;
			break;
			case 2:
			edit=true;
			tmp=&ts1;
			break;
			case 3:
			selected_menu= 0;
			break;
		}
		delay(500);
}
if(PINB==0x02){
	Menu3.next();
	delay(500);
}
if(PINB==0x04){
Menu3.back();
delay(500);
}

}else if(selected_menu==4 && !edit ){
Menu4.display();
if(PINB==0x01){
		switch(Menu4.selected){
			case 0:
			mode_24=false;
			break;
			case 1:
			mode_24=true;
			break;
			case 2:
			selected_menu= 0;
			break;
			
		}
		delay(500);
	
}
if(PINB==0x02){
	Menu4.next();
	delay(500);
}
if(PINB==0x04){
	Menu4.back();
	delay(500);
}

}else if(edit){
	func3(tmp);
}


}

    
	
	
}


void func3(char* a){
	if(PINB==0x02){
		++*a;
		delay(500);
	}else if(PINB==0x04){
		--*a;
		delay(500);
	}else if(PINB==0x01){
		edit^=edit;
		t_active^=1;
		delay(500);
	}
	
}




void delay(int ms ){
	
	TCNT0 = 0x00;  		
	TCCR0A = 0x01;  		
	int tmp=ms*62;
	
	while(tmp!=0){
		if((TIFR0&0x01)==0){
			
			tmp--;
			}  
			
		}
		TIFR0 = 0x01;  		
}
//Lcd function
void Lcd_init(){
	 PORTD=0x01;PORTC=0x06;delay(10);PORTC=0x00;
	 delay(10);
	 PORTD=0x02;PORTC=0x06;delay(10);PORTC=0x00;
	 
	 delay(10);
	 PORTD=0x0F;PORTC=0x06;delay(10);PORTC=0x00;
	 delay(10);
	 PORTD=0x38;PORTC=0x06;delay(10);PORTC=0x00;
	 delay(10);
	PORTD=0x14;PORTC=0x06;delay(10);PORTC=0x00;
	delay(10);
	 PORTD=0x80; PORTC=0x06;delay(10);PORTC=0x00;
	 delay(10);
}
void write_char1(char c){
	PORTD=c;PORTC=0x03;PORTC=0x01;
	delay(1);
}
void write_char2(char c){
	PORTD=c;PORTC=0x05;PORTC=0x01;
	delay(1);
}
void movto(int r,int col){
	switch(r){
		case 1:
		PORTD=0x80+col;PORTC=0x02;delay(1);PORTC=0x00;
		break;
		case 2:
		PORTD=0xc0 + col;PORTC=0x02;delay(1);PORTC=0x00;
		break;
		case 3:
		PORTD=0x80+col;PORTC=0x04;delay(10);PORTC=0x00;
		break;
		case 4:
		PORTD=0xc0 + col;PORTC=0x04;delay(10);PORTC=0x00;
		break;
	}
	delay(1);
}
void write_String1(char *s){
	while(*s!='\0')
	{
write_char1(*s++);
	}
}
void write_String2(char *s){
	while(*s!='\0')
	{
		write_char2(*s++);
	}
}
void clear_screen(){
	PORTD=0x01;PORTC=0x06;delay(1);PORTC=0x00;
	delay(1);
}