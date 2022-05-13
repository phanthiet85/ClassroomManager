//Th? vi?n
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <time.h>
#include <windows.h>
#include <ctype.h>
#define MAX 100

 //Khai báo bi?n
 int dem1 = 0, dem2 = 0 , dem3 = 0;

//Khai báo c?u trúc d? li?u
typedef struct
{
	char maPH[10];
	char tenPH[50];
	char Vitri[15];
	char chucnang[50];
}PHONGHOC;

typedef struct
{
	char maPH[10];
	char slbg[3];
	char bggv[3];
	char quat[3];
	char bongden[3];
}THIETBI;

//Khao bao bi?n toàn c?c
PHONGHOC PH[MAX];
THIETBI TB[MAX];

int main();
void menuchung(PHONGHOC PH[], THIETBI TB[]);
//Hàm xoá màn hình
void clrscr()
{
    CONSOLE_SCREEN_BUFFER_INFO csbiInfo;
    HANDLE hConsoleOut;
    COORD Home = {0, 0};
    DWORD dummy;
    hConsoleOut = GetStdHandle(STD_OUTPUT_HANDLE);
    GetConsoleScreenBufferInfo(hConsoleOut,&csbiInfo);
    FillConsoleOutputCharacter(hConsoleOut, ' ' , csbiInfo.dwSize.X * csbiInfo.dwSize.Y,Home,&dummy);
    csbiInfo.dwCursorPosition.X = 0;
    csbiInfo.dwCursorPosition.Y = 0;
    SetConsoleCursorPosition(hConsoleOut,csbiInfo.dwCursorPosition);
}
//Hàm thay ??i màu n?n
void Chinhmaunen(int ForgC, int BackC)
{
     WORD wColor = ((BackC & 0x0F) << 4) + (ForgC & 0x0F);
     ///Get the handle to the current output buffer...
     HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
     ///This is used to reset the carat/cursor to the top left.
     COORD coord = {0, 0};
     ///A return value... indicating how many chars were written
     ///   not used but we need to capture this since it will be
     ///   written anyway (passing NULL causes an access violation).
     DWORD count;
     ///This is a structure containing all of the console info
     /// it is used here to find the size of the console.
     CONSOLE_SCREEN_BUFFER_INFO csbi;
     ///Here we will set the current color
     SetConsoleTextAttribute(hStdOut, wColor);
     if(GetConsoleScreenBufferInfo(hStdOut, &csbi))
     {
          ///This fills the buffer with a given character (in this case 32=space).
          FillConsoleOutputCharacter(hStdOut, (TCHAR) 32, csbi.dwSize.X * csbi.dwSize.Y, coord, &count);
          FillConsoleOutputAttribute(hStdOut, csbi.wAttributes, csbi.dwSize.X * csbi.dwSize.Y, coord, &count );
          ///This will set our cursor position for the next print statement.
          SetConsoleCursorPosition(hStdOut, coord);
     }
     return;
}

void chuyenmauvienkitu(int ForgC, int BackC)
{
     WORD wColor = ((BackC & 0x0F) << 4) + (ForgC & 0x0F);;
     SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), wColor);
     return;
}


void chuyenmaukitu(WORD color)
{
HANDLE hConsoleOutput;
hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);

CONSOLE_SCREEN_BUFFER_INFO screen_buffer_info;
GetConsoleScreenBufferInfo(hConsoleOutput, &screen_buffer_info);

WORD wAttributes = screen_buffer_info.wAttributes;
color &= 0x000f;
wAttributes &= 0xfff0;
wAttributes |= color;

SetConsoleTextAttribute(hConsoleOutput, wAttributes);
}


void gotoxy(int column, int line)
{
	COORD coord;
	coord.X = column;
	coord.Y = line;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
}

//Ham thoi gian
void setDate(char *s){
	time_t rawtime;
	struct tm *info;
	time(&rawtime);
	info = localtime(&rawtime);
	strftime(s, 40,"Hung Yen - Thang %m Nam %Y", info);
}

//Ham ve
void ve(int x, int y,int z)
{
    gotoxy(x,y);
    printf("%c",z);
}

//Ham xoa khoang trang
void xoa(int x, int y, int z)
{
   int i;
    for(i=x;i<x+z;i++)
    {
        gotoxy(i-1,y);
        printf(" ");

    }
}

void xoakhoang(int x,int y,int z,int t)
{
    int j;
    for(j=y;j<t;j++)
        {
          xoa(x,j,z-y);
        }
}

int kiemtrachuoiso(char *s){
    int i;
    for(i=0;i<strlen(s);i++)
        if(s[i]<48||s[i]>57)
            return 0;
    return 1;
}

int kiemtrakhoangtrang(char s[]){
    int i;
    for(i=0;i<strlen(s);i++)
        if(s[i]==' ')
            return 1;
    return 0;
}

