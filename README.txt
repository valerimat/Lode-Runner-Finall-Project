================================== Final Project - OOP ===================================
                                                                           
██╗░░░░░░█████╗░██████╗░  ██████╗░██╗░░░██╗███╗░░██╗███╗░░██╗███████╗██████╗░
██║░░░░░██╔══██╗██╔══██╗  ██╔══██╗██║░░░██║████╗░██║████╗░██║██╔════╝██╔══██╗
██║░░░░░██║░░██║██║░░██║  ██████╔╝██║░░░██║██╔██╗██║██╔██╗██║█████╗░░██████╔╝
██║░░░░░██║░░██║██║░░██║  ██╔══██╗██║░░░██║██║╚████║██║╚████║██╔══╝░░██╔══██╗
███████╗╚█████╔╝██████╔╝  ██║░░██║╚██████╔╝██║░╚███║██║░╚███║███████╗██║░░██║
╚══════╝░╚════╝░╚═════╝░  ╚═╝░░╚═╝░╚═════╝░╚═╝░░╚══╝╚═╝░░╚══╝╚══════╝╚═╝░░╚═╝
                                                            

name: Valeri Materman 
name: David Yudin 
===============================================================================
Run from police, dig holes, eat shawrmans and drink light alcoholic beverages!!!!!!
===============================================================================
In this exercise we were asked to implement the classic game named Lode Runner
using the SFML library and OOP methods in c++ language.
We will represent you our game that sums up all the techniques, that we learned 
during the semester. 
The game was built from scratch. all the themes and skins were done in Photoshop,
Audio was made in Audacity open source, and the rest by us in visual studio IDE.
At the begining you will encounter the menu which will lead to the game as you press 
enter in order to play.
The game will include the player, few enemies, and coin drawn as laffas and presents
drawn as vodkas. each object has a unique bonus for example the laffas will always give you
a bonus score, but the present are mysterious which means we dont know what might be,
there 4 options bonus score, lives, time and enemy which is a bad surprise.
in order to complete the level we must collect all the laffas and avoid the enemies by dodging
of digging up holes using the X and Y keys.
As we collected all the laffas we go to next level and the same process happens again.
till we finish and win or lose, its all up to you.
Good Luck may be the odds ever in your favor. 
===============================================================================
Controlls:
arrow keys - for vertical and horizontal movement.
ESC        - pressign while in game will open the in game menu
the menu is also controlled using arrow keys and ENTER to select.
Z,X - diggind left and digging right.
===============================================================================
More tehnical stuff:
To load new level add it to the board.txt as all levels above it.
you can walk on enemies that fell into a hole.
you can adjust volume through the MacrosSettings.h
===============================================================================
Design:
Main fuctnion GameController
=>
holds state (polimorphic)
=>
each state handles actions.

Menu sates handles actions of choosing buttons.

Game state -> holds map raw data, curr map and its objects and 2 movement
controllers.

each loop taking the delta time into considertaion tells the 2 controllers to move
theyr dynamic objects.
the enemies move based on alogrithm they have (polimorphicaly).
that is set up on creation based on a radnom number.

the player moves beased on the key pressed.

===============================================================================
classes and their uses:

# the classes listed below are mentioned as .cpp and .h together

--------file: AbstractClasses
              |
	      |_ Clock:              singleton of time
	      |_ MacroSettings:      singleton of the settings
	      |_ Music:              singleton of the music
	      |_ MovementController: Controlls the movement of the player and enemies
-
--------file: Enemy
	      |
	      |_ Enemy:           is a dynamic object which represents the enemy
	      |_ EnemyController: moves the enemies across the map using the algo listed below
	      |_ Graph:           data structure of all the possible moves across the map
	      |_ Node:			  holdes nodes in the graph.
	      |_ Algo:            is a virtual class for the algorithms listed below
	      |_ Bfs:             bfs algorithm which finds the shortest route to the player
	      |_ RandomPath:      does random moves, makes it unpredictable
	      |_ OneSide:         goes left and right and thats it

--------file: Player
	      |
	      |_ Player: is a dynamic object which represents the player 
	      |_ PlayerController: moves the player across the map using the keys from the keyboard
	      |_ Lives: hold the data about the player amount of lives

--------file: States
	      |
	      |_ file: EndGamae
	      |	       |
	      |	       |_ Win: win screen.
	      |        |_ Death: death screen.
 	      |
              |_ file: Game
	      |	       |
	      |	       |_ file: GameObject
              |        |        |
              |        |        |_ Object:          ancestor of the classes listed below 
              |        |        |_ StaticObject:    represents all the static object
              |        |        |_ DynamicObject:   represents all the dynamic object
              |        |        |_ RigidBodyObject: is a ground or wall
              |        |        |_ Ladder:          is a static object that the dynamic object can climb on 
              |        |        |_ Pole:            is a static object that the dynamic object can use to move left and right
              |        |        |_ Coin:            is a static object that player can gain score with when collide
              |        |        |_ Present:         is a static object that player can gain bonus with when collide
              |        |        |_ Bonus:           is a virtual class for the bonuses listed below
              |        |        |_ TimeBonus:       when the player collides with a present we get time bonus
              |        |        |_ ScoreBonus:      when the player collides with a present we get score bonus
              |        |        |_ LivesBonus:      when the player collides with a present we get extra lives
              |        |        |_ EnemyBonus:      when the player collides with a present we get extra enemy
              |        |         
	      |	       |_ Game:    the main class holds the entire game.
	      |	       |_ HUD:     Holds all the data in a GUI way above the game 
	      |	       |_ Map:     Is basically what we see when we play
	      |	       |_ MapData: Holds the raw data of the map 
	      |	       |_ Score:   singleton of score
	      |
	      |_ file: Menues
	      |	       |
	      |	       |_ file: Components
              |        |        |
              |        |        |_ Button:   to setup button.
              |        |        |_ Selection: to setup the selection arrows.
              |        |        
	          |	       |_ file: MainMenu
              |        |        |
              |        |        |_ MainMenu: holds main menue screen
              |        |        |_ InGameMenu: holds in game menue screen
              |        |        
              |        | 
              |        |_ Menu: the base class for all menues and screens that are not game
	      |
	      |_ GameController: runs the games and gets input from the user
	      |_ main:           our .cpp file which lunches everything 



===============================================================================
The Main data structure:
We used the modern data structures, which are strings and smart vectors,
and combined them with SFML variables in order to use complex yet 
understanable form of GUI.
Another data structure we used is singletons
In addition in order to make a smart enemy, we did a matrix out of nodes 
and neighboring list.
with these nodes we could use a BFS algorith so the enemy could find the player
in the shortest way possible every few movements
===============================================================================
Algoithms:
Enemy algorithms:
* BFS . 
* Algorithm to find the most right node or left .
* Algorithm to find a random path.

Bugs: -None-

enjoy the game :)

