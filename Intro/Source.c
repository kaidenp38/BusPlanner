
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
    confirm_reservation(reservation);
    display_reservation_details(reservation);
    return 0;
}
