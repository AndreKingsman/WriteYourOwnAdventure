# WriteYourOwnAdventure
Create and play your very own choose your own adventure stories

1. Overview
2. User guide
3. Structure of the program
4. Ideas for further development

## Overview

As the name suggests, Write Your Own Adventure is a console application written in C that allows you to write and play your own choose your own adventure stories. As of now, the program features a short tutorial (not yet implemented) that demos how an adventure plays, Create Mode, and the ability for you to play through the adventure you created.

The entire program is self-contained in main.c

## User guide

When you start the application, you are presented with the main menu, from where you can navigate to the tutorial, or Create Mode. After you started writing your adventure, you can return to the main menu at any time and start playing.

When you enter Create Mode for the first time you will be prompted to enter a title for your story. Afterwards you start writing the first scenario. The adventure consists of a number of branching scenarios connected through options the player can choose between. Between writing each scenario you can view a summary of your adventure so far and determine which scenario to write next. For each scenario you can write between zero and ten choices. If you do not include any options, the adventure automatically ends if the player reaches that scenario.

When you play your adventure, you start at the first scenario. Depending on your choices, the story unfolds differently.

## Structure of the program

The ```main()``` function only prints introductory text and brings the user to the main menu with ```main_menu()```. The program is divided into several functions that implement all the features. Given that most functions operate on a shared set of variables, most variables are defined globally above the ```main()``` function.

## Ideas for further development

1. Write the tutorial

The story for the tutorial is not finished yet. The tutorial should eventually also serve the purpose of explaining Create Mode in more detail and providing more opportunities for user interaction.

2. Implement a text parser, character stats and items

Character stats (e.g., strength, vitality, dexterity, intelligence etc.) could be used to present unique options to players based on their stats. Items could also be found throughout the adventure that could be used for various purposes during the adventure. A custom text parser would be used to allow the user to write custom scripts as part of their scenario descriptions of options. These would be hidden from the player, unless they satisfy the specified conditions. This would allow for more variation in how the adventures play out.

Here is a first draft of what the parser might look like:
```C
void parse_text(char *text) {

  for (int c = 0; text[c]; ++c) {
    /* if a defined character like an open square [ or curly { bracket is reached, stop printing characters */
    if (text[c] == '[') {
      /* skip characters until the reciprocal closed bracket is reached */
      while (text[c] != ']') ++c;
      ++c;
    }
    /* otherwise print the input character by character */
    printf("%c", text[c]);
  }
}
```
The parser should also copy the text in between the brackets and evaluate it based on defined syntax. Such a parser would allow the user to, for example, hide text from the player unless their character possesses a specific item or character stat.

3. Implement combat encounters

The adventure could be made more dynamic by introducing combat encounters through, for instance, dice combat. If items are implemented, the player could use items with various effects to improve their chances of success in battle.

4. Improve exception handling

At each point that the user inputs text, there is the possibility that the user inputs an invalid option. The program should continue functioning as intended and notify the user of the fact. In most but not all situations exception handling has been implemented.

In the main menu, for example, the user is informed if their input does not correspond to any of the valid options:
```C
  while (1) {
    fgets(user_input, max_len_user_input, stdin);
    user_input[strlen(user_input) - 1] = 0;
    if (user_input[0] == '1') play_tutorial();
    else if (user_input[0] == '2') create_mode();
    else if (user_input[0] == '3') {
      if (*scenarios[0]) play_adventure();
      else printf("No adventure exists yet.\n");
    }
    else if (user_input[0] == '0') {
      printf("Goodbye!");
      exit(0);
    }
    else printf("Invalid input. Please enter either \"1\" to navigate to the tutorial, \"2\" to enter Create Mode, or \"3\" to play your adventure. Enter \"0\" to exit the program.\n");
  }
```
However, when the user is in Create Mode, exceptions are not sufficiently dealt with since the user can edit scenarios to which there exist no links yet, or input non-integer characters:
```C
  while (1) {
    printf("Select which scenario you would like to edit next. You can get an overview of what you have writen so far by entering \"s\" to bring up the summary. Input \"0\" to return to the main menu.\n");
    fgets(user_input, max_len_user_input, stdin);
    user_input[strlen(user_input) - 1] = 0;
    if (user_input[0] == '0') main_menu();
    else if (user_input[0] == 's') print_summary();
    else {
      /* change current_link to user_input. Subtract one to return the correct index */
      current_link = user_input[0] - '0' - 1;
      write_scenario();
    }
  }
```
