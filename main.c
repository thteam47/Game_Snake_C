#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <windows.h>

#define consoleWidth 80 //kich thuoc console
#define consoleLenght 25
#define FALSE -1

enum TrangThai {UP,DOWN,LEFT,RIGHT};
typedef enum TrangThai tt;
//khai bao struct toa do
struct toado {
    int x,y; //x la tung do, y la hoanh do
    };
typedef struct toado ToaDo;
//khai bao struct dot ran
struct snake {
    ToaDo len[40];
    int length;
    tt run;
    int dem;
    int diem;
    int sleep;
    int level;
    };
typedef struct snake Snake;
//khai bao struct hoa qua
struct HoaQua {
    ToaDo TD;
    };
typedef struct HoaQua hoaqua;
//ham goto
void gotoXY(int x, int y)
{
    static HANDLE  h = NULL;
    if(!h)
        h = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD c = {x,y};
    SetConsoleCursorPosition(h,c);
}
//ham mau
void TextColor(int x) {
    HANDLE mau;
    mau = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(mau,x|x|x);
    }
//ham khoi tao
void Start (Snake *sn, hoaqua *fr) {
    //khoi tao ban dau
    sn->length=3;
    sn->len[2].x=9;
    sn->len[0].y=4;
    sn->len[1].x=10;
    sn->len[0].y=4;
    sn->len[0].x=11;
    sn->len[0].y=4;
    sn->run=RIGHT; //trang thai ban dau
    //vi tri hoa qua ban dau
    fr->TD.x=40;
    fr->TD.y=15;
    }
//ham hien thi
void View(Snake *snake, hoaqua *fr) {
    system("cls"); //xoa man hinh
    //hien thi khung
    TextColor(14);
    for (int i=3; i<consoleLenght-3; i++) {
        gotoXY(6,i);
        putchar(178);
        putchar(178);
        }
    for (int i=3; i<consoleLenght-4; i++) {
        gotoXY(consoleWidth-7,i);
        putchar(178);
        putchar(178);
        }
    for (int i=7; i<consoleWidth-7; i++) {
        gotoXY(i,3);
        putchar(178);
        }
    for (int i=7; i<consoleWidth-5; i++) {
        gotoXY(i,consoleLenght-4);
        putchar(178);
        }
    for (int i=3; i<consoleLenght-3; i++) {
        gotoXY(consoleWidth-37,i);
        putchar(178);
        }
    TextColor(10);
    gotoXY(consoleWidth-26,consoleLenght/2-5);
    printf("DEMO SNAKE");
    gotoXY(consoleWidth-25,consoleLenght/2-2);
    printf("LEVEL %d",snake->level);
    int mau3=(rand()%15);
    if (mau3<8)
        mau3=15-mau3;
    TextColor(mau3);
    gotoXY(consoleWidth-25,consoleLenght/2+2);
    printf("DIEM  %d",snake->diem);
    int mau1=(rand()%15);
    //hien thi fruit
    TextColor(14);
    gotoXY(fr->TD.x,fr->TD.y);
    putchar(232);
    //hien thi dau snake
    TextColor(14);
    gotoXY(snake->len[0].x,snake->len[0].y);
    putchar(237);
    //hien thi duoi
    int mau2=(rand()%15);
    if (mau2<8)
        mau2=15-mau2;
    TextColor(mau2);
    for (int i=1; i<snake->length; i++) {
        gotoXY(snake->len[i].x,snake->len[i].y);
        putchar(236);
        }
    }
//ham dieu khien
void Control (Snake *snake) {
    for (int i=snake->length-1; i>0; i--) {
        snake->len[i]=snake->len[i-1];
        }
    if (kbhit()) { //phat hien phim nhat
        int con= _getch(); //gancho con
        //dieu khien
        if (con=='W'||con== 'w') {
            if (snake->len[1].x!=snake->len[2].x)
                snake->run=UP;
            }
        else if (con=='S'||con== 's') {
            if (snake->len[1].x!=snake->len[2].x)
                snake->run=DOWN;
            }
        else if ((con== 'A'||con== 'a')) {
            if (snake->len[1].y!=snake->len[2].y)
                snake->run=LEFT;
            }
        else if (con=='D'||con== 'd') {
            if (snake->len[1].y!=snake->len[2].y)
                snake->run=RIGHT;
            }
        }
    //xu li
    if ((snake->run==LEFT))
        snake->len[0].x--;
    else if (snake->run==UP)
        snake->len[0].y--;
    else if (snake->run==RIGHT)
        snake->len[0].x++;
    else if (snake->run==DOWN)
        snake->len[0].y++;
    }

