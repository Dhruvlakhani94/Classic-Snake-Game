# Classic-Snake-Game
Classic Snake Game (Console Version): Terminal-based Snake game in C++ using ANSI escape codes, featuring real-time input, dynamic difficulty, and animated gameplay. Built with a modular OOP design, including snake movement, food generation, scoring, and restart logic for smooth cross-platform play.

🚀 Features :

Real-time Input: Non-blocking keyboard input for smooth gameplay.
Difficulty Settings: Choose between Easy, Medium, and Hard modes.
Dynamic Speed: The game gets faster every 10 points to increase the challenge.
High Score Tracking: Keeps track of your best score during the current session.
OOP Design: Built using a clean Core and Play class hierarchy.

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

⚙️ Technical Details :
Non-blocking Input: The keyPressed() function uses ioctl and termios to check for input without pausing the game execution.
Rendering: Uses \033[H (ANSI escape codes) to move the cursor to the top-left corner, allowing for flicker-free updates compared to "clearing" the screen.
Data Structures: Uses std::deque<pair<int, int>> to represent the snake's body, allowing efficient addition to the head and removal from the tail.
