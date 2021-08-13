CFLAGS = -Wall

default : shell

shell: main.c bonus3_handle.c cd.c check_process.c cmd_handle.c color.c echo.c environ_handle.c history.c jobs_handle.c ls.c nightswatch.c pinfo.c pipe_handle.c process_handle.c pwd.c redirect_handle.c input.h header.h
	gcc $(CFLAGS) main.c bonus3_handle.c cd.c check_process.c cmd_handle.c color.c echo.c environ_handle.c history.c jobs_handle.c ls.c nightswatch.c pinfo.c pipe_handle.c process_handle.c pwd.c redirect_handle.c -o shell 

clean:
	rm shell