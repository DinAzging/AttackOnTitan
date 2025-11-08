#!/bin/bash

echo "🔧 Компиляция с AddressSanitizer"

# Создаем папку build если не существует
mkdir -p build

echo "📦 Компиляция файлов..."

# Компилируем с максимальной детализацией отладочной информации
g++ -g -fsanitize=address -fno-omit-frame-pointer \
    Entities/*.cpp \
    GameLogic/Battle/*.cpp GameLogic/Cell\ Interactions/*.cpp \
    GameLogic/Components/BattleComponent/*.cpp GameLogic/Components/ForestComponent/*.cpp \
    GameLogic/Components/MovementComponent/*.cpp GameLogic/Components/ViewComponent/*.cpp GameLogic/Components/WarehouseComponent/*.cpp \
    GameLogic/Components/BeastThrowComponent/*.cpp \
    Map/*.cpp \
    "Resource File"/*.cpp \
    "Source Files"/*.cpp \
    States/*.cpp \
    -Iinclude \
    -o build/test_build \
    -lsfml-graphics -lsfml-window -lsfml-system

# Проверяем результат компиляции
if [ $? -eq 0 ]; then
    echo "✅ Компиляция успешна!"
    echo "📁 Исполняемый файл: ./build/test_build"
    
    # Делаем файл исполняемым
    chmod +x build/test_build
    
    echo ""
    echo "🚀 Для запуска выполните: ./run_with_ASan.sh"
    echo "   или: ./run_critical_only.sh (только критические ошибки)"
    
else
    echo "❌ Ошибка компиляции!"
    exit 1
fi