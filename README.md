## Stack

Visualisation of stack and two main functions pop and push:<br />

![hqdefault](https://github.com/CiberMonah/Stack/assets/142305833/610612db-2429-48d5-b4b7-f5883e6516bb)

## Protections
# Canary protection of stack
Our stack looks like:
![CANARY1](https://github.com/CiberMonah/Stack/assets/142305833/c60fa17b-7871-4d1d-bd23-044f4aeb39e5)<br />
Then malware starts to rewrite stack
![CANARY2](https://github.com/CiberMonah/Stack/assets/142305833/58e049e9-6c7c-4424-8efb-13c2e929157f)<br />
And rewrite...<br /><br />
![CANARY3](https://github.com/CiberMonah/Stack/assets/142305833/e1a3fc05-03c4-4197-9a4a-d758a5d304b1)<br />
But! Stack can detect if canary is dead and detect malware:)<br />
Everything is good<br />
# Hash protection
Our stack look like numbers in a row, so we can calculate another number with special algorythm\n<br />
So this hash number is unique<br />
And after every operation push or pop we can count hash and compare it with hash number in stack to detect rewritings<br />

