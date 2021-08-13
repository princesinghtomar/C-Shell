Assignment#2
--- Shell Part # 2

Creat Executable : make shell
Execute          : ./shell

Exiting :- 1) "quit"
           2) "exit"
           3) CNTR + D


Requirements :-


.h files :-
    1)header.h  *contains all modules*
    2)input.h   *contains names of function and global variables*


Files :-
    1)Main.c

1)Shell Prompt <user@sys_name :*absolute address*>, shell open invoked with */home/user* as initial address.
2)"~" or (/home/user) are treated as same any address with as substring */home/user* is replaced with *~*,
3)color are not used for the prompt.
4)signal functions are also present in this file.

**Specification 1:  Input/Output Redirection** :-

Files :-
    1)redirect_handle.c      *contains implementation of ">","<",">>" commands*

Details :-
        ●Error message is displayed if the input file does not exist.
        ●The output file is created (with permissions ​0644​) if it does not already exist.
        ●In case the output file already exists, it is overwritten in case of ">"​ and appended to in case of "​>>"​.
        ●exit code true if command runs smoothly else false.

**Specification 2: Command Pipelines**

Files :-
    1)pipe_handle.c         *contains implementation of pipeline commands*

Details :-
        ●One or more commands can be piped.
        ●supports any number of pipes.
        ●Errors are handled.
        ●Exit codes as per last command executed.

**Specification 3: I/O Redirection within Command Pipelines**

Files :-
    1)pipe_handle.c         *contains implementation of pipeline commands*
    2)redirect_handle.c     *contains implementation of ">","<",">>" commands*

Details :-
        ●One or more commands can be piped.
        ●supports any number of pipes.
        ●Errors are handled as per both pipes and redirection.
        ●Exit codes as per last command executed.

**Specification 4: User-defined Commands**

Files :-
    1)jobs_handle.c                 *contains implementation of "jobs","kjobs","overkill","fg","bg" commands*
    2)environ_handle.c              *contains implementation of "setenv","unsetenv" commands*
    3)main.c                        *contains implementation of quit*

Details :-

    setenv :-
        ●Sets environment variable.
        ●Syntax error if syntax is not like its descrived in the pdf.
        ●Can not set "" as environment variable.
        ●exit code true if command runs successfully

    unsetenv :-
        ●unsets environment variable if present.
        ●Syntax error if syntax is not like its descrived in the pdf.
        ●Error if environment variable not present.
        ●exit code true if command runs successfully
         

    jobs :-
        ●jobs + any_thing_else will give *error*.
        ●gives all the running/stopped job using smallest unused number as their index which returns to 1 after use of overkill.  
        ●Exit codes true if no internal error occurs during command implementation.

    kjob :-
        ●any difference in said syntax and given syntax will result in error.
        ●Error if job index not present or sygnal num is not defined.
        ●exit code true if command runs successfully.
    
    fg :-
        ●any difference in said syntax and given syntax will result in error.
        ●Error if no such process with index number ever created.
        ●exit code as descrived in pdf.

    bg :-
        ●any difference in said syntax and given syntax will result in error.
        ●Error if no such process with index number ever created.
        ●exit code as descrived in pdf.

    overkill :-
        ●overkill + any_thing_else will give *error*.
        ●kill all the background command.
        ●Exit codes true if no internal error occurs during command implementation.
        ●No error if no backgraound process is present.

    quit :-
        ●Uses feof() function to know whether cntl + D is pressed or not.
        ●Treated as a sygnal not as a command.

**Specification 5: Signal Handling**

    CTRL-Z :-
        ●pushes any currently running foreground job into the background.
        ●change its state from running to stopped.

    CTRL-C :-
        ●interrupt any currently running foreground job.
        ●No effect on the terminal.

**Bonuses**

Files :-
    1)cd.c                          *contains implementation of cd- along with cd*     
    2)main.c                        *contains printing part of Bonus 2*
    3)bonus3_handle                 *contains implementation of Bonus 3*

    Bonus 1 :-
        ●implementation in cd-.
        ●By storing previous directory and chdir function.

    Bonus 2 :-
        ●   :') if exit code 1.
        ●   :'( if exit code 0.

    Bonus 3 :-
        ● refer bonus3_handle.c file
