/*#####################################################################################

Space Invaders Game
Group 11

Team:
NIRMAL L.Y.T. 		19/ENG/072
LAKSHITHA N.V.D.	19/ENG/062
MADUWANTHA A.P.		19/ENG/121
RUKSHAN G.G.K.		19/ENG/092

#####################################################################################*/

#include <iostream>
#include "windows.h"
#include "time.h"
#include <string.h>
#include <string>
#include <bitset>

using namespace std;

//A char Array is used as the Game Environment
char Map[40][85] = {

"# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #",
"# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #",
"# #                     #                                                   # #",
"# #                     #                 SS  SS  SS  SS  SS  SS  SS        # #",
"# #   SPACE             #                 @@  @@  @@  @@  @@  @@  @@        # #",
"# #   INVADERS          #                   SS  SS  SS  SS  SS  SS          # #",
"# #   V 0.1             #                   @@  @@  @@  @@  @@  @@          # #",
"# #                     #                                                   # #",
"# # # # # # # # # # # # #                                                   # #",
"# #                     #                                                   # #",
"# #                     #                                                   # #",
"# #   Points :          #                                                   # #",
"# #                     #                                                   # #",
"# #                     #                                                   # #",
"# #                     #                                                   # #",
"# #                     #                                                   # #",
"# #                     #                                                   # #",
"# #                     #                                                   # #",
"# #                     #                                                   # #",
"# #                     #                                                   # #",
"# #                     #                                                   # #",
"# #   Health            #                                                   # #",
"# #   200/200           #                              W                    # #",
"# #                     #                                                   # #",
"# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #",
"# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #",

};

//Game Ending Variable
bool endgame = false;

//The Speed Of the game is decide by this
int gamespeed = 10;

//Bomb Variables
//To activate or Deactivate Bombs
bool bomb_act = 1;
//Keep the record of how many bombs are available
int bomb_count = 3;
//Count how many bombs are used
int bomb_c = 0;

//Bullets
int randomNum;
//Bullet Speed
int bull_speed = 50;

//Health
int maxHealth = 200;
int yourHealth = maxHealth;

//Points
int pointc;

//Sounds
bool sounds = 0;
bool s_fire = 0;
bool s_move = 0;

int x = 0;
int y = 0;

//Functions
void setcolor();        //Color is set by this
void game();            //The main game is run here
void inp_handle();      //All the keyboard inputs are handled here
void settings();        //Settings
void main_menu();       //Main Menu
void how_to_play();     //How to play Options
void exit_q();          //Open when exiting the game

void sound();           //Manage Sound Settings
void colors();          //Manage Color Settings

void game_settings();    //Game settings are Manage By here
void game_speed();      //Game speed is controlled by here
void health();          //Player Health is controlled by here
void Bullets();         //The bullets options are controlled by here

void Bomb_func();       //Change Bomb is activated or deactivated
void num_of_bombs();    //Change the number of bombs available

int main(){
    main_menu();
    game();
    exit_q();

    return 0;
}

void setcolor(int color_code){
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(h, color_code);
}

