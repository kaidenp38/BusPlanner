
#include "BusProperties.h"


void book_seat(Reservation reservations[], int bus_id) {
    int i;
    for (i = 0; i < MAX_SEATS; i++) {
        if (reservations[i].bus_id == 0) {
            reservations[i].bus_id = bus_id;
            reservations[i].seat_number = i + 1;
            break;
        }
    }
}

// E.L ticket id function
void generate_ticket_id(char ticket_id[]) {
    srand(time(NULL));
    const char charset[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    int i;
    for (i = 0; i < 9; i++) {
        ticket_id[i] = charset[rand() % 36];
    }
    ticket_id[i] = '\0';
}

//E.L save reservation function
void save_reservation(Reservation reservation) {
    FILE* fp;
    fp = fopen("reservations.txt", "a");
    if (fp == NULL) {
        fp = fopen("reservations.txt", "w");
        fprintf(fp, "bus_id,seat_number,name,phone_number,ticket_id\n"); // write header to file
        fclose(fp);
        fp = fopen("reservations.txt", "a");
    }
    fprintf(fp, "%d,%d,%s,%s,%s\n", reservation.bus_id, reservation.seat_number, reservation.name, reservation.phone_number, reservation.ticket_id);
    fclose(fp);
}

// E.L get bus choice function
int get_bus_choice() {
    int bus_choice;
    printf("Please select a bus: \n");
    printf("1. Bus A\n");
    printf("2. Bus B\n");
    printf("3. Bus C\n");
    scanf("%d", &bus_choice);
    if (bus_choice < 1 || bus_choice > 3) {
        printf("Invalid choice, please try again\n");
        return 0;
    }
    return bus_choice;
}

// E.L get user input function
void get_user_input(char name[], char phone_number[]) {
    printf("Please enter your name: ");
    scanf("%s", name);
    printf("Please enter your phone number: ");
    scanf("%s", phone_number);
}

// E.L create reservation function
Reservation create_reservation(int bus_choice, char name[], char phone_number[], Reservation reservations[]) {
    Reservation reservation = {
        .bus_id = bus_choice,
    };
    book_seat(reservations, bus_choice);
    generate_ticket_id(reservation.ticket_id);
    strcpy(reservation.name, name);
    strcpy(reservation.phone_number, phone_number);
    return reservation;
}

// E.L confirm reservation function
void confirm_reservation(Reservation reservation) {
    printf("Reservation successful!\n");
    printf("Your ticket ID is: %s\n", reservation.ticket_id);
    printf("Thank you for using our bus reservation system.\n");
}

//E.L Display Reservationf Function
void display_reservation_details(Reservation reservation) {
    printf("Name: %s\n", reservation.name);
    printf("Phone number: %s\n", reservation.phone_number);
    printf("Bus number: %d\n", reservation.bus_id);
    printf("Ticket ID: %s\n", reservation.ticket_id);
}

//A.N Relocate User Function
void relocate_user(Reservation* reservations) {
    int from_seat, to_seat;
    printf("Enter your current seat number: ");
    scanf("%d", &from_seat);
    printf("Enter the seat number you want to move to: ");
    scanf("%d", &to_seat);
    Reservation from_reservation = reservations[from_seat - 1];
    Reservation to_reservation = reservations[to_seat - 1];
    if (from_reservation.seat_number == 0 || to_reservation.seat_number != 0) {
        printf("Error: Invalid seat numbers.\n");
        return;
    }
    strcpy(to_reservation.name, from_reservation.name);
    strcpy(to_reservation.phone_number, from_reservation.phone_number);
    reservations[from_seat - 1].seat_number = 0;
    to_reservation.seat_number = to_seat;
    printf("Seat reservation successfully changed.\n");
}
