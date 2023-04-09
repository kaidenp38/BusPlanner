#define _CRT_SECURE_NO_WARNINGS
#include "BusProperties.h"

//E.L book seat function
void book_seat(Reservation reservations[], int bus_id, int seat_number) {
    reservations[seat_number - 1].bus_id = bus_id;
    reservations[seat_number - 1].seat_number = seat_number;
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

int get_seat_choice() {
    int seat_choice;
    printf("Please select a seat number (1-%d): ", MAX_SEATS);
    scanf("%d", &seat_choice);
    if (seat_choice < 1 || seat_choice > MAX_SEATS) {
        printf("Invalid choice, please try again\n");
        return 0;
    }
    return seat_choice;
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

// checks reservation
int check_seat_reservation(int bus_id, int seat_number, Reservation reservations[]) {
    if (reservations[seat_number - 1].bus_id == bus_id) {
        printf("Seat already reserved for this bus.\n");
        return 1;
    }
    else if (reservations[seat_number - 1].bus_id != 0) {
        printf("Seat already reserved for another bus.\n");
        return 1;
    }
    else {
        return 0;
    }
}

// E.L create reservation function
Reservation create_reservation(int bus_choice, Reservation reservations[]) {
    int seat_choice = 0;
    char name[50], phone_number[20];

    printf("Do you want to choose a specific seat (1) or get a random seat (2)? ");
    int choice;
    scanf("%d", &choice);
    if (choice == 1) {
        seat_choice = get_seat_choice();
        if (check_seat_reservation(bus_choice, seat_choice, reservations)) {
            printf("Seat already booked, please choose another one.\n");
            return create_reservation(bus_choice, reservations);
        }
    }
    else if (choice == 2) {
        // randomly choose an available seat
        int num_available = 0;
        for (int i = 0; i < MAX_SEATS; i++) {
            if (reservations[i].bus_id == 0) {
                num_available++;
            }
        }
        if (num_available == 0) {
            printf("Sorry, no seats available on this bus.\n");
            return (Reservation) { 0 };
        }
        int rand_seat = rand() % num_available + 1;
        for (int i = 0; i < MAX_SEATS; i++) {
            if (reservations[i].bus_id == 0) {
                rand_seat--;
                if (rand_seat == 0) {
                    seat_choice = i + 1;
                    break;
                }
            }
        }
    }
    else {
        printf("Invalid choice, please try again.\n");
        return create_reservation(bus_choice, reservations);
    }

    get_user_input(name, phone_number);

    Reservation reservation = {
        .bus_id = bus_choice,
        .seat_number = seat_choice,
    };
    book_seat(reservations, bus_choice, seat_choice);
    save_reservation(reservation);
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
void display_reservation_details(Reservation reservation)
{
    printf("Name: %s\n", reservation.name);
    printf("Phone number: %s\n", reservation.phone_number);
    printf("Bus number: %d\n", reservation.bus_id);
    printf("Seat number: %d\n", reservation.seat_number);
    printf("Ticket ID: %s\n",reservation.ticket_id);
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

void cancel_reservation(int seat_number, Reservation* reservations) {
    if (seat_number < 1 || seat_number > MAX_SEATS) {
        printf("Error: Invalid seat number.\n");
        return;
    }
    Reservation reservation = reservations[seat_number - 1];
    if (reservation.seat_number == 0) {
        printf("Error: Seat is not reserved.\n");
        return;
    }
    printf("Are you sure you want to cancel the reservation for seat number %d? (Y/N): ", seat_number);
    char confirmation;
    scanf(" %c", &confirmation);
    if (confirmation == 'Y' || confirmation == 'y') {
        reservations[seat_number - 1].seat_number = 0;
        printf("Reservation for seat number %d has been cancelled.\n", seat_number);
    }
    else if (confirmation == 'N' || confirmation == 'n') {
        printf("Reservation for seat number %d has not been cancelled.\n", seat_number);
    }
    else {
        printf("Invalid input. Reservation for seat number %d has not been cancelled.\n", seat_number);
    }
}