# COLOR CONVERTER

Color Converter – это приложение, которое позволяет пользователю выбирать, а затем интерактивно менять цвет, показывая при этом его составляющие в трех цветовых моделях одновременно (доступные цветовые модели: _RGB_, _CMYK_, _HSV_, _HSL, XYZ_, _LAB_).

Приложение разработано с помощью кроссплатформенной IDE – Qt Creator (версия: 6.1.3). Адаптировано для ОС Windows.

Приложение использует стандартные библиотеки Qt: QtWidgets, QMainWindow, QtMath. Документация по данной среде разработки и ее библиотекам доступна на ее [веб-сайте](https://doc.qt.io).
___
Функционал приложения представляет из себя выбор или задание цвета, его перевод из одной цветовой модели в другие и его вывод. 

* Базовый класс приложения – Widget. Его функционал состоит в обработке ввода и изменения данных пользователем, вывод данных при помощи виджетов из стандартных библиотек Qt. Для выбора цвета использован класс QColorDialog.

* ColorConverterClass – класс, предназначенный для перевода цветовых моделей друг в друга, перевода из цветовых моделей в объект класса QColor и наоборот (для вывода цвета), оповещении при переводе “некорректных цветов”. Переводы осуществляются при помощи методов класса QColor и формул перевода в цветовые модели. В качестве источника света используется стандартный источник дневного cвета D65.

* MainWindow – класс, предназначенный для отображения класса Widget и вывода сообщений об округлении при переводе “некорректных цветов” в строку статуса.
___
Недостатки приложения: возможны небольшие округления значений цвета (влияние на цвет не заметно).
