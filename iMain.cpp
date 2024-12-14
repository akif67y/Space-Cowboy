#include "iGraphics.h"
// #include "bitmap_loader.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
# pragma comment(lib, "Winmm.lib")
# include<mmsystem.h>

// boulder gular x change na kore asteriod gular koro

int x = 0, y = 0, r = 20; // k = count of enemy
void drawhomepage();
void drawStartpage();
void drawAboutpage();
void drawScorepage();
void drawMusicpage();
void bulletchange();
void collisionCheck2();
void collisionresult();
void collisionCheck1();
void drawArenapage();
void collisionship();
void collisionshipresult();
void asteriodgenerate();
void healthcollision();
void drawGameoverpage();
void savescore(char newplayer[], int len);

// void rocketbullet();
void drawarena2();
void spaceshipgenerate();
bool music_on = true;
// char lobby_sound[30]="bmp_outputs\\lobby.wav";
// void boroboulderdraw();
typedef struct{
	char name[100];
	int score;
}man;
#define MAX 100
man entry[MAX];
int sorted = 0;
int gunpower = 10;
int damage = 10;
int damagecount = 0;
int score = 0;
typedef struct{
	int x;
	int y;
	int health;
	int move;
	int bulletcheck[30];
}spaceship;

typedef struct{
	int place;
	int check;
}arena;
typedef struct {
	int shiptype;
	int check;

}ship;
arena are ;
ship shi;
int bouldernumber = 0;
int gamestate = 1;
int createBullet = 0;
typedef struct play{
	int x;
	int y;
	int health;
}player;

player hero;
typedef struct borobol{
	char image[250];
	int x;
	int y;
	int health;
}borobol;

typedef struct {
	int x;
	int y;
	int status;

}object;

object shild, helth, boost;
char newplayer[100] = "";
int len = 0;



borobol now[4];
spaceship rocket[2];


char boulder[3][250] = {"bmp_outputs//asteroid.bmp", "bmp_outputs//asteroid.bmp", "bmp_outputs//asteroid.bmp" };
int bulletcheck[60] = {0};
int bouldercheck[3] ={0};
player boulderCoordinate[3];



char point[10000];
void scoreshower(){
	iSetColor(129,128,128);
	iFilledRectangle(100, 500, 100, 40);

    sprintf(point,"Score : %d", score);
	iSetColor(255,0,0);
	iText(110, 520, point, GLUT_BITMAP_HELVETICA_10);

}

void healthchecker(){
	iSetColor(129,128,128);
	iFilledRectangle(700, 500, 100, 40);

    sprintf(point,"Health : %d", hero.health);
	iSetColor(255,0,0);
	iText(710, 520, point, GLUT_BITMAP_HELVETICA_10);

}
void savescore(char newplayer[], int len){
	FILE *fp =fopen("leaderboard.txt", "a");
	fprintf(fp,"%s %d\n", newplayer, score);
	fclose(fp);
}

void iDraw() {
        iClear();
		
		switch(gamestate){
			case 1:
			drawhomepage();
			break;
			case 2:
			drawArenapage();  // gamestate is 2 for drawarena page
			break;
			case 3:
			drawScorepage();
			break;
			case 4 :
			drawMusicpage();
			break;
			case 5 :
			drawAboutpage();
			break;
			case 6:
			drawStartpage(); 
			break;
			case 7:
			drawarena2();
			break;
			case 8:
			drawGameoverpage(); 
			break;// drawstartpage is drawarena1 page

		}
       

}

/*
	function iMouseMove() is called when the user presses and drags the mouse.
	(mx, my) is the position where the mouse pointer is.
	*/
void iMouseMove(int mx, int my) {
	printf("x = %d, y= %d\n",mx,my);
	
}

/*
	function iMouse() is called when the user presses/releases the mouse.
	(mx, my) is the position where the mouse pointer is.
	*/
