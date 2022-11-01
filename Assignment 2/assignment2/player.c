#include "player.h"

int add_card(struct player *target, struct card *new_card)
{

	// Add the card to the hand
	struct hand *new_hand = (struct hand *)malloc(sizeof(struct hand));
	new_hand->top = *new_card;

	// If the hand is empty, just add the card
	if (target->card_list == NULL)
	{
		target->card_list = new_hand;
		target->hand_size++;
		return 0;
	}

	// Otherwise, add the card to the end of the list
	struct hand *current = target->card_list;
	while (current->next != NULL)
	{
		current = current->next;
	}
	current->next = new_hand;
	target->hand_size++;
	return 0;
}

int remove_card(struct player *target, struct card *old_card)
{
	// If the hand is empty, return an error
	if (target->card_list == NULL)
	{
		return 1;
	}

	// If the card is the first in the list, remove it
	if (target->card_list->top.rank == old_card->rank && target->card_list->top.suit == old_card->suit)
	{
		struct hand *temp = target->card_list;
		target->card_list = target->card_list->next;
		free(temp);
		target->hand_size--;
		return 0;
	}

	// Otherwise, find the card in the list and remove it
	struct hand *current = target->card_list;
	while (current->next != NULL)
	{
		if (current->next->top.rank == old_card->rank && current->next->top.suit == old_card->suit)
		{
			struct hand *temp = current->next;
			current->next = current->next->next;
			free(temp);
			target->hand_size--;
			return 0;
		}
		current = current->next;
	}

	// If the card is not in the list, return an error
	return 1;
}

char check_add_book(struct player *target)
{
	// If the hand is empty, return an error
	if (target->card_list == NULL)
	{
		return 0;
	}

	// Check each card in the hand
	struct hand *current = target->card_list;
	while (current != NULL)
	{
		// Check if the card is already in a book
		int in_book = 0;
		for (int i = 0; i < 7; i++)
		{
			if (target->book[i] == current->top.rank)
			{
				in_book = 1;
				break;
			}
		}
		if (in_book)
		{
			current = current->next;
			continue;
		}

		// Check if the card has a match
		struct hand *match = current->next;
		while (match != NULL)
		{
			if (match->top.rank == current->top.rank)
			{
				// Add the book to the player's book list
				for (int i = 0; i < 7; i++)
				{
					if (target->book[i] == 0)
					{
						target->book[i] = current->top.rank;
						break;
					}
				}

				// Remove the cards from the hand
				struct hand *temp = current;
				current = current->next;
				remove_card(target, &temp->top);
				free(temp);
				temp = match;
				match = match->next;
				remove_card(target, &temp->top);
				free(temp);
				break;
			}
			match = match->next;
		}
		if (match == NULL)
		{
			current = current->next;
		}
	}

	// Return the first book added
	for (int i = 0; i < 7; i++)
	{
		if (target->book[i] != 0)
		{
			return target->book[i];
		}
	}
	return 0;
}

int search(struct player *target, char rank)
{
	/*
	 * Search for a card in the player's hand.
	 * Return 1 if found, 0 if not found.
	 */
	struct hand *current = target->card_list;
	while (current != NULL)
	{
		// If the rank matches, return 1
		if (current->top.rank[0] == rank)
		{
			return 1;
		}
		current = current->next;
	}
	return 0;
}

int transfer_cards(struct player *target, struct player *other, char rank)
{
	/*
	 * Transfer all cards of a given rank from one player to another.
	 * Return the number of cards transferred.
	 */
	int count = 0;
	struct hand *current = target->card_list;
	while (current != NULL)
	{
		// If the rank matches, transfer the card
		if (current->top.rank[0] == rank)
		{
			struct hand *temp = current;
			current = current->next;
			add_card(other, &temp->top);
			remove_card(target, &temp->top);
			free(temp);
			count++;
		}
		else
		{
			current = current->next;
		}
	}
	return count;
}

int game_over(struct player *target)
{
	/*
	 * Check if the game is over.
	 * Return 1 if the game is over, 0 if not.
	 */
	for (int i = 0; i < 7; i++)
	{
		if (target->book[i] == 0)
		{
			return 0;
		}
	}
	return 1;
}

int reset_player(struct player *target)
{
	/*
	 * Reset a player's hand and book.
	 */
	struct hand *current = target->card_list;
	while (current != NULL)
	{
		struct hand *temp = current;
		current = current->next;
		free(temp);
	}
	target->card_list = NULL;
	target->hand_size = 0;
	for (int i = 0; i < 7; i++)
	{
		target->book[i] = 0;
	}
	return 0;
}

char computer_play(struct player* target){
	if (target->card_list == NULL){
		return 0;
	}

	struct hand *current = target->card_list;

	while (current != NULL){
		if (search(target, current->top.rank[0])){
			return current->top.rank[0];
		}
		current = current->next;
	}

	return 0;
}

char user_play(struct player* target){
	char rank[2];

	printf("Player user, enter the rank of the card you want to play: ");
	scanf("%s", rank);

	if (search(target, rank[0]) == 1){
		return rank[0];
	} else {
		printf("You do not have that card. Please try again.\n");
		return user_play(target);
	}
}

void print_hand(struct player* target){
	struct hand *current = target->card_list;

	while (current != NULL){
		printf("%s of %s ", current->top.rank, current->top.suit);
		current = current->next;
	}
	printf("\n");
}
