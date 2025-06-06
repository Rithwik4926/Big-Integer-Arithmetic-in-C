Name: Big Integer Arithmetic in C
Description:
This project implements Big Integer Arithmetic in C, allowing operations on integers of arbitrary size beyond the limits of standard data types like int or long. The program supports addition, subtraction, and multiplication of large integers, including handling positive and negative numbers. It uses a custom data structure (bigInt) to store and manipulate numbers as strings, ensuring precision and correctness for very large values.

Features:
Big Integer Representation:
1.Numbers are stored as strings to handle arbitrary sizes.
2.Includes support for positive and negative numbers.

Arithmetic Operations:
1.Addition: Adds two big integers, handling carry and sign.
2.Subtraction: Subtracts two big integers, handling borrow and sign.
3.Multiplication: Multiplies two big integers, handling overflow and sign.

Input Handling:
1.Accepts user input for big integers, automatically adding a sign (+ or -) if missing.

Interactive Menu:
1.Provides a user-friendly menu to perform operations:
  ->Addition
  ->Subtraction
  ->Multiplication
  ->Exit

Edge Case Handling:
1.Handles cases like leading zeros, zero results, and overflow during multiplication.

Technologies Used:
1.C Programming Language
2.String Manipulation for handling large numbers
3.Custom Data Structure (bigInt) for storing big integers
