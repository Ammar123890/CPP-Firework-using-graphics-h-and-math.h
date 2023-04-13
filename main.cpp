#include<iostream>
#include<ctime>
#include<cmath>
#include<graphics.h>

using namespace std;

#define windowWidth 1400
#define windowHight 700
#define rockets 3
#define particles 110
#define y_blast 0.7*windowHight

void prepare_rockets(int [],int[],int [],int [],int [],float []);
void prepare_particles(float[]);
void draw_rocket(int,int,int,int,int);
void draw_particle(int,int,float,int,int,int,int);

float velocity[rockets][particles],angle[rockets][particles];
int main()
{
	cout << "Enter how many triplets you want to launch = ";
	int launch;
	int counting=0;
	cin >> launch;
	int slope[rockets],ranWidth[rockets],rocket_color[rockets],x_blast[rockets];
	int y[rockets];
	float t[rockets];

	initwindow(windowWidth,windowHight);   // to initialize graphic screen.
	srand(time(0));
	bool is_delay=false; // to check if its rocket or particle
	int count=0;
	
	PlaySound("sound.wav",NULL,SND_FILENAME|SND_LOOP|SND_ASYNC);
	while( launch > counting )
	{
	counting++;	
	prepare_rockets(slope,ranWidth,rocket_color,x_blast,y,t); // To define the paramerters of rocket
	prepare_particles(t); 
	bool con=1; // to check whole firework is complete
	delay(200);
	while(con)
	{
	for(int rock=0;rock<rockets;rock++)
		{
			if(y[rock]<y_blast)
			{
				is_delay=true;
				int x=y[rock]/slope[rock]; //formula y=mx
				draw_rocket(x,y[rock],ranWidth[rock],rocket_color[rock],8);
				y[rock]=y[rock]+4; // speed of launcing of rocket
			}
			else //After explosion of rocket
			{
				is_delay=false;
				for(int part=0;part<particles;part++)
				{
					if(t[rock]<4.5) //4.5 is time of particles
					{
					draw_particle(velocity[rock][part],angle[rock][part],t[rock],x_blast[rock],ranWidth[rock],rocket_color[rock],4);	
					t[rock]=t[rock]+.0005;
					}
				}
				if(t[rock]>0.4) // Length of particle 
					for(int part=0;part<particles;part++)
					{
						{
						draw_particle(velocity[rock][part],angle[rock][part],t[rock]-0.4,x_blast[rock],ranWidth[rock],0,20);
						}
					}
			}
			
		if(y[rock]>20) //For launching rocket length and radius
		{
			int x=y[rock]/slope[rock];
			draw_rocket(x,y[rock]-20,ranWidth[rock],0,8);
		}
		}
		for(int rock=0;rock<rockets;rock++)
		{
			if((y[rock]<y_blast))
				con=true;
			else
			{
			for(int part=0;part<particles;part++)
				if(t[rock]<4.5) // For the time of particles 
				{
					con=true;
				}
				else
				{
					con=false;
				}
			}
		}
		
		if(is_delay)
			delay(2); //speed of rocket going up
	//	else
	//		delay(5);
 		if(count%10==0) // To clear the screen while rocket is going up
			cleardevice();
			count++;
	}
	
	//	getch();
		cleardevice();
	}
	return 0;
}

void prepare_rockets(int slope[],int ranWidth[],int rocket_color[],int x_blast[],int y[],float t[])
{
	for(int i=0;i<rockets;i++)
	{
		t[i]=0.0; 
		y[i]=0;
		rocket_color[i]=rand()%12+1;
		slope[i]=rand()%20-80;
		ranWidth[i]=rand()% int(windowWidth*.4)-(windowWidth*.4)/2; // To define the x-axis of screen to explode
		x_blast[i]=y_blast/slope[i]; //Formula y=mx ---> X=y/m 
	}
}
void prepare_particles(float t[]) // void it later
{
	for(int rock=0;rock<rockets;rock++)
	{
		for(int part=0;part<particles;part++)
		{
			velocity[rock][part]=rand()%30+20; // verlocity of projectile of particles
			angle[rock][part]=rand()%361; // angle of projection of particle and rocket
		}
	}
}
void draw_rocket(int x,int y,int ranWidth,int rocket_color,int radius)
{
	x=windowWidth/2+x+ranWidth;
	y=windowHight-y;
	setcolor(rocket_color);    //color of the boundry of circle
	setfillstyle(1,rocket_color); // to select the filling color
	circle(x,y,radius);
	floodfill(x,y,rocket_color);   //to fill the circle with color
}
void draw_particle(int v,int angle,float t,int x_blast,int ranWidth,int rocket_color,int radius)
{
	int x=cos(0.0175*angle)*v*t; // formula of projectile x=v*cos(angle)*t and angle is in radians
	int y=-5*t*t+t*v*sin(0.0175*angle); // formula y=v*sin(angle)
	y=windowHight-(y+y_blast);
	x=windowWidth/2+x+ranWidth+x_blast;
	setcolor(rocket_color);   
	setfillstyle(1,rocket_color);
	circle(x,y,radius);
	floodfill(x,y,rocket_color);
}
