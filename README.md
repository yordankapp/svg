Работа със SVG файлове

В рамките на този проект трябва да се разработи приложение, което работи със файлове във Scalable Vector Graphics (SVG) формат. Приложението трябва да може да зарежда фигури от файла, да извършва върху тях дадени операции, след което да може да записва промените обратно на диска.

За улеснение, в рамките на проекта ще работим само с основните фигури (basic shapes) в SVG. Приложението ви трябва да поддържа поне три от тях. Например можете да изберете да се поддържат линия, кръг и правоъгълник. За повече информация за това кои са базовите фигури, вижте https://www.w3.org/TR/SVG/shapes.html.

Дизайнът на приложението трябва да е такъв, че да позволява при нужда лесно да можете да добавите поддръжка на нови фигури. След като заредите фигурите, потребителят трябва да може да изпълнява дадените в следващия раздел команди, които добавят, изтриват или променят фигурите. Когато записвате фигурите във файл, трябва да генерирате валиден SVG файл.<br>

Операции: <br>
Open - Зарежда съдържанието на файл.<br>
Print -	Извежда на екрана всички фигури.<br>
Create -	Създава нова фигура.<br>
Erase	- Изтрива фигура.<br>
Translate	- Транслира една или всички фигури. Ако потребителят не посочи конкретна фигура, тогава се транслират всички фигури. Aко се посочи конкретна – променя се само тя.<br>
Within - Извежда на екрана всички фигури, които изцяло се съдържат в даден регион. Потребителят може да укаже какъв да бъде регионът – кръг или правоъгълник


Вашата програма трябва да позволява на потребителя да отваря файлове (open), да извършва върху тях някакви операции, след което да записва промените обратно в същия файл (save).  За целта, когато програмата ви се стартира, тя трябва да позволява на потребителя да въвежда команди и след това да ги изпълнява.
Както казахме по-горе, потребителят трябва да може да въвежда команди, чрез които да посочва какво трябва да се направи. Командите могат да имат нула, един или повече параметри, които се изреждат един след друг, разделени с интервали.
Освен ако не е казано друго, всяка от командите извежда съобщение, от което да е ясно дали е успяла и какво е било направено.<br>

Open <br>
Зарежда съдържанието на даден файл. Всички останали команди могат да се изпълняват само ако има успешно зареден файл.
> open file.svg <br>
Successfully opened file.svg <br>

Save <br>
Записва направените промени обратно в същия файл, от който са били прочетени данните.
> save <br>
Successfully saved in file.svg <br>

Exit<br>
Излиза от програмата. <br>
> exit<br>
Exit<br>

Примерен SVG файл figures.svg
```
<?xml version="1.0" standalone="no"?>
<!DOCTYPE svg PUBLIC "-//W3C//DTD SVG 1.1//EN"
  "http://www.w3.org/Graphics/SVG/1.1/DTD/svg11.dtd">
<svg>
  <rectangle x="5" y="5" width="10" height="10" fill="green" />
  <circle cx="5" cy="5" r="5" fill="blue" />
  <rectangle x="100" y="60" width="10" height="10" fill="red" />
  <rectangle x="1000" y="1000" width="10" height="20" fill="yellow" />
</svg>
```

Пример за работа на програмата
> open figures.svg <br>
Successfully opened figures.svg <br>

> print <br>
rectangle 5 5 10 10 green <br>
circle 5 5 5 blue <br>
rectangle 100 60 10 10 red <br>
rectangle 1000 1000 10 20 yellow <br>

> create rectangle 1000 1000 10 20 yellow <br>
Successfully created rectangle (4) <br>

> within rectangle 0 0 30 30 <br>
 rectangle 5 5 10 10 green <br>

> within circle 0 0 5 <br>
No figures are located within this figure <br>

> erase 2 <br>
Erased  (2) <br>

> print <br>
rectangle 5 5 10 10 green <br>
rectangle 100 60 10 10 red <br>
rectangle 1000 1000 10 20 yellow <br>

> erase 100 <br>
There is no figure number 100 <br>
> translate 10 100 <br>
Translated all figures <br>

> print <br>
rectangle 15 105 10 10 green <br>
rectangle 110 160 10 10 red <br>
rectangle 1010 1100 10 20 yellow <br>

> translate  rectangle 15 105 10 10 green 10 10  <br>

> print <br>
rectangle 25 115 10 10 green <br>
rectangle 110 160 10 10 red <br>
rectangle 1010 1100 10 20 yellow <br>

> save <br>
Successfully saved the changes in figures.svg <br>

> exit <br>
Exit


