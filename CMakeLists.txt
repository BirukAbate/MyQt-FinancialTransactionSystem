cmake_minimum_required(VERSION 3.16)
project(MyQt)

set(CMAKE_CXX_STANDARD 17)

# Specifica il percorso di Qt
set(CMAKE_PREFIX_PATH "~/Qt/6.x.x/clang_64/lib/cmake") # Modifica con il percorso corretto

# Trova i componenti Qt
find_package(Qt6 COMPONENTS Widgets REQUIRED)

# Abilita AUTOMOC
set(CMAKE_AUTOMOC ON)

# Aggiungi l'eseguibile
add_executable(MyQt
        main.cpp
        BANK.cpp
        BANK.h
        BankAppGUI.cpp
        BankAppGUI.h
)

# Collega le librerie Qt al progetto
target_link_libraries(MyQt PRIVATE Qt6::Widgets)
