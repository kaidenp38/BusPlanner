
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
            char ticket_id[10], name[50], phone_number[20];
            int bus_choice, seat_choice, found = 0;

            // Get ticket ID from user
            printf("Please enter your ticket ID: ");
            scanf("%s", ticket_id);

            // Search for reservation in file
            FILE* fp = fopen("reservations.txt", "r");
            char line[200];
            while (fgets(line, 200, fp) != NULL) {
                Reservation reservation;
                sscanf(line, "%d,%d,%[^,],%[^,],%s", &reservation.bus_id, &reservation.seat_number, reservation.name, reservation.phone_number, reservation.ticket_id);
                if (strcmp(reservation.ticket_id, ticket_id) == 0) {
                    // Found reservation, get user input for new seat
                    printf("Reservation found for %s.\n", reservation.name);
                    get_user_input(name, phone_number);
                    bus_choice = get_bus_choice();
                    seat_choice = get_seat_choice();
                    reservation.bus_id = bus_choice;
                    reservation.seat_number = seat_choice;
                    strcpy(reservation.name, name);
                    strcpy(reservation.phone_number, phone_number);

                    // Update reservation in file
                    FILE* fp_update = fopen("reservations_update.txt", "w");
                    fprintf(fp_update, "bus_id,seat_number,name,phone_number,ticket_id\n");
                    rewind(fp);
                    while (fgets(line, 200, fp) != NULL) {
                        Reservation res;
                        sscanf(line, "%d,%d,%[^,],%[^,],%s", &res.bus_id, &res.seat_number, res.name, res.phone_number, res.ticket_id);
                        if (strcmp(res.ticket_id, ticket_id) == 0) {
                            fprintf(fp_update, "%d,%d,%s,%s,%s\n", reservation.bus_id, reservation.seat_number, reservation.name, reservation.phone_number, reservation.ticket_id);
                            found = 1;
                        }
                        else {
                            fprintf(fp_update, "%d,%d,%s,%s,%s\n", res.bus_id, res.seat_number, res.name, res.phone_number, res.ticket_id);
                        }
                    }
                    fclose(fp);
                    fclose(fp_update);
                    remove("reservations.txt");
                    rename("reservations_update.txt", "reservations.txt");
                    break;
                }
            }
            fclose(fp);
            if (!found) {
                printf("No reservation found for ticket ID %s.\n", ticket_id);
            }
            else {
                printf("Reservation updated successfully!\n");
            }
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
