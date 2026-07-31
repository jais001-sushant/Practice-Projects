# C Practice Projects

A collection of 10 console-based applications built in C while strengthening core programming fundamentals — memory management, file I/O, terminal control, recursion, and basic algorithmic problem-solving. Each project was built to explore a specific concept in depth rather than just "get it working."

---

## 📂 Projects Overview

| # | Project | What it does | Core Concepts |
|---|---|---|---|
| 1 | [Bank Management System](#1-bank-management-system) | Create accounts, deposit, withdraw, check balance | Binary file I/O, structs, persistent storage |
| 2 | [User Management System](#2-user-management-system) | Register, login, list, and delete users with masked password input | Raw terminal I/O, string handling, linear search |
| 3 | [KBC Game](#3-kbc-game-kaun-banega-crorepati) | Timed quiz game with lifelines, styled like the TV show | Signal handling, timers, file parsing, ANSI colors |
| 4 | [Snake Game](#4-snake-game) | Classic Snake, playable in the terminal | Non-blocking input, real-time game loop, collision detection |
| 5 | [Tic-Tac-Toe](#5-tic-tac-toe) | Human vs Computer, with a heuristic "unbeatable" mode | Game-state evaluation, basic AI logic, structs |
| 6 | [Sudoku Solver](#6-sudoku-solver) | Solves any valid 9x9 Sudoku puzzle automatically | Backtracking, recursion, constraint checking |
| 7 | [Digital Clock](#7-digital-clock) | Live-updating clock and date in 12h/24h format | System time APIs, string formatting |
| 8 | [Progress Bar Simulator](#8-progress-bar-simulator) | Simulates multiple concurrent task progress bars | ANSI escape codes, struct arrays, simulated concurrency |
| 9 | [Simple Calculator](#9-simple-calculator) | Handles 6 arithmetic operations with input validation | Input validation, switch-case logic |
| 10 | [Number Guessing Game](#10-number-guessing-game) | Classic guess-the-number game with attempt tracking | Randomization, loop control |

---

## 🔧 How to Compile and Run

Every project is a single `.c` file. Compile any of them with:

```bash
gcc <Project_Name>.c -o <Project_Name>
./<Project_Name>
```

**Example:**
```bash
gcc Snake_Game.c -o snake
./snake
```

> **Note:** Projects using `termios.h` (Snake, KBC, User Management) rely on Unix-style terminal control and are built for macOS/Linux. They will not compile as-is on Windows without modification.

---

## 📖 Project Details

### 1. Bank Management System
A menu-driven system to create accounts, deposit, withdraw, and check balances — with all data persisted to a binary file (`account.txt`) so records survive between runs.

**Highlights:**
- Uses `fwrite`/`fread` with raw struct binary I/O instead of text parsing
- Updates existing records in-place using `fseek` to rewind and overwrite, rather than rewriting the whole file
- Guards against overdrawing an account and missing account numbers

**Run:** `gcc Bank_Management.c -o bank && ./bank`

---

### 2. User Management System
A registration and login system supporting up to 10 users, with password input that's masked with `*` characters as it's typed — just like a real login screen.

**Highlights:**
- Manually disables terminal echo via `termios` to hide password characters while typing
- Handles backspace correctly during masked input
- Supports registering, logging in, listing, and deleting users in-memory

**Run:** `gcc User_Management.c -o user_mgmt && ./user_mgmt`

---

### 3. KBC Game (Kaun Banega Crorepati)
A timed quiz game modeled on the Indian TV show — complete with a countdown timer per question, two lifelines (50-50 and Skip), colored terminal output, and prize money tracking.

**Highlights:**
- Uses `SIGALRM` and `signal()` to enforce a real per-question countdown timer
- Parses questions dynamically from an external `questions.txt` file rather than hardcoding them
- ANSI escape codes used throughout for a styled, colorful terminal UI

**Run:** `gcc KBC_Game.c -o kbc && ./kbc`
*(requires `questions.txt` in the same directory)*

---

### 4. Snake Game
The classic Snake game, fully playable in the terminal using `w`/`a`/`s`/`d` controls, with the snake wrapping around screen edges and speeding up as your score increases.

**Highlights:**
- Implements non-blocking keyboard input using `select()`, so the snake keeps moving even without a keypress every frame
- Disables canonical terminal mode via `termios` for instant, unbuffered input
- Game speed dynamically increases with score for a real difficulty curve

**Run:** `gcc Snake_Game.c -o snake && ./snake`

---

### 5. Tic-Tac-Toe
A two-mode Tic-Tac-Toe game — Standard (a basic computer opponent) and "God Mode" (a heuristic-driven, effectively unbeatable opponent) — with running score tracking across rounds.

**Highlights:**
- Computer checks for immediate wins, then blocks the player's winning move, before falling back to strategic center/corner play
- Clean separation of concerns: win-checking, draw-checking, and move validation are all independent, reusable functions
- Score persists across multiple rounds within a session

**Run:** `gcc Tic-Tac-Toe.c -o ttt && ./ttt`

---

### 6. Sudoku Solver
Solves any valid 9x9 Sudoku puzzle automatically using a backtracking algorithm, printing the board before and after solving in a clean grid format.

**Highlights:**
- Classic backtracking: tries a digit, recurses, and undoes the move if it leads to a dead end
- Validates row, column, and 3x3 sub-grid constraints before placing every digit
- Formatted output mimics a real Sudoku grid with box dividers

**Run:** `gcc Sudoku_Puzzle.c -o sudoku && ./sudoku`

---

### 7. Digital Clock
A live, continuously updating console clock and date display, with a choice between 12-hour and 24-hour time formats.

**Highlights:**
- Uses the system clock (`time.h`) and `strftime` for locale-correct time/date formatting
- Refreshes the screen every second using ANSI escape sequences instead of a full `system("clear")` call, for smoother updates

**Run:** `gcc Digital_Clock.c -o clock && ./clock`

---

### 8. Progress Bar Simulator
Simulates 5 independent tasks completing at random speeds, each rendered as a live-updating ASCII progress bar until all tasks reach 100%.

**Highlights:**
- Each task tracked via its own struct with independent progress and step-size
- Simulates "concurrency" through a single-threaded loop that updates all tasks per tick — a simplified mental model for real concurrent systems

**Run:** `gcc Progress_Bar.c -o progress && ./progress`

---

### 9. Simple Calculator
A console calculator supporting addition, subtraction, multiplication, division, modulus, and power operations.

**Highlights:**
- Full input validation on every prompt, including division/modulus-by-zero protection
- Uses `pow()` from `math.h` for exponentiation

**Run:** `gcc Simple_Calculator.c -o calc -lm && ./calc`
*(note the `-lm` flag to link the math library)*

---

### 10. Number Guessing Game
The classic guess-the-number game — the program picks a random number between 1 and 100, and the player guesses until they find it, with attempt count tracked.

**Highlights:**
- Randomized target number using `srand(time(0))`
- Robust input validation loop that rejects non-numeric input without crashing

**Run:** `gcc Guessing_Number.c -o guess && ./guess`

---

## 🧠 Skills Demonstrated Across This Repository

- **Systems-level C:** raw terminal control (`termios`), signal handling (`SIGALRM`), binary file I/O
- **Data structures:** structs, arrays of structs, 2D arrays, dynamic memory allocation (`malloc`)
- **Algorithms:** recursive backtracking (Sudoku), game-state evaluation (Tic-Tac-Toe)
- **Real-world I/O patterns:** persistent storage, external config/data files, masked credential input
- **UX in the terminal:** ANSI escape codes for color and screen control, real-time rendering loops

---

## 🛠 Tech Stack

- **Language:** C (C99)
- **Compiler:** GCC
- **Platform:** macOS / Linux (Unix terminal APIs used throughout)

---

## 📌 Notes

This repository is a learning log, not a production codebase — each project was built to deliberately practice a specific concept. Code style and structure improve progressively across projects as more concepts were introduced.