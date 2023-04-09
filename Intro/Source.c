
#include "BusProperties.h"

int main() {
    Reservation reservations[MAX_SEATS] = { 0 };
    int bus_choice = get_bus_choice();
    if (bus_choice == 0) {
        return 1;
    }
    char name[50], phone_number[20];
    get_user_input(name, phone_number);
    Reservation reservation = create_reservation(bus_choice, name, phone_number, reservations);
    save_reservation(reservation);
    printf("Enter 1 to cancel reservation, enter 2 to relocate your seat or any other number to exit: \n\n");
    do {
        int new_choice;
        printf("Enter 1 to cancel a reservation\n\n");
        printf("Enter 2 to relocate a reservation\n\n");
        printf("Enter 3 to exit\n\n");
        scanf("%d", &new_choice);
        switch (new_choice) {
        case 1:
            cancel_reservation(reservations, reservations);
            break;
        case 2:
            relocate_user(reservations);
            break;
        case 3:
            exit(0);
            break;
        default:
            printf("Invalid choice. Please try again.\n");
        }
    } while (1);
    return 0;
}
