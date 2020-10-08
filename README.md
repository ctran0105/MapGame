# Map-Game
Map-Game is a game written in C++ that enables users to control a character to reach its final destination by overcoming obstacles.
* map1.text: store the map as a two-dimensional char array with 20 rows and 40 columns.
* mapGame.cpp: 
  * setCursor(): initialize the player's starting position.
  * hideCursor(): erase the obstacles once the player breaks them.
  * getMove(): move the character's positions around the map according to user's keyboard control.
  * readMap(), printMap(): read the two-dimensional map from map1.text and print it out.
  * isWall(): prevent character from passing across the walls.
  

