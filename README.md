# DA
## 1 лаба - 
Ограничение времени	1 секунда

Ограничение памяти	64Mb

Ввод	стандартный ввод или input.txt

Вывод	стандартный вывод или output.txt

Необходимо реализовать один из стандартных алгоритмов поиска образцов для указанного алфавита.

Вариант алгоритма: Поиск одного образца при помощи алгоритма Кнута-Морриса-Пратта.

Вариант алфавита: Слова не более 16 знаков латинского алфавита (регистронезависимые)

Запрещается реализовывать алгоритмы на алфавитах меньшей размерности, чем указано в задании.
## 2 лаба -
Ограничение времени	15 секунд

Ограничение памяти	512Mb

Ввод	стандартный ввод или input.txt

Вывод	стандартный вывод или output.txt

Необходимо создать программную библиотеку, реализующую указанную структуру данных, на основе которой разработать программу-словарь. В словаре каждому ключу, представляющему из себя регистронезависимую последовательность букв английского алфавита длиной не более 256 символов, поставлен в соответствие некоторый номер, от 0 до 264 - 1. Разным словам может быть поставлен в соответствие один и тот же номер.

Программа должна обрабатывать строки входного файла до его окончания. Каждая строка может иметь следующий формат:

+ word 34 — добавить слово «word» с номером 34 в словарь. Программа должна вывести строку «OK», если операция прошла успешно, «Exist», если слово уже находится в словаре.

- word — удалить слово «word» из словаря. Программа должна вывести «OK», если слово существовало и было удалено, «NoSuchWord», если слово в словаре не было найдено.

word — найти в словаре слово «word». Программа должна вывести «OK: 34», если слово было найдено; число, которое следует за «OK:» — номер, присвоенный слову при добавлении. В случае, если слово в словаре не было обнаружено, нужно вывести строку «NoSuchWord».

! Save /path/to/file — сохранить словарь в бинарном компактном представлении на диск в файл, указанный парамером команды. В случае успеха, программа должна вывести «OK», в случае неудачи выполнения операции, программа должна вывести описание ошибки (см. ниже).

! Load /path/to/file — загрузить словарь из файла. Предполагается, что файл был ранее подготовлен при помощи команды Save. В случае успеха, программа должна вывести строку «OK», а загруженный словарь должен заменить текущий (с которым происходит работа); в случае неуспеха, должна быть выведена диагностика, а рабочий словарь должен остаться без изменений. Кроме системных ошибок, программа должна корректно обрабатывать случаи несовпадения формата указанного файла и представления данных словаря во внешнем файле.

Для всех операций, в случае возникновения системной ошибки (нехватка памяти, отсутсвие прав записи и т.п.), программа должна вывести строку, начинающуюся с «ERROR:» и описывающую на английском языке возникшую ошибку.

Различия вариантов заключаются только в используемых структурах данных:

Красно-чёрное дерево.
## 4 лаба -
Ограничение времени	3.5 секунд

Ограничение памяти	200Mb

Ввод	стандартный ввод или input.txt

Вывод	стандартный вывод или output.txt

Требуется разработать программу, осуществляющую ввод пар «ключ-значение», их упорядочивание по возрастанию ключа указанным алгоритмом сортировки за линейное время и вывод отсортированной последовательности.
Вариант задания определяется типом ключа (и соответствующим ему методом сортировки) и типом значения:
Поразрядная сортировка.

Тип ключа: MD5-суммы (32-разрядные шестнадцатиричные числа).

Тип значения: строки фиксированной длины 64 символа, во входных данных могут встретиться строки меньшей длины, при этом строка дополняется до 64-х нулевыми символами, которые не выводятся на экран.
## 5 лаба -
Ограничение времени	15 секунд

Ограничение памяти	1Gb

Ввод	стандартный ввод или input.txt

Вывод	стандартный вывод или output.txt

Линеаризовать циклическую строку, то есть найти минимальный в лексикографическом смысле разрез циклической строки, с использованием суфф. дерева.
## 7 лаба -
Ограничение времени	10 секунд

Ограничение памяти	1Gb

Ввод	стандартный ввод или input.txt

Вывод	стандартный вывод или output.txt

Заданы длины N отрезков, необходимо выбрать три таких отрезка, которые образовывали бы треугольник с максимальной площадью.
## 8 лаба -
Ограничение времени	10 секунд

Ограничение памяти	1Gb

Ввод	стандартный ввод или input.txt

Вывод	стандартный вывод или output.txt

У вас есть рюкзак, вместимостью m, а так же n предметов, у каждого из которых есть вес wi и стоимость ci. Необходимо выбрать такое подмножество I из них, чтобы:
сумма wi <= m, (сумма ci) * |I| является максимальной из всех возможных.
|I| – мощность множества I.
## 9 лаба -
Ограничение времени	10 секунд

Ограничение памяти	1Gb

Ввод	стандартный ввод или input.txt

Вывод	стандартный вывод или output.txt

Задан неориентированный граф, состоящий из n вершин и m ребер. Вершины пронумерованы целыми числами от 1 до n. Необходимо вывести все компоненты связности данного графа.
