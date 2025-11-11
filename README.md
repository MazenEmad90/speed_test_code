# Typing Speed Test

A simple C++ console application to measure your typing speed (words per minute, WPM) and accuracy.  
Results are saved to a CSV file for review later.

## Features

- Displays a predefined English paragraph (~4 lines) for you to type.  
- Starts timing when you begin typing, stops when you finish (press Enter).  
- Calculates:
  - Time taken (seconds)  
  - Number of words typed  
  - Words per minute (WPM)  
  - Accuracy (%) compared to the target text  
  - A rating based on WPM + accuracy (Beginner / Intermediate / Advanced / Expert)  
- Appends results to `typing_results.csv` with fields: `datetime, wpm, accuracy_percent, rating, words_typed, seconds_taken`.

## Why Use It?

- Improve your typing speed and accuracy over time.  
- Simple and lightweight — no GUI, runs in your terminal/console.  
- Keeps a record of your performance to track improvement.

## Getting Started

### Prerequisites

- A C++ compiler that supports C++11 (or later).  
- Basic familiarity with building/running C++ console applications.

### Build & Run

1. Clone the repository:
   ```bash
   git clone https://github.com/your-username/speed_test_code.git
   cd speed_test_code
