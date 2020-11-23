#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>
#include "cards.h"
#include "deck.h"
#include "eval.h"
#include "future.h"
#include "input.h"

void actScore(deck_t ** hands, size_t n_hands, int * win_arr){
  size_t idex = 0;
  int comp = 0;
  int tie_flag = 0;

  for(size_t j=1; j<n_hands; j++){
    comp = compare_hands(hands[idex],hands[j]);
    if(comp == -1){
      idex = j;
      tie_flag = 0;
    }
    if(comp == 0){
      tie_flag = 1;
    }
  }
  if(tie_flag){
    win_arr[n_hands]++;
  }else{
    win_arr[idex]++;
  }
}

void freeFutCards(future_cards_t * fee_c){
  for(size_t i=0; i<fee_c->n_decks; i++){
    free((fee_c->decks[i]).cards);
  }
  free(fee_c->decks);
  free(fee_c);
}

void freeAll(future_cards_t * fee_c, deck_t ** hands, size_t n_hands, deck_t * rem_deck, int * win_arr){
  freeFutCards(fee_c);
  for(size_t i=0; i<n_hands; i++){
    free_deck(hands[i]);
  }
  free(hands);
  free_deck(rem_deck);
  free(win_arr);
}


int main(int argc, char ** argv) {
  //YOUR CODE GOES HERE
  int n_trials;
  deck_t ** hands;
  deck_t * rem_cards;
  size_t n_hands = 0;
  FILE * f = NULL;
  int * win_arr = NULL;

  future_cards_t * fc = (future_cards_t *)malloc(sizeof(*fc));
  fc->decks = NULL;
  fc->n_decks = 0;

  if((argc==1) || (argc>3))
  {
    fprintf(stderr, "Wrong number of Arguments\nNeed 1 or 2 argument");
    return EXIT_FAILURE;
  }

  if(argc == 2)
  {
    n_trails = 10000;
  }
  else
  {
    n_trails = strToInt(argv[2]);
  }

  f = fopen(argv[1],"r");
  hands = read_input(f, &n_hands, fc);
  rem_cards = build_remaining_deck(hands, n_hands);
  win_arr = (int *)realloc(win_arr, (n_hands+1)*sizeof(*win_arr));
  for(size_t i = 0; i < n_hands + 1; i++)
  {
    win_arr[i] = 0;
  }
  
  for(int i=0; i<n_trails; i++)
  {
    shuffle(rem_cards);
    future_cards_from_deck(rem_cards, fc);
    actScore(hands, n_hands, win_arr);
  }
  for(size_t h=0; h<n_hands; h++)
  {
    printf("Hand %zu won %u / %u times (%.2f%%)\n", h, win_arr[h], n_trails, 100*(float)win_arr[h]/(float)n_trails);
  }
  printf("And there were %u ties\n", win_arr[n_hands]);
  freeAll(fc, hands, n_hands, rem_cards, win_arr);
  fclose(f);
  
  return EXIT_SUCCESS;
}
