#include <stdio.h>
#include "player.h"
#include "deck.h"

typedef int bool;
#define true 1
#define false 0


int main(int args, char* argv[]) 
{
    bool play_again = true;

    while (play_again) {
        bool user_turn = true;
        bool computer_turn = false;

        // Initialize the deck
        shuffle();

        // Initialize the players
        struct player user;
        struct player computer;

        // Deal the cards
        deal_player_cards(&user);
        deal_player_cards(&computer);

        // Print the initial hands
        printf("Your hand: ");
        print_hand(&user);
        printf("Computer's hand: ");
        print_hand(&computer);

        // Play the game
        while (!game_over(&user) && !game_over(&computer)) {
            if (user_turn) {
                char rank = user_play(&user);
                if (rank == 0) {
                    printf("You have no cards of that rank. Go fish!\n");
                    struct card new_card = draw_card();
                    printf("You drew a %s of %s from the deck.\n", new_card.rank, new_card.suit);
                    add_card(&user, new_card);
                } else {
                    printf("You have a card of that rank. You get to go again!\n");
                }
                user_turn = false;
                computer_turn = true;
            } else if (computer_turn) {
                char rank = computer_play(&computer);
                if (rank == 0) {
                    printf("The computer has no cards of that rank. Go fish!\n");
                    struct card new_card = draw_card();
                    printf("The computer drew a %s of %s from the deck.\n", new_card.rank, new_card.suit);
                    add_card(&computer, new_card);
                } else {
                    printf("The computer has a card of that rank. It gets to go again!\n");
                }
                user_turn = true;
                computer_turn = false;
            }
            printf("Your hand: ");
            print_hand(&user);
            printf("Computer's hand: ");
            print_hand(&computer);

        }

    }
}





