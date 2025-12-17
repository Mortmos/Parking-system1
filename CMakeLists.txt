cmake_minimum_required(VERSION 3.16)

project(ParkingSystem LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Вмикаємо автоматичну обробку мета-об'єктів Qt (для Q_OBJECT)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# ---------------------------------------------------------
# Пошук бібліотек Qt (Спочатку шукаємо Qt6, якщо ні - Qt5)
# ---------------------------------------------------------
find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)

# ---------------------------------------------------------
# Додаємо файли проекту
# ---------------------------------------------------------
set(PROJECT_SOURCES
    main.cpp
    MainWindow.cpp
    MainWindow.h
    ParkingLot.cpp
    ParkingLot.h
    ParkingFloor.cpp
    ParkingFloor.h
    ParkingSpot.cpp
    ParkingSpot.h
    SpotWidget.cpp
    SpotWidget.h
    Enums.h
    Ticket.h
)

# ---------------------------------------------------------
# Створення виконуваного файлу
# ---------------------------------------------------------
# Якщо хочете приховати консоль на Windows, додайте WIN32 перед ${PROJECT_SOURCES}
add_executable(ParkingSystem ${PROJECT_SOURCES})

# ---------------------------------------------------------
# Лінкування бібліотек
# ---------------------------------------------------------
target_link_libraries(ParkingSystem PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

# Вивід інформації про версію Qt
message(STATUS "Building with Qt ${QT_VERSION_MAJOR}")
