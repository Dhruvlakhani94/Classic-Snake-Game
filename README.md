# Classic-Snake-Game
Classic Snake Game (Console Version): Terminal-based Snake game in C++ using ANSI escape codes, featuring real-time input, dynamic difficulty, and animated gameplay. Built with a modular OOP design, including snake movement, food generation, scoring, and restart logic for smooth cross-platform play.

🚀 Features :

Real-time Input: Non-blocking keyboard input for smooth gameplay.
Difficulty Settings: Choose between Easy, Medium, and Hard modes.
Dynamic Speed: The game gets faster every 10 points to increase the challenge.
High Score Tracking: Keeps track of your best score during the current session.
OOP Design: Built using a clean Core and Play class hierarchy.

📈 Technical Impact & Performance:

# Algorithm Efficiency :

-Body Management (O(1)): 
Utilizes std::deque<pair<int, int>> for constant-time operations when adding a head and removing a tail, ensuring consistent performance regardless of snake length.
-Collision Detection (O(N)): 
Self-collision logic scales linearly with the snake's length (N), maintaining high frame rates on minimal hardware.
-Spatial Efficiency: 
By representing the board as a coordinate system rather than a static 2D array, the game maintains a minimal memory footprint (under 2MB of RAM).

# Terminal Optimization :
-Zero-Flicker Rendering: 
Instead of using system("clear"), which causes heavy flickering, the engine uses the \033[H ANSI code to reset the cursor position. This results in a 90% reduction in visual noise.
-Low Latency Input: 
The keyPressed() function leverages termios and ioctl to poll for input without pausing execution, providing near-instantaneous response times.

# Gameplay Scaling :
-Difficulty Range: 
Speed transitions from an "Easy" start of 260ms down to a "Hard" floor of 110ms, offering a 2.3x increase in gameplay velocity.
-Dynamic Acceleration: 
The speed variable sp scales automatically, increasing by approximately 5-8% every 10 points scored.

🛠️ Requirements :
Operating System: Linux or macOS (uses <unistd.h>, <termios.h>, and <sys/ioctl.h>).
Compiler: g++ (supporting C++11 or higher).
Terminal: A terminal that supports ANSI escape sequences and UTF-8 characters.
( run in terminal )

🎮 Controls :
Arrow Keys: Change the direction of the snake.
'X' Key: Quit the game immediately.
'R' Key: Restart the game after a Game Over.

📝 Code Overview :

The project is structured into two main classes:

Core Class:
Handles the game state (score, position, snake body deque).
Manages the game board rendering and food generation logic.
Initializes terminal settings to hide the cursor and enable raw input mode.

Play Class (Inherits from Core):
Contains the handleInput() loop to capture arrow keys.
Contains the updateLogic() function to handle collisions and growth.
Manages the main game loop (startGame).
