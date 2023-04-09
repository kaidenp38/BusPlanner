#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_SEATS 20

typedef struct {
    int bus_id;
    int seat_number;
    int is_confirmed;
    char name[50];
    char phone_number[20];
    char ticket_id[10];
} Reservation;

void book_seat(Reservation reservations[], int bus_id, int seat_number);
void generate_ticket_id(char ticket_id[]);
void save_reservation(Reservation reservation);
int get_bus_choice();
int get_seat_choice();
void get_user_input(char name[], char phone_number[]);
int check_seat_reservation(int bus_id, int seat_number, Reservation reservations[]);
Reservation create_reservation(int bus_choice, Reservation reservations[]);
void confirm_reservation(Reservation reservation);
void display_reservation_details(Reservation reservation);
Reservation find_reservation(char ticket_id[]);
//void relocate_user(Reservation* reservations);
void cancel_reservation(Reservation reservation);
