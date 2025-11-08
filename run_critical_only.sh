#!/bin/bash

echo "🔍 Запуск с фильтрацией только КРИТИЧЕСКИХ ошибок"
echo "────────────────────────────────"

# Проверяем существование исполняемого файла
if [ ! -f "./build/test_build" ]; then
    echo "❌ Ошибка: Исполняемый файл не найден!"
    echo "   Сначала выполните: ./compile.sh"
    exit 1
fi

# Настройки ASan только для критических ошибок (игнорируем утечки)
export ASAN_OPTIONS="detect_leaks=0:halt_on_error=1:print_stacktrace=1"
export LSAN_OPTIONS="suppressions=./lsan_suppressions.txt"

echo "📋 Настройки: detect_leaks=0 (игнорируем утечки)"
echo "              halt_on_error=1 (останавливаемся при первой критической ошибке)"
echo ""

# Запускаем программу и фильтруем вывод
echo "🔍 Запуск программы..."
echo "────────────────────────────────"

# Запускаем и перехватываем вывод
OUTPUT=$(./build/test_build 2>&1)
EXIT_CODE=$?

if [ $EXIT_CODE -ne 0 ]; then
    echo "❌ КРИТИЧЕСКАЯ ОШИБКА обнаружена!"
    echo "────────────────────────────────"
    
    # Фильтруем только важные части ошибки
    echo "$OUTPUT" | grep -E -A5 -B2 "(AddressSanitizer|ERROR|SEGV|ABRT|heap-use-after-free|stack-buffer-overflow|double-free)"
    
    echo ""
    echo "💡 Типы критических ошибок:"
    echo "   • SEGV - Segmentation Fault (программа падает)"
    echo "   • heap-use-after-free - использование после free"
    echo "   • stack-buffer-overflow - переполнение стека"
    echo "   • double-free - двойное освобождение памяти"
    
else
    echo "✅ Критических ошибок не обнаружено"
    echo "   (Программа может иметь утечки памяти, но не падает)"
fi

echo ""
echo "🔧 Для полного анализа с утечками: ./run_with_ASan.sh"