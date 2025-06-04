# 42 Philosophers Project by clai-ton

The classic [dining philosophers problem](https://en.wikipedia.org/wiki/Dining_philosophers_problem).

Check for data races with a compiler flag:
`fsanitize=thread`
OR:
`valgrind --tool=helgrind ./philo <args>`
`valgrind --tool=drd ./philo <args>`
and of course, check leaks:
`-fsanitize=address -g`
`valgrind --leak-check=full ./philo <args>`

## Interesting reads

[42 cursus gitbook](https://42-cursus.gitbook.io/guide/rank-03/philosophers)

[Article by ruinadd with mutex playlist](https://medium.com/@ruinadd/philosophers-42-guide-the-dining-philosophers-problem-893a24bc0fe2)

[Article by oceanO with video](https://medium.com/@jalal92/the-dining-philosophers-7157cc05315)

[Article by nesvoboda](https://private-rooster-996.notion.site/philosophers-VM-c60be9c836084edfbcd9c07e29b429c4)

[Article by Mannbell](https://m4nnb3ll.medium.com/the-dining-philoshophers-an-introduction-to-multitasking-a-42-the-network-project-34e4141dbc49)

[Breakdown and code by TommyJD93](https://github.com/TommyJD93/Philosophers)

## Testers and Visualizers

[Tester by newlinuxbot](https://github.com/newlinuxbot/Philosphers-42Project-Tester/tree/master)

['Socrates' Tester by nesvoboda](https://github.com/nesvoboda/socrates?tab=readme-ov-file)

[42PhilosophersHelper by azerfaou](http://github.com/AbdallahZerfaoui/42PhilosophersHelper)

[Visualizer by nafuka11](https://github.com/nafuka11/philosophers-visualizer)
