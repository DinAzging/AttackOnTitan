#!/bin/bash

echo "🚀 Запуск с AddressSanitizer"
echo "────────────────────────────────"

# Проверяем существование исполняемого файла
if [ ! -f "./build/test_build" ]; then
    echo "❌ Ошибка: Исполняемый файл не найден!"
    echo "   Сначала выполните: ./compile.sh"
    exit 1
fi

# Настройки ASan для детального анализа
export ASAN_OPTIONS="detect_leaks=1:halt_on_error=0:print_stacktrace=1:verbosity=1:log_path=asan_log.txt"
export LSAN_OPTIONS="suppressions=./lsan_suppressions.txt:print_suppressions=0"

echo "📋 Настройки ASan:"
echo "   • detect_leaks=1    - обнаружение утечек"
echo "   • print_stacktrace=1 - вывод трассировки стека"
echo "   • log_path=asan_log.txt - запись лога в файл"
echo ""

# Запускаем программу
echo "🔍 Запуск программы..."
echo "────────────────────────────────"
./build/test_build

# Сохраняем код возврата
EXIT_CODE=$?

echo ""
echo "────────────────────────────────"
echo "📊 Анализ завершён (код выхода: $EXIT_CODE)"

# Анализируем результаты
if [ $EXIT_CODE -ne 0 ]; then
    echo "❌ Обнаружены критические ошибки!"
    echo ""
    echo "💡 Критические ошибки:"
    echo "   • SEGV - Segmentation Fault (падение программы)"
    echo "   • heap-use-after-free - использование после освобождения"
    echo "   • stack-buffer-overflow - переполнение стека"
    echo "   • double-free - двойное освобождение памяти"
    
    # Показываем первые критические ошибки из лога
    if [ -f "asan_log.txt" ]; then
        echo ""
        echo "📋 Первые критические ошибки из лога:"
        grep -E -m5 "(ERROR|AddressSanitizer|SEGV|ABRT)" asan_log.txt | head -10
    fi
else
    echo "✅ Программа завершилась успешно"
    echo "   (Возможны только утечки памяти)"
fi

echo ""
echo "📁 Полный лог: asan_log.txt"
echo "🔧 Для фильтрации только критических ошибок: ./run_critical_only.sh"