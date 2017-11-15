# Przetwarzanie-Sygnalow-Biomedycznych
Projekt na przedmiot "Przetwarzanie Sygnałów Biomedycznych"

Instrukcja działania aplikacji:
 1. Obraz wyświetlany z kamery jest podzielony na dwie części (przedzielony czerwoną pionową linią). Po prawej stronie znajduje się obiekt     odniesienia, w tym przypadku jest to kartka A4 o wymiarach 297x210 mm, tj. 29.7x21.0 cm. Na potrzeby pomiarów wykorzystywany jest         tylko dłuższy wymiar.
 2. Po lewej stronie ekranu umieszczany jest mierzony obiekt, np. człowiek. 
 3. Dla obu obiektów odczytywany jest osobno ich rozmiar w pionie (w punktach obrazu) poprzez obliczenie różnicy w pionie pomiędzy             położeniami skrajnch punktów obiektu. Następnie zmierzona wartość jest przeliczana na centymetry wedle wzoru:
              
              wys. obiektu mierzonego[punkty obrazu] * wys. obiektu odniesienia[cm] / wys. obiektu odniesienia[punkty obrazu]

 4. Aby pomiar został wykonany poprawnie, niezbędne jest umieszczenie obu obiektów (odniesienia i mierzonego) w identycznej odległości od     kamery przy ścianie o jednolitym kolorze. Wykorzystany w projekcie obiekt odniesienia, tj. kartka A4, powinna być umieszczona tak, aby     jej dłuższy bok znajdował się prostopadle do krawędzi ściany. W zasięgu kamery nie powinno być innych obiektów, ponieważ mogą one         zafałszować pomiar rozmiaru obiektów.
 5. Ze względu na właściwości kamery, pomiar może być obarczony pewnym błędem ze względu na to, że np. u człowieka, jego                       poszczególne części ciała znajdują się w różnej odległości od obiektywu kamery. W celu zminimalizowania tego efektu, kamera została       ustawiona tak, aby dolna krawędź obrazu znajdowała na wysokości krawędzi pomiędzy ścianą a podłogą.
