
// https://www.easycalculation.com/code-c-program-acceleration-gravity.html
// https://cboard.cprogramming.com/game-programming/132551-gravity-game.html

/*
	Enviorment object :
	
	Functionality :
	º Enviorment Object (used in: )
	º Gravity
	º Wind
	º Light
	º Files ()
	
	Inherit :
	- position
	- movement
	- textue
*/

char enviorment_wind;
char gravity_earth;
char gravity_light;


gravity (){
	float g=2, r=21, re=2, s;
    s = (pow(re,2)/pow(r,2))*g ;
    printf("Acceleration due to gravity = %f",s);
    return 0;
}
 