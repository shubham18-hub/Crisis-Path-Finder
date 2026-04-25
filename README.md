#Crisis Path Finder


A C++ console + SFML visualizer that simulates a city-wide emergency dispatch network. The system manages a road graph, registers emergency vehicles, logs incidents, and dispatches the nearest suitable responder using Dijkstra's shortest path algorithm — all rendered live in an SFML window.

---

## Features

- **City graph builder** — add locations with coordinates, connect them with weighted roads, update traffic weights at runtime
- **Vehicle management** — register Ambulances, Fire Trucks, and Police Cars at any city node; track fuel, location, and availability
- **Emergency logging** — log Medical, Fire, or Police incidents with location and severity (1–10)
- **Smart dispatch** — matches emergency type to vehicle type, picks the vehicle with the lowest real path cost (Dijkstra), falls back to any available vehicle if no type match exists
- **Score-based priority** — recommends the highest-priority emergency using `severity / (path_cost + 1)`
- **Fuel system** — vehicles consume fuel proportional to path cost; auto-refuel on empty
- **Live SFML visualizer** — runs in a background thread showing the city graph, road weights, vehicle positions, fuel bars, and emergency markers in real time

---

## Project Structure

```
.
├── phase3.cpp                      # Main source — full system with SFML
├── routeFinalPhase02.cpp           # Phase 2 — emergency management, basic dispatch
├── routeFinalPhase02_enhanced.cpp  # Phase 2 + error handling + terminal animation
├── routeFinalPhase03.cpp           # Phase 3 — smart dispatch, type matching, priority
├── route1.cpp                      # Phase 1 — Dijkstra + basic menu
├── route.cpp                       # Initial skeleton
└── .vscode/
    ├── tasks.json                  # Build tasks (active file + phase3 with SFML)
    ├── launch.json                 # Debug configurations
    ├── c_cpp_properties.json       # IntelliSense paths
    └── settings.json               # C_Cpp_Runner SFML linker/include config
```

---

## Requirements

| Tool | Version |
|------|---------|
| g++ | 13+ (C++17) |
| SFML | 3.x |
| OS | Windows 10+ / Linux / macOS |

### Windows (MSYS2 — recommended)

Install SFML via MSYS2 ucrt64:

```bash
pacman -S mingw-w64-ucrt-x86_64-sfml
```

SFML will be installed at `C:/msys64/ucrt64`.

---

## Building

### From terminal

```bash
g++ -std=c++17 -o phase3.exe phase3.cpp \
    -IC:/msys64/ucrt64/include \
    -LC:/msys64/ucrt64/lib \
    -lsfml-graphics -lsfml-window -lsfml-system
```

### From VS Code

- **`Ctrl+Shift+B`** — builds the currently active `.cpp` file (no SFML)
- **`Ctrl+Shift+P` → Tasks: Run Task → "Build phase3 (with SFML)"** — builds phase3 with all SFML flags
- **`F5` → "Debug phase3 (with SFML)"** — builds and launches with GDB

---

## Running

```bash
./phase3.exe
```

Two windows open simultaneously:
- **Console** — all menu input and output
- **SFML window** — live city graph visualization

---

## How to Use

### 1. Build the City

```
1. BUILD CITY
  2. ADD LOCATION       ← set x,y coordinates for all 8 nodes
  3. ADD ROAD           ← connect nodes (weight = euclidean distance + random traffic)
```

### 2. Add Vehicles

```
2. ADD VEHICLE
  1. AMBULANCE          ← responds to Medical emergencies
  2. FIRE TRUCK         ← responds to Fire emergencies
  3. POLICE CAR         ← responds to Police emergencies
```

Each vehicle needs a starting location node and gets 100 fuel on registration.

### 3. Log Emergencies

```
3. CREATE EMERGENCY
  → location (0–7), severity (1–10), type (Medical / Fire / Police)
```

### 4. Dispatch

```
4. DISPATCH VEHICLE
  2. DISPATCH VEHICLE
    → system recommends highest-priority emergency
    → enter ID or -1 to accept recommendation
    → nearest matching vehicle is dispatched along shortest path
    → SFML window animates the vehicle moving node by node
```

---

## Sample Input

```
# Set 8 locations
0 0 / 1 0 / 2 0 / 3 0 / 0 1 / 1 1 / 2 1 / 3 1

# Add 8 roads
0 1 / 1 2 / 2 3 / 3 7 / 0 4 / 4 5 / 5 6 / 6 7

# Add vehicles
AMB1  at node 0
FIRE1 at node 2
POL1  at node 5

# Log emergency
Location: 7, Severity: 8, Type: Medical

# Dispatch → system picks AMB1, shortest path 0→1→2→3→7
```

---

## SFML Window Legend

| Symbol | Meaning |
|--------|---------|
| Blue circle | City node |
| Green diamond | Ambulance |
| Red diamond | Fire Truck |
| Blue diamond | Police Car |
| Red marker `!` | Active Medical emergency |
| Orange marker `!` | Active Fire emergency |
| Blue marker `!` | Active Police emergency |
| Grey marker | Resolved emergency |
| Coloured path line | Active dispatch route |
| Fuel bar (green/red) | Vehicle fuel level |

---

## Error Handling

- Invalid integer input loops until a valid number is entered
- Node indices validated against graph bounds before every operation
- Duplicate road detection before adding edges
- Coordinates validated against grid dimensions
- Emergency type restricted to `Medical`, `Fire`, `Police`
- Dispatch checks vehicle availability, type match, path reachability, and fuel sufficiency before selecting

---

## Development Phases

| File | Phase | Description |
|------|-------|-------------|
| `route.cpp` | 0 | Initial skeleton with empty stubs |
| `route1.cpp` | 1 | Working Dijkstra, basic dispatch menu |
| `routeFinalPhase02.cpp` | 2 | Emergency class, dispatch with path display |
| `routeFinalPhase02_enhanced.cpp` | 2+ | Full error handling, terminal path animation |
| `routeFinalPhase03.cpp` | 3 | Type matching, real path cost, severity priority, location update |
| `phase3.cpp` | Final | All Phase 3 features + live SFML visualizer |
