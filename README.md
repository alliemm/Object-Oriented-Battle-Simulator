# C++ OOP Battle Simulator

A fantasy-style battle simulator built with **C++** to demonstrate **object-oriented programming**, including **inheritance**, **polymorphism**, and **encapsulation**.

## Skills
C++17 · Inheritance · Polymorphism · Abstraction · Encapsulation · Composition · Operator Overloading · Dynamic Dispatch · STL (`<vector>`, `<string>`, `<iostream>`)

## Overview
Implements a class hierarchy where **Nobles** battle using **Protectors** with distinct fighting styles.  
Each subclass defines unique behavior through **virtual functions** and dynamic method calls.

### Class Structure
- **Noble (abstract)** → `Lord`, `PersonWithStrengthToFight`  
- **Protector (abstract)** → `Wizard`, `Archer`, `Swordsman`

### Key Features
- Lords can **hire**, **fire**, or lose Protectors who **run away**
- Dynamic **battle simulation** adjusting strengths proportionally
- **Defend()** and **weaken()** methods overridden in subclasses
- Uses **operator overloading** for clean console output