void iMouse(int button, int state, int mx, int my) {
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		
		if(gamestate == 1){   // player is in home menu
			if(mx >= 770 && mx <= 970){
				
				if(my >= 10 && my <= 140){   // goes to different menu based on clicks
					gamestate = 5;
				}
				else if(my >= 160 && my <= 290){
					
					gamestate = 4;
				}
				else if(my >= 310 && my <= 440){
					sorted = 0;
					gamestate = 3;
				}
				else if(my >= 460 && my <= 590){
					gamestate = 2;
				}
			}
		}


		
		else if(gamestate == 2){
			if((mx > 10 && mx < 410) && (my > 275 && my < 550)){
				are.place = 1;
				are.check = 1;
			}
			if((mx > 430 && mx < 830) && (my > 275 && my < 550)){
				are.place = 2;
				are.check = 1;
			}
			if((mx > 10 && mx < 278) && (my > 5 && my < 270)){
				shi.shiptype = 1;
				shi.check = 1;
			}
			if((mx > 285 && mx < 553) && (my > 5 && my < 270)){
				shi.shiptype = 2;
				shi.check = 1;
			}

			if(shi.check == 1 && are.check == 1){
				if( are.place == 1){
					gamestate = 6;    // arena 1 e asteroid er khela hobe
				}
				else if(are.place == 2){
					gamestate = 7;    // arena 2 e spaceship er khela hobe
				}
			}
		}

		else if(gamestate == 6 || gamestate == 7){  // have to change this gamestate
			createBullet = 1;
		}
		else if(gamestate == 8){
			if((my >= 500 && my <= 600) && (mx >= 0 && mx <= 100)){
				gamestate = 1;
			}
		}

		
	}
	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
		
		printf("x = %d, y= %d\n",mx,my);
	}
}

/*
	function iKeyboard() is called whenever the user hits a key in keyboard.
	key- holds the ASCII value of the key pressed.
	*/
void iKeyboard(unsigned char key) {
	// if (key == 'k') {
	// 	createBullet = 1;
	// }
	if(gamestate == 6 || gamestate == 7){
	if( key == 'd'){
		int t = hero.x + 10;
		if(t > 900){
			hero.x = 900;
		}
		else {
			hero.x = t;
		}
	}
	else if(key == 'a'){
		int t = hero.x - 10;
		if(t < 0){
			hero.x =0;
		}
		else {
			hero.x = t;
		}
	}}
	else if(gamestate == 8){
		if(key != '\b' && key != '\r'){
			newplayer[len] = key;
			newplayer[len + 1] = '\0';
			len++;
		}
		else if( key == '\b' ){
			if(len >= 0){
				newplayer[len - 1] = '\0'; 
				len--;
			}
		}
		else if( key == '\r'){
			savescore(newplayer, len);;

		}

	}
	
		
	
}

/*
	function iSpecialKeyboard() is called whenver user hits special keys like-
	function keys, home, end, pg up, pg down, arraows etc. you have to use
	appropriate constants to detect them. A list is:
	GLUT_KEY_F1, GLUT_KEY_F2, GLUT_KEY_F3, GLUT_KEY_F4, GLUT_KEY_F5, GLUT_KEY_F6,
	GLUT_KEY_F7, GLUT_KEY_F8, GLUT_KEY_F9, GLUT_KEY_F10, GLUT_KEY_F11, GLUT_KEY_F12,
	GLUT_KEY_LEFT, GLUT_KEY_UP, GLUT_KEY_RIGHT, GLUT_KEY_DOWN, GLUT_KEY_PAGE UP,
	GLUT_KEY_PAGE DOWN, GLUT_KEY_HOME, GLUT_KEY_END, GLUT_KEY_INSERT
	*/