//int kttrung(char *s, P)
void quaylaimenu(int x,PHONGHOC PH[],THIETBI TB[])
{
    if(x==27)
    {
        clrscr();
      	menuchung(PH,TB);
    }

    else
        {gotoxy(42,5);
         printf("%c",x);
        }
}
//Ham gioi han ky tu chuoi
void gioihankytuchuoi(char *s,int x,int y, int b)
{
    int i,i1=0,i2=0,v=0,k;
    gotoxy(x,y);
    a:
        for(i=i2;i<b;i++)
        {
            s[v]=getch();
            if(s[v]==13)
            {  //s[v]=NULL;
               break;
            }
            else if(s[v]!=8)
            {  printf("%c",s[v]); v++; }
            else
            { if(i!=0)
                {
                    i=i-2;v--;//s[v]=NULL;
					gotoxy(x+i+1,y);printf(" ");gotoxy(x+i+1,y);
                }
                else i--;
            }
        }
        if(i==b)
            while(i1!=13)
        {
            i1=getch();
            if(i1==8)
            {
                i2=i-1;v--;//s[v]=NULL;
				gotoxy(x+i-1,y);printf(" ");gotoxy(x+i-1,y);
                goto a;
            }
            else if(i1==27)
            {
                clrscr();
                main();
            }
        }
        //s[v]=NULL;
}

// Hàm xóa kí t? trong chu?i t? v? trí (vt) và bao nhiêu kí t? (s1)
void strdelete(char *s,int vt,int sl)
{
    int n=strlen(s),i;
    for (i = vt;i <= n-sl ;++i)
        s[i] = s[i+sl];
}

char* CH_Trim(char s[]){
	int i = 0;
	while (s[i]) i++;
	while (s[i - 1] == 32) i--;
	s[i] = 0;
	while (*s == 32) s++;
	return s;
}

int CH_ktKiTuDacBiet(char *s){
	int i, n = strlen(s);
	for (i = 0; i <= n; i++){
		if (((s[i] > 'A') && (s[i]<'Z')) || ((s[i]>'a') && (s[i] < 'z')) || (s[i] != ' ')){
			return 1;
		}
	}
	return 0;
}

//Ham xoa nhieu khoang trang va in hoa chu cai dau
void CH_Hoten(char *s){
	s = _strlwr(s);
	int i, j, n = strlen(s);
	strcpy(s, CH_Trim(s));
	for (i = 0; i <= n; i++){
		// Neu la ki tu dau thi chuyen thanh chu In Hoa
		if (i == 0){
			s[0] = toupper(s[0]);
		}
		//printf("%d: %s\n", i, s);
		if (s[i] == ' '){
			// Neu co khoang trang thi xoa
			if (s[i + 1] == ' '){
				for (j = i + 1; j < n; j++){
					s[j] = s[j + 1];
				}
				s[n] = 0;
				n--;
				i--;
				// Khong phai khoang trang thi chuyen thanh in hoa
			}
			else{
				s[i + 1] = toupper(s[i + 1]);
			}
		}
	}
}

//Hàm chuan hoa khoang trang
void xoakhoangtrang(char s[])
{
    while(s[strlen(s) - 1]==' ')// Xóa h?t kí t? tr?ng ? cu?i chu?i
        s[strlen(s) - 1]=0;
    while(s[0] == ' ')          //Xóa h?t kí t? tr?ng ? d?u chu?i
        strdelete(s,0,1);
}

void bang1(int x, int y, int z)
{
    chuyenmaukitu(11);
	int i, j;
	for(j = y;j < y+z+1;j++)
    	for(i = x; i< x+101; i++)
	    {  if(i== x+13|| i== x+35|| i== x+50|| i==x ||i == x+100)
               {
                   if(j==y && i!= x && i!=x+100 )
                        ve(i,j,194);
                   else if(j==y+2 && i!= x && i!=x+100 )
                        ve(i,j,197);
                   else if(j==y+z && i!= x && i!=x+100 )
                        ve(i,j,193);
                    else if(j==y && i==x)
                        ve(i,j,218);
                    else if(j==y && i== x+100 )
                        ve(i,j,191);
                    else if(j==y+2 && i== x)
                        ve(i,j,195);
                    else if(j==y+2 && i== x+100 )
                        ve(i,j,180);
                    else if(j==y+z && i==x)
                        ve(i,j,192);
                    else if(j==y+z&& i==x+100 )
                        ve(i,j,217);
                    else ve(i,j,179);
               }
            else if(j==y || j== y+2 || j==y+z)
                ve(i,j,196);

        }
    gotoxy(x+3,y+1);    printf("Ma PH");
    gotoxy(x+18,y+1);   printf("Ten phong hoc");
    gotoxy(x+40,y+1);   printf("Vi tri");
    gotoxy(x+70,y+1);  printf("Chuc nang");
}

void bang2( int x, int y,int z)
{
	chuyenmaukitu(11);
    int i, j;
    for(j = y;j < y+z+1;j++)
        for(i = x; i< x+77; i++)
        {  if(i== x+13|| i== x+31|| i== x+53 || i== x+63 || i==x ||i == x+76)
               {
                   if(j==y && i!= x && i!=x+76 )
                        ve(i,j,194);
                   else if(j==y+2 && i!= x && i!=x+76 )
                        ve(i,j,197);
                   else if(j==y+z && i!= x && i!=x+76 )
                        ve(i,j,193);
                    else if(j==y && i==x)
                        ve(i,j,218);
                    else if(j==y && i== x+76)
                        ve(i,j,191);
                    else if(j==y+2 && i== x)
                        ve(i,j,195);
                    else if(j==y+2 && i== x+76)
                        ve(i,j,180);
                    else if(j==y+z && i==x)
                        ve(i,j,192);
                    else if(j==y+z&& i==x+76)
                        ve(i,j,217);
                    else ve(i,j,179);
               }
            else if(j==y || j== y+2 || j==y+z)
                ve(i,j,196);

        }
    gotoxy(x+4,y+1);  printf("Ma PH");
    gotoxy(x+15,y+1); printf("Ban Ghe Hoc Sinh");
    gotoxy(x+34,y+1); printf("Ban Ghe Giao Vien");
    gotoxy(x+56,y+1); printf("Quat");
    gotoxy(x+66,y+1); printf("Bong Den");
}

