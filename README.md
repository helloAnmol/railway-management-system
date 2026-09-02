# 🚆 Railway Management System

A console-based **Railway Management System** developed in **C++** using **Object-Oriented Programming (OOP)** principles.

The project simulates a basic railway reservation system where passengers can search for trains, book and cancel tickets, view ticket details, and check their booking history. An admin panel is also provided for managing train information.

---

## 📌 Project Overview

The Railway Management System is designed to demonstrate how **Object-Oriented Programming concepts** can be applied to build a practical real-world application.

The system provides separate functionalities for:

- 👤 Passengers
- 🔐 Administrators

The current version uses **in-memory storage**, meaning all train and ticket data exists only while the program is running.

---

## ✨ Features

### 👤 Passenger Features

- View all available trains
- Search trains by source and destination
- Book railway tickets
- Automatic seat allocation
- Generate unique PNR numbers
- Select different travel classes
- Calculate fare based on travel class
- View ticket details
- Cancel booked tickets
- View passenger booking history
- Check seat availability
- Input validation for passenger details

### 🔐 Admin Features

- Admin authentication
- View all trains
- Add new trains
- Remove existing trains
- Update train information
- Prevent deletion of trains with existing bookings
- Validate train numbers to prevent duplicates
- Validate seat capacity and fare

---

## 🛠️ Technologies Used

- **C++**
- **Object-Oriented Programming**
- **Standard Template Library (STL)**
- `vector`
- Iterators
- Console-based user interface

---

## 🧠 OOP Concepts Demonstrated

This project was developed to practice and demonstrate important Object-Oriented Programming concepts in C++.

### 1. Classes and Objects

The project contains several classes representing real-world entities:

```text
User
Passenger
Admin
Train
Ticket
RailwaySystem
```

---

## 📌 Current Limitations

This is a console-based educational project, so the current version has some limitations:

- Data is stored only in memory.
- Data is lost when the program terminates.
- No database is currently used.
- No file persistence is implemented.
- Admin credentials are hardcoded for demonstration purposes.
- Train search currently requires exact source and destination names.
- No real payment gateway is integrated.
- No real railway API is used.
- No GUI is currently implemented.