void iSpecialKeyboard(unsigned char key) {

	// if (key == GLUT_KEY_F1) {
	// 	if(music_on == true){
	// 		music_on = false;
	// 		PlaySound(0,0,0);
	// 	}
	// 	else if(music_on == false){
	// 		music_on = true;
	// 		PlaySound(TEXT("bmp_outputs\\lobby.wav") , NULL ,SND_LOOP | SND_ASYNC);
			
	// 	}
	// }
	
}
void drawGameoverpage(){
	iSetColor(128,128,128);
	iFilledRectangle(0,0,1000,600);
	iShowBMP2(0,0,"bmp_outputs//gameover.bmp",0);
	iShowBMP2(0,500,"bmp_outputs//idolo.bmp",1321060);

	iSetColor(255,0,0);
	iText(500,200, "Enter your name :", GLUT_BITMAP_HELVETICA_18);
	iRectangle(500, 150, 150, 40);
	iSetColor(0, 255, 0);
	iText(500, 200, newplayer, GLUT_BITMAP_HELVETICA_18 );


}
void drawArenapage(){
	iSetColor(128,128,128);
	iFilledRectangle(0,0,1000,600);
	iShowBMP2(0,0,"bmp_outputs//home.bmp",0);
	iShowBMP2(10, 275,"bmp_outputs//arena1formenu.bmp",0);
	iShowBMP2(430, 275, "bmp_outputs//arena2formenu.bmp", 0);
	iShowBMP2(10, 5, "bmp_outputs//ship1.bmp", 0);
	iShowBMP2(285, 5, "bmp_outputs//ship2.bmp", 0);

	iSetColor(225,225,225);
	iText(10, 560, "ARENA", GLUT_BITMAP_TIMES_ROMAN_24);
	iText(10, 260, "SHIP", GLUT_BITMAP_TIMES_ROMAN_24);

}
void drawhomepage(){
	shi.check = 0;
	are.check = 0;
	hero.health = 100;
	score = 0;
    iSetColor(128, 128, 128);
	iFilledRectangle(0,0,1000,600);
	iShowBMP2(0,0,"bmp_outputs//home.bmp", 0);

	iShowBMP2(770, 10, "bmp_outputs//buttoncdi.bmp", 0);
	iShowBMP2(770, 160, "bmp_outputs//buttoncdi.bmp", 0);
	iShowBMP2(770, 310, "bmp_outputs//buttoncdi.bmp", 0);
	iShowBMP2(770, 460, "bmp_outputs//buttoncdi.bmp", 0);

	iSetColor(225,225,225);
	iText(800, 69, "ABOUT", GLUT_BITMAP_TIMES_ROMAN_24);
	iText(800, 218, "MUSIC", GLUT_BITMAP_TIMES_ROMAN_24);
	iText(800, 365, "SCORE", GLUT_BITMAP_TIMES_ROMAN_24);
	iText(800, 518, "PLAY", GLUT_BITMAP_TIMES_ROMAN_24);

}
void spaceshipgenerate(){  //
	// srand(time(NULL));
	if(gamestate == 7){
		// srand(time)
	
		for(int j = 0; j < 2 ; j++){  // generating boulder at the start
			// if(k == p) break;
			if(rocket[j].health <= 0){

			rocket[j].health = 100;
			if(j == 0){
				rocket[j].x = 225;
				rocket[j].y = 490;

			}
			else if( j == 1){
				rocket[j].x = 725;
				rocket[j].y = 490;

			}
			// printf("%d", j);
			// k++;
			}
		
		}
	
	//changing exosting rocket x coordinate
	
	for(int i = 0; i < 2 ; i++){  // i can make it one loop

		if(rocket[i].health > 0){

		   //changing existing boulder coordinate
		
		if(rocket[i].move == 1){
			rocket[i].x = rocket[i].x + 20  ;  // egla thikmoto kaj korteche nah
		}
		else if(rocket[i].move == -1) {
			rocket[i].x = rocket[i].x - 20  ;
		}
		if(i == 0){
		if(rocket[i].x < 10){
			rocket[i].x = 10 ;
			rocket[i].move = 1;
		}
		else if(rocket[i].x > 445 ) {
			rocket[i].x = 445;
			rocket[i].move = -1;
		}

		}
		else if( i == 1){
			if(rocket[i].x < 555){
			rocket[i].x = 555 ;
			rocket[i].move = 1;
		}
		else if(rocket[i].x > 900 ) {
			rocket[i].x = 900;
			rocket[i].move = -1;
		}

		}
	

	rocket[i].bulletcheck[24] = rocket[i].x + 45;
	for(int l = 0; l < 29; l++){
		rocket[i].bulletcheck[l] = rocket[i].bulletcheck[l+1];
		rocket[i].bulletcheck[l+1] = 0;
	}
	rocket[i].bulletcheck[29] = 0;
		
			
	}
	

	}

	int t = rand() % 2;
	int p = rand() % 4;
	if(t == 1){
		for(int j = 0, k = 0; j < 3; j++){  // generating boulder at the start
			if(k == p) break;
			if(bouldercheck[j] == 0){

			bouldercheck[j] = 1;
			boulderCoordinate[j].x = 0 + rand() % 600;
			boulderCoordinate[j].y = 575;
			k++;
			
			}
		}
		
	}
		for(int i = 0; i < 3 ; i++){
		int s = rand() % 2;   //changing existing boulder coordinate
		
		if(s == 0){
			boulderCoordinate[i].x = boulderCoordinate[i].x + 50  ;
		}
		else {
			boulderCoordinate[i].x = boulderCoordinate[i].x - 50  ;
		}
		
		if(boulderCoordinate[i].x >= 990) boulderCoordinate[i].x = 990;  //ekta arektake hit korleo direction change kora uchit
		if(boulderCoordinate[i].x < 10) boulderCoordinate[i]. x = 0;
		boulderCoordinate[i].y = boulderCoordinate[i].y - 50;
		if(boulderCoordinate[i].y < 5){
			bouldercheck[i] = 0;  //removing it when reaches the end of the screen;
		}
		}

		int f = rand() % 7;
	if(f == 3 && shild.status == 0){
		shild.x = 10 + rand() % 500;
		shild.y = 590;
		shild.status = 1;
	}
	else if(f == 2 && helth.status == 0){
		helth.x = 10 + rand() % 500;
		helth.y = 590;
		helth.status = 1;
	}
	else if(f == 6 && boost.status == 0){
		boost.x = 10 + rand() % 500;
		boost.y = 590;
		boost.status = 1;
	}

	if(shild.status == 1){
		shild.y = shild.y - 50;
		if(shild.y < 5) shild.status = 0;
	}
	if(helth.status == 1){
		helth.y = helth.y - 50;
		if(helth.y < 5) helth.status = 0;
	}
	if(boost.status == 1){
		boost.y = boost.y - 50;
		if(boost.y < 5) boost.status = 0;
	}
	
	}
		
	

		

}
void collisionship(){

	for(int i = 0; i < 60; i++){
		if(bulletcheck[i] != 0 && bulletcheck[i] != -1){  // bullet hits plane
			
			for(int k = 0; k < 2; k++){
				if(rocket[k].health > 0){
					if((bulletcheck[i] >= rocket[k].x && bulletcheck[i] <= rocket[k].x + 100) &&( (i * 10 >= rocket[k].y && i * 10 <= rocket[k].y + 100) )){
						rocket[k].health -= gunpower * 3;
						bulletcheck[i] = -1;
						
					}
				}
			}


			for(int k = 0; k < 3; k++){  // bullet hitls boulder health decrease of boulder
				if(bouldercheck[k] == 1){
					if((bulletcheck[i] >= boulderCoordinate[k].x && bulletcheck[i] <= boulderCoordinate[k].x + 60) &&( (i * 10 >= boulderCoordinate[k].y && i * 10 <= boulderCoordinate[k].y + 60) )){
						boulderCoordinate[k].health -= gunpower;
						bulletcheck[i] = -1;
						
					}
				}
			}

		}

	}
		//boulder hits plane
		for(int j = 0; j < 3;j++){
			if(bouldercheck[j] == 1){
				if(( boulderCoordinate[j].x + 60 >= hero.x && boulderCoordinate[j].x <= hero.x + 105) &&( boulderCoordinate[j].y <= hero.y + 80 )){
					hero.health -= damage /2;
					iShowBMP2(boulderCoordinate[j].x, boulderCoordinate[j].y, "bmp_outputs//collision.bmp",0);
					boulderCoordinate[j].health = 0;
				}
			}
			
		}

// bullet of enemy hits plane
for(int i = 0; i < 2; i++){
	for(int j = 0; j < 30; j++){

		if(rocket[i].bulletcheck[j] != 0 && rocket[i].bulletcheck[j] != -1){

					if((rocket[i].bulletcheck[j] >= hero.x && rocket[i].bulletcheck[j] <= hero.x + 100) &&( (j * 20 >= hero.y && j * 20 <= hero.y + 70) )){
						iShowBMP2(hero.x, hero.y, "bmp_outputs//collision.bmp",0);
						hero.health -= damage / 5;
						rocket[i].bulletcheck[j] = -1;	
					}
				
		}

	}

}




}

