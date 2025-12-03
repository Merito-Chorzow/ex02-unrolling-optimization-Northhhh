[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-22041afd0340ce965d47ae6ef1cefeee28c7c493a6346c4f15d667ab976d596c.svg)](https://classroom.github.com/a/bDlMFcrW)
[![Open in Visual Studio Code](https://classroom.github.com/assets/open-in-vscode-2e0aaae1b6195c2367325f4f02e2d04e9abb55f0b24a779b69b11b9e10269abc.svg)](https://classroom.github.com/online_ide?assignment_repo_id=21932142&assignment_repo_type=AssignmentRepo)
# Unrolling ×4 i porównanie -O0/-O2/-O3

## Cel
- Dodać wariant funkcji z **unrolling ×4** (C lub ASM) i porównać działanie.
- Zbudować przy `-O0`, `-O2`, `-O3` i porównać rozmiar (`size`) i metrykę czasową (pętla 100×).
- Upewnić się, że warianty zwracają **ten sam wynik**.

## Krok po kroku
1. Uzupełnij `sum8_unroll4` (w C *lub* jako `asm/sum8_unroll4.S` – wtedy pamiętaj dodać do Makefile).
2. Zmieniaj `CFLAGS` w Makefile na `-O0/-O2/-O3` (lub dodaj cele `make O0/O2/O3`).
3. Uruchom: `make && ./scripts/run.sh` i zanotuj wyniki, rozmiar (`make size`).
4. W logu QEMU powinno pojawić się „OK [ex02]” jeśli wyniki się zgadzają.

## Oddanie (GitHub Classroom)
Analogicznie jak w Ćw.1 — push uruchamia CI, które sprawdza znacznik „OK”. Dodaj krótką tabelę: wersja → rozmiar `.text` oraz metrykę.

## Kryteria zaliczenia
- Poprawna implementacja `sum8_unroll4` — 50%.
- Porównanie wyników i rozmiarów + krótkie wnioski — 30%.
- Zielony status CI — 20%.
