Introduction:
"Strategic Five" is a C++ console-based game that allows players to engage in a strategic battle on a 9x9 or 15x15 grid. 
The game supports two modes: Human vs Human and Human vs Bot, providing an immersive experience that captures
the essence of strategic thinking."



Prerequisites:
To compile and run the game, you need:
-A C++ compiler (e.g., g++)
-Windows operating system (for sound functionality)



Instructions:

-Open a terminal or command prompt.
-Navigate to the directory where the C++ file is located using the cd command. For example: cd "path/to/your/directory"
-Replace "path/to/your/directory" with the actual path where the C++ file is stored.

-Compile the C++ code using the provided command: g++ Untitled-1.cpp -o Untitled-1 -lwinmm
-Ensure that the -lwinmm flag is included to link the Windows Multimedia Library for sound functionality.

-Run the compiled executable using: .\2023361
-Please note that the command assumes the executable file is named "2023361." If you've named it differently, replace "Untitled-1" with your executable's name.

-if above instructions don't work, simply run this command on your terminal:
-cd "d:\Documents\Giki\Semester 2\Assignments\CS112\Assignment#2\2023361\" ; if ($?) { g++ 2023361.cpp -o 2023361 -lwinmm } ; if ($?) { .\2023361 }
-Dont forget to change path according to where you saved your file(inside inverted commas)

-Follow the on-screen instructions to choose the board size and game mode.
-Don't forget to add space between coordinates before pressing enter: e.g. 0 1 




Important Note:

-Limitations: This game has been designed for Windows and relies on the Windows Multimedia Library for sound. If you are using a different operating system, you may need to adjust the sound-related code.

-Compilation Errors: If you encounter any compilation errors, ensure that your C++ compiler is installed correctly, and all necessary libraries are available.

-Command Line Interface: The game is designed to be run in a command-line interface. Ensure that your terminal or command prompt supports the necessary features for a smooth gaming experience.