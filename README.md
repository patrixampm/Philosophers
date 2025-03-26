## Philosophers
### The dining philosophers problem in C

This project is my own solution to the classic **dining philosophers problem**, where one or more philosophers are sat at a round table with a dish in the middle. Philosophers can only eat, think or sleep, and they can only carry out one of these actions at a time.

Each philosopher has **one fork**, but **needs two forks** to eat, and so must borrow the neighbouring fork (to the left or to the right). When one philosopher finishes eating, the forks are left on the table and she/he immediately starts to sleep. After sleep comes thinking time, and this process will repeat until one or more philosophers die due to hunger, or each one has eaten a previously established number of times.

My program receives a **4 arguments**, and **optionaly one extra argument**, described as follows:
- number_of_philosophers: not much to explain here.
- time_to_die: milliseconds a philosopher can live without eating.
- time_to_eat: milliseconds a philosopher spends eating.
- time_to_sleep: milliseconds a philosopher spends sleeping.
- number_of_times_each_philosopher_must_eat: this is the optional argument, and it sets the minimum number of times each philisopher must eat in order for the cycle to stop.

There is a *time_to_think*, which is the spearing time he/she has between sleeping and picking his/her forks up to eat.

The aim is to avoid any philosophers from dying of hunger. This will depend, of course, on the milliseconds set in the arguments, but if enough time is given, my program will have pair and impair philosophers take turns to use their forks to eat, and the cycle will go on as long as you let it.

### HOW?

Well, each fork is a resource shared by **concurrent threads** (the philisophers), and so a **mutex** must be used to lock each shared resource (fork or other). Also other resources should be locked, like printing to the terminal, and modifying shared variables that flag the death of a philosopher, making the program stop. This is done to prevent data races.

I used the **PTHREADS library** to create and handle both threads and mutex's.

If you want to download my repo, you can clone it, execute:
```
make
```
in the root of the repo, and execute the program with (for example):
```
./philo 8 800 200 200 4
```
where ./philo executes the program, 8 is the number of philosophers, 800 milliseconds to die of hunger, 200 milliseconds to eat, 200 milliseconds to sleep, and 4 are the times, at least, each philosopher should eat.

Enjoy messing around with the arguments, or the code!