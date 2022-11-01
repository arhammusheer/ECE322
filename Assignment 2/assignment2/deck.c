#include "deck.h"

int shuffle(){
		
	// Shuffle the deck
	for (int i = 0; i < 52; i++)
	{
		int random = rand() % 52;
		struct card temp = deck_instance.list[i];
		deck_instance.list[i] = deck_instance.list[random];
		deck_instance.list[random] = temp;
	}

	return 0;
}

int deal_player_cards(struct player* target){
	
	// Check if the player has a hand
	if (target->card_list != NULL)
	{
		return 1;
	}

	// Deal 7 cards to the player
	for (int i = 0; i < 7; i++)
	{
		struct card* new_card = next_card();
		if (new_card == NULL)
		{
			return 1;
		}
		add_card(target, new_card);
	}

	return 0;
}


struct card* next_card( ){
	
	// Check if the deck is empty
	if (deck_instance.top_card == 52)
	{
		return NULL;
	}

	// Return the top card
	struct card* top_card = &deck_instance.list[deck_instance.top_card];
	deck_instance.top_card++;
	return top_card;
}

size_t size(){
	
	// Return the number of cards left in the deck
	return 52 - deck_instance.top_card;
}