void game(){

    while (endgame == false){

        srand(time(0));
        system("cls");
        //Print Map at the beginning
        for (y = 0; y<26; y++){
            cout<< Map[y] <<endl;
        }

        if (bomb_act==1){
            cout<<"\nBomb Status : Activated."<<endl;
            cout<<"Bomb Count : "<<bomb_c<<" / "<<bomb_count<<endl;
        }
        else if (bomb_act==0){
            cout<<"\nBomb Status : Deactivated."<<endl;
        }

        //Print Points
        {
        Map[11][13] = ':';
        Map[11][15] = '0' + pointc/100;
        Map[11][16] = '0' + (pointc/10)-((pointc/100)*10);
        Map[11][17] = '0' + pointc-((pointc/10)*10);}

        //Print Your Health
        {int print_health = yourHealth;

        Map[22][6] = '0' + print_health/100;
        Map[22][7] = '0' + (print_health/10)-((print_health/100)*10);
        Map[22][8] = '0' + print_health-((print_health/10)*10);}

        //Print Max Health
        {int print_maxHealth = maxHealth;

        Map[22][10] = '0' + print_maxHealth/100;
        Map[22][11] = '0' + (print_maxHealth/10)-((print_maxHealth/100)*10);
        Map[22][12] = '0' + print_maxHealth-((print_maxHealth/10)*10);}


        //End Game when Health is 0
        if (yourHealth <= 0){
            //Clear Screen After Fail
            system("cls");
            //Make Game End
            endgame = true;
        }

        //Process
        for (y = 0; y<40; y++){
            for ( x = 0; x<70; x++){
                switch (Map[y][x]){

                //Player
                case 'W':{
                    inp_handle();
                    break;
                }

                //Player Bullets
                case ('^'):{
                    Map[y][x] = ' ';
                    y--;
                    if (Map[y][x] != '#' && Map[y][x] != '@' && Map[y][x] != 'S' && Map[y][x] != 'X' && Map[y][x] != 'Y'){

                        Map[y][x] = '^';
                    }
                   else if(Map[y][x] == '@'){
                        Map[y][x] = 'X';
                        pointc+=5;
                    }
                    else if(Map[y][x] == 'S'){
                        Map[y][x] = 'Y';
                        pointc+=3;
                    }
                    else if(Map[y][x] == 'X'){
                        Map[y][x] = 'Y';
                        pointc+=2;
                    }
                    else if(Map[y][x] == 'Y'){
                        Map[y][x] = ' ';
                        pointc++;
                    }
                    break;

                }

                //Player Bomb
                case ('O'):{
                        Map[y][x] = ' ';
                        y--;
                        if (Map[y][x] != '#' && Map[y][x] != '@' && Map[y][x] != 'S' && Map[y][x] != 'X' && Map[y][x] != 'Y' && Map[y][x] != '^'){
                            Map[y][x] = 'O';
                        }
                        else if (Map[y][x] == '@' || Map[y][x] == 'S' || Map[y][x] == 'X' || Map[y][x] == 'Y'){
                                bomb_c++;

                            //Points
                            if(Map[y][x] == '@'){
                                pointc+=5;
                            }
                            else if(Map[y][x] == 'S'){
                                pointc+=3;
                            }
                            else if(Map[y][x] == 'X'){
                                pointc+=2;
                            }
                            else if(Map[y][x] == 'Y'){
                                pointc++;
                            }

                            Map[y][x] = ' ';

                            Map[y+1][x] = 'g';
                            Map[y+1][x+1] = 'g';
                            Map[y-1][x-1] = 'g';
                            Map[y][x+1] = 'g';
                            Map[y][x-1] = 'g';
                        }

                    break;
                }

                //Bomb Particles
                case ('g'):{
                    Map[y][x] = ' ';
                    y--;
                    if (Map[y][x] != '#' && Map[y][x] != '@' && Map[y][x] != 'S' && Map[y][x] != 'X' && Map[y][x] != 'Y' && Map[y][x] != '^'){
                        Map[y][x] = 'g';
                    }
                    else if (Map[y][x] == '@' || Map[y][x] == 'S' || Map[y][x] == 'X' || Map[y][x] == 'Y'){

                         //Points
                        if(Map[y][x] == '@'){
                            pointc+=5;
                        }
                        else if(Map[y][x] == 'S'){
                            pointc+=3;
                        }
                        else if(Map[y][x] == 'X'){
                            pointc+=2;
                        }
                        else if(Map[y][x] == 'Y'){
                            pointc++;
                        }

                        Map[y][x] = ' ';

                    }


                    break;

                }

                //Shield
                case 'K':{
                    Map[y][x] = ' ';
                    y--;
                    if(Map[y][x] == ' '){
                        Map[y][x] = 'L';
                    }

                    break;
                }

                //Enemies
                case '@':
                case 'S':
                case 'X':
                {
                    randomNum = rand() %bull_speed +1;

                    if(randomNum == 1){
                        if(Map[y+1][x] != '@' && Map[y+1][x] != 'X' && Map[y+1][x] != 'Y' && Map[y+1][x] != 'S'){
                            y++;
                            Map[y][x] = '|';
                        }
                    }
                    break;
                }

                //Enemy Bullets
                case '|':{
                    Map[y][x]= ' ';
                    y++;

                    if (Map[y][x] != '#' && Map[y][x] != 'W' && Map[y][x] != 'S' && Map[y][x] != 'X' && Map[y][x] != 'Y'){
                        Map[y][x] = '|';
                    }
                    else if(Map[y][x] == 'W' ) {
                        yourHealth -= 20;
                    }
                    break;
                }
                }
            }
        }
    }
}