void healthcollision(){
		if(damagecount != 0){ damagecount--;}
		else{
			damage = 10;
		}
		if(shild.status == 1){
			if(( shild.x + 30 >= hero.x && shild.x <= hero.x + 105) &&( shild.y <= hero.y + 76  && shild.y + 30 >= hero.y)){
				damage = 0;
				damagecount = 1000;
				shild.status = 0;
			}
		}


		if(helth.status == 1){
			if(( helth.x + 30 >= hero.x && helth.x <= hero.x + 105) &&( helth.y <= hero.y + 76  && helth.y + 30 >= hero.y)){
				hero.health = hero.health + 100;
				helth.status = 0;
			}
		 }

		
			if(boost.status == 1){
			if(( boost.x + 30 >= hero.x && boost.x <= hero.x + 105) &&( boost.y <= hero.y + 76  && boost.y + 30>= hero.y)){
				gunpower = gunpower + 5;
				boost.status = 0;
			}
		}
	
}






		



void drawarena2(){

	iSetColor(128,128,128);
	iFilledRectangle(0,0,1000,600);
	iShowBMP2(0,0, "bmp_outputs//arena2.bmp", 0);
	if(shi.shiptype == 1){
		if(damagecount != 0){
			iCircle(hero.x + 50, hero.y + 50, 50);
		}
		iShowBMP2(hero.x, hero.y, "bmp_outputs//spike2.bmp", 0);
	}
	else if(shi.shiptype == 2){
		if(damagecount != 0){
			iCircle(hero.x + 50, hero.y + 50, 50);
		}
		iShowBMP2(hero.x, hero.y, "bmp_outputs//starwars.bmp", 0);
	}
	bulletchange();
		for(int i = 0; i < 3; i++){
		if(bouldercheck[i] == 1){  // it will work on bouldercheck status
		
		iShowBMP2(boulderCoordinate[i].x, boulderCoordinate[i].y, boulder[i],0);
	}
	}

	for(int i = 0; i < 2; i++){
		if(rocket[i].health > 0){  // it will work on bouldercheck status
		
		iShowBMP2(rocket[i].x, rocket[i].y,"bmp_outputs//enemy.bmp",0);
	}
	for(int j = 0 ; j < 25; j++){

		if(rocket[i].bulletcheck[j] != 0 && rocket[i].bulletcheck[j] != -1){  // 0 for out of screen and -1 for hitting the plane
			
			iShowBMP2(rocket[i].bulletcheck[j], j * 20, "bmp_outputs//sbullet.bmp", 0);  //showing the bullets where they are for every rocket
			
		}
		
	}

	if(helth.status == 1){
		iShowBMP2(helth.x, helth.y, "bmp_outputs//health.bmp",0);
	}
	if(shild.status == 1){
		iShowBMP2(shild.x, shild.y, "bmp_outputs//shield.bmp",0);
	}
	if(boost.status == 1){
		iShowBMP2(boost.x, boost.y, "bmp_outputs//booster_token.bmp",0);
	}
	
	collisionship();
	healthcollision();
	collisionshipresult();


	healthchecker();
	scoreshower();
	
	
	}}

	
