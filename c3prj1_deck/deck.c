#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "deck.h"
void print_hand(deck_t * hand){
  card_t ** ptr = hand->cards;
  for(int i=0; i<(hand->n_cards); i++){
    print_card(**ptr);
    printf("%s"," ");
    ptr++;
  }
}

int deck_contains(deck_t * d, card_t c) {
  card_t ** ptr = d->cards;
  for(int i=0; i<(d->n_cards); i++){
    if(suit_letter(**ptr)== suit_letter(c) && value_letter(**ptr)==value_letter(c)){
      return 1;
    }
    ptr++;
  }
  return 0;
}

void cardPtr_swap(card_t ** ptr1, card_t ** ptr2){
  card_t * temp = *ptr1;
  *ptr1 = *ptr2;
  *ptr2 = temp;
}


void shuffle(deck_t * d){
  card_t ** ptr = d->cards;
  int size = (int)(d->n_cards);
  for(int i=0; i<size; i++){
    int newPos = ((int)rand())%size;
    cardPtr_swap(ptr+i,ptr+newPos);
  }
}

void assert_full_deck(deck_t * d) {
  card_t ** ptr = d->cards;
  deck_t temp_deck;
  temp_deck.cards = d->cards;
  for(int i=0; i<(d->n_cards); i++){
    card_t temp_card = **ptr;
    assert_card_valid(temp_card);
    if(i>0){
      temp_deck.n_cards = (size_t)i;
      assert(!deck_contains(&temp_deck, temp_card));
    }
    ptr++;
  }
}

void add_card_to(deck_t *deck, card_t c) {
  deck->n_cards++;
  deck->cards = realloc(deck->cards, (deck->n_cards)*sizeof(*(deck->cards)));
  deck->cards[deck->n_cards - 1] = NULL;
  deck->cards[deck->n_cards - 1] = realloc(deck->cards[deck->n_cards - 1], sizeof(*(deck->cards[deck->n_cards - 1])));
  deck->cards[deck->n_cards - 1]->suit = c.suit;
  deck->cards[deck->n_cards - 1]->value = c.value;
}


card_t * add_empty_card(deck_t * deck) {
  card_t *temp_card = malloc(sizeof(*temp_card));
  temp_card->suit = 0;
  temp_card->value = 0;
  deck->n_cards++;
  deck->cards = realloc(deck->cards, (deck->n_cards)*sizeof(*(deck->cards)));
  deck->cards[deck->n_cards - 1] = temp_card;
  return temp_card;
}

deck_t* make_deck_exclude(deck_t * excluded_cards) {
  card_t temp_c;
  deck_t *ret_d = malloc(sizeof(*ret_d));
  ret_d->n_cards = 0;
  ret_d->cards = NULL;
  int cond;

  for (unsigned i = 0; i < 52; i++) {
    temp_c = card_from_num(i);
    cond = deck_contains(excluded_cards, temp_c);
    if (cond == 0) {
      add_card_to(ret_d, temp_c);
    }
  }
  return ret_d;
}

deck_t * build_remaining_deck(deck_t ** hands, size_t n_hands) {
  deck_t *temp_h;
  deck_t *no_ret_d = malloc(sizeof(*no_ret_d));
  deck_t *ret_d;
  no_ret_d->n_cards = 0;
  no_ret_d->cards = NULL;
  card_t *temp_c;
  for (size_t i = 0; i < n_hands; i++) {
    temp_h = hands[i];
    for (size_t j = 0; j < temp_h->n_cards; j++) {
      temp_c = temp_h->cards[j];
      if (temp_c->value != 0) {
	if (deck_contains(no_ret_d, *temp_c) == 0) {
	  add_card_to(no_ret_d, *temp_c);
	}
      }
    }
  }
  ret_d = make_deck_exclude(no_ret_d);
  free_deck(no_ret_d);
  return ret_d;
}

void free_deck(deck_t * deck) {
  for (size_t i = 0; i < deck->n_cards; i++) {
    free(deck->cards[i]);
  }
  free(deck->cards);
  free(deck);
}

