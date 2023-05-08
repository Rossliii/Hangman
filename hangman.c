#include <string.h>
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include "hangman-io.h"
#include "words.h"

const int max_len = 50;

// win(word) check if the word is without '*'
// requires: word is a vaild pointer
// time: O(n)
bool win(char* word) {
  assert(word);
  for (int i = 0; word[i] != 0; i++) {
    if (word[i] == '*') {
      return false;
    }
  }
  return true;
}

// is_char(word, cha) return true if cha is a number of word character, false 
//   otherwise
// requires: word is a vaild pointer
//           cha is on upper or lower case of alphbet
// time: O(n)
bool is_char(char* word, char cha) {
  int len = strlen(word);
  for (int i = 0; i < len; i++) {
    if (word[i] == cha) {
        return true;
    } else {
        continue;
    }
  }
  return false;
}

// game_num() read a character judge if the input is valid number corresponding 
//   to word
// effect: reads input
//         produces output
int game_num(void) {
  int n = 0;
  while (scanf("%d", &n) > 0) {
    printf(enter_game_number, max_words);
    if (1 <= n && n <= max_words) {
        break;
    } else {
        printf("%s", invalid_game_number);
    }
  }
    return n;
}

// enter(strikes, word) read character to continue the game
// requires: word is a vaild pointer
//           strikes is alwayes max_strikes
// effects: reads input
//          produces output
// runtime: O(n)
void enter (int strikes, char* word) {
  assert(word);
  assert(strikes == max_strikes);
  bool dup = false;
  int len = strlen(word);
  char check[50] = {0};
  char str[50] = {0};
  char adv[50] = {0};
  strcpy(str, word);
  int hung = 0;
  for (int i = 0; i < len; i++) {
    if (word[i] == ' ') {
      str[i] = ' ';
    }
    str[i] = '*';
  }
  strcpy(check, str);
  strcpy(adv, str);
  char cha = 0;
  while (1) {
    dup = false;
    printf("%s", letter_prompt);
    printf("%s\n", str);
    if (scanf(" %c", &cha) > 0) {
        if (!((cha >= 'a' && cha <= 'z') || (cha >= 'A' && cha <= 'Z'))) {
            printf(not_a_letter, cha);
            print_hangman(6 - strikes);
            continue;
        }
        if (cha >= 'a' && cha <= 'z') {
            cha -= ('a' - 'A');
        }
        for (int i = 0; i < len; i++) {
          if (check[i] == cha) {
            check[i] = cha;
            printf(already_guessed_letter, cha);
            print_hangman(max_strikes - strikes);
            dup = true;
            break;
          }
        }

        if (dup) {
          continue;
        }

        int judge = is_char(word, cha);
        if (judge == false) {
          printf(not_in_word, cha);
          if (hung == max_strikes - 1) {
            print_hangman(max_strikes);
            break;
          }
          strikes -= 1;
          printf(not_last_guess, strikes);
          hung += 1;
        } else {
          for (int i = 0; i < len; i++) {
            if (word [i] == cha) {
              adv[i] = cha;
            }
          }
          if (win(adv)) {
            break;
          } else {
            for (int i = 0; i < len; i++) {
              if (word [i] == cha) {
                str[i] = cha;
              }
            }
          }
        }
        print_hangman(6 - strikes);
    }
    for (int i = 0; i < max_strikes; i++) {
      if (check[i] == '*') {
         check[i] = cha;
         }
    }
  }
  if (hung == max_strikes - 1) {
    printf(game_over, word);
  } else {
    printf(congratulations, word);
  }
}

// game() start the hangman game as instruction
// requires: produces output 
//           reads input
// runtime: O(n)
void game (void) {
  char cha = 0;
  bool judge = true;
  do {
    int strikes = max_strikes;
    char word[50] ={'\0'};
    const char* temp = get_word(game_num());
    strcpy(word, temp); 
    int len = strlen(word);
    for (int i = 0; i < len; i++) {
      if (word[i] > 97) {
          word[i] -= 32;
      }
    }
    print_hangman(max_strikes - strikes);
    enter(max_strikes, word);  
    while(1) {
      printf("%s",play_again);
      if (scanf(" %c", &cha)) {
        if (cha == 'Y' || cha == 'y') {
          judge = true;
          break;
        } else if (cha == 'N' || cha == 'n') {
          judge = false;
          break;
        } else {
          printf("%s", invalid_play_again_response);
          continue;
        }
      }
    }
  } while (judge);
}

int main(void) {
  game();
}