void bang3(int x,int y,int z,int t)
{
	chuyenmaukitu(14);
    int i, j;
    for(j = y;j < y+z+1;j++)
        for(i = x; i< x+t+1; i++)
        {  if( i==x ||i == x+t)
               {
                   if(j==y && i!= x && i!=x+64 )
                        ve(i,j,187);
                    else if(j==y+z&& i!= x && i!=x+64)
                        ve(i,j,188);
                    else if(j==y && i==x)
                        ve(i,j,201);
                    else if(j==y+z && i==x)
                        ve(i,j,200);
                    else if(j==y+z&& i==x+64)
                        ve(i,j,217);
                    else ve(i,j,186);
               }
            else if(j==y || j==y+z)
                ve(i,j,205);
        }
		gotoxy(68,5); printf("0:Quay lai menu chinh");
}

void bang4()
{
	chuyenmaukitu(12);
	int i,j,x=0,y=0;
 	for(i=x;i<= x+130;i++)
 		for(j=y;j<= y+32;j++)
 		{ if(i==x || i==x+130)
 			{ if(j==y && i==x && i!=x+130)
 				ve(i,j,201);
 				else if(j==y && i!=x && i==x+130)
 				ve(i,j,187);
 				else if(j==y+32&& i==x && i!=x+130)
 				ve(i,j,200);
 				else if(j==y+32 && i!=x && i==x+130)
 				ve(i,j,188);
 				else ve(i,j,186);
			}
			else if(j==y || j==y+32)
			ve(i,j,205);
		}

}	

int serTB(THIETBI TB[], char s[])
{
    int i ;
		for(i=0;i<dem2;i++)
       { if(strcmp(TB[i].maPH, s) == 0)
            return i;
       }
    return -1;
	}

int serPH(PHONGHOC PH[], char s[])
{
    int i ;
		for(i=0;i<dem1;i++)
       { if(strcmp(PH[i].maPH, s) == 0)
            return i;
       }
    return -1;

}
 
 void addPH(PHONGHOC PH[]){
	int a=10,b=8,z=5;
	bang1(a,b,z);
	 if(dem1 > MAX)
        {       gotoxy(a,b-2);
                printf("Khong du bo nho luu KH:");
        }
    else{   do{
    				do{
                		xoa(a+3,b+3,8);
                		fflush(stdin);
                		gioihankytuchuoi(PH[dem1].maPH,a+3,b+3,8);
                	if(kiemtrakhoangtrang(PH[dem1].maPH)==1)
                    	{
                        xoa(2,25,100);
                        gotoxy(1,25);
                    	printf("Nhap sai!!! Vui long nhap lai!!!");
                        	}
            		else if (3 > strlen(PH[dem1].maPH) || strlen(PH[dem1].maPH) >= 8)
						{
                        xoa(2,25,100);
                        gotoxy(1,25);
                        printf("Nhap sai!!! Vui long nhap lai!!!");
							}
                	}while(3 > strlen(PH[dem1].maPH) || strlen(PH[dem1].maPH) > 8 || kiemtrakhoangtrang(PH[dem1].maPH)==1);
                    		xoa(2,25,100);
                    	do{
                    		xoa(a+15,b+3,20);
                			fflush(stdin);
                			gioihankytuchuoi(PH[dem1].tenPH,a+15,b+3,20);
                			CH_Hoten(PH[dem1].tenPH);
                			if (3 > strlen(PH[dem1].tenPH) || strlen(PH[dem1].tenPH) >= 32)
							{
                        		xoa(2,25,100);
                        		gotoxy(1,25);
                        		printf("Nhap sai!!! Vui long nhap lai!!!");
									}
                			 if (CH_ktKiTuDacBiet(PH[dem1].tenPH) != 1)
							 {
                           		xoa(2,25,100);
                        		gotoxy(1,25);
                        		printf("Nhap sai!!! Vui long nhap lai!!!");
									}
                			  if(kiemtrachuoiso(PH[dem1].tenPH)==1)
                    		  {
                           		 xoa(2,25,100);
                        		 gotoxy(1,25);
                        		 printf("Nhap sai!!! Vui long nhap lai!!!");
									}
                			}while(strlen(PH[dem1].tenPH)>32||strlen(PH[dem1].tenPH)<3||CH_ktKiTuDacBiet(PH[dem1].tenPH) != 1||kiemtrachuoiso(PH[dem1].tenPH)==1);
					xoa(2,25,100);	
                		do{ 
							xoa(a+37,b+3,10);
                        	fflush(stdin);
                        	gioihankytuchuoi(PH[dem1].Vitri,a+38,b+3,6);
                        	CH_Hoten(PH[dem1].Vitri);
                    	if(kiemtrakhoangtrang(PH[dem1].Vitri)==1)
                    	{
                        	xoa(2,25,100);
                        	gotoxy(1,25);
                    		} 
                    }while(kiemtrakhoangtrang(PH[dem1].Vitri)!=1);
                    	do{
                    		xoa(a+53,b+3,48);
               				fflush(stdin);
               				gioihankytuchuoi(PH[dem1].chucnang,a+53,b+3,48); 
                			xoakhoangtrang(PH[dem1].chucnang);
                		if (CH_ktKiTuDacBiet(PH[dem1].chucnang) != 1)
							 {
                           		xoa(2,25,100);
                        		gotoxy(1,25);
                        		printf("Nhap sai!!! Vui long nhap lai!!!");
									}
                		if(kiemtrachuoiso(PH[dem1].chucnang)==1)
                    		  {
                           		 xoa(2,25,100);
                        		 gotoxy(1,25);
                        		 printf("Nhap sai!!! Vui long nhap lai!!!");
									}
							}while(kiemtrachuoiso(PH[dem1].chucnang)==1 || CH_ktKiTuDacBiet(PH[dem1].chucnang) != 1);
						dem1++;
              			b++; 
        			}while(dem1 <1);
    		}
}