//Input Handle
void inp_handle(){
    if (GetAsyncKeyState(VK_LEFT) !=0){
        int newX = x-1;
        switch (Map[y][newX]) {
            case ' ':
                Map[y][x] = ' ';
                x--;
                Map[y][newX] = 'W';
                //Sleep(40);
                if (sounds == 1 && s_move == 1){
                    Beep(1523,5);
                }
                break;
        }
    }

    if (GetAsyncKeyState(VK_RIGHT) !=0){

        int newX = x+1;
        switch (Map[y][newX]) {
            case ' ':
                Map[y][x] = ' ';
                x++;
                Map[y][newX] = 'W';
                // Sleep(40);
                if (sounds == 1 && s_move == 1){
                    Beep(1523,5);
                }
                break;
            }
        }

    if (GetAsyncKeyState(VK_UP) !=0){
        int newY = y-1;
        switch (Map[newY][x]) {
            case ' ':
                Map[y][x] = ' ';
                y--;
                Map[newY][x] = 'W';
                //Sleep(40);
                if (sounds == 1 && s_move == 1){
                    Beep(1523,5);
                }
                break;
        }
    }

    if (GetAsyncKeyState(VK_DOWN) !=0){
        int newY = y+1;
        switch (Map[newY][x]) {
            case ' ':
                Map[y][x] = ' ';
                y++;
                Map[newY][x] = 'W';
                // Sleep(40);
                if (sounds == 1 && s_move == 1){
                    Beep(1523,5);
                }
                break;
            }
        }

    if (GetAsyncKeyState(VK_SPACE) != 0){
        y--;
        Map[y][x] = '^';
        if (sounds == 1 && s_fire == 1){
            Beep(1523,5);
        }
    }

    if (GetAsyncKeyState(VK_ESCAPE) != 0){
        system("cls");
        main_menu();
    }

    if (GetAsyncKeyState(VK_TAB) != 0){
        if(bomb_act==1){
            if(bomb_c < bomb_count){
            y--;
            Map[y-1][x-1] = 'O';
            if (sounds == 1 && s_fire == 1){
                Beep(123,5);
            }
            }
        }
    }

    if (GetAsyncKeyState(VK_BACK) != 0){
        y--;
        if(Map[y][x] == ' '){
            Map[y][x] = 'K';
        }

    }
}

void settings(){
    system("cls");
    cout<<"Settings : \n\n";
    cout<< "(1) Sound\n";
    cout<< "(2) Colors\n";
    cout<< "(3) Game settings\n";
    cout<< "(4) Back\n";

    cout<<endl<<endl;
    string set_change;
    while(1){
        cout<<"Select Your choice : ";
        cin >> set_change;

        if (set_change == "sound" || set_change == "Sound" || set_change == "SOUND" || set_change == "1"){
            sound();
            break;
        }
        else if(set_change == "colors" || set_change == "COLORS" || set_change == "Colors" || set_change == "2"){
            colors();
            break;
        }
        else if(set_change == "Settings" || set_change == "settings" || set_change == "SETTINGS" || set_change == "3"){
            game_settings();
            break;
        }
        else if(set_change == "back" || set_change == "BACK" || set_change == "Back" || set_change == "4"){
            main_menu();
            break;
        }
        else{
            cout<<"Sorry....Did not get that\n\n";
        }
    }
}

