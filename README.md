# WriteYourOwnAdventure
Create and play your very own choose your own adventure stories

1. Overview
2. User guide
3. Structure of the program
4. Ideas for further development

## Overview

As the name suggests, Write Your Own Adventure is a console application written in C that allows you to write and play your own choose your own adventure stories. As of now, the program features a short tutorial that demos how an adventure plays, Create Mode, and the ability for you to play through the adventure you created.

The entire program is self-contained in main.c

## User guide

When you start the application, you are presented with the main menu, from where you can navigate to the tutorial, or Create Mode. After you started writing your adventure, you can return to the main menu at any time and start playing.

When you enter Create Mode for the first time you will be prompted to enter a title for your story. Afterwards you start writing the first scenario. The adventure consists of a number of branching scenarios connected through options the player can choose between. Between writing each scenario you can view a summary of your adventure so far and determine which scenario to write next. For each scenario you can write between zero and ten choices. If you do not include any options, the adventure automatically ends if the player reaches that scenario.

When you play your adventure, you start at the first scenario. Depending on your choices, the story unfolds differently.

## Structure of the program

The ```main()``` function only prints introductory text and brings the user to the main menu with ```main_menu()```. The program is divided into several functions that implement all the features. Given that most functions operate on a shared set of variables, most variables are defined globally above the ```main()``` function.

## Ideas for further development

1. Expand the tutorial

The story for the tutorial is not finished yet. The tutorial should eventually also serve the purpose of explaining Create Mode in more detail and providing more opportunities for user interaction.

2. Implement a text parser, character stats and items



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