void addTB(THIETBI TB[])
{   
	int a=10,b=8,z=5;
    bang2(a,b,z);
   if(dem2 > MAX)
        {       gotoxy(a-2,b);
                printf("Khong du bo nho luu MH: ");
        }

    else
    {   do{
            do{
                xoa(a+3,b+3,8);
                fflush(stdin);
                gioihankytuchuoi(TB[dem2].maPH,a+3,b+3,8);
                if(kiemtrakhoangtrang(TB[dem2].maPH)==1)
                    {
                        xoa(2,25,100);
                        gotoxy(1,25);
                    	printf("Nhap sai!!! Vui long nhap lai!!!");
                        }
            	else if (3 > strlen(TB[dem2].maPH) || strlen(TB[dem2].maPH) >= 8)
				{
                        xoa(2,25,100);
                        gotoxy(1,25);
                        printf("Nhap sai!!! Vui long nhap lai!!!");
					}
                }while(3 > strlen(TB[dem2].maPH) || strlen(TB[dem2].maPH) > 8 || kiemtrakhoangtrang(TB[dem2].maPH)==1);
            xoa(2,25,100);
            do{
            		xoa(a+20,b+3,5);
        			fflush(stdin);
        			gioihankytuchuoi(TB[dem2].slbg,a+20,b+3,2);
	       			if(kiemtrachuoiso(TB[dem2].slbg)!=1)
                    {
                        xoa(2,25,100);
                        gotoxy(1,25);
                        printf("Nhap sai!!! Vui long nhap lai!!!");
						}
				}while(kiemtrachuoiso(TB[dem2].slbg)!=1);
			xoa(2,25,100);
			do{
					xoa(a+41,b+3,5);
        			fflush(stdin);
			        gioihankytuchuoi(TB[dem2].bggv,a+41,b+3,1);
			        if(kiemtrachuoiso(TB[dem2].bggv)!=1)
                    {
                        xoa(2,25,100);
                        gotoxy(1,25);
                        printf("Nhap sai!!! Vui long nhap lai!!!");
						}
			}while(kiemtrachuoiso(TB[dem2].slbg)!=1);
        	xoa(2,25,100);
        	do{
        		xoa(a+58,b+3,5);
        		fflush(stdin);
        		gioihankytuchuoi(TB[dem2].quat,a+58,b+3,1);
        		if(kiemtrachuoiso(TB[dem2].quat)!=1)
                    {
                        xoa(2,25,100);
                        gotoxy(1,25);
                        printf("Nhap sai!!! Vui long nhap lai!!!");
						}
			}while(kiemtrachuoiso(TB[dem2].quat)!=1);
			xoa(2,25,100);
			do{
				xoa(a+65,b+3,5);
        		fflush(stdin);
				gioihankytuchuoi(TB[dem2].bongden,a+68,b+3,1);
        		if(kiemtrachuoiso(TB[dem2].bongden)!=1)
                    {
                        xoa(2,25,100);
                        gotoxy(1,25);
                        printf("Nhap sai!!! Vui long nhap lai!!!");
						}
			}while(kiemtrachuoiso(TB[dem2].bongden)!=1);
        dem2++;
        b++;
        }while(dem2 < 1);
    }
}

void ViewPH(PHONGHOC PH[])
{
    int i,trang =1, maxtrang,key,du=9;
    int x=10,y=8,z=13 ;
    maxtrang = dem1/10+1;
      do{
          bang1(x,y,z);
       for(i=10*(trang-1); i <= 10*(trang-1)+du;i++)
       {
            gotoxy(x+3,y+3);    printf("%s",PH[i].maPH);
            gotoxy(x+14,y+3);   printf("%s",PH[i].tenPH);
            gotoxy(x+37,y+3);   printf("%s",PH[i].Vitri);
            gotoxy(x+53,y+3);   printf("%s",PH[i].chucnang);
            y++;
       }
       gotoxy(33,25); printf("Note: Nhan phim <== de sang trai, ==> de sang phai");
       gotoxy(51,22); printf("Trang %d/%d",trang,maxtrang);
       key =_getch();
           if(key == 77)
            {
                if(trang == maxtrang-1){
                    trang++;
                    du=dem1%10-1;
                  }
                else if(trang == maxtrang){
                    trang =1;
                    du=9;
                  }
                  else {
                    trang++;
                    du=9;
                  }
            }
            else if(key == 75)
            {

              if(trang == 1)
                {
                    trang = maxtrang;
                    du=dem1%10-1;
                }
               else
                {
                    trang--;
                    du=9;

                }
            }
             y=8;
       }while(key != 13);
}

