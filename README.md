# Containers_CPP

В рамках данного проекта написана собственная библиотека, реализующая основные стандартные контейнерные классы языка С++: `list` (список), `map` (словарь), `queue` (очередь), `set` (множество), `stack` (стек) и `vector` (вектор). Реализации предоставляет весь набор стандартных методов и атрибутов для работы с элементами, проверкой заполненности контейнера и итерирования. В качестве дополнительного задания  реализованы еще несколько не так часто используемых, но отличающихся деталями реализации контейнерных классов из контейнерной библиотеки C++: `array` (массив), `multiset` (мультимножество).


Каждый вид контейнеров предоставляет пользователю следующие методы:

- стандартные конструкторы (конструктор по умолчанию, конструктор копирования, конструктор перемещения, конструктор со списком инициализации, см. материалы);

- методы доступа к элементам контейнера (например, осуществление доступа к элементу с индексом i);

- методы проверки наполненности контейнера (например, количество элементов в контейнере, проверка на пустоту контейнера);

- методы изменения контейнера (удаление и добавление новых элементов, очистка контейнера);

- методы для работы с итератором контейнера.

Итераторы обеспечивают доступ к элементам контейнера. Для каждого контейнера конкретный тип итератора будет отличаться. Это связано с различным видом организации наборов объектов в контейнерных классах, а также с фактической реализацией контейнера. Итераторы реализуются в таком виде, чтобы они работали схожим образом с указателем на элемент массива языка Си. Именно такой подход через использование итераторов и позволяет взаимодействовать с любыми контейнерами одинаковым образом. Контейнеры предоставляют через методы `begin()` и `end()` итераторы, которые указывают на первый и следующий после последнего элементы контейнера соответственно.

Над итератором `iter` определены следующие операции:

- `*iter`: получение элемента, на который указывает итератор;

- `++iter`: перемещение итератора вперед для обращения к следующему элементу;

- `--iter`: перемещение итератора назад для обращения к предыдущему элементу;

- `iter1 == iter2`: два итератора равны, если они указывают на один и тот же элемент;

- `iter1 != iter2`: два итератора не равны, если они указывают на разные элементы.

## Реализация Containers_CPP

- Программа разработана на языке C++ стандарта C++17 с использованием компилятора gcc
- Код программы находится в папке src
- Использованы итераторы
- Классы являются шаблонными
- Классы реализованы внутри пространства имен `s21`
- Методы контейнерных классов покрыты unit-тестами c помощью библиотеки GTest
- В проекте соблюдена логика работы стандартной библиотеки шаблонов (STL) (в части проверок, работы с памятью и поведения в нештатных ситуациях)