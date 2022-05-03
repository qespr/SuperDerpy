I need to learn C and what is better motivation than Ponies? This probably won't go anywhere but it never hurts to try.

In case I'll get past few commits, here are some of my goals:

- [ ] Make a little bit better documentation
- [ ] Actually understand what is going on
- [ ] Find out what the next levels should have been like
- [ ] Make at least one new Full level

Original description:

------------------------------------------------------------------------------------------------

Become Derpy Hooves and fight with muffinzombies in this free software game in order to rescue Ponyville ponies so they can defeat
Discord once again!

Equestria is again under Discord's attack! Now he's using an army of muffinzombies to bring back chaos and lack of harmony into
ponies world. But he didn't think about some mare who knows everything about muffins...

*Super Derpy: Muffin Attack* is written in C and requires Allegro 5.0.6. Works on Windows, GNU/Linux and Mac OS X.

The game uses CMake as build system, so its building process is pretty typical.

Compilation:

	mkdir build; cd build
	cmake ..
	make

Running (from top directory):

	build/superderpy

Installation (as root):

	make install

For packaging information, read lib/README.txt

Written by Sebastian Krzyszkowiak <dos@dosowisko.net>
