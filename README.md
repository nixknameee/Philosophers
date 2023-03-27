# Philosophers

This project is a simulation of the dining philosophers problem, which is a classic synchronization problem in computer science. The goal of the project is to implement a solution that allows a fixed number of philosophers to share a table and eat spaghetti without deadlocking or starving.
The dining philosophers problem is a classic example in computer science of a synchronization problem that arises when multiple processes or threads compete for shared resources. It is used to illustrate the challenges of concurrent programming and the need for synchronization mechanisms to prevent deadlocks and resource starvation.

In the dining philosophers problem, a group of philosophers sit around a circular table with a bowl of spaghetti in the middle. Each philosopher alternates between thinking and eating, but they can only eat if they have two forks, one on each side of them. If a philosopher cannot get both forks, they must wait until the forks are available.

The challenge is to implement a solution that prevents deadlocks, where all philosophers are waiting for a fork that will never be released, and resource starvation, where some philosophers never get to eat because they are always waiting for a fork.

One popular solution to the dining philosophers problem is to use a resource hierarchy, where each fork is numbered, and the philosophers always try to pick up the lower-numbered fork first before the higher-numbered one. This ensures that no two philosophers can pick up the same two forks simultaneously, preventing deadlocks.

Another solution is to use a waiter, who manages the allocation of forks to the philosophers and ensures that no more than four philosophers are eating at the same time. This approach also prevents deadlocks and ensures that all philosophers get a chance to eat.
# Installation

To run this project, you will need to have the following tools installed on your system:

    C compiler (e.g. GCC)
    Make build system

Once you have these tools installed, you can clone the repository and build the project by running the following commands:

bash

> git clone https://github.com/nixknameee/philosophers.git
> cd philosophers
> make

This will compile the program and create an executable file called philosophers.
# Usage

To run the program, you need to provide three arguments: the number of philosophers, the time in milliseconds when someone dies if they don't eat, and the time in milliseconds it takes to eat.

css

> ./philosophers [number_of_philosophers] [time_to_die] [time_to_eat]

For example, to run the program with 5 philosophers who die after 800 milliseconds without eating and take 200 milliseconds to eat, you would run:

bash

> ./philosophers 5 800 200

# Features

This implementation of the dining philosophers problem includes the following features:

    Philosopher threads that represent the philosophers and their behaviors
    Fork mutexes that represent the forks and their availability
    A death timer that kills philosophers who don't eat for a certain amount of time
    A logging system that reports the status of each philosopher and their actions

# Credits

This project was completed as part of the curriculum at 42, a software engineering school. The code was written by me and @gkonstan.
