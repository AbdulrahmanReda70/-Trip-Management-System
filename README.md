# Trip Management System

## Overview
The Trip Management System is a comprehensive C++ application designed to manage trip bookings, display available trips and offers, and handle user and trip information efficiently. It allows users to select trips, apply discounts, and manage their bookings through an interactive console interface.

---

## Features
1. **User Authentication**  
   - Secret key-based management access.
   - Integration with a basic login system for user authentication.

2. **Trip Management**  
   - Add, edit, and view trip details.
   - Manage trip availability and offers dynamically.

3. **Discounted Offers**  
   - Calculate and display discounts on trips.
   - Show original and discounted prices for trips.

4. **Trip Selection**  
   - View trips based on availability in the current week.
   - Search for trips by day and week.

5. **Ticket Management**  
   - Generate and display tickets with trip and payment details.
   - Update trip capacities based on bookings.

6. **Interactive Console**  
   - User-friendly menu for seamless navigation.
   - Flexible options to continue or exit actions.

---

## Code Structure

### Main Functions
- **BigIntro()**  
  Displays an introductory interface with terms and conditions and allows users to proceed after agreement.

- **management_section()**  
  Handles secure access to trip management functions.

- **manageTrips()**  
  Offers options to add or edit trips through a menu-driven interface.

- **displayAvailableOffers()**  
  Displays trips with active offers and their discounted prices.

- **Selected_trip()**  
  Allows users to choose trips based on availability or search criteria (day and week).

- **printTicketAndUpdateTrip()**  
  Generates tickets for bookings, adjusts trip capacities, and deducts payment from user balance. (Overloaded for flexible ticket printing.)

---

## Classes
### Trip
- Manages trip details such as ID, day, week, origin, destination, prices, and availability.  
- Includes methods to get and set current capacities for different classes.

### User
- Represents users with attributes like name, username, password, and balance.  
- Integrates with a login system for secure authentication.

---

## Usage
1. Clone the repository:  
   ```bash
   git clone <repository_url>