void drawStartpage(){
	// srand(time(NULL));
	iSetColor(128,128,128);
	iFilledRectangle(0,0,1000,600);
	iShowBMP2(0,0, "bmp_outputs//arena1.bmp", 0);
	if(shi.shiptype == 1){
		if(damagecount != 0){
			iCircle(hero.x + 50, hero.y + 50, 50);
		}
		iShowBMP2(hero.x, hero.y, "bmp_outputs//spike2.bmp", 0);
	} 
	else if(shi.shiptype == 2){
		if(damagecount != 0){
			iCircle(hero.x + 50, hero.y + 50, 50);
		}
		iShowBMP2(hero.x, hero.y, "bmp_outputs//starwars.bmp", 0);
	}
	
	bulletchange();
	for(int i = 0; i < 3; i++){
		if(bouldercheck[i] == 1){  // it will work on bouldercheck status
		
		iShowBMP2(boulderCoordinate[i].x, boulderCoordinate[i].y, boulder[i],0);
	}
	}
	
	for(int i = 0; i < 4; i++){   

		
		iShowBMP2(now[i].x, now[i].y, now[i].image, 0);
	
	}
	if(shild.status == 1){
		iShowBMP2(shild.x, shild.y, "bmp_outputs//shield.bmp",0);
	}
	if(helth.status == 1){
		iShowBMP2(helth.x, helth.y, "bmp_outputs//health.bmp",0);
	}
	
	if(boost.status == 1){
		iShowBMP2(boost.x, boost.y, "bmp_outputs//booster_token.bmp",0);
	}
	collisionCheck1();
	collisionCheck2();
	collisionresult();

	
	healthchecker();
	scoreshower();
	

	
}
void bulletchange(){
	if(createBullet == 1){ 
		bulletcheck[8] = hero.x + 45;
		createBullet = 0;
	}

	for(int i = 8; i < 60; i++){
		if(bulletcheck[i] != 0 && bulletcheck[i] != -1){
			
			iShowBMP2(bulletcheck[i], i * 10, "bmp_outputs//sbullet.bmp", 0);
			
		}
	}
	for(int i = 59; i >=8; i--){
			bulletcheck[i + 1] = bulletcheck[i] ;
			bulletcheck[i] = 0;
		
	}

}
void asteriodgenerate(){
// eita execute howar jonno condition deya lagbe(differenent arena te gele eita execute hobena)
if(gamestate == 6){
	int t = rand() % 2;
	int p = rand() % 4;
	if(t == 1){
		for(int j = 0, k = 0; j < 3; j++){  // generating boulder at the start
			if(k == p) break;
			if(bouldercheck[j] == 0){

			bouldercheck[j] = 1;
			boulderCoordinate[j].x = 0 + rand() % 600;
			boulderCoordinate[j].y = 575;
			k++;
			
			}
		}
		
	}
		for(int i = 0; i < 3 ; i++){
		int s = rand() % 2;   //changing existing boulder coordinate
		
		if(s == 0){
			boulderCoordinate[i].x = boulderCoordinate[i].x + 50  ;
		}
		else {
			boulderCoordinate[i].x = boulderCoordinate[i].x - 50  ;
		}
		
		if(boulderCoordinate[i].x >= 990) boulderCoordinate[i].x = 990;  //ekta arektake hit korleo direction change kora uchit
		if(boulderCoordinate[i].x < 10) boulderCoordinate[i]. x = 0;
		boulderCoordinate[i].y = boulderCoordinate[i].y - 50;
		if(boulderCoordinate[i].y < 5){
			bouldercheck[i] = 0;  //removing it when reaches the end of the screen;
		}
		}

		for(int i = 0; i < 4; i++){
			now[i].y = now[i].y - 70;
			// noshto hoye geleo etai korbo(health 0 hoile)
			if(now[i]. y < 5) now[i].y = 598;
		
		}

			int f = rand() % 7;
	if(f == 3 && shild.status == 0){
		shild.x = 10 + rand() % 500;
		shild.y = 590;
		shild.status = 1;
	}
	else if(f == 2 && helth.status == 0){
		helth.x = 10 + rand() % 500;
		helth.y = 590;
		helth.status = 1;
	}
	else if(f == 6 && boost.status == 0){
		boost.x = 10 + rand() % 500;
		boost.y = 590;
		boost.status = 1;
	}

	if(shild.status == 1){
		shild.y = shild.y - 80;
		if(shild.y < 10) shild.status = 0;
	}
	if(helth.status == 1){
		helth.y = helth.y - 80;
		if(helth.y < 10) helth.status = 0;
	}
	if(boost.status == 1){
		boost.y = boost.y - 80;
		if(boost.y < 10) boost.status = 0;
	}

	}

	
	
	}






