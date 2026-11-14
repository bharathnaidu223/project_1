# TREASURE HUNT – A Battle of Luck and Strategy

A beginner-friendly, two-player console game written in C. Players take turns searching a hidden 5 × 5 map for treasures and bonus spots.

## How to play

- Each player gets five regular attempts, followed by one extra pick in the lucky bonus round.
- Enter a row and column from 1 to 5 when prompted.
- A treasure is worth 10 points; a bonus spot is worth 5 points.
- Empty locations are worth 0 points.
- Players share the map, so a location that has already been searched cannot be selected again.
- The map updates after each turn but does not show undiscovered locations.
- The player with the higher score wins. Equal scores result in a tie.

Treasure and bonus locations are predefined in `initializeMap()`; the game does not generate them randomly.

## Build and run on Windows

Open PowerShell in this folder and compile the program:

```powershell
gcc -std=c99 -Wall -Wextra -pedantic treasure_hunt.c -o treasure_hunt.exe
.\treasure_hunt.exe
```

If PowerShell says that `gcc` is not recognized, GCC may not be on the current terminal's `PATH`. Restart VS Code and open a new terminal to pick up a newly installed compiler. For the WinLibs package installed with this project, you can also temporarily add its compiler directory in the current PowerShell session:

```powershell
$gccDir = Join-Path $env:LOCALAPPDATA 'Microsoft\WinGet\Packages\BrechtSanders.WinLibs.POSIX.UCRT_Microsoft.Winget.Source_8wekyb3d8bbwe\mingw64\bin'
$env:Path = "$gccDir;$env:Path"
gcc -std=c99 -Wall -Wextra -pedantic treasure_hunt.c -o treasure_hunt.exe
.\treasure_hunt.exe
```

## Map symbols

| Symbol | Meaning |
| --- | --- |
| `?` | Unexplored location |
| `X` | Searched empty location |
| `T` | Found treasure |
| `B` | Found bonus spot |

## Functions

- `displayWelcome()` prints the title and game rules.
- `initializeMap()` clears the game arrays and places treasures and bonus spots.
- `displayMap()` displays searched locations while keeping hidden locations secret.
- `readNumber()` reads whole-number input and handles non-numeric entries.
- `playerTurn()` prompts a player to select a valid, unsearched location and updates the game.
- `calculateScore()` returns the points for a selected location.
- `displayResults()` prints the final scores and announces the winner or a tie.
- `main()` initializes the game, runs all regular turns and the bonus round, then displays the results.

The program uses only the `stdio.h` header and beginner-level C features, including functions, arrays, loops, conditionals, `scanf()`, and `printf()`.

## Sample output

```text
TREASURE HUNT - A Battle of Luck

Player 1 - attempt 1 of 5
Choose a row (1-5): 1
Choose a column (1-5): 2
TREASURE! You found the loot. The map owes you a high-five!
Player 1: 10 points | Player 2: 0 points

*** LUCKY BONUS ROUND: Player 1 gets one extra pick! ***

FINAL TREASURE TALLY
Player 1: 35 points
Player 2: 0 points

The crown goes to PLAYER 1! What a legendary loot grab!
Thanks for playing TREASURE HUNT!
```