void ViewTB(THIETBI TB[])
{
	int i,trang =1, maxtrang,key,du=9;
    int x=16,y=8,z=13;
    maxtrang = dem2/10+1;
      do{
          bang2(x,y,z);
       for(i=10*(trang-1); i <= 10*(trang-1)+du;i++)
       {
            gotoxy(x+4,y+3);  printf("%s",TB[i].maPH);
    		gotoxy(x+23,y+3); printf("%s",TB[i].bggv);
    		gotoxy(x+41,y+3); printf("%s",TB[i].slbg);
    		gotoxy(x+58,y+3); printf("%s",TB[i].quat);
    		gotoxy(x+68,y+3); printf("%s",TB[i].bongden);
            y++;
       }
       gotoxy(33,25); printf("Note: Nhan phim <== de sang trai, ==> de sang phai");
       gotoxy(51,22); printf("Trang %d/%d",trang,maxtrang);
       key =_getch();
           if(key == 77)
            {
                if(trang == maxtrang-1){
                    trang++;
                    du=dem2%10-1;
                  }
                else if(trang == maxtrang){
                    trang =1;
                    du=9;
                  }
                  else {
                    trang++;
                    du=9;
                  }
            }
            else if(key == 75)
            {

              if(trang == 1)
                {
                    trang = maxtrang;
                    du=dem2%10-1;
                }
               else
                {
                    trang--;
                    du=9;

                }
            }
             y=8;
       }while(key != 13);
}


void suaPH(PHONGHOC PH[])
{
    char s[10];
    int x2,i,x=20,y=9,z=5;
	chuyenmaukitu(11);
    gotoxy(x+5,y-1);
    printf("Nhap ma phong hoc muon sua \t");
    fflush(stdin);
    gets(s);
    xoakhoangtrang(s);
    x2 = serPH(PH,s);
    if(x2 == -1)
    {        gotoxy(x+50,y-1);
         printf("Khong co ma phong hoc nay");
         gotoxy(x+12,y-4);
    }

    else
    {   bang1(x,y,z);
        gotoxy(x-19,y+3);   printf("Du lieu ban dau ->");
        gotoxy(x-19,y+4);   printf("Du lieu moi     ->");
        gotoxy(x+3,y+3); printf("%s",PH[x2].maPH);
        gotoxy(x+15,y+3); printf("%s",PH[x2].tenPH);
        gotoxy(x+38,y+3); printf("%s",PH[x2].Vitri);
        gotoxy(x+53,y+3); printf("%s",PH[x2].chucnang);
        y++;
                	do{
						xoa(x+3,y+3,8);
                		fflush(stdin);
                		gioihankytuchuoi(PH[x2].maPH,x+3,y+3,8);
                	if(kiemtrakhoangtrang(PH[x2].maPH)==1)
                    	{
                        xoa(2,25,100);
                        gotoxy(1,25);
                    	printf("Nhap sai!!! Vui long nhap lai!!!");
                        	}
            		else if (3 > strlen(PH[x2].maPH) || strlen(PH[x2].maPH) >= 8)
						{
                        xoa(2,25,100);
                        gotoxy(1,25);
                        printf("Nhap sai!!! Vui long nhap lai!!!");
							}
                	}while(3 > strlen(PH[x2].maPH) || strlen(PH[x2].maPH) > 8 || kiemtrakhoangtrang(PH[x2].maPH)==1);
                    		xoa(2,25,100);
                    	do{
                    		xoa(x+15,y+3,20);
                			fflush(stdin);
                			gioihankytuchuoi(PH[x2].tenPH,x+15,y+3,20);
                			CH_Hoten(PH[dem1].tenPH);
                			if (3 > strlen(PH[x2].tenPH) || strlen(PH[x2].tenPH) >= 32)
							{
                        		xoa(2,25,100);
                        		gotoxy(1,25);
                        		printf("Nhap sai!!! Vui long nhap lai!!!");
									}
                			 if (CH_ktKiTuDacBiet(PH[x2].tenPH) != 1)
							 {
                           		xoa(2,25,100);
                        		gotoxy(1,25);
                        		printf("Nhap sai!!! Vui long nhap lai!!!");
									}
                			  if(kiemtrachuoiso(PH[x2].tenPH)==1)
                    		  {
                           		 xoa(2,25,100);
                        		 gotoxy(1,25);
                        		 printf("Nhap sai!!! Vui long nhap lai!!!");
									}
                			}while(strlen(PH[x2].tenPH)>32||strlen(PH[x2].tenPH)<3||CH_ktKiTuDacBiet(PH[x2].tenPH) != 1||kiemtrachuoiso(PH[x2].tenPH)==1);
					xoa(2,25,100);	
                		do{ 
							xoa(x+37,y+3,10);
                        	fflush(stdin);
                        	gioihankytuchuoi(PH[x2].Vitri,x+38,y+3,6);
                        	CH_Hoten(PH[x2].Vitri);
                    		//xoakhoangtrang(PH[dem1].Vitri);
                    	if(kiemtrakhoangtrang(PH[x2].Vitri)==1)
                    	{
                        	xoa(2,25,100);
                        	gotoxy(1,25);
                    		} 
                    }while(kiemtrakhoangtrang(PH[x2].Vitri)!=1);
                    	do{
                    		xoa(x+53,y+3,48);
               				fflush(stdin);
               				gioihankytuchuoi(PH[x2].chucnang,x+53,y+3,48); 
                			xoakhoangtrang(PH[x2].chucnang);
                		if (CH_ktKiTuDacBiet(PH[x2].chucnang) != 1)
							 {
                           		xoa(2,25,100);
                        		gotoxy(1,25);
                        		printf("Nhap sai!!! Vui long nhap lai!!!");
									}
                		if(kiemtrachuoiso(PH[x2].chucnang)==1)
                    		  {
                           		 xoa(2,25,100);
                        		 gotoxy(1,25);
                        		 printf("Nhap sai!!! Vui long nhap lai!!!");
									}
							}while(kiemtrachuoiso(PH[x2].chucnang)==1 || CH_ktKiTuDacBiet(PH[x2].chucnang) != 1);
  }
}

