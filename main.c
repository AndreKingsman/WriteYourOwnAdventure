#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* GLOBAL VARIABLES */
int current_link = 0;
int next_link = 0;
int max_len_user_input = 10;
int max_num_scenarios = 100;
int max_len_scenario_text = 10000;
int max_len_option_text = 1000;

/* title of adventure */
char title[1000];
/* array of descriptions for each scenario */
char scenarios[100][10000];
/* array of descriptions for all branching choices */
char choices[100][10][1000];
/* array of indices linking each choice to its scenario */
int links[100][10];

/* FUNCTIONS */
void main_menu();
void print_summary();
void create_mode();
void write_scenario();
void play_tutorial();
void play_adventure();
void exit(int return_code);

/* MAIN */
int main(void) {
  printf("-----------------------------------\n");
  printf("Welcome to Write Your Own Adventure\n");
  printf("-----------------------------------\n\n");
  
  printf("Write Your Own Adventure allows you to create and play your very own choose your own adventure stories. Visit the tutorial first or dive straight into Create Mode. Happy adventuring!\n\n");

  /* present the main menu to the user */
  main_menu();
  return 0;
}

/* MENU FUNCTIONS */
void main_menu() {
  printf("---------\n");
  printf("MAIN MENU\n");
  printf("---------\n\n");

  printf("[1] Tutorial\n[2] Create\n[3] Play\n\n");  
  printf("Input \"1\" to start the tutorial, \"2\" to enter Create Mode, or \"3\" to play your adventure. Input \"0\" to exit the program. Hit ENTER to execute your input.\n");

  char user_input[max_len_user_input];

  while (1) {
    /* capture the user's input */
    fgets(user_input, max_len_user_input, stdin);
    user_input[strlen(user_input) - 1] = 0;
    /* if input equals one, route the user to the tutorial */
    if (user_input[0] == '1') play_tutorial();
    /* route the user to Create Mode if their input equals two*/
    else if (user_input[0] == '2') create_mode();
    else if (user_input[0] == '3') {
      if (*scenarios[0]) play_adventure();
      /* if the user's input equals three but no adventure exists yet, inform the user */
      else printf("No adventure exists yet.\n");
    }
    /* exit the program if the user's input equals zero */
    else if (user_input[0] == '0') {
      printf("Goodbye!");
      exit(0);
    }
    /* if the input matches non of the above options, inform the user that the input is invalid */
    else printf("Invalid input. Please enter either \"1\" to navigate to the tutorial, \"2\" to enter Create Mode, or \"3\" to play your adventure. Enter \"0\" to exit the program.\n");
  }
}

/* print summary of scenarios */
void print_summary() {
  int len_text = 50;

  /* print all non-empty scenarios */
  for (int i = 0; *scenarios[i]; ++i) {
    printf("[%d] ", i + 1);
    /* print the first n characters of each scenario */
    for (int c = 0; scenarios[i][c] != '\0' && c < len_text; ++c) {
      printf("%c", scenarios[i][c]);
    }
    printf("...\n");
    /* print the link associated with each option */
    for (int j = 0; *choices[i][j]; ++j) {
      printf("\tOption %d leads to scenario %d\n", j + 1, links[i][j] + 2);
    }
  }
  printf("\n");
}

/* CREATE FUNCTIONS */
/* allow user to create individual scenario */
void create_mode() {
  printf("-----------\n");
  printf("CREATE MODE\n");
  printf("-----------\n\n");
  /* if a title does not yet exist, prompt the user to input the title */
  if (!*title) {
    char title_text[1000];
    printf("Start by giving your adventure a name.\n");
    fgets(title_text, 1000, stdin);
    title_text[strlen(title_text) - 1] = 0;
    /* copy the input to the title variable */
    strcpy(title, title_text);
    /* after the user titles their adventure, they continue by writing the first scenario */
    write_scenario();
  }

  char user_input[max_len_user_input];
  while (1) {
    printf("Select which scenario you would like to edit next. You can get an overview of what you have writen so far by entering \"s\" to bring up the summary. Input \"0\" to return to the main menu.\n");
    fgets(user_input, max_len_user_input, stdin);
    user_input[strlen(user_input) - 1] = 0;
    /* the user continues writing scenarios until they wish to return to the main menu */
    if (user_input[0] == '0') main_menu();
    else if (user_input[0] == 's') print_summary();
    else {
      /* change current_link to user_input. Subtract one to return the correct index */
      current_link = user_input[0] - '0' - 1;
      write_scenario();
    }
  }
}

void write_scenario() {
  char scenario_text[max_len_scenario_text];
  
  printf("Input a description for scenario %d and hit ENTER.\n", current_link + 1);
  fgets(scenario_text, max_len_scenario_text, stdin);
  scenario_text[strlen(scenario_text) - 1] = 0;
  strcpy(scenarios[current_link], scenario_text);

  char option_text[max_len_option_text];
  int num_options = 0;

  printf("Input each option seperately, hitting ENTER after each. Input \"0\" and hit ENTER after you have added all options.\n");
  /* input each option seperately until the user decides to continue by entering zero instead */
  for (int i = 0; 1; ++i) {
    fgets(option_text, max_len_option_text, stdin);
    option_text[strlen(option_text) - 1] = 0;
    
    if (option_text[0] == '0') break;
    strcpy(choices[current_link][i], option_text);
    ++num_options;
  }

  /* automatically generate links based on the number of options the user had writen */
  int temp;
  for (int i = 0; i <= num_options; ++i) {
    links[current_link][i] = next_link + i;
    /* store the temporary result to update next_link after the for loop */
    temp = next_link + i;
  }
  next_link = temp;
}

/* PLAY FUNCTIONS */
void play_tutorial() {
  printf("TUTORIAL IS UNDER CONSTRUCTION\n");
  /* return the user to the main menu */
  main_menu();
}

void play_adventure() {
  int link = 0;
  char user_input[max_len_user_input];

  /* print title of adventure */
  printf("%s\n\n", title);
  while (*scenarios[link]) {
    /* print scenario corresponding to link */
    printf("%s\n\n", scenarios[link]);
    /* if there are no options, end the adventure */
    if (!*choices[link][0]) {
      printf("The end.\n\n");
      main_menu();
    }
    /* print all options associated with scenario */
    for (int i = 0; *choices[link][i]; ++i) {
      printf("[%d] %s\n", i + 1, choices[link][i]);
    }
    printf("\n");

    /* allow the user to select an option */
    fgets(user_input, max_len_user_input, stdin);
    user_input[strlen(user_input) - 1] = 0;
    if (user_input[0] == '0') main_menu();
    /* change link to link to the scenario associated with the chosen option */
    link = links[link][user_input[0] - '0'];
  }
}