void main_menu(){
    system("cls");
    cout<<"Main Menu : \n\n";
    cout<< "(1) Play\n";
    cout<< "(2) Settings\n";
    cout<< "(3) How to play\n";
    cout<< "(4) Exit\n\n";

    string main_set_change;
    while(1){
        cout<<"Select Your choice : ";
        cin >> main_set_change;

        if (main_set_change == "play" || main_set_change == "PLAY" || main_set_change == "Play" || main_set_change == "1"){
            game();
            break;
        }
        else if(main_set_change == "Settings" || main_set_change == "settings" || main_set_change == "SETTINGS" || main_set_change == "2"){
            settings();
            break;
        }
        else if(main_set_change == "How" ||  main_set_change == "how" || main_set_change == "HOW"|| main_set_change == "3"){
            how_to_play();
            break;
        }
        else if(main_set_change == "exit" || main_set_change == "EXIT" || main_set_change == "Exit" || main_set_change == "4"){
            exit_q();
            break;
        }
        else{
            cout<<"Sorry....Did not get that\n\n";
        }
    }
}

void how_to_play(){
    system("cls");
    cout<< "How to Play : \n\n";
    cout<< "Move Ship : \n\n";
    cout<< "Move right  = Right Arrow Key\n";
    cout<< "Move Left   = Left Arrow Key\n";
    cout<< "Move up     = Up Arrow Key\n";
    cout<< "Move down   = Down Arrow Key\n\n";

    cout<< "Fire        = Space\n";
    cout<< "Bomb        = Tab\n";
    cout<< "Shield      = Backspace\n\n";

    cout<< "Main Menu    = Escape (ESC)\n\n";

    cout<< "For more info refer the document\n\n";

    system("pause");
    main_menu();
}

void exit_q(){
    system("cls");
    cout<<"Thank you for playing...\n";

    system("pause");
    exit(0);
}

//Settings
//Sounds Settings
void sound(){
    system("cls");
    cout<< "Sound : \n\n";
    system("cls");
    cout<< "Sound (on/off) : " << sounds << endl;
    cout<< "Fire (on/off) : " << s_fire << endl;
    cout<< "Movement (on/off) : " << s_move << endl;

    bool s_set_change = 0;
    string inp_s_set_change;
    while(1){
        cout<<"Do you want to change settings (y/n) : ";
        cin>> inp_s_set_change;
        //cout<<endl;
        if (inp_s_set_change == "yes" || inp_s_set_change == "YES" || inp_s_set_change == "Yes" || inp_s_set_change == "1" || inp_s_set_change == "y" || inp_s_set_change == "Y"){
            s_set_change = 1;
            break;
        }
        else if(inp_s_set_change == "no" || inp_s_set_change == "NO" || inp_s_set_change == "No" || inp_s_set_change == "0" || inp_s_set_change == "n" || inp_s_set_change == "N"){
            s_set_change = 0;
            break;
        }
        else{
            cout<<"Sorry....Did not get that\n\n";
        }
    }

    system("cls");
    string inp_s;
    if (s_set_change == 1){
         while(1){
            cout<< "Sound (on/off) : ";
            cin>> inp_s;
            if (inp_s == "on" || inp_s == "ON" || inp_s == "On" || inp_s == "1"){
                sounds = 1;
                break;
            }
            else if(inp_s == "off" || inp_s == "OF" || inp_s == "Of" || inp_s == "0"){
                sounds = 0;
                break;
            }
            else{
                cout<<"Sorry....Did not get that\n\n";
            }
        }

        if (sounds==1){
        while(1){
            cout<< "Fire Sound (on/off) : ";
            cin>> inp_s;
            if (inp_s == "on" || inp_s == "ON" || inp_s == "On" || inp_s == "1"){
                s_fire = 1;
                break;
            }
            else if(inp_s == "off" || inp_s == "OF" || inp_s == "Of" || inp_s == "0"){
                s_fire = 0;
                break;
            }
            else{
                cout<<"Sorry....Did not get that\n\n";
            }
        }

        while(1){
            cout<< "Movement Sound (on/off) : ";
            cin>> inp_s;
            if (inp_s == "on" || inp_s == "ON" || inp_s == "On" || inp_s == "1"){
                s_move = 1;
                break;
            }
            else if(inp_s == "off" || inp_s == "OF" || inp_s == "Of" || inp_s == "0"){
                s_move = 0;
                break;
            }
            else{
                cout<<"Sorry....Did not get that\n\n";
            }
        }}
        settings();
    }
    else{
        cout<<"Go back\n\n";
        settings();
    }
}