// Sua du lieu
void suaTB(THIETBI TB[])
{	char s[10];
    int x1,i,a=20,b=9,z=5;
    chuyenmaukitu(11);
    gotoxy(a+5,b-1);
    printf("Nhap ma phong hoc muon sua \t");
    fflush(stdin);
    gets(s);
    xoakhoangtrang(s);
    x1 = serTB(TB,s);
    if(x1 == -1)
    {        gotoxy(a+50,b-1);
         printf("Khong co du lieu phong hoc nay");
         gotoxy(a+12,b-4);
    }

    else
    {   bang2(a,b,z);
        gotoxy(a-19,b+3);   printf("Du lieu ban dau ->");
        gotoxy(a-19,b+4);   printf("Du lieu moi     ->");
        gotoxy(a+2,b+3); printf("%s",TB[x1].maPH);
        gotoxy(a+21,b+3); printf("%s",TB[x1].slbg);
        gotoxy(a+40,b+3); printf("%s",TB[x1].bggv);
        gotoxy(a+57,b+3); printf("%s",TB[x1].quat);
        gotoxy(a+68,b+3); printf("%s",TB[x1].bongden);
        b++;
			do{
             	xoa(a+3,b+3,8);
                fflush(stdin);
                gioihankytuchuoi(TB[x1].maPH,a+3,b+3,8);
                if(kiemtrakhoangtrang(TB[x1].maPH)==1)
                    {
                        xoa(2,25,100);
                        gotoxy(1,25);
                    	printf("Nhap sai!!! Vui long nhap lai!!!");
                        }
            	else if (3 > strlen(TB[x1].maPH) || strlen(TB[x1].maPH) >= 8)
				{
                        xoa(2,25,100);
                        gotoxy(1,25);
                        printf("Nhap sai!!! Vui long nhap lai!!!");
					}
                }while(3 > strlen(TB[x1].maPH) || strlen(TB[x1].maPH) > 8 || kiemtrakhoangtrang(TB[x1].maPH)==1);
            xoa(2,25,100);
            do{
            		xoa(a+20,b+3,5);
        			fflush(stdin);
        			gioihankytuchuoi(TB[x1].slbg,a+20,b+3,2);
	       			if(kiemtrachuoiso(TB[x1].slbg)!=1)
                    {
                        xoa(2,25,100);
                        gotoxy(1,25);
                        printf("Nhap sai!!! Vui long nhap lai!!!");
						}
				}while(kiemtrachuoiso(TB[x1].slbg)!=1);
			xoa(2,25,100);
			do{
					xoa(a+41,b+3,5);
        			fflush(stdin);
			        gioihankytuchuoi(TB[x1].bggv,a+41,b+3,1);
			        if(kiemtrachuoiso(TB[x1].bggv)!=1)
                    {
                        xoa(2,25,100);
                        gotoxy(1,25);
                        printf("Nhap sai!!! Vui long nhap lai!!!");
						}
			}while(kiemtrachuoiso(TB[x1].slbg)!=1);
        	xoa(2,25,100);
        	do{
        		xoa(a+58,b+3,5);
        		fflush(stdin);
        		gioihankytuchuoi(TB[x1].quat,a+58,b+3,1);
        		if(kiemtrachuoiso(TB[x1].quat)!=1)
                    {
                        xoa(2,25,100);
                        gotoxy(1,25);
                        printf("Nhap sai!!! Vui long nhap lai!!!");
						}
			}while(kiemtrachuoiso(TB[x1].quat)!=1);
			xoa(2,25,100);
			do{
				xoa(a+65,b+3,5);
        		fflush(stdin);
				gioihankytuchuoi(TB[x1].bongden,a+68,b+3,1);
        		if(kiemtrachuoiso(TB[x1].bongden)!=1)
                    {
                        xoa(2,25,100);
                        gotoxy(1,25);
                        printf("Nhap sai!!! Vui long nhap lai!!!");
						}
			}while(kiemtrachuoiso(TB[x1].bongden)!=1);
    }
}

// Xoa du lieu
void xoaPH(PHONGHOC PH[])
{
    char s[10];
    int x2, i;
    chuyenmaukitu(11);
    gotoxy(15,8);
    printf("Nhap ma phong hoc muon xoa:");
    fflush(stdin);
    gets(s);
    x2 = serPH(PH, s);
    if( x2 == -1)
        { gotoxy(15,9);
          printf("Khong co ma phong hoc nay ");
        }
    else {  gotoxy(15,9);
            printf("Da xoa thong tin phong hoc co ma %s",s);
            for(i = x2;i < dem1; i++)
            {
                PH[i]=PH[i+1];
            }
        dem1--;
        }

}

