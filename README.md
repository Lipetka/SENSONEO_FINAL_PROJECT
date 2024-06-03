This is is a "final" project done on nRF52840 for learning purposes.

This project should showcase some basic and advanced uses of ZephyrOS with as extensive commentary as possible.

The goal is to use this project as an knowledge base for other project (if I forget how to do something I will find it here).


Task of project:

-  Utilize all 4 buttons and 4 Leds
    - **LED 0** and **LED 1** will alternatively blink
    - The speed of alternating will be **decreased/increased** by **button 0** and **button 1**
    - Blinking is tied to timer interrupts, button clicks are also driven by interrupts
    - ~~Whole blinking task is ran in separate "thread"~~

- Utilize state machine
    _State machine is one of my most favorite ways to code basically anything._
    - **LED 2** and **LED 3** will light up based on current state machine state
    - There will be 4 states represented by led lights (0,0)(1,0)(1,1)(0,1)
    - ~~Make the state machine run in separate "thread"~~

_More tasks will be thought out while learning tutorials and reading more docs._