//Color Seetings
void colors(){
    int color_name=10;

    system("cls");
    cout<< "Colors : \n\n";

    for(int i=0;i<255;i++){

        if(i%16==0){
            cout<<endl;
        }
        setcolor(i);

        if (i%17!=0){
            if (i<10){
                cout<<" "<<i<<"  ";
            }
            else if(i<100){
                cout<<i<<"  ";
            }
            else{
                cout<<i<<" ";
            }
        }
    }
    setcolor(10);
    cout<<endl<<endl;

    cout<< "Enter the Color Code Number from list : ";
    cin>>color_name;

    setcolor(color_name);
    system("pause");
    settings();
}

//Game Settings
void game_settings(){
    system("cls");
    cout<<"Game Settings : \n\n";
    cout<< "(1) Game Speed\n";
    cout<< "(2) Max Health\n";
    cout<< "(3) Bullets Speed\n";
    cout<< "(4) Bomb Active\n";
    cout<< "(5) Number of Bombs\n";
    cout<< "(6) Play\n";
    cout<< "(7) Back\n\n";

    string main_set_change;
    while(1){
        cout<<"Select Your choice : ";
        cin >> main_set_change;

        system("cls");
        if (main_set_change == "Speed" || main_set_change == "speed" || main_set_change == "SPEED" || main_set_change == "1"){
            game_speed();
            break;
        }
        else if(main_set_change == "Health" || main_set_change == "HEALTH" || main_set_change == "health" || main_set_change == "2"){
            health();
            break;
        }
        else if(main_set_change == "Bullets" ||  main_set_change == "bullets" || main_set_change == "BULLETS"|| main_set_change == "3"){
            Bullets();
            break;
        }
        else if(main_set_change == "Bomb" ||  main_set_change == "bomb" || main_set_change == "BOMB"|| main_set_change == "4"){
            Bomb_func();
            break;
        }
        else if(main_set_change == "Number" ||  main_set_change == "number" || main_set_change == "NUMBER"|| main_set_change == "5"){
            num_of_bombs();
            break;
        }
        else if(main_set_change == "Play" ||  main_set_change == "play" || main_set_change == "PLAY"|| main_set_change == "6"){
            game();
            break;
        }
        else if(main_set_change == "Back" || main_set_change == "back" || main_set_change == "BACK" || main_set_change == "7"){
            settings();
            break;
        }
        else{
            cout<<"Sorry....Did not get that\n\n";
        }
    }
}

void game_speed(){
    string inp_game_speed;
    system("cls");
    cout << "Current Game Speed : "<<gamespeed<<endl<<endl;
    while(1){
        try{
            cout<< "Enter your preferred Game Speed : ";
            cin>>inp_game_speed;
            if(stoi(inp_game_speed)>0){
                gamespeed = stoi(inp_game_speed);
            }else{
                cout<<"\n\nEnter number larger than 0.\n\n";
                system("pause");
                game_speed();
            }
        }
        catch(const invalid_argument & e){
            cout<<"\n\nEnter valid Number please\n\n";
            system("pause");
            game_speed();
        }
        game_settings();
        break;
    }
}