void drawMusicpage(){
	iSetColor(128,128,128);
	iFilledRectangle(0,0,1000,600);
   
}
void drawAboutpage(){

}
void drawScorepage(){ 
	iSetColor(128,128,128);
	iFilledRectangle(0,0,1000,600);
	
	iShowBMP2(0,0,"bmp_outputs//home.bmp",0);
		
	
	 //etar operation gulo ekbar kora dorker, show hobe barbar;
if(sorted == 0){
FILE *fp = fopen("leaderboard.txt", "r");
 if (fp == NULL) {
        printf("Error opening file\n");
        return;
    }
int t = 2;
int i = 0;
while (t != EOF && i < MAX) {
        t = fscanf(fp, "%s %d\n", entry[i].name, &entry[i].score);
        i++;
    }
    fclose(fp);


int max = 0;
int k,j;
for( j = 0; j < i - 1; j++){
	max = j;
	for( k = j + 1; k < i; k++){
		if(entry[max].score < entry[k].score){
			max = k;
		}
	}
	int t;
	char str[100];
	t = entry[max].score;
	entry[max].score = entry[j].score;
	entry[j].score = t;

	strcpy(str, entry[max].name);
	strcpy(entry[max].name, entry[j].name);
	strcpy(entry[j].name, str);
	
}
sorted = 1;
}
	

iSetColor(255,0,0);
for(int l = 0; l < 5; l++ ){
	char display[1000];
	sprintf(display, "%s %d", entry[l].name, entry[l].score);
	int x = 300;
	int y = 500 - 110 * l;
	iText(x,y,display, GLUT_BITMAP_HELVETICA_18);
}

//array this array of strucuture but in different jinish

	

 
	//entry theke top 5 print korbo;



}
void first(){
	// srand(time(NULL));
	hero.x = 500;
	hero.y = 0;
	hero.health = 100;
	for(int i = 0; i < 4; i++){
		strcpy(now[i].image, "bmp_outputs//tile001.bmp");
		// now[i].y = 598 - (rand() % 100);
		now[i].health = 20;
	}
	now[1].y = 50 + (rand()% 100); 
	now[2].y = 150 + (rand() % 100);
	now[3].y = 250 + (rand() % 100);
	now[4].y = 350 + (rand() % 100);

	now[1].x = 350 + (rand()% 100);
	now[2].x = 450 + (rand() % 100);
	now[3].x = 650 + (rand() % 100);
	now[4].x = 850 + (rand() % 100);

	for(int i = 0; i < 3; i++){
		boulderCoordinate[i].health = 10;
	}

	are.place = 0; 
	are.check = 0;
	shi.shiptype = 0;
	shi.check = 0;

	for(int i = 0; i < 2; i++){
		rocket[i]. x = -1;
		rocket[i].y = -1;
		rocket[i].health = 0;
		for(int j = 0; j < 30; j++) rocket[i].bulletcheck[j] = 0;
		// rocket[i].bulletcheck[60] = {0};
	}
	rocket[0].move = 1;
	rocket[1].move = -1;

	shild.x = 0;
	shild.y = 0;
	shild.status = 0;
	helth.x = 0;
	helth.y = 0;
	helth.status =0;
	boost.x = 0;
	boost.y = 0;
	boost.status = 0;

	for(int i = 0; i < MAX; i++){
		entry[i].score = 0;
		strcpy(entry[i].name,"");
	}

}

