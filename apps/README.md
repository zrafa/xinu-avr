### Several applications for getting started

```
example0 : basic Xinu app for quick start

example1 : write "hi" on the console


example2 :  example of creating processes in Xinu:
            sndA  --  repeatedly emit 'A' on the console without terminating
            sndB  --  repeatedly emit 'B' on the console without terminating

example3 : example of 2 processes executing the same code concurrently
            sndch  --  output a character on a serial device indefinitely

example4 : main, produce, consume
             n = 0;	/* external variables are shared by all processes
             main  --  example of unsynchronized producer and consumer processes
             produce  --  increment n 2000 times and exit
             consume  --  print n 2000 times and exit

example5 :  main, prod2, cons2 */
             n = 0;	/* external variables are shared by all processes
             main  --  producer and consumer processes synchronized with 
                       semaphores
             prod2  --  increment n 2000 times, waiting for it to be consumed
             cons2  --  print n 2000 times, waiting for it to be produced

shell : the Xinu Shell application
```

