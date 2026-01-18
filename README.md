# 🚗 Vehicle Rental Management System (C++)

## 📑 Table of Contents
- [Summary](#brief-one-line-Summary)
- [Overview](#overview)
- [Problem Statement](#problem-statement)
- [Dataset](#dataset)
- [Tools & Technologies](#tools-and-technologies)
- [Features & Methods](#methods)
- [Output](#output)
- [How to Run the Project](#how-to-run-this-project)
- [Results & Conclusion](#results--conclusion)
- [Future Improvements](#future-work)
- [Author](#-author) 

---

## Brief One-Line Summary
A console-based Vehicle Rental Management System built in C++ that manages vehicle inventory and customer rentals with persistent file storage.

---

## Overview
This project was developed as my **First Semester C++ Final Project** in the **Programming Fundamentals** course.  
It is a comprehensive menu-driven console application that simulates a real-world vehicle rental facility.

The system allows administrators to:
- Manage vehicle inventory (add, edit, search, delete)
- Process customer rentals
- Maintain persistent data using file handling

---

## Problem Statement
Traditional vehicle rental management using paper records or basic spreadsheets is inefficient, error-prone, and lacks automation.

This project addresses these challenges by providing:

- **Vehicle Inventory Management:** Track vehicle details, availability, and types  
- **Customer Management:** Store renter information and rental history  
- **Rental Processing:** Handle vehicle rentals with proper validation  
- **Data Persistence:** Ensure data survives between program sessions  
- **Search & Reporting:** Quickly find vehicles and view customer details  

---

## Dataset
The project uses two local text files for data storage:
### Vehicles Data.txt
    ```text
        ID,Model,RegistrationNumber,Type,Availability
        101,Toyota Corolla,ABC-123,car,true
    ```
### Customer Data.txt
    ```text
        Name,Phone,CNIC,Email,RentedVehicleID
        John Doe,03001234567,42101-1234567-8,john@email.com,101
    ```
All data is managed using C++ file handling without any external databases.

---

## Tools and Technologies
- Programming Language: C++ (Standard 11+)

### Core Concepts Used
- Structures (struct) for Vehicle and Customer
- Dynamic Memory Allocation (resizable arrays)
- File Handling (ifstream, ofstream)
- String Manipulation (stringstream, find, substr)
- Console I/O with formatting (iomanip)
- Modular Programming (separate functions)
- Input Validation

---

## Methods
### System Architecture
1. **Data Structures**
- Vehicle: ID, Model, Registration Number, Type, Availability
- Customer: Name, Phone, CNIC, Email, Rented Vehicle ID

2. **Core Functionality**
- Vehicle Management: CRUD operations with ID validation
- Rental Processing: Availability checking and assignment
- File Persistence: Automatic save/load from text files
- Search Capabilities: By ID or vehicle type

3. **Key Algorithms**
- Dynamic array resizing when capacity is exceeded
- CSV parsing for file data loading
- Case-insensitive string comparison
- Transaction-style file updates for data integrity

### Menu Options
- Add New Vehicle
- Display Vehicles (all / available only)
- Search Vehicle (by ID or type)
- Edit Vehicle Details
- Delete Vehicle
- Rent a Vehicle
- Display Customers

---

## Output
The program provides:
- Formatted console interface with clear menus
- Tabular display of vehicle records
- Rental receipts with customer details
- Persistent data storage between runs
- Search results with availability status

### Sample Interface
    ```text
        =====================================================
        =====      WELCOME TO CAR RENTING FACILITY      =====
        =====================================================
        1. Add New Vehicle to Facility.
        2. Display Vehicles of Facility.
        3. Search Vehicle in Facility.
        4. Edit Details of Vehicle
        5. Delete Vehicle From System
        6. Rent a Vehicle.
        7. Display Customers.
        0. Exit
        -------------------------------------------
        Enter your Choice :
    ```

---

## How to Run this Project
### Prerequisites
- Any C++ compiler (GCC, MinGW, Visual Studio, Code::Blocks, Dev-C++)

### Steps to Run
1. **Clone the repository:**
    ```bash
        git clone https://github.com/TalhaIrfan-dev/Vehicle-Management-and-Renting-System.git
    ```
2. **Navigate to the project directory**
3. **Compile the source code:**
    ```bash
        g++ "Vehicle Management and Renting Facility.cpp" -o vehicle_rental.exe
    ```
4. **Run the program:**
    ```bash
        ./vehicle_rental.exe   # Linux / macOS
        vehicle_rental.exe     # Windows
    ```
📁 Data files will be created automatically on first run.

---

## Results & Conclusion
### Achievements
- ✅ Complete vehicle rental management system implemented
- ✅ All CRUD operations functional with persistence
- ✅ Dynamic memory management without memory leaks
- ✅ User-friendly console interface
- ✅ Real-world business logic simulation
### Learning Outcomes
- Strengthened C++ fundamentals
- Learned persistent data storage using files
- Improved problem-solving and system design skills
- Gained experience managing a medium-scale project
This project demonstrates strong command over structured programming, file handling, and system design.

---

## Future Work
- Convert to Object-Oriented Programming (OOP)
- Add vehicle return functionality and rental history
- Implement GUI (Qt / Windows Forms)
- Database integration (SQLite / MySQL)
- Billing and invoice system

---

## 👤 Author

**Talha Irfan**  
*BS Software Engineering — Sukkur IBA University*  
- 💼 LinkedIn: https://www.linkedin.com/in/talha-irfan-dev/
- 🌐 GitHub: https://github.com/TalhaIrfan-dev  
- ✉️ Email: talhairfanchoudry@gmail.com  
- 📍 Location: Sukkur, Pakistan
