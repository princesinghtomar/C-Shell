// variables --

pid_t array[200];
pid_t previous_process;
pid_t front_process_id;
pid_t p_pid[200];
char com_str[200];
char prev_dir[5000];
char p_name[200][600];
int child_process;
int back_len ;
int p_status[200];

//color funcions --

void bold_green();
void bold_blue();
void bold_red();
void bold_yellow();
void yellow();
void red();
void green();
void blue();
void green();
void reset();

//functions : --

//main functions : --

struct passwd get_user_name(); 

int check_tilda(char *str1, char *str2, int len);

void sig_stp_handle(int s);

void sig_handle(int val);

//pwd function : --

int execute_pwd_func(char *command[200], int len, char command_string[200]);

//cd function : --

int execute_cd_func(char *command[200], int len, char command_string[200]);

//echo function : --

int execute_echo_func(char *command[200], int len, char command_string[200]);

// ls functions : --

void print_time(char *str);

int implement_ls(DIR *dr, int flag, char directory[200], char command_string[200]);

int execute_ls_func(char *command[200], int len, char command_string[200]);

// pinfo function : --

int execute_pinfo_func(char *command[200], int len, char command_string[200]);

//history functions : --

void restructure_history(int len, char path[500], char *buffer[200]);

int check_history(char *command);

void create_history(char *command);

int print_history(char *command[200], int len, char command_string[200]);

//nightswatch functions : --

void mode1();

void mode2();

int getkey();

int get_interrupt(int flag);

int get_newborn();

int nightswatch(char *command[200], int len, char command_string[200]);

//check process function : --

void check_process();

//back-front process functions : --

int execute_back_process(char *command[200], int len, char command_string[200]);

int execute_front_process(char *command[200], int len, char command_string[200]);

//command handle functions : --

int dirct_command(char *str[200], int len, char command_string[200]);

int dist_command_2(char *command);

int dist_command_1(char *command);

//piping functions : --

int handle_pipe(char *commands, int len);

//redirection functions : --

char **redirect(char **args);

//environ variable functions : --

int setenv_function(char *command[200], int len, char command_string[200]);

int unsetenv_function(char *command[200], int len, char command_string[200]);

//job handling functions : --

int jobs(int len);

int kjob(char **str, int len, char *command_string);

int overkill(char **str,int len,char *command_string);

int fg(char **command, int len, char *command_string);

int bg(char **command, int len, char *command_string);

// and & or functions : --

int and_n_or(char *command);