void health(){
    string inp_health;
    system("cls");
    cout << "Current Max Health : "<<maxHealth<<endl<<endl;
    while(1){
        try{
            cout<< "Enter your preferred Health : ";
            cin>>inp_health;
            if(stoi(inp_health)>0){
                maxHealth = stoi(inp_health);
                yourHealth = maxHealth;
                game_settings();
                break;
            }else{
                cout<<"\n\nEnter number larger than 0.\n\n";
                system("pause");
                health();
            }
        }
        catch(const invalid_argument & e){
            cout<<"\n\nEnter valid Number please\n\n";
            system("pause");
            health();
        }
        health();
        break;
    }
}

void Bullets(){
    string inp_bull_speed;
    system("cls");
    cout << "Current Enemy Bullet Speed : "<<bull_speed<<endl<<endl;
    while(1){
        try{
            cout<< "Enter your preferred Bullet Speed : ";
            cin>>inp_bull_speed;
            if(stoi(inp_bull_speed)>0){
                bull_speed = stoi(inp_bull_speed);
                game_settings();
                break;
            }else{
                cout<<"\n\nEnter number larger than 0.\n\n";
                system("pause");
                Bullets();
            }
        }
        catch(const invalid_argument & e){
            cout<<"\n\nEnter valid Number please\n\n";
            system("pause");
            Bullets();
        }
        Bullets();
        break;
    }
}

void Bomb_func(){
    string bomb_stat;
    string inp_bomb_count;

    while(1){
        if (bomb_act==1){
            cout<< "Bombs are Activated.\n\nDo you want to Deactivate : ";
            cin>> bomb_stat;

            if (bomb_stat == "yes" || bomb_stat == "YES" || bomb_stat == "Yes" || bomb_stat == "1" || bomb_stat == "y" || bomb_stat == "Y"){
            bomb_act = 0;

            cout<< "\n\nBombs are Deactivated.\n\n";
            system("pause");

            game_settings();

            break;
        }
        else if(bomb_stat == "no" || bomb_stat == "NO" || bomb_stat == "No" || bomb_stat == "0" || bomb_stat == "n" || bomb_stat == "N"){
            bomb_act = 1;

            cout<< "\n\nBombs are Activated.\n\n";
            system("pause");

            game_settings();

            break;
        }
        else{
            cout<<"Sorry....Did not get that\n\n";
        }



        }
        else if (bomb_act==0){
            cout<< "Bombs are Deactivated.\n\nDo you want to Activate : ";
            cin>> bomb_stat;

            if (bomb_stat == "yes" || bomb_stat == "YES" || bomb_stat == "Yes" || bomb_stat == "1" || bomb_stat == "y" || bomb_stat == "Y"){
            bomb_act = 1;

            cout<< "\n\nBombs are Activated.\n\n";
            system("pause");

            game_settings();

            break;
        }
        else if(bomb_stat == "no" || bomb_stat == "NO" || bomb_stat == "No" || bomb_stat == "0" || bomb_stat == "n" || bomb_stat == "N"){
            bomb_act = 0;

            cout<< "\n\nBombs are Deactivated.\n\n";
            system("pause");

            game_settings();

            break;
        }
        else{
            cout<<"Sorry....Did not get that\n\n";
        }
        }


    }
}

void num_of_bombs(){
    string inp_num_of_boms;
    system("cls");
    cout << "Current Number of Bombs Available : "<<bomb_count<<endl<<endl;
    while(1){
        try{
            cout<< "Enter your preferred Number of Bombs : ";
            cin>>inp_num_of_boms;
            if(stoi(inp_num_of_boms)>0){
                bomb_count = stoi(inp_num_of_boms);
                game_settings();
                break;
            }else{
                cout<<"\n\nEnter number larger than 0.\n\n";
                system("pause");
                num_of_bombs();
            }
        }
        catch(const invalid_argument & e){
            cout<<"\n\nEnter valid Number please\n\n";
            system("pause");
            num_of_bombs();
        }
        num_of_bombs();
        break;
    }
}


