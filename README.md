**Клетки поля:**

1 - белая шашка

2 - черная шашка

3 - белая дамка

4 - черная дамка

=======================================================================================

**Для хода игрока проверяется корректность ввода данных:**

Ход представляется парой строк (откуда, куда) (например вводим без кавычек "e5 d6").

Ходим только по диагонали

Простая шашка либо ходит на 1 вперед, либо ест

Дамка ходит на сколько угодно вперед или назад

Есть обязательно

Есть можно только 1 шашку за раз

=========================================================================================

Если выбранной шашкой игрок может съесть несколько шашек компьютера, то после первого съедения ему предлагается продолжить ход необходимое количество раз.
Для этого нужно ввести следующую клетку, в которую нужно перейти (например без кавычек "f7")

Ход игрока закончен, когда он выбранной шашкой съел все, что смог, или, если не может ничего съесть, сделал ход

==========================================================================================

Компьютер смотрит, может ли он что-то съесть, и ест пока есть возможность

Если есть нечего, то делает обычный ход

==========================================================================================

g++ checkers.cpp