void collisionCheck1(){
	// if  bullet hit any boulder
	// asteriod
	
for(int i = 0; i < 60; i++){
		if(bulletcheck[i] != 0 && bulletcheck[i] != -1){
			
			for(int k = 0; k < 3; k++){
				if(bouldercheck[k] == 1){
					if((bulletcheck[i] >= boulderCoordinate[k].x && bulletcheck[i] <= boulderCoordinate[k].x + 60) &&( (i * 10 >= boulderCoordinate[k].y && i * 10 <= boulderCoordinate[k].y + 60) )){
						boulderCoordinate[k].health -= gunpower;
						bulletcheck[i] = -1;
						
					}
				}
			}
		}
	}


		for(int j = 0; j < 3;j++){
			if(bouldercheck[j] == 1){
				if(( boulderCoordinate[j].x + 60 >= hero.x && boulderCoordinate[j].x <= hero.x + 105) &&( boulderCoordinate[j].y <= hero.y + 80 )){
					hero.health -= damage;
					iShowBMP2(boulderCoordinate[j].x, boulderCoordinate[j].y, "bmp_outputs//collision.bmp",0);
					boulderCoordinate[j].health = 0;
				}
			}
			
		}
		if(damagecount != 0){ damagecount--;}
		else{
			damage = 10;
		}
		if(shild.status == 1){
			if(( shild.x + 30 >= hero.x && shild.x <= hero.x + 105) &&( shild.y <= hero.y + 30  && shild.y >= hero.y)){
				damage = 0;
				damagecount = 1000;
				shild.status = 0;
			}
		}
		if(helth.status == 1){
			if(( helth.x + 30 >= hero.x && helth.x <= hero.x + 105) &&( helth.y <= hero.y + 30  && helth.y >= hero.y)){
				hero.health = hero.health + 100;
				helth.status = 0;
			}
		}
		if(boost.status == 1){
			if(( boost.x + 30 >= hero.x && boost.x <= hero.x + 105) &&( boost.y <= hero.y + 30  && boost.y >= hero.y)){
				gunpower = gunpower + 5;
				boost.status = 0;
			}
		}


}
void collisionshipresult(){
		for(int j = 0; j< 3; j++){
		if(boulderCoordinate[j].health <= 0){
			score += 10;
			iShowBMP2(boulderCoordinate[j].x, boulderCoordinate[j].y, "bmp_outputs//collision.bmp",0);

			bouldercheck[j] = 1;
			boulderCoordinate[j].x = 0 + rand() % 600;
			boulderCoordinate[j].y = 575;
			boulderCoordinate[j].health = 10;
		}
	}
	for(int i = 0; i< 2; i++){
		if(rocket[i].health <= 0){
			score += 40;
			iShowBMP2(rocket[i].x, rocket[i].y, "bmp_outputs//collision_effect.bmp",0);
			rocket[i].health = 100;
			if(i == 0){
				rocket[i].x = 225;
				rocket[i].y = 490;

			}
			else if( i == 1){
				rocket[i].x = 725;
				rocket[i].y = 490;

			}

		}
	}



if(hero.health <= 0){
		gamestate = 8;
	}
}
void collisionresult(){
		for(int j = 0; j< 3; j++){
		if(boulderCoordinate[j].health <= 0){
			score += 10; // 10 points for boulders
			iShowBMP2(boulderCoordinate[j].x, boulderCoordinate[j].y, "bmp_outputs//collision.bmp",0);
			bouldercheck[j] = 1;
			boulderCoordinate[j].x = 0 + rand() % 600;
			boulderCoordinate[j].y = 575;
			boulderCoordinate[j].health = 10;
		}
	}
	for(int j = 0; j<4; j++){
		if(now[j].health <= 0){
			score += 20; // 20 points for big boulders
			iShowBMP2(now[j].x,now[j].y, "bmp_outputs//collision.bmp",0);
			now[j].y = 598;
			now[j].health = 20;
			
		}
	}
	if(hero.health <= 0){
		gamestate = 8;
	}
}
void collisionCheck2(){
	for(int i = 0; i < 60; i++){
		if(bulletcheck[i] != 0 && bulletcheck[i] != -1){
			// boulder
			for(int j = 0; j < 4; j++){
				if((bulletcheck[i] >= now[j].x && bulletcheck[i] <= now[j].x + 60) &&( (i * 10 >= now[j].y && i * 10 <= now[j].y + 60) )){
					now[j].health = now[j].health - gunpower;
					bulletcheck[i] = -1;
				}
			}
		}
		
		}
		for(int j = 0; j < 4; j++){
				if(( now[j].x + 60 >= hero.x && now[j].x <= hero.x + 105) &&(  now[j].y <= hero.y + 80 )){
					hero.health -= damage;
					iShowBMP2(now[j].x,now[j].y, "bmp_outputs//collision.bmp",0);
					now[j].health = 0;
				}
			}

}







int main() {
	
	
	
	srand(time(NULL));
	first();
	iSetTimer(500, asteriodgenerate);
	iSetTimer(200, spaceshipgenerate);
	//place your own initialization codes here.
		
		PlaySound(TEXT("music.wav"), NULL , SND_LOOP|SND_ASYNC);
	
	
	iInitialize(1000, 600, "SPACE COWBOY");
	return 0;
}