//xu ly chuong trinh
int process(Snake *snake,hoaqua *fr) {
    //khi an duoc fruit
    if (snake->len[0].x==fr->TD.x&&snake->len[0].y==fr->TD.y) {
        snake->dem++;
        if (snake->level==1) {
            snake->diem+=8;
            }
        if (snake->sleep>30) {
            if (snake->dem%2==0)
                snake->sleep-=50;
            if (snake->level==2)
                snake->diem+=6;
            else if (snake->level==3)
                if (snake->sleep>150)
                    snake->diem+=5;
                else
                    snake->diem+=6;
            else if (snake->level==4)
                if (snake->sleep>150)
                    snake->diem+=5;
                else
                    snake->diem+=6;

        }
        else snake->diem+=8;
        for (int i=snake->length; i>0; i--)
            snake->len[i]=snake->len[i-1];
        snake->length++; //tang do dai

        if ((snake->run==LEFT))
            snake->len[0].x--;
        else if (snake->run==UP)
            snake->len[0].y--;
        else if (snake->run==RIGHT)
            snake->len[0].x++;
        else if (snake->run==DOWN)
            snake->len[0].y++;

        //ngau nhien vi tri hien thi fruit
        fr->TD.x=rand()%(consoleWidth-44);
        if (fr->TD.x<8)
            fr->TD.x+=8;
        fr->TD.y=rand()%(consoleLenght-8);
        if (fr->TD.y<4)
            fr->TD.y+=4;

        }
    //dieu kien xu li cham bien
    if (snake->len[0].x<8||snake->len[0].x>=consoleWidth-36||snake->len[0].y>=consoleLenght-4||snake->len[0].y<4)
        return FALSE;
    //xu li khi can duoi
    for (int i=3; i<snake->length; i++) {
        if (snake->len[0].x== snake->len[i].x&&snake->len[0].y== snake->len[i].y)
            return FALSE;
        }
    }
void ShowConsoleCursor(int showFlag)
{
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_CURSOR_INFO     cursorInfo;

    GetConsoleCursorInfo(out, &cursorInfo);
    cursorInfo.bVisible = showFlag; // set the cursor visibility
    SetConsoleCursorInfo(out, &cursorInfo);
}
void main() {
    int level;
    Snake *snake=(Snake*)malloc(sizeof(Snake));
    hoaqua *fruit=(hoaqua*)malloc(sizeof(hoaqua));
        ShowConsoleCursor(0); // pass 0 to hid cursor

starton: //choi lai
    system("cls");
    //giao dien ban dau
    gotoXY((consoleWidth-18)/2,consoleLenght/2-5);
    printf("DEMO SNAKE");
    gotoXY((consoleWidth-20)/2,consoleLenght/2-3);
    printf("Chon Muc Do");
    gotoXY((consoleWidth-17)/2,consoleLenght/2-1);
    printf("1. Nhanh");
    gotoXY((consoleWidth-22)/2,consoleLenght/2+1);
    printf("2. Trung Binh");
    gotoXY((consoleWidth-17)/2,consoleLenght/2+3);
    printf("3. Cham");
    gotoXY((consoleWidth-17)/2,consoleLenght/2+5);
    printf("4. Auto");
    gotoXY((consoleWidth-12)/2,consoleLenght/2+7);
    scanf("%d",&snake->level);
    switch (snake->level) {
        case 1: {
            snake->sleep=10;
            break;
            }
        case 2: {
            snake->sleep=150;
            break;
            }
        case 3: {
            snake->sleep=400;
            break;
            }
        case 4: {
            snake->sleep=300;
            break;
            }
        default:
            goto starton;
        }
    //khoi tao
    Start(snake,fruit);
    srand(time(NULL)); //khoi tao bo so dem
    snake->diem=0;
    snake->dem=0;
    while (1) {
        //view
        View(snake,fruit);
        //Control
        Control(snake);
        //process
        int end= process(snake,fruit);
        //win lose
        if (end==FALSE) {
out:
            system("cls"); //xoa man hinh
            //khung
            TextColor(14);
            for (int i=3; i<consoleLenght-3; i++) {
                gotoXY(6,i);
                putchar(178);
                putchar(178);
                }
            for (int i=3; i<consoleLenght-4; i++) {
                gotoXY(consoleWidth-7,i);
                putchar(178);
                putchar(178);
                }
            for (int i=7; i<consoleWidth-7; i++) {
                gotoXY(i,3);
                putchar(178);
                }
            for (int i=7; i<consoleWidth-5; i++) {
                gotoXY(i,consoleLenght-4);
                putchar(178);
                }
            //hien thi end
            gotoXY((consoleWidth-30)/2,consoleLenght/2-3);
            printf("Ban da thua. Ban dat duoc %d diem\n",snake->diem);
            gotoXY((consoleWidth-24)/2,consoleLenght/2-1);
            printf("Ban Co Muon Choi Lai Khong");
            gotoXY((consoleWidth-10)/2,consoleLenght/2+1);
            printf("1. Choi Lai");
            gotoXY((consoleWidth-8)/2,consoleLenght/2+3);
            printf("2. Thoat");
            //lua chon
            int out1=getch();
            if (out1==50) //end
                break;
            else if (out1==49) //return
                goto starton;
            else
                goto out; //nhap lai

            }
        Sleep(snake->sleep); //nghi

        }
    }
