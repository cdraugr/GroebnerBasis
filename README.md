# Groebner Basis Lib
Небольшой мануал:

## Установка и запуск библиотеки:

Сначала нужно всё это скачать:

```bash
git clone https://github.com/cdraugr/GroebnerBasis.git
```
В папке `GroebnerBasis/GroebnerLib/` будет лежать библиотека. В ней можно прописать `make` и создастся собранная библиотека `GroebnerLib.a`.

## Использование библиотеки

Вы можете собрать её, как и любую другую `.a` библиотеку. Например, [тут](https://github.com/cdraugr/GroebnerBasis/blob/b990c86263161787e347125bac447118edb8641a/TestGroebnerLib/Makefile#L29) (тот же проект, но тесты) есть пример.

В самом же коде потребуется написать `#include "FastGB.h"`, чтобы использовать все возможности `gb::`.

## Собрать тесты

В `GroebnerBasis/TestGroebnerLib/` имеются тесты со своим Makefile'ом, так что чтобы собрать их достаточно аналогично просто прописать `make` (он соберёт библиотеку сам, отдельно это делать не нужно). Собранный файл будет называться `GroebnerTest.out`.

## Makefile

Оба Makefile (в тестах и в библиотеке) поддерживают `make [all]` ,`make re`, `make fclean`, `make clean`.

---
