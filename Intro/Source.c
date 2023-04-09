
#include "BusProperties.h"
#include <stdio.h>
#include <stdbool.h>

int main() {
    bool programLoop = true;
    while (programLoop)
    {
        Reservation reservations[MAX_SEATS] = { 0 };
        int menuChoice;
        printf("Welcome to the bus planner program\n");
        printf("select the option that applys to what you want to do.\n");
        printf("1. Book a seat\n");
        printf("2. Relocate a seat\n");
        printf("3. Cancel a reservation\n");
        printf("4. Exit the program\n");
        scanf_s("%d", &menuChoice);

        if (menuChoice == 1)
        {
            int bus_choice = get_bus_choice();
            if (bus_choice == 0) {
                return 1;
            }
            Reservation reservation = create_reservation(bus_choice,reservations);
            if (reservation.bus_id == 0) {
                printf("Reservation unsuccessful.\n");
                return 1;
            }
            save_reservation(reservation);
            confirm_reservation(reservation);
            display_reservation_details(reservation);
        }
        else if (menuChoice == 2)
        {
            relocate_user(reservations);
        }
        else if (menuChoice == 3)
        {
            // code to cancel a seat.
            Reservation cancel;
            printf("Please enter the reservation details to cancel:\n");
            printf("Bus Number: ");
            scanf("%d", &cancel.bus_id);
            printf("Seat number: ");
            scanf("%d", &cancel.seat_number);
            printf("Ticket ID: ");
            scanf("%s", cancel.ticket_id);

            cancel_reservation(cancel);

        }
        else if (menuChoice == 4)
        {
            programLoop = false;
            exit(1);
        }
        else
        {
            printf("not a valid option.");
        }
    }
    return 0;
}
