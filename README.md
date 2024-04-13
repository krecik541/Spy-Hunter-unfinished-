This code comprises a simple game implemented in C++ using the SDL library. It includes functionalities for rendering game elements, handling player movement, generating and updating the game map, managing user interface elements such as score display and life indicators, and saving game results. The game involves controlling a player character to navigate through dynamically generated obstacles while collecting points.

# Files:
  a) game.h: Header file containing declarations for functions related to initializing, handling events, rendering, and cleaning up the game.  
  b) draw.h: Header file containing declarations for functions related to drawing on the screen, including text, shapes, and game elements.  
  c) player.h: Header file containing declarations for functions related to updating and rendering the player character.  
  d) map.h: Header file containing declarations for functions related to generating, updating, and rendering the game map.  
  e) ui.h: Header file containing declarations for functions related to updating and rendering the user interface elements.  

# Functions:
  a) main(): The entry point of the game. It initializes SDL, sets up the game environment, and enters the main game loop.  
  b) init(): Initializes the game, including creating the window, renderer, loading assets, and setting initial game state.  
  c) handleEvents(): Handles SDL events such as key presses and window closure.  
  d) render(): Renders the game elements onto the screen.  
  e) clean(): Cleans up resources and exits the game.  
  f) update(): Updates the game state based on user input and game logic.  
  g) Various drawing functions: Functions responsible for drawing various elements such as text, shapes, the player character, and the game map.  

# How to Play:
Use the arrow keys to control the player character's movement.  
Press 'UP' or 'DOWN' to adjust speed.  
Press 'N' to start a new game.  
Press 'P' to pause the game.  
Press 'F' to end the game and save your score.  
Press 'ESC' to exit the game.  
 
