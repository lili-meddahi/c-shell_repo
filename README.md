                                   ___        ___    __    __  
                                 /     \    /     \ |  |  |  |
                                |       |  |   |   ||  |  |  |
                                |   |   |  |   | __||  |__|  |
                                |   |---    \__ \_  |   __   |
                            ____|   |____   ___\  \ |  |  |  |
                           |____    _____| |   |   ||  |  |  |
                                |   |      |       ||  |  |  |
                                |___|       \_____/ |__|  |__|
                                

README
__________________
  This is a homemade shell script(fairfield shell) created by the authors for a project. It can 
take user input and execute command line code. In this project there is this readme, a makefile, and
the fsh.c shell script.

AUTHORS
__________________
  The authors of this project are LUKE BROWN and LILI MEDDAHI. We would like to thank our professor 
JEFF KRAMER for the inspiration for this project.

MAKEFILE
__________________
  The makefile of this program stores the commands to compile and recompile the fsh.c file as needed.

FSH.C
__________________
  The .c file of this program holds the meat and potatoes of our program, it takes user input, reads
it, and executes the commands inputted by the user. It has implemented methods for changing the
directory, listing all files in the directory, and changing the shell.

  cd
    Change directory. Takes arguments to switch to a directory, navigate back one directory, or can
    navigate to the root(no argument).
  ls
    List. Takes no arguments in this shell. Lists all non-hidden files in the current directory.
  exit
    Exit. Takes no arguments. Exits the shell. Be sure to save your files before you use this
    command!