// Xoa du lieu
void xoaTB(THIETBI TB[])
{
    char s[10];
    int x1, i;
    chuyenmaukitu(11);
    gotoxy(15,8);
    printf("Nhap ma phong hoc muon xoa:");
    fflush(stdin);
    gets(s);
    x1 = serTB(TB, s);
    if( x1 == -1)
        { gotoxy(15,9);
          printf("Khong co ma phong hoc nay ");
        }
    else {  gotoxy(15,9);
            printf("Da xoa du lieu thong tin co ma %s",s);
            for(i = x1;i < dem2; i++)
            {
                TB[i]=TB[i+1];
            }
        dem2--;
        }

}

void R_DATA1(PHONGHOC PH[]){
	FILE *f1, *f2;
    int i;
    PHONGHOC ph;
    f2 = fopen("data1.txt", "r");
	if (f2 == NULL){
		gotoxy(1,35);
		printf("KHONG TIM THAY FILE.");
	}
	else{
		fread(&dem1, sizeof(int), 1, f2);
	}
	fclose(f2);

    f1 = fopen("Phonghoc.txt","r");
    if(f1==NULL)
        printf("Khong tim thay file");
    for(i = 0;i< dem1;i++)
    {
        fread(&ph, sizeof(PHONGHOC), 1, f1);
        PH[i] = ph;
    }
    fclose(f1);
}

void R_DATA2(THIETBI TB[]){
	FILE *f1, *f2;
     int i;
     THIETBI tb;
    f2 = fopen("data2.txt", "r");
	if (f2 == NULL){
		printf("KHONG TIM THAY FILE.");
	}
	else{
		fread(&dem2, sizeof(int), 1, f2);
	}
	fclose(f2);

    f1 = fopen("Thietbi.txt","r");
    if(f1==NULL)
        printf("Khong tim thay file");
    for(i = 0;i< dem2;i++)
    {
        fread(&tb, sizeof(THIETBI), 1, f1);
        TB[i] = tb;
    }
    fclose(f1);
}

void W_DATA1(PHONGHOC PH[])
{
    FILE *f1,*f2;
    int i;
    f2 = fopen("data1.txt", "w");
	fwrite(&dem1, sizeof(int), 1, f2);
	fclose(f2);

    f1 = fopen("Phonghoc.txt","w");
    for(i = 0;i < dem1;i++)
    {
        fwrite(&PH[i],sizeof(PHONGHOC), 1, f1);

    }
    fclose(f1);
}

void W_DATA2(THIETBI TB[]){
	FILE *f1,*f2;
    int i;
    f2 = fopen("data2.txt", "w");
	fwrite(&dem2, sizeof(int), 1, f2);
	fclose(f2);

    f1 = fopen("Thietbi.txt","w");
    for(i = 0;i < dem2;i++)
    {
        fwrite(&TB[i],sizeof(THIETBI), 1, f1);

    }
    fclose(f1);
}

 void menu1(PHONGHOC PH[],THIETBI TB[])
{
	int n;
    int a=2,b=2,x; char s[10];
    chuyenmaukitu(14);
    bang4();
    do{ bang3(3,1,5,110);
        gotoxy(a+50,b); printf("BANG CHUC NANG");
        gotoxy(a+25,b+1); printf("1:Nhap du lieu");
        gotoxy(a+68,b+1); printf("2:Xem du lieu");
        gotoxy(a+25,b+2); printf("3:Sua du lieu");
        gotoxy(a+68,b+2); printf("4:Xoa du lieu");
        gotoxy(a+25,b+3); printf("Chon chuc nang:");
        lap:
		x = getch();
		quaylaimenu(x,PH,TB); 
        switch(x)
         {  case 49:
		 			chuyenmaukitu(11);
		 			xoakhoang(a,b+5,a+120,b+30);
                    gotoxy(a+38,b+5);
                    printf("CHUC NANG NHAP DU LIEU ");
                    R_DATA1(PH);
                    addPH(PH);
					W_DATA1(PH);
                    goto lap;
                    break;
            case 50: chuyenmaukitu(11);
					xoakhoang(a,b+5,a+120,b+30);
                    gotoxy(a+33,b+5);
                    printf("BANG DU LIEU THONG TIN HIEN CO ");                 
                    R_DATA1(PH); 
					ViewPH(PH);
                    goto lap;
                     break;
            case 51: chuyenmaukitu(11);
					xoakhoang(a,b+5,a+120,b+30);
                    gotoxy(a+38,b+5);
                    printf("BANG SUA DU LIEU ");
                    R_DATA1(PH); 
					suaPH(PH);
					W_DATA1(PH);
                    goto lap;
                    break;
            case 52:chuyenmaukitu(11);
					xoakhoang(a,b+5,a+120,b+30);
                    gotoxy(a+38,b+5);
                    printf("BANG XOA DU LIEU\n");
                    R_DATA1(PH); 
                    xoaPH(PH);
                    W_DATA1(PH);
                    gotoxy(a+30,b+3);
                    goto lap;
                    break;
            default: gotoxy(a+40,b+3);
                     goto lap;
                     break;


         }
    }while(x == 10);
}

