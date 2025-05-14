# Stronghold: Kingdom Management Simulator

## Project Overview

Stronghold is a C++-based console application that simulates the management of a medieval kingdom. Players act as rulers, making strategic decisions to balance resources, population, military, economy, leadership, and banking systems. In **Phase 1**, the game focused on a single-player experience with dynamic interactions, random events, and turn-based progression. **Phase 2** expands the game with multiplayer support, a navigable world map, diplomacy, war, and trade systems, allowing up to four players to compete or cooperate in a shared world. The game features interconnected subsystems, random and player-triggered events, and a rich simulation of kingdom governance, offering a complex and engaging experience.

The project demonstrates object-oriented programming (OOP) principles, including inheritance, polymorphism, encapsulation, and abstraction, while providing an interactive and immersive gaming experience suitable for both single-player and multiplayer scenarios.

## Project Division

The codebase is organized into multiple C++ files, each handling specific components of the game. Below is the updated project structure, including new files and functionalities introduced in Phase 2:

### 1. Header File
- **Stronghold.h**: Defines all classes, their attributes, and method signatures. It serves as the central header file, including forward declarations and class definitions for `Resource`, `Population`, `SocialClass` (with derived classes `Peasant`, `Merchant`, `Noble`), `Military`, `Economy`, `Leadership`, `Bank`, `Event`, `Kingdom`, and new Phase 2 classes: `MultiplayerManager`, `TextMap`, `DiplomacySystem`, `WarSystem`, and `TradeSystem`.

### 2. Implementation Files
- **Resource.cpp**: Manages resources (e.g., Gold, Food, Wood, Stone) with methods for production, consumption, and status display.
- **Population.cpp**: Handles population dynamics, including growth rate, happiness, health, and revolt checks.
- **SocialClass.cpp**: Implements the base `SocialClass` with methods for tax generation, happiness, and productivity. Includes a virtual destructor.
- **socialClassDerived.cpp**: Contains implementations for derived classes `Peasant`, `Merchant`, and `Noble`, each with unique contributions (e.g., food for peasants, gold for merchants, influence for nobles).
- **Military.cpp**: Manages the kingdom's army, including soldier recruitment, training, equipment, morale, and strength calculations.
- **Economy.cpp**: Oversees the kingdom's treasury, tax collection, inflation, and services cost, with methods to spend gold and update economic conditions.
- **Leadership.cpp**: Manages the ruler's attributes, such as popularity, leadership ability, and corruption, with mechanics for coups and elections.
- **Bank.cpp**: Handles banking operations, including loans, interest rates, reserves, and corruption management through audits.
- **Event.cpp**: Implements random and user-triggered events that impact various kingdom systems (e.g., population, military, economy).
- **Kingdom.cpp**: The core class that integrates all subsystems, managing the kingdom's state, turn progression, event handling, and game saving/loading.
- **MultiplayerManager.cpp** (Phase 2): Manages multiple players (2–4), handling player setup, turn progression, and global events that affect all kingdoms.
- **TextMap.cpp** (Phase 2): Implements a text-based world map with locations and connections, allowing players to move their kingdom’s focus between locations.
- **DiplomacySystem.cpp** (Phase 2): Manages diplomatic interactions, including forming alliances and sending messages between kingdoms.
- **WarSystem.cpp** (Phase 2): Handles war declarations and battle resolutions based on military strength, with outcomes affecting soldiers and morale.
- **TradeSystem.cpp** (Phase 2): Implements legal trading and smuggling of resources between kingdoms, with a risk-based mechanic for smuggling.
- **main.cpp**: Contains the main game loop, user interface, and input handling. It provides a menu-driven interface with colored console output, now supporting multiplayer interactions, map navigation, diplomacy, war, and trade actions.

## Technologies Used

- **C++**: The primary programming language, leveraging OOP principles for modular and maintainable code.
- **Windows API**: Utilized for colored console output on Windows systems (via `windows.h` and `SetConsoleTextAttribute`).
- **Random Number Generation**: Employed `cstdlib` and `ctime` for random events, battle outcomes, smuggling risks, and dynamic gameplay elements.
- **Console Input/Output**: Used `iostream`, `conio.h` (for `_getch`), and `string` for user interaction and display.
- **File I/O**: Leveraged `fstream` for saving and loading game states to text files, supporting persistence across sessions.

## Code Explanation

