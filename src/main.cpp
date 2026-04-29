#include "polinom.h"
#include <iostream>
#include <string>

int main() {
  Polinom p1, p2, p_res;
  int op = -1;

  auto input = [](Polinom &p, std::string n) {
    int count;
    std::cout << ">>> Инициализация объекта [" << n << "]\n";
    std::cout << "Укажите общее количество мономов: ";
    std::cin >> count;
    for (int i = 0; i < count; ++i) {
      double c;
      int d;
      std::cout << "  Элемент #" << i + 1 << " (коэффициент и степень xyz): ";
      std::cin >> c >> d;
      p.addMonom(c, d);
    }
  };

  input(p1, "A");
  input(p2, "B");

  while (op != 0) {
    std::cout << "\n========================================" << std::endl;
    std::cout << "ТЕКУЩИЕ ДАННЫЕ В ПАМЯТИ:" << std::endl;
    std::cout << " [Полином A]: ";
    p1.print();
    std::cout << " [Полином B]: ";
    p2.print();
    std::cout << "----------------------------------------" << std::endl;
    std::cout << "ДОСТУПНЫЕ ОПЕРАЦИИ:" << std::endl;
    std::cout << " 1. Сложить выражения (A + B)" << std::endl;
    std::cout << " 2. Вычесть второе из первого (A - B)" << std::endl;
    std::cout << " 3. Масштабировать полином A (умножить на число)"
              << std::endl;
    std::cout << " 4. Найти произведение полиномов (A * B)" << std::endl;
    std::cout << " 5. Перезаписать данные (A = B)" << std::endl;
    std::cout << " 6. Проверить объекты на идентичность" << std::endl;
    std::cout << " 0. Завершить сеанс" << std::endl;
    std::cout << "----------------------------------------" << std::endl;
    std::cout << "Введите номер команды: ";
    std::cin >> op;

    if (op == 0) {
      std::cout << "Завершение работы программы..." << std::endl;
      break;
    }

    std::cout << "\n>>> ВЫПОЛНЕНИЕ:";
    switch (op) {
    case 1:
      p_res = p1 + p2;
      std::cout << "\nРезультат сложения: ";
      p_res.print();
      break;
    case 2:
      p_res = p1 - p2;
      std::cout << "\nРезультат вычитания: ";
      p_res.print();
      break;
    case 3: {
      double k;
      std::cout << "\nВведите числовой множитель: ";
      std::cin >> k;
      p_res = p1 * k;
      std::cout << "Итог масштабирования: ";
      p_res.print();
      break;
    }
    case 4:
      try {
        p_res = p1 * p2;
        std::cout << "\nРезультат произведения: ";
        p_res.print();
      } catch (...) {
        std::cout << "\n[Ошибка]: Превышена допустимая степень!" << std::endl;
      }
      break;
    case 5:
      p1 = p2;
      std::cout << "\nОбъект A успешно обновлен данными из B." << std::endl;
      break;
    case 6:
      std::cout << "\nСтатус проверки: ";
      if (p1 == p2)
        std::cout << "Объекты полностью идентичны." << std::endl;
      else
        std::cout << "Объекты имеют различия." << std::endl;
      break;
    default:
      std::cout << "\nКоманда не распознана. Попробуйте снова." << std::endl;
    }
  }
  return 0;
}