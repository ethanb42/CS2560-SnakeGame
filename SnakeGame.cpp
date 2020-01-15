// SFML_Test.cpp : snake game 

#include "pch.h"
#include <SFML/Graphics.hpp>   //using namespace sf 
#include <time.h> 
#include <iostream>


//dimensions for window size and background 
int num_vertBox = 30, num_horzBox = 20;
int size = 16; //number of pixels 
int w = size * num_horzBox;  //background number of pixels in width 
int h = size * num_vertBox;    //background number of pixels in height 


//Snake variables to dertermine length and direction 
int direction;    //direction the snake is moving 

/******************MOD3*************************/
int directionTwo; //direction the snake is moving
/******************MOD3 END*************************/

int snake_length = 4; //initial size is 4 

/******************MOD3*************************/
int snakeTwo_length = 4; //initial size is 4
/******************MOD3 END*************************/

int score = 0; //the number of food eaten

/******************MOD3*************************/
int scoreTwo = 0; //number of food eaten by snake two
/******************MOD3 END*************************/

//Actual Snake in game is an array of x,y coordinates of sprite2 
struct Snake
{
	int x, y;        //each sprite of snake needs an x,y coordinate 

};

Snake s[100];

/******************MOD3*************************/
Snake s2[100];
/******************MOD3 END*************************/


//***NEW*** this is the fruit or food that the snake will eat 
struct Fruit
{
	int x, y;    // only one sprite needed for one food item 

}food;


//move snake head based on user input and body by incrementing  
//forward by iterating through arrays previous position 
void move() {

	//1st update body so everything updates in proper order 
	//move the body only!  s[0] = head will not be changed here 
	for (int i = snake_length; i > 0; i--)
	{
		s[i].x = s[i - 1].x;
		s[i].y = s[i - 1].y;
	}

	//2nd update the head 
	//Head of snake, s[0] depends on direction user inputs  
	//if user presses up 
	if (direction == 0)
		s[0].y -= 1;

	//if user presses down 
	if (direction == 1)
		s[0].y += 1;

	//if user presses left 
	if (direction == 2)
		s[0].x -= 1;

	//if user presses right 
	if (direction == 3)
		s[0].x += 1;


	//***NEW*** If Snake eats food it should grow 
	//check if snake head = food location 

	if (((s[0].x) == food.x) && ((s[0].y) == food.y))
	{
		//increment snake 
		snake_length++;
		score++;

		//Randomly place food somewhere else 
		food.x = rand() % num_horzBox;
		food.y = rand() % num_vertBox;

		
		
	}


	//***NEW*** Boundary Checking snake as is hits screen end 
	//loop snake back on other side 
	//LEFT and RIGHT 
	if (s[0].x > num_horzBox)
		s[0].x = 0;

	if (s[0].x < 0)
		s[0].x = num_horzBox;

	//TOP and BOTTOM 
	if (s[0].y > num_vertBox)
		s[0].y = 0;

	if (s[0].y < 0)
		s[0].y = num_vertBox;



	//***NEW*** Check if you eat body of snake 
	for (int i = 1; i < snake_length; i++)
	{

		//Cut Snake body from place eaten 
		if (s[0].x == s[i].x && s[0].y == s[i].y)
			snake_length = i;
			//used to keep score and decrease delay
			score = snake_length;
			
	}
}

/******************MOD3*************************/
void moveTwo() {

	//1st update body so everything updates in proper order 
	//move the body only!  s[0] = head will not be changed here 
	for (int i = snakeTwo_length; i > 0; i--)
	{
		s2[i].x = s2[i - 1].x;
		s2[i].y = s2[i - 1].y;
	}

	//2nd update the head 
	//Head of snake, s[0] depends on direction user inputs  
	//if user presses up 
	if (directionTwo == 0)
		s2[0].y -= 1;

	//if user presses down 
	if (directionTwo == 1)
		s2[0].y += 1;

	//if user presses left 
	if (directionTwo == 2)
		s2[0].x -= 1;

	//if user presses right 
	if (directionTwo == 3)
		s2[0].x += 1;


	//***NEW*** If Snake eats food it should grow 
	//check if snake head = food location 

	if (((s2[0].x) == food.x) && ((s2[0].y) == food.y))
	{
		//increment snake 
		snakeTwo_length++;
		scoreTwo++;

		//Randomly place food somewhere else 
		food.x = rand() % num_horzBox;
		food.y = rand() % num_vertBox;

	}


	//***NEW*** Boundary Checking snake as is hits screen end 
	//loop snake back on other side 
	//LEFT and RIGHT 
	if (s2[0].x > num_horzBox)
		s2[0].x = 0;

	if (s2[0].x < 0)
		s2[0].x = num_horzBox;

	//TOP and BOTTOM 
	if (s2[0].y > num_vertBox)
		s2[0].y = 0;

	if (s2[0].y < 0)
		s2[0].y = num_vertBox;



	//***NEW*** Check if you eat body of snake 
	for (int i = 1; i < snakeTwo_length; i++)
	{

		//Cut Snake body from place eaten 
		if (s2[0].x == s2[i].x && s2[0].y == s2[i].y)
			snakeTwo_length = i;
		//used to keep score and decrease delay
		scoreTwo = snakeTwo_length;
		
	}
}
/******************MOD3 END*************************/