### Core Mechanics
- **Kingdom Management**: The `Kingdom` class remains the central hub, coordinating subsystems (`Population`, `Military`, `Economy`, `Leadership`, `Bank`, `Resource`, `SocialClass`, and new Phase 2 systems: `DiplomacySystem`, `WarSystem`, `TradeSystem`). It handles turn progression (`advanceTurn`), event processing (`handleEvent`), and game state persistence (`saveGame`, `loadGame`).
- **Resources**: The `Resource` class manages quantities, production, and consumption of resources like Gold, Food, Wood, and Stone, now used in trade and smuggling actions.
- **Population and Social Classes**: The `Population` class tracks total population, happiness, health, and growth. Social classes (`Peasant`, `Merchant`, `Noble`) contribute resources or influence, affected by taxes, events, and diplomatic relations.
- **Military**: The `Military` class manages soldiers, training, equipment, and morale. In Phase 2, military strength determines battle outcomes in the `WarSystem`.
- **Economy**: The `Economy` class handles the treasury, tax rates, inflation, and service costs. Phase 2 introduces penalties for failed smuggling attempts, impacting the treasury.
- **Leadership**: The `Leadership` class tracks the ruler’s popularity, ability, and corruption, now influenced by diplomatic successes or war outcomes.
- **Bank**: The `Bank` class manages loans, interest, and reserves, with corruption affecting loan availability. Audits remain a key mechanic for financial stability.
- **Events**: The `Event` class introduces dynamic challenges or benefits, now impacting multiplayer interactions (e.g., global market fluctuations).
- **Multiplayer Management** (Phase 2): The `MultiplayerManager` class supports 2–4 players, each controlling a unique kingdom. It manages turn order, player setup, and global events (e.g., market fluctuations every three turns).
- **World Map** (Phase 2): The `TextMap` class creates a navigable map with locations (e.g., Castle) and connections, allowing players to move their kingdom’s focus, potentially affecting resource production or diplomatic reach.
- **Diplomacy** (Phase 2): The `DiplomacySystem` class enables players to form alliances (up to three) and send messages to other kingdoms, fostering cooperation or strategic communication.
- **War** (Phase 2): The `WarSystem` class allows players to declare war on others, with battles resolved based on military strength. Victories boost morale and reduce enemy soldiers, while defeats have the opposite effect.
- **Trade** (Phase 2): The `TradeSystem` class supports legal trading and smuggling of resources. Legal trades are straightforward, while smuggling carries a risk (30% base, scaled by amount), with failure resulting in resource loss and treasury penalties.

### Key Features
- **Turn-Based Gameplay**: Each player takes a turn to manage their kingdom, with global events occurring periodically to affect all players.
- **Multiplayer Support** (Phase 2): Up to four players can compete or cooperate, each managing their own kingdom with unique names and strategies.
- **Navigable World Map** (Phase 2): Players can move between connected locations, adding a spatial dimension to strategic decisions.
- **Diplomacy System** (Phase 2): Players can form alliances or send messages, enhancing cooperative or deceptive gameplay.
- **War System** (Phase 2): Players can declare wars, with battles impacting military strength and kingdom stability.
- **Trade System** (Phase 2): Legal trading and risky smuggling provide new ways to manage resources and interact with other kingdoms.
- **User Interface**: The menu-driven interface in `main.cpp` now includes options for multiplayer actions (e.g., diplomacy, war, trade, map movement), with colored console output for clarity.
- **Dynamic Interactions**: Subsystems remain interconnected, with Phase 2 adding interactions like trade affecting economies, wars impacting militaries, and diplomacy influencing leadership popularity.
- **Save/Load System**: Extended to save the state of all players’ kingdoms, preserving multiplayer game progress.
- **Event System**: Players can trigger predefined or custom events, with global events in multiplayer mode affecting all kingdoms simultaneously.

### Notable Code Details
- **OOP Principles**:
  - **Inheritance**: `Peasant`, `Merchant`, and `Noble` inherit from `SocialClass`, while Phase 2 classes like `DiplomacySystem`, `WarSystem`, and `TradeSystem` are embedded in `Kingdom`.
  - **Polymorphism**: Virtual methods in `SocialClass` ensure dynamic behavior, reused in Phase 2 for consistent subsystem interactions.
  - **Encapsulation**: Private attributes with public getters/setters protect data, extended to new classes like `MultiplayerManager` and `TextMap`.
  - **Abstraction**: New systems abstract complex interactions (e.g., battle resolution, smuggling risk) into simple method calls.
