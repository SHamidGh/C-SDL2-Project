#include<cmath>
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL2_gfx.h>
#include <SDL2/SDL_mixer.h>
#include <conio.h>
#include <ctime>
#include<fstream>
///Seyed Hamid Ghasemi (400109768)  seyyedhamid.ghasemi@gmail.com
///Mohammad Morsali (400101956)  mohammadmorsali8181@gmail.com
using namespace std;
///******************************************************************************
SDL_Renderer* Renderer;
int L=1280,W=800;      //L tool & W ertefa'e window
SDL_Event *event = new SDL_Event();
int x1=100,y1=100,w=100,h=100;
int pause;
double dt=0.117;
string text="";
string image_adress;
string stadium;
string plat;
string ball;
bool istyping1,istyping2;
const short int num_head=10,num_boot=6,num_stadium=6,num_plat=5,num_ball=8;
string name_of_powers[10];
short int nstadium=1,nplat=1;
int j=0;
int a=-13;
int b=-37;
double t=0;
int n_music=0;
string lines[90];
int n_lines;
string name_of_music[4];
string music_address;
int current_time=0,timer_game,delt;
double ddt;
Mix_Chunk *Effect_Button;
Mix_Chunk *jumpbreath;
Mix_Chunk *Effects_kick;
Mix_Chunk *collision;
Mix_Chunk *goalcheering;
///*************************************************************************
struct player
{
    int gol;
    double x;
    double y;
    string head;
    int nhead;
    string foot;
    int nfoot;
    string name;
    short int power;
    double t_power;
    int r_head;
    double vx;
    double vy;
    double gam_x;
    struct foot
    {
        double angle;
        double angle_gam;
        int tool;
        int arz;
        int x;
        int y;
        struct  Point_relative
        {
            int x;
            int y;
        }point;
    } boot;
}player1,player2;
struct Displays
{
    bool Start;
    bool Move ;
    bool Menu;
    bool Setting;
    bool About;
    bool Game;
    bool Pause;
    bool exit;
    bool choose;
    bool endgame;
    bool table;
    bool option;
}Display;
struct images
{
    string start;
    string Menu;
    string choose;
    string pause;
    string table_back;
}image;
struct muses
{
    int x;
    int y;
}muse;
struct Ball
{
    int n;
    double x;
    double y;
    double vx;
    double vy;
    double r;
    double x0;
    double y0;
    double vx0;
    double vy0;
    struct zarib
    {
        double kaf;
        double tirak;
    }z;
    string ball;
}bal;
struct Events
{
    bool click;
    bool right_p1;
    bool left_p1;
    bool right_p2;
    bool left_p2;
    bool mshoot_p1;
    bool mshoot_p2;
    bool shoot_p1;
    bool shoot_p2;
    bool up_p1;
    bool up_p2;
    short int power_p1;
    int start_time_power_p1;
    short int power_p2;
    int start_time_power_p2;

}eventt;
struct circle
{
    int x;
    int y;
    int r;
}circles,circles_of_choose_player[15],circles_of_pause[2];
struct rectt
{
    int x1;
    int y1;
    int width;
    int height;
}rects_of_choose_player[10],rects_of_game[9],rects_of_pause[4];
struct tirak
{
    double x;
    double y;
    double arz;
    double ertefa;
    string name;
}tirak_r,tirak_l;
struct _files
{
    string asami[50];
    int tedad_bord[50];
    int tedad_bakht[50];
    int tedad_mosavi[50];
    int tedad_goal_zade[50];
    int tedad_goal_khorde[50];
    int num;
    int tafazol_gol[50];
    int tedad_bazi[50];
    int score[50];
}file;
struct cheeter
{
    bool ok;
    bool cheet;
    int time_start;
}cheet;
struct textures
{
    SDL_Texture *stadiumm;
    SDL_Texture *platt;
    SDL_Texture *p1_h;
    SDL_Texture *p2_h;
    SDL_Texture *p1_f;
    SDL_Texture *p2_f;
    SDL_Texture *tirakr;
    SDL_Texture *tirakl;
    SDL_Texture *balll;
    SDL_Texture *mane;
    SDL_Texture *About;
    SDL_Texture *Freeze;

}texture_my;
struct points_of_boot
{
    struct related_point
    {
        double x;
        double y;
    }_1,_2,_3,_4;

}pbp1,pbp2;
///*********************************************************************************************************
void rect(int x,int y,int w,int h,int R, int G, int B, int fill_boolian );
void window_color( int R, int G, int B);
void menu(int R, int G, int B);
void texture(int xp,int yp,string addressOfImage,int width,int height);
void nextt(string place,int plu);
void Do();
void write(string text, int x, int y ,int w, int h,int Size);
void change_pictcure_of_menu();
bool muse_in_circle(circle a);
void Present();
void Fade(string Adress);
void events();
void change_pictcure_of_choose();
void dynamic_changes_in_choose_display();
void present_choose();
bool muse_in_rect(rectt rec);
void dynamic_changes_in_menu_display();
void change_picture_of_pause();
void present_game();
void present_pause();
void textureEx (int xp,int yp,string addressOfImage,int width,int height,int point_x,int point_y,double angle);
void set_first();
void meghdardehi_avvalie();
void start_of_game();
void set_normal_p1();
void set_normal_p2();
void do_powers();
double diffclock(clock_t clock1,clock_t clock2);
void barkhord_toop();
void openfiles_and_make_tablefile();
void add_players_to_files();
void Do_game();
void Do_pause();
void present_endgame();
void fast_texture(int xp,int yp,SDL_Texture *myTexture,int width,int height);
void load_game_images();
void shoot();
double davaran_x(double x_fixpoint,double y_fixpoint,double x,double y,double angel);
double davaran_y(double x_fixpoint,double y_fixpoint,double x,double y,double angel);
bool barkhord_2noghte(double x1,double y1,double x2,double y2,bool barkhord_up_Or_right);
void do_move_game();
void shoroo_mojaddad(int nofp);
void present_table();
void present_setting();
void present_abaot();
void present_option();
void animeishen_of_punch(int number_of_pleyer);
///***************************************************************************************************************
int main( int argc, char * argv[] )
{
    srand(time(NULL));
    Uint32 SDL_flags = SDL_INIT_VIDEO | SDL_INIT_TIMER ;
    Uint32 WND_flags = SDL_WINDOW_SHOWN;
    SDL_Window *m_window;
    SDL_Init( SDL_flags );
    SDL_CreateWindowAndRenderer( L, W, WND_flags, &m_window, &Renderer );
    SDL_RaiseWindow(m_window);
    SDL_DisplayMode DM;
    SDL_GetCurrentDisplayMode(0, &DM);
    meghdardehi_avvalie();
    openfiles_and_make_tablefile();
    SDL_Init(SDL_INIT_VIDEO||SDL_INIT_AUDIO);
    Mix_OpenAudio(44100,MIX_DEFAULT_FORMAT,2,2048);
    Mix_Music *ostad=Mix_LoadMUS("music//0.mp3");//esm file bray entkahab file music dar in nahie entkhab mishavad
    Mix_PlayMusic(ostad,-1); //ostad y esme randome kamelan brash
    Mix_VolumeMusic(1000);
    Effect_Button = Mix_LoadWAV("music//Effects_Button.WAV") ;
    jumpbreath = Mix_LoadWAV("music//jumpbreath.WAV") ;
    Effects_kick = Mix_LoadWAV("music//Effects_kick.WAV") ;
    collision = Mix_LoadWAV("music//collision.WAV") ;
    goalcheering = Mix_LoadWAV("music//goalcheering.WAV") ;
    while(!Display.exit)
    {
        clock_t start = clock();
        current_time = time(NULL);
        set_first();
        events();
        do_powers();
        Do();
        set_first();
        Present();
        SDL_RenderPresent(Renderer);
        SDL_RenderClear(Renderer);
        clock_t end = clock();
        delt=diffclock(start,end);
        current_time+=delt;
    }
    SDL_DestroyWindow( m_window );
    SDL_DestroyRenderer( Renderer );
	SDL_Quit();
    return 0;
}
void events ()
{
    muse.x=event->button.x;
    muse.y=event->button.y;
    if(SDL_PollEvent(event))
    {
        if(event->type==SDL_KEYDOWN&&!Display.Game)
        {
            switch( event->key.keysym.sym )
            {
                case SDLK_ESCAPE:
                {
                    Display.exit=true;
                    return ;
                }
                case SDLK_BACKSPACE:
                {
                    if(text.size())
                    text = text.substr(0,text.size()-1);
                    break;
                }
            }
        }
        if(Display.Game)
        {
            if(event->type==SDL_KEYDOWN)
            {
                switch( event->key.keysym.sym )
                {
                    case SDLK_ESCAPE:
                    {
                        Display.exit=true;
                        return ;
                    }
                    case  SDLK_RIGHT:
                    {
                        eventt.right_p2=true;
                        break;
                    }
                    case  SDLK_LEFT:
                    {
                        eventt.left_p2=true;
                        break;
                    }
                    case  SDLK_UP:
                    {
                      Mix_PlayChannel(-1, jumpbreath, 0);
                        eventt.up_p2=true;
                        break;
                    }
                    case  SDLK_DOWN:
                    {
                        eventt.mshoot_p2=true;
                        break;
                    }
                     case  SDLK_RSHIFT:
                    {
                        if(player2.t_power==1)
                        {
                            if(player2.power!=10)
                            {
                                eventt.power_p2=player2.power;
                            }
                            else
                            {
                               eventt.power_p2=rand()%9+1;
                            }
                            eventt.start_time_power_p2=timer_game;
                            if(player2.power==6)
                            {
                                animeishen_of_punch(2);
                            }
                            if(eventt.power_p2==7)
                            {
                                player1.gam_x*=-1;
                            }

                            player2.t_power=0;
                        }
                        break;
                    }
                     case SDLK_q:
                    {
                        if(player1.t_power==1)
                        {
                            if(player1.power!=10)
                            {
                                eventt.power_p1=player1.power;
                            }
                            else
                            {
                               eventt.power_p1=rand()%9+1;
                            }
                            eventt.start_time_power_p1=timer_game;
                            if(player1.power==6)
                            {
                                animeishen_of_punch(1);
                            }
                            if(eventt.power_p1==7)
                            {
                                player2.gam_x*=-1;
                            }
                            player1.t_power=0;
                        }
                        break;
                    }
                     case   SDLK_d:
                    {
                        eventt.right_p1=true;
                        break;
                    }
                     case   SDLK_a:
                    {
                        eventt.left_p1=true;
                            break;
                    }
                     case   SDLK_w:
                    {
                        Mix_PlayChannel(-1, jumpbreath, 0);
                        eventt.up_p1=true;
                            break;
                    }
                     case    SDLK_s:
                    {
                        eventt.mshoot_p1=true;
                    }
                    case SDLK_e:
                    {
                            if(player1.name=="Hamid9436"&&cheet.ok)
                            {
                                cheet.cheet=true;
                                cheet.ok=false;
                                cheet.time_start=timer_game;
                                tirak_l.y+=300;
                                tirak_l.ertefa-=300;
                                tirak_r.y-=100;
                                tirak_r.ertefa+=100;
                            }
                    }
                }
            }
            else if(event->type==SDL_KEYUP)
            {
                switch( event->key.keysym.sym )
                {
                    case  SDLK_RIGHT:
                    {
                        eventt.right_p2=false;
                        break;
                    }
                    case  SDLK_LEFT:
                    {
                        eventt.left_p2=false;
                        break;
                    }
                    case  SDLK_UP:
                    {
                        eventt.up_p2=false;
                        break;
                    }
                    case  SDLK_DOWN:
                    {
                        eventt.mshoot_p2=false;
                        break;
                    }
                    case   SDLK_d:
                    {
                        eventt.right_p1=false;
                        break;
                    }
                     case   SDLK_a:
                    {
                        eventt.left_p1=false;
                            break;
                    }
                     case   SDLK_s:
                    {
                        eventt.mshoot_p1=false;
                            break;
                    }
                     case   SDLK_w:
                    {
                        eventt.up_p1=false;
                            break;
                    }
                }
            }
        }
        if(event->type== SDL_MOUSEBUTTONDOWN)
        {
            switch(event->button.clicks)
            {
                case SDL_BUTTON_LEFT:
                {
                   Mix_PlayChannel(-1, Effect_Button, 0);
                   eventt.click=true;
                   break;
                }
            }
        }
        else if(event->quit.type==SDL_QUIT)
        {
            Mix_PlayChannel(-1, Effect_Button, 0);
            Display.exit=true;
            return ;
        }
        else if(event->type==SDL_TEXTINPUT)
        {
            Mix_PlayChannel(-1, Effect_Button, 0);
            text+=event->text.text;
        }
    }
}
void Present()
{
    if(Display.Start)
    {
        Fade("photos//starting.jpg");
        Display.Menu=true;
    }
    if(Display.Menu)
    {
        if(Display.Game||Display.Pause||Display.Start)
        {
            Fade("0");
            Fade(image.Menu);
            Display.About=false;
            Display.Game=false;
            Display.Pause=false;
            Display.Start=false;
        }
        else
        {
            texture(0,0,image.Menu,L,W);
        }
    }
    if(Display.table)
    {
        if(Display.Menu)
        {
            Fade("0");
            Fade(image.table_back);
            Display.Menu=false;
        }
        else
        {
            present_table();
        }

    }
    if(Display.Setting)
    {
        Display.Menu=false;
        SDL_RenderPresent(Renderer);
        SDL_RenderClear(Renderer);
        present_setting();
    }
    if(Display.About)
    {
        if(Display.Menu)
        {
            Fade("0");
            Fade("photos//about.png");
            Display.Menu=false;
            texture(0,0,"photos//about.png",L,W);
            present_abaot();

        }
        else
        {
            fast_texture(0,0,texture_my.About,L,W);
            boxRGBA(Renderer,3,3,L/20+2,W/20+2,0,0,0,250);
            boxRGBA(Renderer,5,5,L/20,W/20,255,0,0,190);
            write("Back",7,7,L/20-6,W/20-10,30);
            write("About",3*L/8,20,L/4,50,100);
            write("project of fandamentals of programming",L/4,W/8-20,L/2,7*W/8/6,100);
            write("Electrical engineering departmant,sharif university of technology",L/8,W/8+7*W/8/6-40,6*L/8,7*W/8/6,100);
            write("professors: Dr.Araste & Dr.Vahdat",L/4,W/8+7*W/8/6+7*W/8/6-40,L/2,W/16,100);
            write("designers: Seyed Hamid Ghasemi           (seyyedhamid.ghasemi@gmail.com)",L/16,W/8+7*W/8/6+7*W/8/6,14*L/16,7*W/8/6,100);
            write("         & Mohammad Morsali              (mohammadmorsali8181@gmail.com)",L/16,W/8+7*W/8/6+7*W/8/6+7*W/8/6,14*L/16,7*W/8/6,100);
            write("2022,january",7*L/16,W/8+7*W/8/6+7*W/8/6+7*W/8/6+7*W/8/6,L/8,7*W/8/6,100);
            write("the project is a simple copy of<<Head soccer game>> and based on c++ by SDL2/Graphic",L/16,W/8+7*W/8/6+7*W/8/6+7*W/8/6+7*W/8/6+7*W/8/6,14*L/16,7*W/8/6,100);
        }
    }
    if(Display.choose)
    {
        if(Display.About||Display.Pause||Display.Setting||Display.Menu)
        {
            Fade("0");
            Fade(image.choose);
            Display.About=false;
            Display.Game=false;
            Display.Pause=false;
            Display.Setting=false;
            Display.Menu=false;
        }
        else
        {
            present_choose();
        }
    }
    if(Display.Game)
    {

        if(Display.About||Display.choose||Display.Pause||Display.Setting||Display.Start)
        {
            start_of_game();
            Display.choose=false;
            timer_game=0;
        }
        else
        {
            present_game();
            if(eventt.power_p1==9||eventt.power_p2==9)
            {
                fast_texture(rects_of_game[4].x1+4,rects_of_game[4].y1,texture_my.Freeze,rects_of_game[4].width-8,rects_of_game[4].height);
            }
            if(eventt.power_p1==8||eventt.power_p2==8)
            {
                fast_texture(bal.x-bal.r,bal.y-bal.r,texture_my.Freeze,2*bal.r,2*bal.r);
            }
            else if(!(eventt.power_p1==1||eventt.power_p2==1))
            {
                fast_texture(bal.x-bal.r,bal.y-bal.r,texture_my.balll,2*bal.r,2*bal.r);
            }
            if(eventt.power_p2==6)
            {
                textureEx(player1.boot.x,player1.boot.y,player1.foot,player1.boot.tool,player1.boot.arz,player1.boot.point.x,player1.boot.point.y,player1.boot.angle);
                fast_texture(player1.x-player1.r_head,player1.y-player1.r_head,texture_my.p1_h,2*player1.r_head,2*player1.r_head);
                fast_texture(player1.x-player1.r_head,player1.y-player1.r_head,texture_my.Freeze,player1.boot.x+player1.boot.tool-(player1.x-player1.r_head),player1.boot.y+player1.boot.arz-(player1.y-player1.r_head));
                //boxRGBA(Renderer,player1.x-player1.r_head,player1.y-player1.r_head,player1.boot.x+player1.boot.tool,player1.boot.y+player1.boot.arz,0,0,200,100);
            }
            else if(eventt.power_p2!=3)
            {
                textureEx(player1.boot.x,player1.boot.y,player1.foot,player1.boot.tool,player1.boot.arz,player1.boot.point.x,player1.boot.point.y,player1.boot.angle);
                fast_texture(player1.x-player1.r_head,player1.y-player1.r_head,texture_my.p1_h,2*player1.r_head,2*player1.r_head);
            }
            if(eventt.power_p1==6)
            {
                fast_texture(player2.boot.x,player2.y-player2.r_head,texture_my.Freeze,player2.x+player2.r_head-player2.boot.x,player2.boot.y+player2.boot.arz-(player2.y-player2.r_head));
            }
            else if(eventt.power_p1!=3)
            {
                textureEx(player2.boot.x,player2.boot.y,player2.foot,player2.boot.tool,player2.boot.arz,player2.boot.point.x,player2.boot.point.y,player2.boot.angle);
                fast_texture(player2.x-player2.r_head,player2.y-player2.r_head,texture_my.p2_h,2*player2.r_head,2*player2.r_head);
            }
            //filledCircleRGBA(Renderer,player2.boot.point.x+player2.boot.x+pbp2._1.x,player2.boot.point.y+player2.boot.y+pbp2._1.y,1,255,255,255,255);
            //filledCircleRGBA(Renderer,player2.boot.x+player2.boot.tool,player2.boot.y,1,255,255,255,255);
            //lineRGBA(Renderer,player1.boot.x+70,player1.boot.y+18,player1.boot.x+160,player1.boot.y+46,255,255,255,255);
//            aalineRGBA(Renderer,davaran_x(player1.boot.x,player1.boot.y,pbp1._1.x,pbp1._1.y,player1.boot.angle),davaran_y(player1.boot.x,player1.boot.y,pbp1._1.x,pbp1._1.y,player1.boot.angle),davaran_x(player1.boot.x,player1.boot.y,pbp1._2.x,pbp1._2.y,player1.boot.angle),davaran_y(player1.boot.x,player1.boot.y,pbp1._2.x,pbp1._2.y,player1.boot.angle),200,0,0,255);
//            aalineRGBA(Renderer,davaran_x(player1.boot.x,player1.boot.y,pbp1._2.x,pbp1._2.y,player1.boot.angle),davaran_y(player1.boot.x,player1.boot.y,pbp1._2.x,pbp1._2.y,player1.boot.angle),davaran_x(player1.boot.x,player1.boot.y,pbp1._3.x,pbp1._3.y,player1.boot.angle),davaran_y(player1.boot.x,player1.boot.y,pbp1._3.x,pbp1._3.y,player1.boot.angle),200,0,0,255);
//            aalineRGBA(Renderer,davaran_x(player1.boot.x,player1.boot.y,pbp1._3.x,pbp1._3.y,player1.boot.angle),davaran_y(player1.boot.x,player1.boot.y,pbp1._3.x,pbp1._3.y,player1.boot.angle),davaran_x(player1.boot.x,player1.boot.y,pbp1._4.x,pbp1._4.y,player1.boot.angle),davaran_y(player1.boot.x,player1.boot.y,pbp1._4.x,pbp1._4.y,player1.boot.angle),200,0,0,255);
//            aalineRGBA(Renderer,davaran_x(player2.boot.x+player2.boot.tool,player2.boot.y,pbp2._1.x,pbp2._1.y,player2.boot.angle),davaran_y(player2.boot.x+player2.boot.tool,player2.boot.y,pbp2._1.x,pbp2._1.y,player2.boot.angle),davaran_x(player2.boot.x+player2.boot.tool,player2.boot.y,pbp2._2.x,pbp2._2.y,player2.boot.angle),davaran_y(player2.boot.x+player2.boot.tool,player2.boot.y,pbp2._2.x,pbp2._2.y,player2.boot.angle),200,0,0,255);
//            aalineRGBA(Renderer,davaran_x(player2.boot.x+player2.boot.tool,player2.boot.y,pbp2._2.x,pbp2._2.y,player2.boot.angle),davaran_y(player2.boot.x+player2.boot.tool,player2.boot.y,pbp2._2.x,pbp2._2.y,player2.boot.angle),davaran_x(player2.boot.x+player2.boot.tool,player2.boot.y,pbp2._3.x,pbp2._3.y,player2.boot.angle),davaran_y(player2.boot.x+player2.boot.tool,player2.boot.y,pbp2._3.x,pbp2._3.y,player2.boot.angle),200,0,0,255);
//            aalineRGBA(Renderer,davaran_x(player2.boot.x+player2.boot.tool,player2.boot.y,pbp2._3.x,pbp2._3.y,player2.boot.angle),davaran_y(player2.boot.x+player2.boot.tool,player2.boot.y,pbp2._3.x,pbp2._3.y,player2.boot.angle),davaran_x(player2.boot.x+player2.boot.tool,player2.boot.y,pbp2._4.x,pbp2._4.y,player2.boot.angle),davaran_y(player2.boot.x+player2.boot.tool,player2.boot.y,pbp2._4.x,pbp2._4.y,player2.boot.angle),200,0,0,255);

            if(eventt.power_p1==4)
            {
                fast_texture(tirak_l.x+tirak_l.arz-30,tirak_l.y,texture_my.mane,30,tirak_l.ertefa);
            }
            if(eventt.power_p2==4)
            {
                fast_texture(tirak_r.x,tirak_l.y,texture_my.mane,30,tirak_l.ertefa);
            }
            timer_game+=delt;

        }
    }
    if(Display.Pause)
    {
        present_game();
        texture(bal.x-bal.r,bal.y-bal.r,bal.ball,2*bal.r,2*bal.r);
        //filledCircleRGBA(Renderer,bal.x,bal.y,bal.r,255,0,20,255);
        textureEx(player1.boot.x,player1.boot.y,player1.foot,player1.boot.tool,player1.boot.arz,player1.boot.point.x,player1.boot.point.y,player1.boot.angle);
        texture(player1.x-player1.r_head,player1.y-player1.r_head,player1.head,2*player1.r_head,2*player1.r_head);
        //circleRGBA(Renderer,player1.x,player1.y,player1.r_head,255,0,0,255);
        filledCircleRGBA(Renderer,player1.boot.point.x+player1.boot.x,player1.boot.point.y+player1.boot.y,1,255,255,255,255);
        filledCircleRGBA(Renderer,player1.boot.x,player1.boot.y,1,255,255,255,255);
        textureEx(player2.boot.x,player2.boot.y,player2.foot,player2.boot.tool,player2.boot.arz,player2.boot.point.x,player2.boot.point.y,player2.boot.angle);
        texture(player2.x-player2.r_head,player2.y-player2.r_head,player2.head,2*player2.r_head,2*player2.r_head);
        lineRGBA(Renderer,player1.boot.x+70,player1.boot.y+18,player1.boot.x+160,player1.boot.y+46,255,255,255,255);
        present_pause();

    }
    if(Display.endgame)
    {
        present_endgame();
    }
    if(Display.option)
    {
        present_option();
    }
}
void Do()
{
    if(Display.Menu)
    {
        change_pictcure_of_menu();
        dynamic_changes_in_menu_display();
    }
    else if(Display.table)
    {
        if(eventt.click)
        {
            if(muse.x>=3&&muse.x<=3+2+L/20&&muse.y>=3&&muse.y<=3+2+W/20&&muse.x>=0&&muse.x<=L&&muse.y>=0&&muse.y<=W)
            {
                Display.Start=true;
                Display.table=false;
            }
        }
    }
    else if(Display.Setting)
    {
    }
    else if(Display.About)
    {
        if(eventt.click&&muse.x>=3&&muse.x<=3+2+L/20&&muse.y>=3&&muse.y<=3+2+W/20&&muse.x>=0&&muse.x<=L&&muse.y>=0&&muse.y<=W)
        {
            Display.Start=true;
            Display.About=false;
        }
    }
    else if(Display.choose)
    {
        dynamic_changes_in_choose_display();
        change_pictcure_of_choose();
        if(muse_in_circle(circles_of_choose_player[14])&&eventt.click)
        {
            Display.Game=true;
            load_game_images();
            SDL_Delay(25);
        }
    }
    else if(Display.Game)
    {
        do_move_game();
        shoot();
        Do_game();
    }
    else if(Display.Pause)
    {
        Do_pause();
    }
    else if(Display.endgame)
    {
        if(eventt.click)
        {
            Display.endgame=false;
            Display.Start=true;
            meghdardehi_avvalie();
        }
    }
}
void dynamic_changes_in_menu_display()
{
    if(eventt.click)
    {
        if(muse.x>=510&&muse.x<=770&&muse.y>=195&&muse.y<=295)
        {
            Mix_PlayChannel(-1, Effect_Button, 0);
            Display.choose=true;
        }
        else if(muse.x>=510&&muse.x<=770&&muse.y>=349&&muse.y<=450)
        {
            Mix_PlayChannel(-1, Effect_Button, 0);
            Display.table=true;
            openfiles_and_make_tablefile();
        }
        else if(muse.x>=510&&muse.x<=770&&muse.y>=503&&muse.y<=606)
        {
            Mix_PlayChannel(-1, Effect_Button, 0);

            Display.Setting=true;
        }
        else if(muse.x>=510&&muse.x<=770&&muse.y>=659&&muse.y<=760)
        {
            Mix_PlayChannel(-1, Effect_Button, 0);
            Display.About=true;
        }
        else if(muse.x>=12&&muse.x<=144&&muse.y>=733&&muse.y<=789)
        {
            Mix_PlayChannel(-1, Effect_Button, 0);
            Display.exit=true;
        }
    }
}
void nextt(string place,int plu)
{
    if(place=="player1")
    {
        player1.nhead+=plu;
        if(player1.nhead>num_head)
        {
            player1.nhead=1;
        }
        if(player1.nhead==0)
        {
            player1.nhead=num_head;
        }
        player1.head="photos//players//";
        player1.head+=to_string(player1.nhead);
        player1.head+="player1.png";
        player1.power=player1.nhead;
    }
    else if(place=="boot1")
    {
        player1.nfoot+=plu;
        if(player1.nfoot>num_boot)
        {
            player1.nfoot=1;
        }
        if(player1.nfoot==0)
        {
            player1.nfoot=num_boot;
        }
        player1.foot="photos//boots//";
        player1.foot+=to_string(player1.nfoot);
        player1.foot+="boot1.png";
    }
    else if(place=="player2")
    {
        player2.nhead+=plu;
        if(player2.nhead>num_head)
        {
            player2.nhead=1;
        }
        if(player2.nhead==0)
        {
            player2.nhead=num_head;
        }
        player2.head="photos//players//";
        player2.head+=to_string(player2.nhead);
        player2.head+="player2.png";
        player2.power=player2.nhead;
    }
    else if(place=="boot2")
    {
        player2.nfoot+=plu;
        if(player2.nfoot>num_boot)
        {
            player2.nfoot=1;
        }
        if(player2.nfoot==0)
        {
            player2.nfoot=num_boot;
        }
        player2.foot="photos//boots//";
        player2.foot+=to_string(player2.nfoot);
        player2.foot+="boot2.png";
    }
    else if(place=="stadium")
    {
        nstadium+=plu;
        if(nstadium>num_stadium)
        {
            nstadium=1;
        }
        if(nstadium==0)
        {
            nstadium=num_stadium;
        }
        stadium="photos//stadium//";
        stadium+=to_string(nstadium);
        stadium+="stadium.jpg";
    }
    else if(place=="plat")
    {
        nplat+=plu;
        if(nplat>num_plat)
        {
            nplat=1;
        }
        if(nplat==0)
        {
            nplat=num_plat;
        }
        plat="photos//plat//";
        plat+=to_string(nplat);
        plat+="plat.jpg";
    }
    else if(place=="ball")
    {
        bal.n+=plu;
        if(bal.n>num_ball)
        {
            bal.n=1;
        }
        if(bal.n==0)
        {
            bal.n=num_ball;
        }
        bal.ball="photos//ball//";
        bal.ball+=to_string(bal.n);
        bal.ball+="ball.png";
    }
}
void change_pictcure_of_choose()
{
    int i=0;
    for(i=0;i<15;i++)
    {
        if(muse_in_circle(circles_of_choose_player[i]))
        {
            image.choose="photos//choose//";
            image.choose+=to_string(i);
            image.choose+="choose.jpg";
            return  ;
        }
    }
    if(!istyping2&&(istyping1||(muse.x>=rects_of_choose_player[0].x1&&muse.x<=rects_of_choose_player[0].width+rects_of_choose_player[0].x1&&muse.y>=rects_of_choose_player[0].y1&&muse.y<=rects_of_choose_player[0].height+rects_of_choose_player[0].y1)))
    {
        if(istyping1)
        {
            player1.name=text;
        }
        image.choose="photos//choose//";
        image.choose+=to_string(15);
        image.choose+="choose.jpg";
        return ;
    }
    else if(istyping2||(muse.x>=rects_of_choose_player[1].x1&&muse.x<=rects_of_choose_player[1].width+rects_of_choose_player[1].x1&&muse.y>=rects_of_choose_player[1].y1&&muse.y<=rects_of_choose_player[1].height+rects_of_choose_player[1].y1))
    {
        if(istyping2)
        {
            player2.name=text;
        }
        image.choose="photos//choose//";
        image.choose+=to_string(16);
        image.choose+="choose.jpg";
        return ;
    }
    image.choose="photos//choose//";
    image.choose+="choose.jpg";
    return ;
}
bool muse_in_circle(circle a)
{
    if(((((muse.x-a.x)*(muse.x-a.x)+(muse.y-a.y)*(muse.y-a.y))<=a.r*a.r))&&muse.x<L&&muse.x>0&&muse.y<W&&muse.y>0)
    {
        return true;
    }
    return false;
}
void change_pictcure_of_menu()
{
    if(muse.x>=510&&muse.x<=770&&muse.y>=195&&muse.y<=295)
    {
        image.Menu="photos//menu//";
        image.Menu+="menu_start.jpg";
    }
    else if(muse.x>=510&&muse.x<=770&&muse.y>=349&&muse.y<=450)
    {
        image.Menu="photos//menu//";
        image.Menu+="menu_leage table.jpg";
    }
    else if(muse.x>=510&&muse.x<=770&&muse.y>=503&&muse.y<=606)
    {
        image.Menu="photos//menu//";
        image.Menu+="menu_setting.jpg";
    }
    else if(muse.x>=510&&muse.x<=770&&muse.y>=659&&muse.y<=760)
    {
        image.Menu="photos//menu//";
        image.Menu+="menu_about.jpg";
    }
    else if(muse.x>=12&&muse.x<=144&&muse.y>=733&&muse.y<=789)
    {
        image.Menu="photos//menu//";
        image.Menu+="menu_exit.jpg";
    }
    else
    {
        image.Menu="photos//menu//";
        image.Menu+="menu.jpg";
    }
}
void dynamic_changes_in_choose_display()
{
    if(eventt.click)
        {
            if(muse_in_circle(circles_of_choose_player[0]))
            {
                nextt("player1",-1);
                istyping2=false;
                istyping1=false;
            }
            else if(muse_in_circle(circles_of_choose_player[1]))
            {
                nextt("player1",1);
                istyping2=false;
                istyping1=false;
            }
            else if(muse_in_circle(circles_of_choose_player[2]))
            {
                nextt("player2",-1);
                istyping2=false;
                istyping1=false;
            }
            else if(muse_in_circle(circles_of_choose_player[3]))
            {
                nextt("player2",1);
                istyping2=false;
                istyping1=false;
            }
            else if(muse_in_circle(circles_of_choose_player[4]))
            {
                nextt("boot1",-1);
                istyping2=false;
                istyping1=false;
            }
            else if(muse_in_circle(circles_of_choose_player[5]))
            {
                nextt("boot1",1);
                istyping2=false;
                istyping1=false;
            }
            else if(muse_in_circle(circles_of_choose_player[6]))
            {
                nextt("boot2",-1);
                istyping2=false;
                istyping1=false;
            }
            else if(muse_in_circle(circles_of_choose_player[7]))
            {
                nextt("boot2",1);
                istyping2=false;
                istyping1=false;
            }
            else if(muse_in_circle(circles_of_choose_player[8]))
            {
                nextt("ball",-1);
                istyping2=false;
                istyping1=false;
            }
            else if(muse_in_circle(circles_of_choose_player[9]))
            {
                nextt("ball",1);
                istyping2=false;
                istyping1=false;
            }
            else if(muse_in_circle(circles_of_choose_player[10]))
            {
                nextt("stadium",-1);
                istyping2=false;
                istyping1=false;
            }
            else if(muse_in_circle(circles_of_choose_player[11]))
            {
                nextt("stadium",1);
                istyping2=false;
                istyping1=false;
            }
            else if(muse_in_circle(circles_of_choose_player[12]))
            {
                nextt("plat",-1);
                istyping2=false;
                istyping1=false;
            }
            else if(muse_in_circle(circles_of_choose_player[13]))
            {
                nextt("plat",1);
                istyping2=false;
                istyping1=false;
            }
            else if(muse.x>=rects_of_choose_player[0].x1&&muse.x<=rects_of_choose_player[0].width+rects_of_choose_player[0].x1&&muse.y>=rects_of_choose_player[0].y1&&muse.y<=rects_of_choose_player[0].height+rects_of_choose_player[0].y1)
            {
                if(!istyping1)
                {
                    istyping2=false;
                    text=player1.name;
                }
                istyping1=true;
                SDL_StartTextInput();
            }
            else if(muse.x>=rects_of_choose_player[1].x1&&muse.x<=rects_of_choose_player[1].width+rects_of_choose_player[1].x1&&muse.y>=rects_of_choose_player[1].y1&&muse.y<=rects_of_choose_player[1].height+rects_of_choose_player[1].y1)
            {
                if(!istyping2)
                {
                    istyping1=false;
                    text=player2.name;
                }
                istyping2=true;
                SDL_StartTextInput();
            }
            else
            {
            SDL_StopTextInput();
            istyping1=false;
            istyping2=false;
            }
        }
}
void present_choose()
{
    texture(0,0,image.choose,L,W);
    texture(rects_of_choose_player[2].x1+15,rects_of_choose_player[2].y1+15,player1.head,rects_of_choose_player[2].width-30,rects_of_choose_player[2].height-30);
    texture(rects_of_choose_player[3].x1+15,rects_of_choose_player[3].y1+15,player2.head,rects_of_choose_player[3].width-30,rects_of_choose_player[3].height-30);
    texture(rects_of_choose_player[4].x1+67,rects_of_choose_player[4].y1+4,player1.foot,rects_of_choose_player[4].width-2*67,rects_of_choose_player[4].height-8);
    texture(rects_of_choose_player[5].x1+67,rects_of_choose_player[5].y1+4,player2.foot,rects_of_choose_player[5].width-2*67,rects_of_choose_player[5].height-8);
    texture(rects_of_choose_player[8].x1,rects_of_choose_player[8].y1,stadium,rects_of_choose_player[8].width,rects_of_choose_player[8].height);
    texture(rects_of_choose_player[9].x1,rects_of_choose_player[9].y1,plat,rects_of_choose_player[9].width,rects_of_choose_player[9].height);
    texture(circles_of_choose_player[14].x-circles_of_choose_player[14].r,circles_of_choose_player[14].y-circles_of_choose_player[14].r,bal.ball,2*circles_of_choose_player[14].r,2*circles_of_choose_player[14].r);
    write(player1.name,rects_of_choose_player[0].x1+7,rects_of_choose_player[0].y1,rects_of_choose_player[0].width-14,rects_of_choose_player[0].height,124);
    write(player2.name,rects_of_choose_player[1].x1+7,rects_of_choose_player[1].y1,rects_of_choose_player[1].width-14,rects_of_choose_player[1].height,124);
    if(player1.head!=" ")
    {
        write(name_of_powers[player1.power-1],rects_of_choose_player[6].x1+7,rects_of_choose_player[6].y1,rects_of_choose_player[6].width-14,rects_of_choose_player[6].height,124);
    }
    if(player2.head!=" ")
    {
        write(name_of_powers[player2.power-1],rects_of_choose_player[7].x1+7,rects_of_choose_player[7].y1,rects_of_choose_player[7].width-14,rects_of_choose_player[7].height,124);
    }
}
void Fade(string Adress)
{
    if(Adress=="0")
    {
        for(int i=0;i<55;i++)
        {
            boxRGBA(Renderer,0,0,L,W,0,0,0,i);
            SDL_RenderPresent(Renderer);
            SDL_Delay(16);
        }
        return ;
    }
    for(int i=255;i>0;i-=10)
    {
        texture(0,0,Adress,L,W);
        boxRGBA(Renderer,0,0,L,W,0,0,0,i);
        SDL_RenderPresent(Renderer);
        SDL_Delay(16);
    }
    return ;
}
void texture(int xp,int yp,string addressOfImage,int width,int height)
{
        int n = addressOfImage.length();
        char char_array[n+1];
        strcpy(char_array, addressOfImage.c_str());
        SDL_Texture *myTexture;
        myTexture = IMG_LoadTexture( Renderer, char_array);
        int w1, h1;
        SDL_QueryTexture(myTexture, NULL, NULL, &w1, &h1);
        SDL_Rect texr1;
        texr1.x = xp;
        texr1.y = yp;
        texr1.w = width;
        texr1.h = height;
        SDL_RenderCopy( Renderer, myTexture, NULL, &texr1);
        SDL_DestroyTexture(myTexture);
}
void rect(int x,int y,int w,int h,int R, int G, int B, int fill_boolian )
{

    SDL_Rect rectangle ;

    rectangle.x = x;

    rectangle.y = y;

    rectangle.w = w;

    rectangle.h = h;





    SDL_SetRenderDrawColor(Renderer, R, G, B, 255);

    if (fill_boolian==1)

        SDL_RenderFillRect(Renderer, &rectangle);

    SDL_RenderDrawRect(Renderer, &rectangle);

   // SDL_RenderPresent(Renderer);



}
void window_color(int R, int G, int B)
{

    SDL_SetRenderDrawColor( Renderer, R, G, B, 255 );

    SDL_RenderClear( Renderer );



    // Show the window

  //SDL_RenderPresent( Renderer );



}
bool muse_in_rect(rectt rec)
{
    if(muse.x>=rec.x1&&muse.x<=rec.x1+rec.width&&muse.y>=rec.y1&&muse.y<=rec.y1+rec.height&&muse.x>=0&&muse.x<=L&&muse.y>=0&&muse.y<=W)
    {
      return true;
    }
    return false;
}
void change_picture_of_pause()
{
    for(int i=0;i<4;i++)
    {
      if(muse_in_rect(rects_of_pause[i]))
        {
            image.pause="photos//pause//";
            image.pause+=to_string(i);
            image.pause+="pause.png";
            return ;
        }
    }
    image.pause="photos//pause//";
    image.pause+="pause.png";
    return ;
}
void present_game()
{
    fast_texture(0,0,texture_my.stadiumm,L,W-259);
    fast_texture(0,W-259,texture_my.platt,L,259);
    aalineRGBA(Renderer,0,W-259+129,L,W-259+129,255,255,255,255);
    fast_texture(tirak_r.x,tirak_r.y,texture_my.tirakr,tirak_r.arz,tirak_r.ertefa);
    fast_texture(tirak_l.x,tirak_l.y,texture_my.tirakl,tirak_l.arz,tirak_l.ertefa);
    texture(0,0,"photos//pause1.png",60,60);
    texture(L-60,0,"photos//pause2.png",60,60);
    rect(rects_of_game[0].x1,rects_of_game[0].y1,rects_of_game[0].width,rects_of_game[0].height,150,255,150,1);
    rect(rects_of_game[2].x1,rects_of_game[2].y1,rects_of_game[2].width,rects_of_game[2].height,150,255,150,1);
    rect(rects_of_game[4].x1,rects_of_game[4].y1,rects_of_game[4].width,rects_of_game[4].height,230, 138, 0,1);
    rect(rects_of_game[5].x1,rects_of_game[5].y1,rects_of_game[5].width,rects_of_game[5].height,0,0,0,1);
    rect(rects_of_game[6].x1,rects_of_game[6].y1,rects_of_game[6].width,rects_of_game[6].height,0, 0, 102,1);
    rect(rects_of_game[7].x1,rects_of_game[7].y1,rects_of_game[7].width,rects_of_game[7].height,0,0,0,1);
    rect(rects_of_game[8].x1,rects_of_game[8].y1,rects_of_game[8].width,rects_of_game[8].height,0, 0, 102,1);
    rect(rects_of_game[1].x1,rects_of_game[1].y1,player1.t_power*rects_of_game[1].width,rects_of_game[1].height,255*player1.t_power, 0, 0,1); //power p1
    rect(rects_of_game[3].x1-player2.t_power*rects_of_game[3].width,rects_of_game[3].y1,player2.t_power*rects_of_game[3].width,rects_of_game[3].height,255*player2.t_power, 0, 0,1); //power p2
    write(player1.name,rects_of_game[6].x1+3,rects_of_game[6].y1+1,rects_of_game[6].width-6,rects_of_game[6].height-2,124);
    write(player2.name,rects_of_game[8].x1+3,rects_of_game[8].y1+1,rects_of_game[8].width-6,rects_of_game[8].height-2,124);
    write(to_string(player1.gol),rects_of_game[5].x1+1,rects_of_game[5].y1+1,rects_of_game[5].width-2,rects_of_game[5].height-2,124);
    write(to_string(player2.gol),rects_of_game[7].x1+1,rects_of_game[7].y1+1,rects_of_game[7].width-2,rects_of_game[7].height-2,124);
    if(eventt.power_p1==9)
    {
        write(to_string(((int)eventt.start_time_power_p1/10)/100),rects_of_game[4].x1+4,rects_of_game[4].y1,rects_of_game[4].width-8,rects_of_game[4].height,124);
    }
    else if(eventt.power_p2==9)
    {
        write(to_string(((int)eventt.start_time_power_p2/10)/100),rects_of_game[4].x1+4,rects_of_game[4].y1,rects_of_game[4].width-8,rects_of_game[4].height,124);
    }
    else
    {
        write(to_string(((int)timer_game/10)/100),rects_of_game[4].x1+4,rects_of_game[4].y1,rects_of_game[4].width-8,rects_of_game[4].height,124);
    }
}
void present_pause()
{
    string l0="              How to Play";
    string l1="           General controls";
    string l2="------------------------------------------";
    string l3="Player one                 Player two";
    string l4="Move right=D               Move right=RIGHT";
    string l5="Move left=S                Move left=LEFT";
    string l6="Jump=W                     Jump=UP";
    string l8="               Exit=ESC";
    string l9="            Action Controls";
    string l10="------------------------------------------";
    string l11="Player one                Player two";
    string l12="Shoot=S                   Shoot=DOWN";
    string l13="Power=Q                   Power=RSHIFT";
    boxRGBA(Renderer,0,0,L,W,0,0,0,190);
    texture(240,100,image.pause,500,700);
    boxRGBA(Renderer,640,260,1000,540,77, 255, 77,190);
    stringRGBA(Renderer,650,279,l0.c_str(),0,0,0,255);
    stringRGBA(Renderer,650,298,l1.c_str(),0,0,0,255);
    stringRGBA(Renderer,650,317,l2.c_str(),0,0,0,255);
    stringRGBA(Renderer,650,336,l3.c_str(),0,0,0,255);
    stringRGBA(Renderer,650,355,l4.c_str(),0,0,0,255);
    stringRGBA(Renderer,650,374,l5.c_str(),0,0,0,255);
    stringRGBA(Renderer,650,393,l6.c_str(),0,0,0,255);
    stringRGBA(Renderer,650,431,l8.c_str(),0,0,0,255);
    stringRGBA(Renderer,650,450,l9.c_str(),0,0,0,255);
    stringRGBA(Renderer,650,469,l10.c_str(),0,0,0,255);
    stringRGBA(Renderer,650,488,l11.c_str(),0,0,0,255);
    stringRGBA(Renderer,650,507,l12.c_str(),0,0,0,255);
    stringRGBA(Renderer,650,526,l13.c_str(),0,0,0,255);

}
void textureEx (int xp,int yp,string addressOfImage,int width,int height,int point_x,int point_y,double angle)
{
        int n = addressOfImage.length();
        char char_array[n+1];
        strcpy(char_array, addressOfImage.c_str());
        SDL_Texture *myTexture;
        myTexture = IMG_LoadTexture( Renderer, char_array);
        int w1, h1;
        SDL_QueryTexture(myTexture, NULL, NULL, &w1, &h1);
        SDL_Rect texr1;
        texr1.x = xp;
        texr1.y = yp;
        texr1.w = width;
        texr1.h = height;
        SDL_Point point={point_x, point_y};
        SDL_RenderCopyEx(Renderer,myTexture,NULL,&texr1,angle,&point,SDL_FLIP_NONE);
        SDL_DestroyTexture(myTexture);
}
void set_first()
{
    eventt.click=false;
    player1.boot.x=player1.x-40;
    player1.boot.y=player1.y+player1.r_head-34;
    player2.boot.x=player2.x-player2.boot.tool+40;
    player2.boot.y=player2.y+player2.r_head-34;
   // player1.gam_x=player1.boot.point.x;
}
void start_of_game()
{
            Fade("0");
            for(int i=255;i>0;i-=5)
            {
                texture(0,0,stadium,L,W-259);
                texture(0,W-259,plat,L,259);
                aalineRGBA(Renderer,0,W-259+129,L,W-259+129,255,255,255,255);
                texture(L-160,W-259+129+10-363,"darvazeh.png",160,363);
                texture(0,W-259+129+10-363,"darvazeh.png",160,363);
                boxRGBA(Renderer,0,0,L,W,0,0,0,i);
                SDL_RenderPresent(Renderer);
                SDL_Delay(16);
            }
            Display.About=false;
            Display.Game=true;
            Display.Pause=false;
            Display.Setting=false;
            Display.Start=false;
            Display.choose=false;
            for(int i=400;i>0;i-=13)
            {
                texture(0,0,stadium,L,W-259);
                texture(0,W-259,plat,L,259);
                textureEx(player1.boot.x-i,player1.boot.y,player1.foot,player1.boot.tool,player1.boot.arz,player1.boot.point.x,player1.boot.point.y,player1.boot.angle);
                texture(player1.x-player1.r_head-i,player1.y-player1.r_head,player1.head,2*player1.r_head,2*player1.r_head);
                textureEx(player2.boot.x+i,player2.boot.y,player2.foot,player2.boot.tool,player2.boot.arz,player2.boot.point.x,player2.boot.point.y,player2.boot.angle);
                texture(player2.x-player2.r_head+i,player2.y-player2.r_head,player2.head,2*player2.r_head,2*player2.r_head);
                aalineRGBA(Renderer,0,W-259+129,L,W-259+129,255,255,255,255);
                texture(L-160,W-259+129+10-363,"darvazeh.png",160,363);
                texture(0,W-259+129+10-363,"darvazeh.png",160,363);
                SDL_RenderPresent(Renderer);
                SDL_Delay(16);
            }
        return ;
}
void barkhord_toop()
{
    if((bal.x+bal.r>=L&&bal.vx0>0)||(bal.x-bal.r<=10&&bal.vx0<0))  // chap rast
    {
        Mix_PlayChannel(-1, collision, 0);
        bal.vx*=-1;
        t=0;
        bal.x0=bal.x;
        bal.y0=bal.y;
        bal.vx0=bal.vx;
        bal.vy0=bal.vy;
    }
    if(bal.y+bal.r>=W-130&&bal.vy>0)  // bala paeen
    {
        Mix_PlayChannel(-1, collision, 0);
        bal.vy*=-bal.z.kaf;
        t=0;
        bal.x0=bal.x;
        bal.y0=bal.y;
        bal.vx0=bal.vx;
        bal.vy0=bal.vy;
    }
    else if(bal.y-bal.r<=0&&bal.vy<0)
    {
        Mix_PlayChannel(-1, collision, 0);
        bal.vy*=-1;
        t=0;
        bal.x0=bal.x;
        bal.y0=bal.y;
        bal.vx0=bal.vx;
        bal.vy0=bal.vy;
    }
    if((bal.y+bal.r>=tirak_l.y&&bal.y-bal.r<=tirak_r.y)&&((bal.x-bal.r<tirak_l.x+tirak_l.arz)&&(bal.x+bal.r>=tirak_l.x))&&bal.vy>0)   //tirak left
    {
        Mix_PlayChannel(-1, collision, 0);
        bal.vy*=-1;
        t=0;
        bal.x0=bal.x;
        bal.y0=bal.y;
        bal.vx0=bal.vx;
        bal.vy0=bal.vy;
    }
    else if((bal.x-bal.r<=tirak_l.x+tirak_l.arz&&bal.x+bal.r>=tirak_l.x+tirak_l.arz)&&(bal.y+bal.r>=tirak_l.y&&bal.y-bal.r<=tirak_l.y+32)&&bal.vx<0)
    {
        Mix_PlayChannel(-1,goalcheering, 0);
        bal.vx*=-bal.z.tirak;
        t=0;
        bal.x0=bal.x;
        bal.y0=bal.y;
    }
    else if((bal.y-bal.r<=tirak_l.y+32&&bal.y+bal.r>=tirak_l.y+32)&&((bal.x-bal.r<=tirak_l.x+tirak_l.arz)&&(bal.x+bal.r>=tirak_l.x))&&bal.vy<0)
    {
        Mix_PlayChannel(-1, collision, 0);
        bal.vy*=-1;
        t=0;
        bal.x0=bal.x;
        bal.y0=bal.y;
        bal.vx0=bal.vx;
        bal.vy0=bal.vy;
    }
    else if((bal.x+bal.r>tirak_r.x&&bal.x-bal.r<=L)&&(bal.y+bal.r>=tirak_r.y&&bal.y<=tirak_r.y)&&bal.vy>0)            //tirak right
    {
        Mix_PlayChannel(-1, collision, 0);
        bal.vy*=-1;
        t=0;
        bal.x0=bal.x;
        bal.y0=bal.y;
        bal.vx0=bal.vx;
        bal.vy0=bal.vy;
    }
    else if((bal.x+bal.r>=tirak_r.x&&bal.x-bal.r<=tirak_r.x)&&(bal.y+bal.r>=tirak_r.y&&bal.y-bal.r<=tirak_r.y+32)&&bal.vx>0)
    {
        Mix_PlayChannel(-1,goalcheering, 0);
        bal.vx*=-bal.z.tirak;
        t=0;
        bal.x0=bal.x;
        bal.y0=bal.y;
        bal.vx0=bal.vx;
        bal.vy0=bal.vy;
    }
    else if((bal.y-bal.r<=tirak_r.y+32&&bal.y>=tirak_r.y+32)&&(bal.x+bal.r>=tirak_r.x&&bal.x<=L)&&bal.vy<0)
    {
        Mix_PlayChannel(-1, collision, 0);
        bal.vy*=-1;
        t=0;
        bal.x0=bal.x;
        bal.y0=bal.y;
        bal.vx0=bal.vx;
        bal.vy0=bal.vy;
    }

    if(barkhord_2noghte(davaran_x(player1.boot.x,player1.boot.y,pbp1._1.x,pbp1._1.y,player1.boot.angle),davaran_y(player1.boot.x,player1.boot.y,pbp1._1.x,pbp1._1.y,player1.boot.angle),davaran_x(player1.boot.x,player1.boot.y,pbp1._2.x,pbp1._2.y,player1.boot.angle),davaran_y(player1.boot.x,player1.boot.y,pbp1._2.x,pbp1._2.y,player1.boot.angle),true))
    {
        Mix_PlayChannel(-1, collision, 0);
        t=0;
        bal.y0=bal.y;
        bal.x0=bal.x;
        bal.vx=(sqrt(bal.vx*bal.vx+bal.vy*bal.vy)+50)*cos(45*3.14/180);
        bal.vy=-1*(sqrt(bal.vx*bal.vx+bal.vy*bal.vy)+50)*sin(45*3.14/180);
        bal.vx0=bal.vx;
        bal.vy0=bal.vy;
    }
    else if(sqrt((bal.x-player1.x)*(bal.x-player1.x)+(bal.y-player1.y)*(bal.y-player1.y))<=bal.r+3+player1.r_head)
    {
        Mix_PlayChannel(-1, collision, 0);
        t=0;
        double delta_y=bal.y-player1.y;
        double delta_x=player1.x-bal.x;
        double dist=sqrt((bal.x-player1.x)*(bal.x-player1.x)+(bal.y-player1.y)*(bal.y-player1.y));
        double sinteta=delta_y/dist;
        double costeta=delta_x/dist;
        double vxx=(bal.vx*sinteta+bal.vy*costeta)*sinteta-abs((int)(bal.vx*costeta-bal.vy*sinteta)+23)*costeta;
        bal.vy=(bal.vx*sinteta+bal.vy*costeta)*costeta+abs((int)(bal.vx*costeta-bal.vy*sinteta)-23)*sinteta;
        bal.vx=vxx;
        bal.x=player1.x-(bal.r+player1.r_head)*costeta;
        bal.y=player1.y+(bal.r+player1.r_head)*sinteta;
        bal.x0=bal.x;
        bal.y0=bal.y;
        bal.vx0=bal.vx;
        bal.vy0=bal.vy;
    }
    else if(barkhord_2noghte(davaran_x(player1.boot.x,player1.boot.y,pbp1._2.x,pbp1._2.y,player1.boot.angle),davaran_y(player1.boot.x,player1.boot.y,pbp1._2.x,pbp1._2.y,player1.boot.angle),davaran_x(player1.boot.x,player1.boot.y,pbp1._3.x,pbp1._3.y,player1.boot.angle),davaran_y(player1.boot.x,player1.boot.y,pbp1._3.x,pbp1._3.y,player1.boot.angle),true))
    {
        Mix_PlayChannel(-1, collision, 0);
        t=0;
        bal.y0=bal.y;
        bal.x0=bal.x;
        bal.vx=(sqrt(bal.vx*bal.vx+bal.vy*bal.vy)+50)*cos(25*3.14/180);
        bal.vy=-1*(sqrt(bal.vx*bal.vx+bal.vy*bal.vy)+50)*sin(25*3.14/180);
        bal.vx0=bal.vx;
        bal.vy0=bal.vy;
    }
    else if(barkhord_2noghte(davaran_x(player1.boot.x,player1.boot.y,pbp1._3.x,pbp1._3.y,player1.boot.angle),davaran_y(player1.boot.x,player1.boot.y,pbp1._3.x,pbp1._3.y,player1.boot.angle),davaran_x(player1.boot.x,player1.boot.y,pbp1._4.x,pbp1._4.y,player1.boot.angle),davaran_y(player1.boot.x,player1.boot.y,pbp1._4.x,pbp1._4.y,player1.boot.angle),false))
    {
        Mix_PlayChannel(-1, collision, 0);
        t=0;
        bal.y0=bal.y;
        bal.x0=bal.x;
        bal.vx=-1*(sqrt(bal.vx*bal.vx+bal.vy*bal.vy)+50)*cos(-15*3.14/180);
        bal.vy=-1*(sqrt(bal.vx*bal.vx+bal.vy*bal.vy)+50)*sin(-15*3.14/180);
        bal.vx0=bal.vx;
        bal.vy0=bal.vy;

    }

    if(barkhord_2noghte(davaran_x(player2.boot.x+player2.boot.tool,player2.boot.y,pbp2._1.x,pbp2._1.y,player2.boot.angle),davaran_y(player2.boot.x+player2.boot.tool,player2.boot.y,pbp2._1.x,pbp2._1.y,player2.boot.angle),davaran_x(player2.boot.x+player2.boot.tool,player2.boot.y,pbp2._2.x,pbp2._2.y,player2.boot.angle),davaran_y(player2.boot.x+player2.boot.tool,player2.boot.y,pbp2._2.x,pbp2._2.y,player2.boot.angle),true))
    {
        Mix_PlayChannel(-1, collision, 0);
        t=0;
        bal.y0=bal.y;
        bal.x0=bal.x;
        bal.vx=-1*(sqrt(bal.vx*bal.vx+bal.vy*bal.vy)+50)*cos(45*3.14/180);
        bal.vy=-1*(sqrt(bal.vx*bal.vx+bal.vy*bal.vy)+50)*sin(45*3.14/180);
        bal.vx0=bal.vx;
        bal.vy0=bal.vy;
    }
    else if(barkhord_2noghte(davaran_x(player2.boot.x+player2.boot.tool,player2.boot.y,pbp2._2.x,pbp2._2.y,player2.boot.angle),davaran_y(player2.boot.x+player2.boot.tool,player2.boot.y,pbp2._2.x,pbp2._2.y,player2.boot.angle),davaran_x(player2.boot.x+player2.boot.tool,player2.boot.y,pbp2._3.x,pbp2._3.y,player2.boot.angle),davaran_y(player2.boot.x+player2.boot.tool,player2.boot.y,pbp2._3.x,pbp2._3.y,player2.boot.angle),false))
    {
        Mix_PlayChannel(-1, collision, 0);
        t=0;
        bal.y0=bal.y;
        bal.x0=bal.x;
        bal.vx=-1*(sqrt(bal.vx*bal.vx+bal.vy*bal.vy)+50)*cos(25*3.14/180);
        bal.vy=-1*(sqrt(bal.vx*bal.vx+bal.vy*bal.vy)+50)*sin(25*3.14/180);
        bal.vx0=bal.vx;
        bal.vy0=bal.vy;

    }
    else if(barkhord_2noghte(davaran_x(player2.boot.x,player2.boot.y,pbp2._3.x,pbp2._3.y,player2.boot.angle),davaran_y(player2.boot.x,player2.boot.y,pbp2._3.x,pbp1._3.y,player2.boot.angle),davaran_x(player2.boot.x,player2.boot.y,pbp2._4.x,pbp2._4.y,player2.boot.angle),davaran_y(player2.boot.x,player2.boot.y,pbp2._4.x,pbp2._4.y,player2.boot.angle),false))
    {
        Mix_PlayChannel(-1, collision, 0);
        t=0;
        bal.y0=bal.y;
        bal.x0=bal.x;
        bal.vx=-1*(sqrt(bal.vx*bal.vx+bal.vy*bal.vy)+50)*cos(-15*3.14/180);
        bal.vy=-1*(sqrt(bal.vx*bal.vx+bal.vy*bal.vy)+50)*sin(-15*3.14/180);
        bal.vx0=bal.vx;
        bal.vy0=bal.vy;

    }
    else if(sqrt((bal.x-player2.x)*(bal.x-player2.x)+(bal.y-player2.y)*(bal.y-player2.y))<=bal.r+3+player2.r_head)
    {
        Mix_PlayChannel(-1, collision, 0);
        t=0;
        double delta_y=bal.y-player2.y;
        double delta_x=player2.x-bal.x;
        double dist=sqrt((bal.x-player2.x)*(bal.x-player2.x)+(bal.y-player2.y)*(bal.y-player2.y));
        double sinteta=delta_y/dist;
        double costeta=delta_x/dist;
        double vxx=(bal.vx*sinteta+bal.vy*costeta)*sinteta-abs((int)(bal.vx*costeta-bal.vy*sinteta)+23)*costeta;
        bal.vy=(bal.vx*sinteta+bal.vy*costeta)*costeta+abs((int)(bal.vx*costeta-bal.vy*sinteta)-23)*sinteta;
        bal.vx=vxx;
        bal.x=player2.x-(bal.r+player2.r_head)*costeta;
        bal.y=player2.y+(bal.r+player2.r_head)*sinteta;
        bal.x0=bal.x;
        bal.y0=bal.y;
        bal.vx0=bal.vx;
        bal.vy0=bal.vy;
    }
    if(eventt.power_p1==4)
    {
        if(barkhord_2noghte(tirak_l.x+tirak_l.arz,tirak_l.y,tirak_l.x+tirak_l.arz,tirak_l.y+tirak_l.ertefa+40,true)&&bal.vx0<0)
        {
        Mix_PlayChannel(-1, collision, 0);
            bal.vx*=-1;
            t=0;
            bal.x0=bal.x;
            bal.y0=bal.y;
            bal.vx0=bal.vx;
            bal.vy0=bal.vy;
        }
    }
    else if(bal.x<=tirak_l.x+tirak_l.arz&&bal.y-bal.r>tirak_l.y+32)
    {
        Mix_PlayChannel(-1,goalcheering, 0);
        SDL_Delay(500);
        eventt.power_p1=0;
        eventt.power_p2=0;
        player1.t_power+=0.2;
        shoroo_mojaddad(1);
    }
     if(eventt.power_p2==4)
    {
        if(barkhord_2noghte(tirak_r.x,tirak_r.y,tirak_r.x,tirak_r.y+tirak_r.ertefa+40,false)&&bal.vx0>0)
        {
            Mix_PlayChannel(-1, collision, 0);
            bal.vx*=-1;
            t=0;
            bal.x0=bal.x;
            bal.y0=bal.y;
            bal.vx0=bal.vx;
            bal.vy0=bal.vy;
        }
    }
    else if(bal.x>=tirak_r.x&&bal.y-bal.r>tirak_r.y+32)
    {
        Mix_PlayChannel(-1,goalcheering, 0);
        SDL_Delay(500);
        eventt.power_p1=0;
        eventt.power_p2=0;
        player2.t_power+=0.2;
        shoroo_mojaddad(2);
    }
}
void do_powers()
{
    if(eventt.power_p1!=0&&timer_game-eventt.start_time_power_p1<=8000)
    {
        switch(eventt.power_p1)
        {
            case 1:
            {
                break;
            }
            case 2:
            {
                 player1.gam_x=25;
                 break;
            }
            case 3:
            {
                 break;
            }
            case 5:
            {
                  bal.r=40;
                  break;
            }
        }
    }
    else
    {
        set_normal_p1();
    }

    if(eventt.power_p2!=0&&timer_game-eventt.start_time_power_p2<=8000)
    {
        switch(eventt.power_p2)
        {
            case 1:
            {
                break;
            }
            case 2:
            {
                 player2.gam_x=25;
                 break;
            }
            case 5:
            {
                bal.r=40;
                break;
            }
        }
    }
    else
    {
        set_normal_p2();
    }

    if(cheet.cheet&&timer_game-cheet.time_start>=4000)
    {
        tirak_l.y=W-483-90;
        tirak_l.ertefa=363+90;
        tirak_r.y=W-483-90;
        tirak_r.ertefa=363+90;
        cheet.cheet=false;
        cheet.time_start=0;
    }
    if(eventt.power_p1!=5&&eventt.power_p2!=5)
    {
        bal.r=20;
    }
}
void set_normal_p1()
{
    if(eventt.power_p1==9)
    {
        timer_game=eventt.start_time_power_p1;
    }
    eventt.power_p1=0;
    if(eventt.power_p2!=7)
    {
    player1.gam_x=15;
    }
}
void set_normal_p2()
{
    if(eventt.power_p2==9)
    {
        timer_game=eventt.start_time_power_p2;
    }
    eventt.power_p2=0;
    if(eventt.power_p1!=7)
    {
        player2.gam_x=15;
    }
}
double diffclock(clock_t clock1,clock_t clock2)
{
    double diffticks=-(clock1-clock2);
    double diffms=(diffticks);
    return diffms;
}
void openfiles_and_make_tablefile()
{
    file.num=0;
    int i=0;
    ifstream names("files//name.txt");
    while (names.good())
    {
     names>>file.asami[i];
     i++;
     file.num++;
    }
    if(file.asami[i-1]=="")
    {
        file.num--;
    }
    names.close();
    ifstream nbord("files//nbord.txt");
    if (nbord.good())
    {
           for (int i=0;i<file.num;i++)
           {
               nbord>>file.tedad_bord[i];
           }
           nbord.close();
    }
    ifstream ngoalzade("files//ngoalzade.txt");
    if (ngoalzade.good())
    {
        for (int i=0;i<file.num;i++)
        {
            ngoalzade>>file.tedad_goal_zade[i];
        }

        ngoalzade.close();
    }
    ifstream ngoalkhorde("files//ngoalkhorde.txt");
    if (ngoalkhorde.good())
    {
        for (int i=0;i<file.num;i++)
        {
            ngoalkhorde>>file.tedad_goal_khorde[i];
        }
        ngoalkhorde.close();
    }
    ifstream nbakht("files//nbakht.txt");
    if (nbakht.good())
    {
           for (int i=0;i<file.num;i++)
           {
               nbakht>>file.tedad_bakht[i];
           }
           nbakht.close();
    }
    ifstream nmosavi("files//nmosavi.txt");
    if (nmosavi.good())
    {
           for (int i=0;i<file.num;i++)
           {
               nmosavi>>file.tedad_mosavi[i];
           }
           nmosavi.close();
    }
    for (int i=0;i<file.num;i++)
    {
        file.tafazol_gol[i]=-file.tedad_goal_khorde[i]+file.tedad_goal_zade[i];
    }
    for (int i=0;i<file.num;i++)
    {
        file.score[i]=3*file.tedad_bord[i]+file.tedad_mosavi[i];
    }
    for ( int i=0;i<file.num;i++)
    {
        file.tedad_bazi[i]=file.tedad_bord[i]+file.tedad_mosavi[i]+file.tedad_bakht[i];
    }
    bool s=true;
    for ( int j=0;s;j++)
    {
        s=false;
        for (int i=0;i<file.num-1;i++)
        {
            if (file.score[i]<file.score[i+1])
            {
                swap(file.tafazol_gol[i],file.tafazol_gol[i+1]);
                swap(file.asami[i],file.asami[i+1]);
                swap(file.tedad_mosavi[i],file.tedad_mosavi[i+1]);
                swap(file.score[i],file.score[i+1]);
                swap(file.tedad_bazi[i],file.tedad_bazi[i+1]);
                swap(file.tedad_bord[i],file.tedad_bord[i+1]);
                swap(file.tedad_bakht[i],file.tedad_bakht[i+1]);
                swap(file.tedad_goal_zade[i],file.tedad_goal_zade[i+1]);
                swap(file.tedad_goal_khorde[i],file.tedad_goal_khorde[i+1]);
                s=true;
            }
        }
    }
    ofstream table("files//table.txt");
    if (table.good())
    {
        table<<"                                              (((top players)))                                           "<<endl;
        table<<setw(20)<<"name|"<<setw(20)<<"score|"<<setw(20)<<"match|"<<setw(20)<<"goal average|"<<setw(20)<<"wins|"<<setw(20)<<"loss|"<<setw(20)<<"draws|"<<endl;
        for (int i=0;i<file.num;i++)
        {
            table<<setw(20)<<file.asami[i]<<"|"<<setw(20)<<file.score[i]<<"|"<<setw(20)<<file.tedad_bazi[i]<<"|"<<setw(20)<<file.tafazol_gol[i]<<"|"<<setw(20)<<file.tedad_bord[i]<<"|"<<setw(20)<<file.tedad_bakht[i]<<"|"<<setw(20)<<file.tedad_mosavi[i]<<"|"<<endl;
        }
    }
    table.close();
}
void add_players_to_files()
{
    int tedad_goal_khorde1=0,tedad_goal_zade1=0,tedad_bord1=0,tedad_mosavi1=0,tedad_bakht1=0,tedad_bazi1=0,point1=0,ekhtelaf1=0;
    int tedad_goal_khorde2=0,tedad_goal_zade2=0,tedad_bord2=0,tedad_mosavi2=0,tedad_bakht2=0,tedad_bazi2=0,point2=0,ekhtelaf2=0;
    bool flag1=false,flag2=false;
    int c1=-1,c2=-1;
     for (int i=0;i<file.num;i++)
     {
         if (player1.name==file.asami[i])
         {
             flag1=true;
             c1=i;
         }
          if (player2.name==file.asami[i])
         {
             flag2=true;
             c2=i;
         }
     }
     if (player1.gol==player2.gol&& c1==-1 &&c2!=-1)
     {
        tedad_goal_zade1=player1.gol;
        tedad_goal_khorde1=player2.gol;
        tedad_mosavi1++;
        point1++;
        ekhtelaf1=tedad_goal_zade1-tedad_goal_khorde1;
        file.tedad_mosavi[c2]++;
        file.tedad_goal_zade[c2]=player2.gol;
        file.tedad_goal_khorde[c2]=player1.gol;
     }
      else if (player1.gol==player2.gol && c1!=-1 &&c2==-1)
     {
        tedad_goal_zade2=player2.gol;
        tedad_goal_khorde2=player1.gol;
        tedad_mosavi2++;
        point2++;
        ekhtelaf2=tedad_goal_zade2-tedad_goal_khorde2;
        file.tedad_mosavi[c1]++;
        file.tedad_goal_zade[c1]=player2.gol;
        file.tedad_goal_khorde[c1]=player1.gol;
     }
      else if (player1.gol==player2.gol && c1!=-1 &&c2!=-1)
     {
        file.tedad_mosavi[c2]++;
        file.tedad_goal_zade[c2]=player2.gol;
        file.tedad_goal_khorde[c2]=player1.gol;
        file.tafazol_gol[c2]=file.tedad_goal_zade[c2]-file.tedad_goal_khorde[c2];
        file.tedad_mosavi[c1]++;
        file.tedad_goal_zade[c1]=player2.gol;
        file.tedad_goal_khorde[c1]=player1.gol;
     }
      else if (player1.gol==player2.gol && c1==-1 &&c2==-1)
     {
       tedad_goal_zade1=player1.gol;
       tedad_goal_khorde1=player2.gol;
       tedad_mosavi1++;
       point1++;
       ekhtelaf1=tedad_goal_zade1-tedad_goal_khorde1;
       tedad_goal_zade2=player2.gol;
       tedad_goal_khorde2=player2.gol;
       tedad_mosavi2++;
       point2++;
       ekhtelaf2=tedad_goal_zade2-tedad_goal_khorde2;
     }
      else if (player1.gol>=player2.gol && c1==-1 &&c2!=-1)
     {
        tedad_goal_zade1=player1.gol;
        tedad_goal_khorde1=player2.gol;
        tedad_bord1++;
        file.tedad_bakht[c2]++;
        point1=3;
        ekhtelaf1=tedad_goal_zade1-tedad_goal_khorde1;
        file.tedad_goal_zade[c2]=player2.gol;
        file.tedad_goal_khorde[c2]=player1.gol;
     }
      else if (player1.gol>=player2.gol && c1!=-1 &&c2==-1)
     {
        tedad_goal_zade2=player2.gol;
        tedad_goal_khorde2=player1.gol;
        tedad_bakht2++;
        file.tedad_bord[c1];
        ekhtelaf2=tedad_goal_zade2-tedad_goal_khorde2;
        file.tedad_goal_zade[c1]=player2.gol;
        file.tedad_goal_khorde[c1]=player1.gol;
     }
      else if (player1.gol>=player2.gol && c1!=-1 &&c2!=-1)
     {
         file.tedad_goal_zade[c2]=player2.gol;
         file.tedad_goal_khorde[c2]=player1.gol;
         file.tedad_bord[c1]++;
         file.tedad_bakht[c2]++;
         file.tedad_goal_zade[c1]=player1.gol;
         file.tedad_goal_khorde[c1]=player2.gol;
     }
      else if (player1.gol>=player2.gol && c1==-1 &&c2==-1)
     {
       tedad_goal_zade1=player1.gol;
       tedad_goal_khorde1=player2.gol;
       tedad_bord1++;
       point1=3;
       tedad_bakht2++;
       ekhtelaf1=tedad_goal_zade1-tedad_goal_khorde1;
       tedad_goal_zade2=player2.gol;
       tedad_goal_khorde2=player1.gol;
       ekhtelaf2=tedad_goal_zade2-tedad_goal_khorde2;
     }
      else if (player1.gol<=player2.gol && c1==-1 &&c2!=-1)
     {
        tedad_goal_zade1=player1.gol;
        tedad_goal_khorde1=player2.gol;
        tedad_bakht1++;
        ekhtelaf1=tedad_goal_zade1-tedad_goal_khorde1;
        file.tedad_bord[c2]++;
        file.tedad_goal_zade[c2]=player2.gol;
        file.tedad_goal_khorde[c2]=player1.gol;
     }
      else if (player1.gol<=player2.gol && c1!=-1 &&c2==-1)
     {
        tedad_goal_zade2=player2.gol;
        tedad_goal_khorde2=player1.gol;
        tedad_bord2++;
        point2=3;
        ekhtelaf2=tedad_goal_zade2-tedad_goal_khorde2;
        file.tedad_bakht[c1]++;
        file.tedad_goal_zade[c1]=player1.gol;
        file.tedad_goal_khorde[c1]=player2.gol;
     }
      else if (player1.gol<=player2.gol && c1!=-1 &&c2!=-1)
     {
        file.tedad_bord[c2]++;
        file.tedad_bakht[c1]++;
        file.tedad_goal_zade[c2]=player2.gol;
        file.tedad_goal_khorde[c2]=player1.gol;
        file.tedad_goal_zade[c1]=player1.gol;
        file.tedad_goal_khorde[c1]=player2.gol;
     }
      else if (player1.gol<=player2.gol && c1==-1 &&c2==-1)
     {
       tedad_goal_zade1=player1.gol;
       tedad_goal_khorde1=player2.gol;
       tedad_bakht1++;
       ekhtelaf1=tedad_goal_zade1-tedad_goal_khorde1;
       tedad_goal_zade2=player2.gol;
       tedad_goal_khorde2=player1.gol;
       tedad_bord2++;
       point2=3;
       ekhtelaf2=tedad_goal_zade2-tedad_goal_khorde2;
     }
    ofstream nbord("files//nbord.txt");
    if (nbord.good())
    {
           for (int i=0;i<file.num;i++)
           {
               nbord<<file.tedad_bord[i]<<endl;
           }
           if (!flag1)
           nbord<<tedad_bord1<<endl;
           if (!flag2)
           nbord<<tedad_bord2<<endl;
           nbord.close();
    }
    ofstream ngoalzade("files//ngoalzade.txt");
    if (ngoalzade.good())
    {
        for (int i=0;i<file.num;i++)
        {
            ngoalzade<<file.tedad_goal_zade[i]<<endl;
        }
        if (!flag1)
          ngoalzade<<tedad_goal_zade1<<endl;
          if (!flag2)
          ngoalzade<<tedad_goal_zade2<<endl;
        ngoalzade.close();
    }
    ofstream ngoalkhorde("files//ngoalkhorde.txt");
    if (ngoalkhorde.good())
    {
        for (int i=0;i<file.num;i++)
        {
            ngoalkhorde<<file.tedad_goal_khorde[i]<<endl;
        }
        if (!flag1)
        ngoalkhorde<<tedad_goal_khorde1<<endl;
        if (!flag2)
        ngoalkhorde<<tedad_goal_khorde2<<endl;
        ngoalkhorde.close();
    }
    ofstream nbakht("files//nbakht.txt");
    if (nbakht.good())
    {
           for (int i=0;i<file.num;i++)
           {
               nbakht<<file.tedad_bakht[i]<<endl;
           }
           if (!flag1)
            nbakht<<tedad_bakht1<<endl;
            if (!flag2)
            nbakht<<tedad_bakht2<<endl;
           nbakht.close();
    }
    ofstream nmosavi("files//nmosavi.txt");
    if (nmosavi.good())
    {
           for (int i=0;i<file.num;i++)
           {
               nmosavi<<file.tedad_mosavi[i]<<endl;
           }
           if (!flag1)
           nmosavi<<tedad_mosavi1<<endl;
           if (!flag2)
           nmosavi<<tedad_mosavi2<<endl;
           nmosavi.close();
    }
    ofstream names("files//name.txt");
    if (names.good())
    {
           for (int i=0;i<file.num;i++)
           {
               names<<file.asami[i]<<endl;
           }
           if (!flag1)
           names<<player1.name<<endl;
           if (!flag2)
           names<<player2.name<<endl;
           names.close();
    }
}
void Do_game()
{
        if(timer_game>90000||player1.gol==7||player2.gol==7)
        {
            Display.Game=false;
            Display.endgame=true;
            add_players_to_files();
        }

        if(player1.t_power<1)
            player1.t_power+=delt/30000.0;
        else if(player1.t_power>1)
            player1.t_power=1;
        if(player2.t_power<1)
            player2.t_power+=delt/30000.0;
        else if(player2.t_power>1)
            player2.t_power=1;

        if(eventt.click)
        {
            if(muse_in_circle(circles_of_pause[0]))
            {
                pause=1;
                Display.Game=false;
                Display.Pause=true;
            }
            else if(muse_in_circle(circles_of_pause[1]))
            {
                pause=2;
                Display.Game=false;
                Display.Pause=true;
            }
        }
        if(player1.vy<0||player1.y<550&&eventt.power_p2!=6)
        {
            player1.y+=player1.vy*0.117;
            player1.vy+=200*0.117;
        }
        else if(eventt.power_p2!=6)
        {
            player1.vy=0;
            player1.y=550;
        }

        if(player2.vy<0||player2.y<550&&eventt.power_p1!=6)
        {
            player2.y+=player2.vy*0.117;
            player2.vy+=200*0.117;
        }
        else if(eventt.power_p1!=6)
        {
            player2.vy=0;
            player2.y=550;
        }
        if(!(eventt.power_p1==8||eventt.power_p2==8))
        {
            t+=0.1;
        }
        if(!(eventt.power_p1==8||eventt.power_p2==8))
        {
            if(abs(bal.vy)<0.01&&bal.y+bal.r==W-259+129)
            {
                bal.y0=W-259+129-bal.r;
                bal.y=W-259+129-bal.r;
                bal.vy0=0;
                bal.vy=0;
            }
            else
            {
                bal.x=bal.vx0*t+bal.x0;
                bal.y=bal.vy0*t+0.5*20*t*t+bal.y0;
                bal.vy=20*t+bal.vy0;
                bal.vx=bal.vx0;
            }
             barkhord_toop();
        }
        else
        {
            bal.vx=0;
            bal.vy=0;
            bal.vx0=0;
            bal.vy0=0;
            bal.x0=bal.x;
            bal.y0=bal.y;
            t=0;
        }
}
void Do_pause()
{
    change_picture_of_pause();
        if(eventt.click)
        {
            if(muse_in_rect(rects_of_pause[0]))
            {
                Display.Pause=false;
                Display.Game=true;
            }
            else if(muse_in_rect(rects_of_pause[1]))
            {
                timer_game=0;
                bal.x=L/2;
                bal.x0=bal.x;
                bal.y=300;
                bal.y0=bal.y;
                bal.vx=0;
                bal.vy=-100;
                bal.vx0=bal.vx;
                bal.vy0=bal.vy;
                player2.gol=0;
                player2.t_power=0;
                player2.x=1006;
                player2.y=550;
                player2.boot.x=player2.x-player2.boot.tool+40;
                player2.boot.y=player2.y+player2.r_head-34;
                player2.boot.angle=0;
                player2.boot.angle_gam=3;
                player2.vy=0;
                player2.vx=0;
                player2.gam_x=15;
                player1.gol=0;
                player1.x=274;
                player1.y=550;
                player1.t_power=0;
                player1.boot.x=player1.x-40;
                player1.boot.y=player1.y+player1.r_head-34;
                player1.boot.angle=0;
                player1.boot.angle_gam=3;
                player1.vx=0;
                player1.vy=0;
                player1.gam_x=15;
                Display.Pause=false;
                Display.Game=true;
            }
            else if(muse_in_rect(rects_of_pause[2]))
            {
                Display.Pause=false;
                Display.option=true;
            }
            else if(muse_in_rect(rects_of_pause[3]))
            {
                Display.Start=true;
                Display.Pause=false;
                if(pause==1)
                {
                    player1.gol=0;
                    player2.gol=3;
                }
                else if(pause==2)
                {
                    player1.gol=3;
                    player2.gol=0;
                }
                add_players_to_files();
            }
        }
}
void present_endgame()
{
        present_game();
        texture(bal.x-bal.r,bal.y-bal.r,bal.ball,2*bal.r,2*bal.r);
        textureEx(player1.boot.x,player1.boot.y,player1.foot,player1.boot.tool,player1.boot.arz,player1.boot.point.x,player1.boot.point.y,player1.boot.angle);
        texture(player1.x-player1.r_head,player1.y-player1.r_head,player1.head,2*player1.r_head,2*player1.r_head);
        filledCircleRGBA(Renderer,player1.boot.point.x+player1.boot.x,player1.boot.point.y+player1.boot.y,1,255,255,255,255);
        filledCircleRGBA(Renderer,player1.boot.x,player1.boot.y,1,255,255,255,255);
        textureEx(player2.boot.x,player2.boot.y,player2.foot,player2.boot.tool,player2.boot.arz,player2.boot.point.x,player2.boot.point.y,player2.boot.angle);
        texture(player2.x-player2.r_head,player2.y-player2.r_head,player2.head,2*player2.r_head,2*player2.r_head);
        lineRGBA(Renderer,player1.boot.x+70,player1.boot.y+18,player1.boot.x+160,player1.boot.y+46,255,255,255,255);
        boxRGBA(Renderer,0,0,L,W,0,0,0,190);
        if(player1.gol>player2.gol)
        {
            string str="*** ";
            str+=player1.name;
            str+=" is Winnner ***";
            write(str,L/4,W/4,L/2,W/2,245);
            string continu="__click to continue__";
            write(continu,3*L/8,3*W/4+10,L/4,W/8,245);
        }
        else if(player1.gol<player2.gol)
        {
            string str="*** ";
            str+=player2.name;
            str+=" is Winnner ***";
            write(str,L/4,W/4,L/2,W/2,245);
            string continu="__click to continue__";
            write(continu,3*L/8,3*W/4+10,L/4,W/8,245);
        }
        else
        {
            string str="*** ";
            str+="Draw ***";
            write(str,L/4,W/4,L/2,W/2,245);
            string continu="__click to continue__";
            write(continu,3*L/8,3*W/4+10,L/4,W/8,245);
        }
}
void present_table()
{
    texture(0,0,image.table_back,L,W);
    boxRGBA(Renderer,3,3,L/20+2,W/20+2,0,0,0,250);
    boxRGBA(Renderer,5,5,L/20,W/20,255,0,0,190);
    write("Back",7,7,L/20-6,W/20-10,30);
    boxRGBA(Renderer,L/10,W/10,9*L/10,9*W/10,0,0,0,150);
    write("name",L/10+10,W/10,8/7*L/10,8*(W/10)/(file.num+1)-5,player1.x);
    write("score",10+L/10+8*L/10/7,W/10,8/7*L/10,8*(W/10)/(file.num+1)-5,player1.x);
    write("match",10+L/10+8*L/10/7+8*L/10/7,W/10,8/7*L/10,8*(W/10)/(file.num+1)-5,player1.x);
    write("goal difference",10+L/10+8*L/10/7+8*L/10/7+8*L/10/7,W/10,8/7*L/10,8*(W/10)/(file.num+1)-5,player1.x);
    write("wins",10+L/10+8*L/10/7+8*L/10/7+8*L/10/7+8*L/10/7,W/10,8/7*L/10,8*(W/10)/(file.num+1)-5,player1.x);
    write("loss",10+L/10+8*L/10/7+8*L/10/7+8*L/10/7+8*L/10/7+8*L/10/7,W/10,8/7*L/10,8*(W/10)/(file.num+1)-5,player1.x);
    write("draws",10+L/10+8*L/10/7+8*L/10/7+8*L/10/7+8*L/10/7+8*L/10/7+8*L/10/7,W/10,8/7*L/10,8*(W/10)/(file.num+1)-5,player1.x);
    for(int i=1;i<file.num+1;i++)
    {
        write(file.asami[i-1],L/10+10,W/10+8*(W/10)/(file.num+1)*i,8/7*L/10,8*(W/10)/(file.num+1)-5,player1.x);
        write(to_string(file.score[i-1]),10+L/10+8*L/10/7,W/10+8*(W/10)/(file.num+1)*i,8/7*L/10,8*(W/10)/(file.num+1)-5,player1.x);
        write(to_string(file.tedad_bazi[i-1]),10+L/10+8*L/10/7+8*L/10/7,W/10+8*(W/10)/(file.num+1)*i,8/7*L/10,8*(W/10)/(file.num+1)-5,player1.x);
        write(to_string(file.tafazol_gol[i-1]),10+L/10+8*L/10/7+8*L/10/7+8*L/10/7,W/10+8*(W/10)/(file.num+1)*i,8/7*L/10,8*(W/10)/(file.num+1)-5,player1.x);
        write(to_string(file.tedad_bord[i-1]),10+L/10+8*L/10/7+8*L/10/7+8*L/10/7+8*L/10/7,W/10+8*(W/10)/(file.num+1)*i,8/7*L/10,8*(W/10)/(file.num+1)-5,player1.x);
        write(to_string(file.tedad_bakht[i-1]),10+L/10+8*L/10/7+8*L/10/7+8*L/10/7+8*L/10/7+8*L/10/7,W/10+8*(W/10)/(file.num+1)*i,8/7*L/10,8*(W/10)/(file.num+1)-5,player1.x);
        write(to_string(file.tedad_mosavi[i-1]),10+L/10+8*L/10/7+8*L/10/7+8*L/10/7+8*L/10/7+8*L/10/7+8*L/10/7,W/10+8*(W/10)/(file.num+1)*i,8/7*L/10,8*(W/10)/(file.num+1)-5,player1.x);
    }
    for(int i=0;i<=7;i++)
    {
        vlineRGBA(Renderer,L/10+8*L/10*i/7,W/10,9*W/10,255,255,255,255);
    }
    for(int i=0;i<=file.num+1;i++)
    {
        hlineRGBA(Renderer,L/10,9*L/10,W/10+8*W/10*i/(file.num+1),255,255,255,255);
    }
}
void load_game_images()
{
    int n = stadium.length();
    char char_array[n+1];
    strcpy(char_array, stadium.c_str());
    texture_my.stadiumm = IMG_LoadTexture( Renderer, char_array);

    int nn = plat.length();
    char char_array2[nn+1];
    strcpy(char_array2, plat.c_str());
    texture_my.platt = IMG_LoadTexture( Renderer, char_array2);

    int nnn = player1.foot.length();
    char char_array3[nnn+1];
    strcpy(char_array3, player1.foot.c_str());
    texture_my.p1_f = IMG_LoadTexture( Renderer, char_array3);

    int nnnn = player1.head.length();
    char char_array4[nnnn+1];
    strcpy(char_array4, player1.head.c_str());
    texture_my.p1_h = IMG_LoadTexture( Renderer, char_array4);

    int nnnnn = player2.foot.length();
    char char_array5[nnnnn+1];
    strcpy(char_array5, player2.foot.c_str());
    texture_my.p2_f = IMG_LoadTexture( Renderer, char_array5);

    int nnnnnn = player2.head.length();
    char char_array6[nnnnnn+1];
    strcpy(char_array6, player2.head.c_str());
    texture_my.p2_h = IMG_LoadTexture( Renderer, char_array6);

    int nnnnnnn = tirak_l.name.length();
    char char_array7[nnnnnnn+1];
    strcpy(char_array7, tirak_l.name.c_str());
    texture_my.tirakl = IMG_LoadTexture( Renderer, char_array7);

    int nnnnnnnn = tirak_r.name.length();
    char char_array8[nnnnnnnn+1];
    strcpy(char_array8, tirak_r.name.c_str());
    texture_my.tirakr = IMG_LoadTexture( Renderer, char_array8);

    int nnnnnnnnn = bal.ball.length();
    char char_array9[nnnnnnnnn+1];
    strcpy(char_array9, bal.ball.c_str());
    texture_my.balll = IMG_LoadTexture( Renderer, char_array9);

    string mane="photos//mane.png";
    int nnnnnnnnnn = mane.length();
    char char_array10[nnnnnnnnnn+1];
    strcpy(char_array10, mane.c_str());
    texture_my.mane = IMG_LoadTexture( Renderer, char_array10);

    string ice="photos//ice.png";
    int nnnnnnnnnnn = ice.length();
    char char_array11[nnnnnnnnnnn+1];
    strcpy(char_array11, ice.c_str());
    texture_my.Freeze = IMG_LoadTexture( Renderer, char_array11);

}
void fast_texture(int xp,int yp,SDL_Texture *myTexture,int width,int height)
{
    SDL_Rect texr1;
    texr1.x = xp;
    texr1.y = yp;
    texr1.w = width;
    texr1.h = height;
    SDL_RenderCopy( Renderer,myTexture, NULL, &texr1);
}
bool barkhord_2noghte(double x1,double y1,double x2,double y2,bool barkhord_up_Or_right)
{
    y1=W-y1;
    y2=W-y2;
    double by=W-bal.y;
    if(x1>x2)
    {
        swap(x1,x2);
        swap(y1,y2);
    }

    if(x2!=x1&y2!=y1)
    {
        double m=(y2-y1)/(x2-x1);
        double d1=(-1*m*bal.x+by+m*x1-y1)/sqrt(1+m*m);
        double d3=(bal.x/m+by-(y1+x1/m))/sqrt(1+1/(m*m));
        double d2=(bal.x/m+by-(y2+x2/m))/sqrt(1+1/(m*m));
        if(m>0)
        {
            if(barkhord_up_Or_right&&d1<=bal.r&&d1>=0&&d2<=bal.r&&d3>=-1*bal.r)
            {
                return true;
            }
            else if(!barkhord_up_Or_right&&d1>=-1*bal.r&&d1<=0&&d2<=bal.r&&d3>=-1*bal.r)
            {
                return true;
            }
            return false;
        }
        if(((barkhord_up_Or_right&&d1<=bal.r&&d1>=0)||(!barkhord_up_Or_right&&d1>=-1*bal.r&&d1<=0))&&d3<=bal.r&&d2>=-1*bal.r)
        {
            return true;
        }
        return false;
    }
    if(x2==x1)
    {
        if(y1>y2)
        {
                swap(y1,y2);
        }

        if(barkhord_up_Or_right)
        {
           if(by-bal.r<=y2&&by+bal.r>=y1&&bal.x-bal.r<=x1&&bal.x>=x1)
           {
               return true;

           }
            return false;
        }
        else
        {

            if(by-bal.r<=y2&&by+bal.r>=y1&&bal.x+bal.r>=x1&&bal.x<=x1)
           {
               return true;

           }
            return false;
        }
    }
    if(y2==y1)
    {
        if(x1>x2)
        {
                swap(x1,x2);
        }
        if(barkhord_up_Or_right)
        {
           if(by-bal.r<=y2&&by>=y2&&bal.x+bal.r>=x1&&bal.x-bal.r<=x2)
           {
               return true;
           }
            return false;
        }
        else
        {
            if(by<=y2&&by+bal.r>=y2&&bal.x+bal.r>=x1&&bal.x-bal.r<=x2)
           {
               return true;
           }
            return false;
        }
    }
}
void shoot()
{
    if(eventt.shoot_p1)
    {
        player1.boot.angle-=player1.boot.angle_gam;
        if(player1.boot.angle<=-30)
        {
            player1.boot.angle_gam*=-1;
        }
        if(player1.boot.angle==0)
        {
            eventt.shoot_p1=false;
            player1.boot.angle_gam*=-1;
        }
    }
    if(eventt.shoot_p2)
    {
        player2.boot.angle+=player2.boot.angle_gam;
        if(player2.boot.angle>=30)
        {
            player2.boot.angle_gam*=-1;
        }
        if(player2.boot.angle==0)
        {
            eventt.shoot_p2=false;
            player2.boot.angle_gam*=-1;
        }
    }
}
void do_move_game()
{
    if(eventt.left_p1&&player1.x>100&&eventt.power_p2!=6)
    {
        player1.x-=player1.gam_x;
    }
    if(eventt.right_p1&&player1.x<1180&&eventt.power_p2!=6&&(player1.boot.x+player1.boot.tool+player1.gam_x<player2.boot.x-5))
    {
        player1.x+=player1.gam_x;
    }
    if(eventt.up_p1&&eventt.power_p2!=6)
    {
        if(player1.y==550)
        player1.vy=-300;
    }
    if(eventt.mshoot_p1&&eventt.power_p2!=6)
    {
        eventt.shoot_p1=true;
    }
    if(eventt.left_p2&&player2.x>100&&eventt.power_p1!=6&&(player2.boot.x-player2.gam_x>player1.boot.x+player1.boot.tool+5))
    {
        player2.x-=player2.gam_x;
    }
    if(eventt.right_p2&&player2.x<1180&&eventt.power_p1!=6)
    {
        player2.x+=player2.gam_x;
    }
    if(eventt.up_p2&&eventt.power_p1!=6)
    {
        if(player2.y==550)
        player2.vy=-300;
    }
    if(eventt.mshoot_p2&&eventt.power_p1!=6)
    {
        eventt.shoot_p2=true;
    }
}
void shoroo_mojaddad(int nofp)
{
    if(nofp==1)
    {
        bal.x=L/2;
        bal.y=3*W/10;
        bal.vx=-50;
        bal.vy=0;
        bal.x0=bal.x;
        bal.y0=bal.y;
        bal.vx0=bal.vx;
        bal.vy0=bal.vy;
        player2.gol++;
    }
    else
    {
        bal.x=L/2;
        bal.y=3*W/10;
        bal.vx=50;
        bal.vy=0;
        bal.x0=bal.x;
        bal.y0=bal.y;
        bal.vx0=bal.vx;
        bal.vy0=bal.vy;
        player1.gol++;
    }
    player2.x=1006;
    player2.y=550;
    player2.vy=0;
    player1.x=274;
    player1.y=550;
    player1.vy=0;
}
void present_abaot()
{
    for(int i=800;i>0;i-=40)
            {
                fast_texture(0,0,texture_my.About,L,W);
                write("project of fandamentals of programming",L/4,W/8-20+i,L/2,7*W/8/6,100);
                SDL_RenderPresent(Renderer);
                SDL_RenderClear(Renderer);
                SDL_Delay(25);
            }
            for(int i=800-7*W/8/6;i>0;i-=40)
            {
                fast_texture(0,0,texture_my.About,L,W);
                write("project of fandamentals of programming",L/4,W/8-20,L/2,7*W/8/6,100);
                write("Electrical engineering departmant,sharif university of technology",L/8,W/8+7*W/8/6-40+i,6*L/8,7*W/8/6,100);
                SDL_RenderPresent(Renderer);
               // SDL_RenderClear(Renderer);
                SDL_Delay(25);
            }
            for(int i=800-7*W/8/6-7*W/8/6;i>0;i-=40)
            {
                fast_texture(0,0,texture_my.About,L,W);
                write("project of fandamentals of programming",L/4,W/8-20,L/2,7*W/8/6,100);
                write("Electrical engineering departmant,sharif university of technology",L/8,W/8+7*W/8/6-40,6*L/8,7*W/8/6,100);
                write("professors: Dr.Araste & Dr.Vahdat",L/4,W/8+7*W/8/6+7*W/8/6-40+i,L/2,W/16,100);
                SDL_RenderPresent(Renderer);
               // SDL_RenderClear(Renderer);
                SDL_Delay(25);
            }
            for(int i=800-7*W/8/6-7*W/8/6-7*W/8/6;i>0;i-=40)
            {
                fast_texture(0,0,texture_my.About,L,W);
                write("project of fandamentals of programming",L/4,W/8-20,L/2,7*W/8/6,100);
                write("Electrical engineering departmant,sharif university of technology",L/8,W/8+7*W/8/6-40,6*L/8,7*W/8/6,100);
                write("professors: Dr.Araste & Dr.Vahdat",L/4,W/8+7*W/8/6+7*W/8/6-40,L/2,W/16,100);
                write("designers: Seyed Hamid Ghasemi           (seyyedhamid.ghasemi@gmail.com)",L/16,i+W/8+7*W/8/6+7*W/8/6,14*L/16,7*W/8/6,100);
                write("         & Mohammad Morsali              (mohammadmorsali8181@gmail.com)",L/16,i+W/8+7*W/8/6+7*W/8/6+7*W/8/6,14*L/16,7*W/8/6,100);
                SDL_RenderPresent(Renderer);
               // SDL_RenderClear(Renderer);
                SDL_Delay(25);
            }
            for(int i=800-7*W/8/6-7*W/8/6-7*W/8/6-7*W/8/6;i>0;i-=40)
            {
                fast_texture(0,0,texture_my.About,L,W);
                write("project of fandamentals of programming",L/4,W/8-20,L/2,7*W/8/6,100);
                write("Electrical engineering departmant,sharif university of technology",L/8,W/8+7*W/8/6-40,6*L/8,7*W/8/6,100);
                write("professors: Dr.Araste & Dr.Vahdat",L/4,W/8+7*W/8/6+7*W/8/6-40,L/2,W/16,100);
                write("designers: Seyed Hamid Ghasemi           (seyyedhamid.ghasemi@gmail.com)",L/16,W/8+7*W/8/6+7*W/8/6,14*L/16,7*W/8/6,100);
                write("         & Mohammad Morsali              (mohammadmorsali8181@gmail.com)",L/16,W/8+7*W/8/6+7*W/8/6+7*W/8/6,14*L/16,7*W/8/6,100);
                write("2022,january",7*L/16,i+W/8+7*W/8/6+7*W/8/6+7*W/8/6+7*W/8/6,L/8,7*W/8/6,100);
                SDL_RenderPresent(Renderer);
                SDL_RenderClear(Renderer);
                SDL_Delay(25);
            }
            for(int i=800-7*W/8/6-7*W/8/6-7*W/8/6-7*W/8/6-7*W/8/6;i>0;i-=40)
            {
                fast_texture(0,0,texture_my.About,L,W);
                write("project of fandamentals of programming",L/4,W/8-20,L/2,7*W/8/6,100);
                write("Electrical engineering departmant,sharif university of technology",L/8,W/8+7*W/8/6-40,6*L/8,7*W/8/6,100);
                write("professors: Dr.Araste & Dr.Vahdat",L/4,W/8+7*W/8/6+7*W/8/6-40,L/2,W/16,100);
                write("designers: Seyed Hamid Ghasemi           (seyyedhamid.ghasemi@gmail.com)",L/16,W/8+7*W/8/6+7*W/8/6,14*L/16,7*W/8/6,100);
                write("         & Mohammad Morsali              (mohammadmorsali8181@gmail.com)",L/16,W/8+7*W/8/6+7*W/8/6+7*W/8/6,14*L/16,7*W/8/6,100);
                write("2022,january",7*L/16,W/8+7*W/8/6+7*W/8/6+7*W/8/6+7*W/8/6,L/8,7*W/8/6,100);
                write("the project is a simple copy of<<Head soccer game>> and based on c++ by SDL2/Graphic",L/16,i+W/8+7*W/8/6+7*W/8/6+7*W/8/6+7*W/8/6+7*W/8/6,14*L/16,7*W/8/6,100);
                SDL_RenderPresent(Renderer);
                SDL_RenderClear(Renderer);
                SDL_Delay(25);
            }
}
void present_setting()
{
    double x0=L/2,y0=W/2;
    double x=x0,y=y0-10;
    double vx=90,vy=0;
    texture(0,0,"photos//setting_back.jpg",L,W);
    while(Display.Setting&&!Display.exit)
    {
        double x00=x;
        x+=vx*0.01;
        vx+=(10000/(pow((pow((x-x0),2)+pow(y-y0,2)),3/2)))*(x0-x)*0.1;
        double y00=y;
        y+=vy*0.01;
        vy+=(10000/(pow((pow((x-x0),2)+pow(y-y0,2)),3/2)))*(y0-y)*0.1;
        aalineRGBA(Renderer,x00,y00,x,y,0,0,255,255);
        boxRGBA(Renderer,0,0,L,W,0,0,0,1);
        write("Setting",3*L/8,20,L/4,W/8,100);
        write("Music volume:",20,W/4,L/8,W/8,100);
        texture(20,3*W/8+20,"photos//1speaker.png",W/16,W/16);
        texture(20+W/16+8,3*W/8+20,"photos//2speaker.png",W/16,W/16);
        texture(20+W/16+W/16+16,3*W/8+20,"photos//3speaker.png",W/16,W/16);
        texture(20+W/16+W/16+W/16+24,3*W/8+20,"photos//4speaker.png",W/16,W/16);
        write("Music:",20,4*W/8,L/8,W/8,100);
        filledCircleRGBA(Renderer,L/16,6*W/8,20,255,0,0,255);
        filledCircleRGBA(Renderer,L/16,6*W/8,17,0,0,0,255);
        filledCircleRGBA(Renderer,5*L/16,6*W/8,20,255,0,0,255);
        filledCircleRGBA(Renderer,5*L/16,6*W/8,17,0,0,0,255);
        boxRGBA(Renderer,5,5,L/20,W/20,255,0,0,190);
        boxRGBA(Renderer,L/16+30,6*W/8-20,L/16+30+4*L/16-60,6*W/8-20+40,0,2,200,255);
        write(name_of_music[n_music],L/16+30,6*W/8-20,4*L/16-60,40,100);
        write("Back",7,7,L/20-6,W/20-10,30);
        events();
        if(eventt.click)
        {
             if(muse.x>=20&&muse.x<=20+W/16&&muse.y>=3*W/8+20&&muse.y<=3*W/8+20+W/16&&muse.x>=0&&muse.x<=L&&muse.y>=0&&muse.y<=W)
            {
                Mix_VolumeMusic(500);
            }
            else  if(muse.x>=20+W/16+8&&muse.x<=20+W/16+8+W/16&&muse.y>=3*W/8+20&&muse.y<=3*W/8+20+W/16&&muse.x>=0&&muse.x<=L&&muse.y>=0&&muse.y<=W)
            {
                Mix_VolumeMusic(200);
            }
            else  if(muse.x>=20+W/16+W/16+16&&muse.x<=20+W/16+W/16+16+W/16&&muse.y>=3*W/8+20&&muse.y<=3*W/8+20+W/16&&muse.x>=0&&muse.x<=L&&muse.y>=0&&muse.y<=W)
            {
                Mix_VolumeMusic(50);
            }
            else  if(muse.x>=20+W/16+W/16+W/16+24&&muse.x<=20+W/16+W/16+W/16+24+W/16&&muse.y>=3*W/8+20&&muse.y<=3*W/8+20+W/16&&muse.x>=0&&muse.x<=L&&muse.y>=0&&muse.y<=W)
            {
                Mix_VolumeMusic(0);
            }
            else if(((((muse.x-L/16)*(muse.x-L/16)+(muse.y-6*W/8)*(muse.y-6*W/8))<=20*20))&&muse.x<L&&muse.x>0&&muse.y<W&&muse.y>0)
            {
                n_music--;
                if(n_music==-1)
                {
                    n_music=4;
                }
                music_address="music//";
                music_address+=to_string(n_music);
                music_address+=".mp3";
                SDL_Init(SDL_INIT_VIDEO || SDL_INIT_AUDIO);  //defualt in k music play beshe
                Mix_OpenAudio(44100,MIX_DEFAULT_FORMAT,2,2048);
                Mix_Music *ostad=Mix_LoadMUS( music_address.c_str());//esm file bray entkahab file music dar in nahie entkhab mishavad
                Mix_PlayMusic(ostad,-1); //ostad y esme randome kamelan brash
            }
            else if(((((muse.x-5*L/16)*(muse.x-5*L/16)+(muse.y-6*W/8)*(muse.y-6*W/8))<=20*20))&&muse.x<L&&muse.x>0&&muse.y<W&&muse.y>0)
            {
                n_music++;
                if(n_music==4)
                {
                    n_music=0;
                }
                music_address="music//";
                music_address+=to_string(n_music);
                music_address+=".mp3";
                SDL_Init(SDL_INIT_VIDEO || SDL_INIT_AUDIO);  //defualt in k music play beshe
                Mix_OpenAudio(44100,MIX_DEFAULT_FORMAT,2,2048);
                Mix_Music *ostad=Mix_LoadMUS( music_address.c_str());//esm file bray entkahab file music dar in nahie entkhab mishavad
                Mix_PlayMusic(ostad,-1); //ostad y esme randome kamelan brash
            }
            else if(muse.x>=3&&muse.x<=3+2+L/20&&muse.y>=3&&muse.y<=3+2+W/20&&muse.x>=0&&muse.x<=L&&muse.y>=0&&muse.y<=W)
            {
                Display.Start=true;
                Display.Setting=false;
            }
            eventt.click=false;
        }
        SDL_RenderPresent(Renderer);
    }
}
void present_option()
{
    double x0=L/2,y0=W/2;
    double x=x0,y=y0-10;
    double vx=90,vy=0;
    texture(0,0,"photos//setting_back.jpg",L,W);
    while(Display.option&&!Display.exit)
    {
        double x00=x;
        x+=vx*0.01;
        vx+=(10000/(pow((pow((x-x0),2)+pow(y-y0,2)),3/2)))*(x0-x)*0.1;
        double y00=y;
        y+=vy*0.01;
        vy+=(10000/(pow((pow((x-x0),2)+pow(y-y0,2)),3/2)))*(y0-y)*0.1;
        aalineRGBA(Renderer,x00,y00,x,y,0,0,255,255);
        boxRGBA(Renderer,0,0,L,W,0,0,0,1);
        write("Setting",3*L/8,20,L/4,W/8,100);
        write("Music volume:",20,W/4,L/8,W/8,100);
        texture(20,3*W/8+20,"photos//1speaker.png",W/16,W/16);
        texture(20+W/16+8,3*W/8+20,"photos//2speaker.png",W/16,W/16);
        texture(20+W/16+W/16+16,3*W/8+20,"photos//3speaker.png",W/16,W/16);
        texture(20+W/16+W/16+W/16+24,3*W/8+20,"photos//4speaker.png",W/16,W/16);
        write("Music:",20,4*W/8,L/8,W/8,100);
        filledCircleRGBA(Renderer,L/16,6*W/8,20,255,0,0,255);
        filledCircleRGBA(Renderer,L/16,6*W/8,17,0,0,0,255);
        filledCircleRGBA(Renderer,5*L/16,6*W/8,20,255,0,0,255);
        filledCircleRGBA(Renderer,5*L/16,6*W/8,17,0,0,0,255);
        boxRGBA(Renderer,5,5,L/20,W/20,255,0,0,190);
        boxRGBA(Renderer,L/16+30,6*W/8-20,L/16+30+4*L/16-60,6*W/8-20+40,0,2,200,255);
        write(name_of_music[n_music],L/16+30,6*W/8-20,4*L/16-60,40,100);
        write("Back",7,7,L/20-6,W/20-10,30);
        events();
        if(eventt.click)
        {
             if(muse.x>=20&&muse.x<=20+W/16&&muse.y>=3*W/8+20&&muse.y<=3*W/8+20+W/16&&muse.x>=0&&muse.x<=L&&muse.y>=0&&muse.y<=W)
            {
                Mix_VolumeMusic(500);
            }
            else  if(muse.x>=20+W/16+8&&muse.x<=20+W/16+8+W/16&&muse.y>=3*W/8+20&&muse.y<=3*W/8+20+W/16&&muse.x>=0&&muse.x<=L&&muse.y>=0&&muse.y<=W)
            {
                Mix_VolumeMusic(200);
            }
            else  if(muse.x>=20+W/16+W/16+16&&muse.x<=20+W/16+W/16+16+W/16&&muse.y>=3*W/8+20&&muse.y<=3*W/8+20+W/16&&muse.x>=0&&muse.x<=L&&muse.y>=0&&muse.y<=W)
            {
                Mix_VolumeMusic(50);
            }
            else  if(muse.x>=20+W/16+W/16+W/16+24&&muse.x<=20+W/16+W/16+W/16+24+W/16&&muse.y>=3*W/8+20&&muse.y<=3*W/8+20+W/16&&muse.x>=0&&muse.x<=L&&muse.y>=0&&muse.y<=W)
            {
                Mix_VolumeMusic(0);
            }
            else if(((((muse.x-L/16)*(muse.x-L/16)+(muse.y-6*W/8)*(muse.y-6*W/8))<=20*20))&&muse.x<L&&muse.x>0&&muse.y<W&&muse.y>0)
            {
                n_music--;
                if(n_music==-1)
                {
                    n_music=4;
                }
                music_address="music//";
                music_address+=to_string(n_music);
                music_address+=".mp3";
                SDL_Init(SDL_INIT_VIDEO || SDL_INIT_AUDIO);  //defualt in k music play beshe
                Mix_OpenAudio(44100,MIX_DEFAULT_FORMAT,2,2048);
                Mix_Music *ostad=Mix_LoadMUS( music_address.c_str());//esm file bray entkahab file music dar in nahie entkhab mishavad
                Mix_PlayMusic(ostad,-1); //ostad y esme randome kamelan brash
            }
            else if(((((muse.x-5*L/16)*(muse.x-5*L/16)+(muse.y-6*W/8)*(muse.y-6*W/8))<=20*20))&&muse.x<L&&muse.x>0&&muse.y<W&&muse.y>0)
            {
                n_music++;
                if(n_music==4)
                {
                    n_music=0;
                }
                music_address="music//";
                music_address+=to_string(n_music);
                music_address+=".mp3";
                SDL_Init(SDL_INIT_VIDEO || SDL_INIT_AUDIO);  //defualt in k music play beshe
                Mix_OpenAudio(44100,MIX_DEFAULT_FORMAT,2,2048);
                Mix_Music *ostad=Mix_LoadMUS( music_address.c_str());//esm file bray entkahab file music dar in nahie entkhab mishavad
                Mix_PlayMusic(ostad,-1); //ostad y esme randome kamelan brash
            }
            else if(muse.x>=3&&muse.x<=3+2+L/20&&muse.y>=3&&muse.y<=3+2+W/20&&muse.x>=0&&muse.x<=L&&muse.y>=0&&muse.y<=W)
            {
                Display.Pause=true;
                Display.option=false;
            }
            eventt.click=false;
        }
        SDL_RenderPresent(Renderer);
    }
}
void write(string text, int x, int y ,int w, int h,int Size)
{
    if(TTF_Init() == -1){
    }else{
    }
    TTF_Font* ourFont = TTF_OpenFont("AovelSansRounded-rdDL.ttf",Size);
    if(ourFont == nullptr){
        exit(1);
    }
    SDL_Surface* surfaceText = TTF_RenderText_Solid(ourFont,text.c_str(),{255,255,255,255});
    SDL_Texture* textureText = SDL_CreateTextureFromSurface(Renderer,surfaceText);
    SDL_FreeSurface(surfaceText);
    SDL_Rect rectangle;
    rectangle.x = x;
    rectangle.y = y;
    rectangle.w = w;
    rectangle.h = h;
    SDL_RenderCopy(Renderer,textureText,NULL,&rectangle);
    SDL_DestroyTexture(textureText);
    TTF_CloseFont(ourFont);
}
double davaran_x(double x_fixpoint,double y_fixpoint,double x,double y,double angel)
{
    return x_fixpoint+sqrt(x*x+y*y)*sin(-angel*3.14/180+atan(x/y));
}
double davaran_y(double x_fixpoint,double y_fixpoint,double x,double y,double angel)
{
    return y_fixpoint+sqrt(x*x+y*y)*cos(-angel*3.14/180+atan(x/y));
}
void meghdardehi_avvalie()
{
    ///meghdar dehi avvalie
    name_of_powers[0]="Invisible Ball";
    name_of_powers[1]="Sonic";
    name_of_powers[2]="Invisible Rival";
    name_of_powers[3]="closed gate";
    name_of_powers[4]="Big Ball";
    name_of_powers[5]="Freeze Rival";
    name_of_powers[6]="Reverse";
    name_of_powers[7]="Freeze Ball";
    name_of_powers[8]="Freeze Time";
    name_of_powers[9]="Thief";
    //*********************
    cheet.ok=true;
    cheet.cheet=false;
    //*********************
    bal.n=1;
    bal.x=L/2;
    bal.x0=bal.x;
    bal.y=300;
    bal.y0=bal.y;
    bal.vx=0;
    bal.vy=-100;
    bal.vx0=bal.vx;
    bal.vy0=bal.vy;
    bal.z.kaf=0.9;
    bal.z.tirak=0.34;
    bal.r=20;
    //*****
    player2.head=" ";
    player2.nfoot=1;
    player2.nhead=1;
    player2.name="";
    player2.gol=0;
    player2.t_power=0;
    player2.boot.tool=162;
    player2.boot.arz=75;
    player2.r_head=73;
    player2.x=1006;
    player2.y=550;
    player2.boot.point.x=player2.boot.tool;
    player2.boot.point.y=0;
    player2.boot.x=player2.x-player2.boot.tool+40;
    player2.boot.y=player2.y+player2.r_head-34;
    player2.boot.angle=0;
    player2.boot.angle_gam=3;
    player2.vy=0;
    player2.vx=0;
    player2.gam_x=15;
    //*****************************************
    player1.head=" ";
    player1.nhead=1;
    player1.nfoot=1;
    player1.name="";
    player1.gol=0;
    player1.x=274;
    player1.y=550;
    player1.t_power=0;
    player1.boot.arz=78;
    player1.boot.tool=160;
    player1.r_head=73;
    player1.boot.point.x=0;
    player1.boot.point.y=0;
    player1.boot.x=player1.x-40;
    player1.boot.y=player1.y+player1.r_head-34;
    player1.boot.angle=0;
    player1.boot.angle_gam=3;
    player1.vx=0;
    player1.vy=0;
    player1.gam_x=15;
    //********************************************
    image.Menu="photos//menu//menu.jpg";
    image.choose="photos//choose//0choose.jpg";
    image.pause="photos//pause//pause.png";
    image.table_back="photos//table.jpg";
    //************
    circles_of_pause[0]={30,30,30};
    circles_of_pause[1]={L-30,30,30};
    //*************
    circles_of_choose_player[0]={124,208,22};
    circles_of_choose_player[1]={514,208,22};
    circles_of_choose_player[2]={766,208,22};
    circles_of_choose_player[3]={1153,208,22};
    circles_of_choose_player[4]={142,373,22};
    circles_of_choose_player[5]={487,373,22};
    circles_of_choose_player[6]={781,373,22};
    circles_of_choose_player[7]={1138,373,22};
    circles_of_choose_player[8]={568,283,22};
    circles_of_choose_player[9]={715,283,22};
    circles_of_choose_player[10]={49,631,22};
    circles_of_choose_player[11]={586,631,22};
    circles_of_choose_player[12]={688,631,22};
    circles_of_choose_player[13]={1228,631,22};
    circles_of_choose_player[14]={640,286,40};
    //***************
    rects_of_choose_player[0]={259,22,597-259,70-22};
    rects_of_choose_player[1]={922,22,1258-922,70-22};
    rects_of_choose_player[2]={157,97,482-157,321-97};
    rects_of_choose_player[3]={799,97,1121-799,321-97};
    rects_of_choose_player[4]={178,349,449-178,395-349};
    rects_of_choose_player[5]={820,352,1099-820,394-352};
    rects_of_choose_player[6]={349,424,532-349,461-424};
    rects_of_choose_player[7]={985,424,1168-985,463-424};
    rects_of_choose_player[8]={94,493,547-94,767-493};
    rects_of_choose_player[9]={730,493,1186-730,767-493};
    //***************
    circles.x=100;
    circles.y=100;
    circles.r=10;
    //***************
    rects_of_game[0]={10,70,250,30};
    rects_of_game[1]={12,72,246,26};
    rects_of_game[2]={L-10-250,70,250,30};
    rects_of_game[3]={L-12,72,246,26};
    rects_of_game[4]={L/2-40,10,80,90};
    rects_of_game[5]={L/2-91,30,50,50};
    rects_of_game[6]={L/2-292,30,200,50};
    rects_of_game[7]={L/2+41,30,50,50};
    rects_of_game[8]={L/2+92,30,200,50};
    //***************
    rects_of_pause[0]={364,175,604-364,265-175};
    rects_of_pause[1]={364,316,604-364,406-316};
    rects_of_pause[2]={364,457,604-364,547-457};
    rects_of_pause[3]={364,607,604-364,706-607};
    //***************
    istyping1=false;
    istyping2=false;
    //*****************
    Display={true,false,false,false,false,false,false,false,false};
    //***************
    tirak_l.x=0;
    tirak_l.y=W-483-90;
    tirak_l.arz=160;
    tirak_l.ertefa=363+90;
    tirak_l.name="photos//darvazeh_l.png";
    tirak_r.x=L-160;
    tirak_r.y=W-483-90;
    tirak_r.arz=160;
    tirak_r.ertefa=363+90;
    tirak_r.name="photos//darvazeh_r.png";
    //*********************
    eventt.power_p1=0;
    eventt.power_p2=0;
    //*********************
    pbp1._1.x=70;
    pbp1._1.y=18;
    pbp1._2.x=161;
    pbp1._2.y=46;
    pbp1._3.x=161;
    pbp1._3.y=78;
    pbp1._4.x=-1;
    pbp1._4.y=78;
    //*********************
    pbp2._1.x=-86;
    pbp2._1.y=21;
    pbp2._2.x=-163;
    pbp2._2.y=43;
    pbp2._3.x=-163;
    pbp2._3.y=77;
    pbp2._4.x=2;
    pbp2._4.y=77;
    //*********************
    Display.About=false;
    Display.choose=false;
    Display.endgame=false;
    Display.exit=false;
    Display.Game=false;
    Display.Menu=false;
    Display.Move=false;
    Display.Pause=false;
    Display.Setting=false;
    Display.table=false;
    Display.Start=true;
    //**********************
    name_of_music[0]="first";
    name_of_music[1]="second";
    name_of_music[2]="third";
    name_of_music[3]="forth";
    //***********************
    string about="photos//about.png";
    int n = about.length();
    char char_array[n+1];
    strcpy(char_array, about.c_str());
    texture_my.About = IMG_LoadTexture( Renderer, char_array);
}
void animeishen_of_punch(int number_of_pleyer)
{
    if(number_of_pleyer==1)
    {
       double teta=atan((player2.y-player1.boot.y)/(player2.x-player1.boot.x-player1.boot.tool));
       for(int i=0;player1.boot.x+player1.boot.tool+i*cos(teta)<player2.x;i+=10)
       {
            present_game();
            if(!(eventt.power_p1==1||eventt.power_p2==1))
            {
                fast_texture(bal.x-bal.r,bal.y-bal.r,texture_my.balll,2*bal.r,2*bal.r);
            }
            if(eventt.power_p2!=3)
            {
                textureEx(player1.boot.x,player1.boot.y,player1.foot,player1.boot.tool,player1.boot.arz,player1.boot.point.x,player1.boot.point.y,player1.boot.angle);
                fast_texture(player1.x-player1.r_head,player1.y-player1.r_head,texture_my.p1_h,2*player1.r_head,2*player1.r_head);
            }
            if(eventt.power_p1!=3)
            {
                textureEx(player2.boot.x,player2.boot.y,player2.foot,player2.boot.tool,player2.boot.arz,player2.boot.point.x,player2.boot.point.y,player2.boot.angle);
                fast_texture(player2.x-player2.r_head,player2.y-player2.r_head,texture_my.p2_h,2*player2.r_head,2*player2.r_head);
            }
            texture(player1.boot.x+player1.boot.tool+i*cos(teta)-20,player1.boot.y+i*sin(teta),"photos//freeze.png",40,40);
            SDL_RenderPresent(Renderer);
       }
    }
    else if(number_of_pleyer==2)
    {
        double teta=atan((player1.y-player2.boot.y)/(player1.x-player2.boot.x));
         for(int i=0;player2.boot.x-i*cos(teta)>player1.x;i+=10)
       {
            present_game();
            if(!(eventt.power_p1==1||eventt.power_p2==1))
            {
                fast_texture(bal.x-bal.r,bal.y-bal.r,texture_my.balll,2*bal.r,2*bal.r);
            }
            if(eventt.power_p2!=3)
            {
                textureEx(player1.boot.x,player1.boot.y,player1.foot,player1.boot.tool,player1.boot.arz,player1.boot.point.x,player1.boot.point.y,player1.boot.angle);
                fast_texture(player1.x-player1.r_head,player1.y-player1.r_head,texture_my.p1_h,2*player1.r_head,2*player1.r_head);
            }
            if(eventt.power_p1!=3)
            {
                textureEx(player2.boot.x,player2.boot.y,player2.foot,player2.boot.tool,player2.boot.arz,player2.boot.point.x,player2.boot.point.y,player2.boot.angle);
                fast_texture(player2.x-player2.r_head,player2.y-player2.r_head,texture_my.p2_h,2*player2.r_head,2*player2.r_head);
            }
            texture(player2.boot.x-i*cos(teta),player2.boot.y-i*sin(teta),"photos//freeze.png",40,40);
            SDL_RenderPresent(Renderer);
       }
    }
}