int main()
{

	//Setting pseudorandom time, TODO:discuss true random vs pseudorandom  
	srand(time(0));

	//Window that we can play the game in  
	sf::RenderWindow window(sf::VideoMode(w, h), "Snake Game");

	//Textures load an image into the GPU Memory 
	sf::Texture t1, t2, t3,t4;
	t1.loadFromFile("image/white.png");
	t2.loadFromFile("image/red.png");


	/******************MOD3*************************/
	//green is now used for snake two
	t4.loadFromFile("image/green.png");
	/******************MOD3 END*************************/

	/******************MOD1*************************/
	//I made my snake eat strawberries
	t3.loadFromFile("image/strawberry.png");
	/******************MOD1 END*************************/


	//Sprite has physical dimmensions that can be set in  
	//coordinate system, setPosition(x,y), and drawn on screen 
	sf::Sprite sprite1(t1);
	sf::Sprite sprite2(t2);
	sf::Sprite sprite3(t3);
	sf::Sprite sprite4(t4);



	//***NEW*** initially place food somewhere on screen 
	food.x = 10;
	food.y = 10;

	sf::Clock clock;
	float timer = 0.0f, delay = 0.1f;

	while (window.isOpen())
	{
		//Error in class I placed this before the while loop 
		//Should be placed in while loop as shown here to update 
		//timer  

		float time = clock.getElapsedTime().asSeconds();
		clock.restart();
		timer += time;

		//Allow us to check when a user does something 
		sf::Event e;

		//Check when the window is closed 
		while (window.pollEvent(e))
		{
			//If user presses x in the top right, Windows, top left, Mac,  close the window 
			if (e.type == sf::Event::Closed)
			{
				window.close();
			}
		}

		//Control for Snake by User 
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) direction = 0;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) direction = 1;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) direction = 2;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) direction = 3;



		/******************MOD3*************************/
		//Control for 2nd Snake by user
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) directionTwo = 0;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) directionTwo = 1;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) directionTwo = 2;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) directionTwo = 3;
		/******************MOD3 END*************************/


		/******************MOD2*************************/
		if (timer > delay)
		{
			timer = 0; //reset timer 
			int temp = score+scoreTwo;
			move();    //move Snake one sprite forward
			moveTwo(); //move the second snake one sprite 
			//both snakes get faster when either one of them eats a fruit

			//IF THE SCORE CHANGES, IT PRINTS BOTH SNAKES SCORES MOD(4)
			if (temp < score +scoreTwo) {
				delay = delay - 0.01f;;
				std::cout << "\nScore 1: " << score << "\nScore 2: " << scoreTwo << std::endl;
			}
			else if (temp > score +scoreTwo) {
				for (int x = temp; temp > (score + scoreTwo); temp--) {
					delay = delay + 0.01f;
				}
				std::cout << "\nScore 1: " << score << "\nScore 2: " << scoreTwo << std::endl;
			}
			
		}
		/******************MOD2 END*************************/

		/*****************

		//Draw in window

		*****************/
		window.clear();    //clear the window so new frame can be drawn in 

		//NOTE: Order matters as we will draw over items listed first.  
		//Hence the background should be the first thing you will always do 
		//1st: Draw Background first 
		for (int i = 0; i < num_horzBox; i++)
		{
			for (int j = 0; j < num_vertBox; j++)
			{
				//Set position of sprite1 one at a time 
				sprite1.setPosition(i*size, j*size);

				//Draw sprite1 but, do not show it on screen.  
				window.draw(sprite1);
			}
		}

		//2nd: Then Draw snake otherwise background will be drawn over snake if order was reversed with background 
		for (int i = 0; i < snake_length; i++)
		{
			//position sprite2 one at a time 
			sprite2.setPosition(s[i].x*size, s[i].y*size);
			

			//Draw sprite2 one at a time by drawing over background 
			window.draw(sprite2);
			
		}

		/******************MOD3*************************/
		//**NEW** 2nd part two draw in the 2nd snake
		for (int i = 0; i < snakeTwo_length; i++) {
			//position of sprite4 at a time
			sprite4.setPosition(s2[i].x*size, s2[i].y*size);
			//draw Sprite4
			window.draw(sprite4);

		}
		/******************MOD3 END*************************/

		//***NEW*** 3rd: Draw Fruit 
			sprite3.setPosition(food.x*size, food.y*size);
			window.draw(sprite3);
		
		//Show everything we have drawn on the screen
		window.display();
	}
	return 0;

}