- **Error Handling**: Input validation in `main.cpp` now covers multiplayer inputs (e.g., valid kingdom targets for diplomacy or war) and map movements, preventing invalid actions.
- **Randomization**: Phase 2 enhances randomization with smuggling risks and battle outcomes, using `rand()` seeded by `srand(time(nullptr))`.

## My Contributions

As the developers, my peer and I:
- **Designed the Game Concept**: Extended the single-player simulation into a multiplayer experience, adding strategic depth with map navigation, diplomacy, war, and trade.
- **Structured the Codebase**: Added new files (`MultiplayerManager.cpp`, `TextMap.cpp`, `DiplomacySystem.cpp`, `WarSystem.cpp`, `TradeSystem.cpp`) while maintaining modular design and clear separation of concerns.
- **Implemented Core Mechanics**: Developed multiplayer support, map navigation, diplomacy, war, and trade systems, ensuring seamless integration with existing subsystems.
- **Enhanced the User Interface**: Updated the menu system to include new options for multiplayer actions, map movement, diplomacy, war, and trade, with clear prompts and colored feedback.
- **Extended Persistence**: Modified the save/load system to handle multiple kingdoms, ensuring multiplayer games can be resumed.
- **Added New Systems**:
  - Implemented `MultiplayerManager` to manage player turns and global events.
  - Created `TextMap` for a navigable world map with location connections.
  - Developed `DiplomacySystem` for alliances and messaging.
  - Built `WarSystem` for war declarations and battle resolutions.
  - Designed `TradeSystem` with legal trading and risk-based smuggling.
- **Ensured Robustness**: Added input validation for new features (e.g., valid map destinations, kingdom targets), boundary checks for alliances (max 3), and error handling for trade/smuggling failures.
- **Tested and Debugged**: Extensively tested multiplayer interactions, map navigation, diplomacy, war outcomes, and trade mechanics to ensure balanced and bug-free gameplay.
- **Resolved Compilation Issues**: Fixed errors related to incomplete types, extra qualifications, and case mismatches in `Stronghold.h` and other files, ensuring the codebase compiles cleanly.

## How to Play

1. **Setup**:
   - Start the game and choose the number of players (2–4).
   - Enter unique names for each player’s kingdom.

2. **Gameplay**:
   - Each player takes turns managing their kingdom via a menu-driven interface.
   - Use the menu (1-9, A-F, S, L, Q) to issue decrees, including:
     - **Resource Management**: Boost farms, logging, or mining (1–3).
     - **Military Actions**: Recruit soldiers, train troops, or upgrade armory (4–6).
     - **Economic Decisions**: Change tax rates, request/repay loans, or conduct bank audits (7–9, A).
     - **Events**: Trigger predefined or custom events (B).
     - **Turn Progression**: Advance to the next player’s turn (C).
     - **Diplomacy**: Send messages or form alliances with other kingdoms (D).
     - **War**: Declare war and resolve battles (W).
     - **Trade**: Engage in legal trading or smuggling (T).
     - **Map Navigation**: Move between locations on the world map (M).
     - **Messages**: View diplomatic messages (F).
     - **Save/Load**: Save or load game progress (S, L).
     - **Quit**: Exit the game (Q).
   - Monitor kingdom status (resources, population, military, etc.) displayed each turn.

3. **Winning**: The game continues until players choose to quit or a kingdom collapses (e.g., due to revolt or military defeat). No formal win condition exists, encouraging strategic play and competition.

## Future Improvements

- **AI Opponents**: Introduce AI-controlled kingdoms to allow single-player games against computer opponents or to fill multiplayer slots when fewer than four players are available.
- **Expanded Map Features**: Add location-specific bonuses (e.g., increased resource production in certain areas) or events tied to specific map locations to enhance strategic depth.
- **Advanced Diplomacy**: Implement treaties, trade embargoes, or betrayal mechanics to make diplomacy more dynamic and impactful.
- **War Enhancements**: Add terrain effects, unit types (e.g., archers, cavalry), or siege mechanics to make battles more varied and tactical.
- **Trade Economy**: Introduce a dynamic market with fluctuating resource prices based on supply and demand across kingdoms.
- **Graphical Interface**: Transition from console to a graphical user interface (e.g., using SFML or Qt) for a more engaging user experience.
- **Networked Multiplayer**: Enable online multiplayer to allow players to compete remotely, expanding the game’s accessibility.
- **Event Variety**: Expand the event system with more diverse events, including chained events or player-driven storylines.
- **Balancing and Testing**: Fine-tune game balance (e.g., smuggling risks, battle outcomes) and conduct extensive playtesting to ensure fair and enjoyable multiplayer dynamics.