void menu2(THIETBI TB[], PHONGHOC PH[])
{
	int n;
    int a=2,b=2,x; char s[10];
    chuyenmaukitu(14);
	bang4();
    do{ bang3(3,1,5,110);
        gotoxy(a+50,b); printf("BANG CHUC NANG");
        gotoxy(a+25,b+1); printf("1:Nhap du lieu");
        gotoxy(a+68,b+1); printf("2:Xem du lieu");
        gotoxy(a+25,b+2); printf("3:Sua du lieu");
        gotoxy(a+68,b+2); printf("4:Xoa du lieu");
        gotoxy(a+25,b+3); printf("Chon chuc nang:");
        lap:
        x = getch();
		quaylaimenu(x,PH,TB);
        switch(x)
         {  case 49: chuyenmaukitu(11);
		 			xoakhoang(a,b+5,a+120,b+30);
                    gotoxy(a+38,b+5);
                    printf("CHUC NANG NHAP DU LIEU");
                    R_DATA2(TB);
                    addTB(TB);
                    W_DATA2(TB);
                    goto lap;
                    break;
            case 50:	chuyenmaukitu(11);
					xoakhoang(a,b+5,a+120,b+30);
                    gotoxy(a+33,b+5);
                    printf("BANG DU LIEU THONG TIN HIEN CO ");					                   
                    R_DATA2(TB);
                    ViewTB(TB);
                    goto lap;
                     break;
            case 51: chuyenmaukitu(11);
					xoakhoang(a,b+5,a+120,b+30);
                    gotoxy(a+38,b+5);
                    printf("BANG SUA DU LIEU ");
                    R_DATA2(TB);
                    suaTB(TB);
                    W_DATA2(TB);
                    goto lap;
                    break;
            case 52: chuyenmaukitu(11);
                    xoakhoang(a,b+5,a+120,b+30);
                    gotoxy(a+38,b+5);
                    printf("BANG XOA DU LIEU \n");
                    R_DATA2(TB);
					xoaTB(TB);
					W_DATA2(TB);
                    gotoxy(a+30,b+3);
                    goto lap;
                    break;
            default:  gotoxy(a+40,b+3);
                     goto lap;
                     break;


         }
    }while(x == 10);
}

void menuchung(PHONGHOC PH[], THIETBI TB[])
{
	int a=10,b=5,cn;
    bang4();
    chuyenmaukitu(14);
   char ch;
   lap:
    gotoxy(a+30,b-2);   printf("QUAN LY PHONG HOC CO SO 2");
    gotoxy(a+25,b-1);	printf("TRUONG DAI HOC SU PHAM KY THUAT HUNG YEN");
    gotoxy(a+34,b+1);      printf(" 1 - PHONG HOC ");
    gotoxy(a+34,b+2);      printf(" 2 - TRANG THIET BI  ");
    gotoxy(a+34,b+3);      printf(" 3 - THOAT");
    gotoxy(a-5,b+7);    printf("Nhap chuc nang ban chon: \t");
    scanf("%d",&cn);
    if(cn >3)

        goto lap;
    switch(cn)
    {
        case 1: clrscr();
                menu1(PH,TB);
                goto lap;
                break;
        case 2: clrscr();
                menu2(TB,PH);
                goto lap;
                break;
        case 3: gotoxy(2,25);
                printf("Ban co muon thoat chuong trinh (Y/N): \n");
                fflush(stdin);
                gotoxy(40,25);
                ch = toupper(getchar());
                if(ch == 'Y')
                    exit(0);
                else if(ch == 'N')
                  {    clrscr();
                      main();
                  }
                  break;
        default: gotoxy(a-5,b+8);
                 printf("Nhap chuc nang tu 1-> 3");
    }
}

void linhtinh()
{
	int a=10,b=5, cm;
	char x1[35],x2[10],x3[35], s[40];
	
	bang4();
	chuyenmaukitu(14);
    gotoxy(a+34,b-3);
 	printf("TRUONG DAI HOC SU PHAM KY THUAT HUNG YEN");
    gotoxy(a+42,b-2);
 	printf("KHOA CONG NGHE THONG TIN");
 	gotoxy(a+42,b+22);
 	setDate(s);
	puts(s);
	gotoxy(a+51,b+3);
	printf("DO AN I");
 	gotoxy(a+34,b+5);
 	printf("XAY DUNG PHAN MEM QUAN LY PHONG HOC CO SO 2");
 	gotoxy(a+39,b+6);
 	printf("TRUONG DAI HOC SU PHAM KY THUAT");
 	gotoxy(a+50,b+7);
 	printf("HUNG YEN");
 	gotoxy(a+26,b+10);
 	printf("Nguoi thuc hien    :");
 	gotoxy(a+26,b+11);
 	printf("Lop                :");
 	gotoxy(a+26,b+12);
 	printf("Giao vien huong dan:");
 			
	 do{
	 	xoa(a+47,b+10,32); 
		fflush(stdin);
		gioihankytuchuoi(x1,a+46,b+10,32);
	 }while(strlen(x1) < 1);
 	do{
 		xoa(a+47,b+11,20);
		fflush(stdin); 
		gioihankytuchuoi(x2,a+46,b+11,6);
	 }while(kiemtrachuoiso(x2) != 1);
	 do{
	 	xoa(a+47,b+12,32);
		fflush(stdin);
		gioihankytuchuoi(x3,a+46,b+12,32);
	 }while(strlen(x3) < 1);
 	gotoxy(5,25); printf("Nhan Enter de tiep tuc, ESC de thoat...");
    cm = toupper(getch());
    if(cm == 27)
	{      
		clrscr();
        exit(0);
		}
    else if(cm == 13)
    {   
		clrscr();
        menuchung(PH,TB);
        }
}

int main()
{
	Chinhmaunen(2,1);
	linhtinh();
	_getch();
	}

