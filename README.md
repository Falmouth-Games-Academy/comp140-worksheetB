# The Page
## Proposal: Hand Puppet The Game
### Concept
You play as a hand with a laser-beam spewing mouth in a 2D side-scrolling platform game taking place on campus. Using a bareboned motion controller of straps and rings--with your hand shaped like a talking mouth--you bounce up and down to move along, and use a crouch-jump motion to jump. To use your laser beam, open your mouth wide. The laser beam will make a satisfying BLAAAAAARGH with a vibration feedback effect, and an additional effect of vaporising any enemy foolish enough to stand in your way.  

The storyline is brief but simple: the assignment is due tomorrow and the game hasn't been made yet. Your goal is to get to the studio on time to make the game before it's too late. The gameplay revolves around destroying evil mutant 'animals' (shadow puppets) with your laser, but there may be some RPG elements. For example, you may be sent on a mission by the Monday sock to find his missing partner. In fact, socks might be a regular collectible. Getting a pair will unleash new powers.  

As a stretch goal, a Transformation ability will add some diversity to the gameplay. By changing your hand from a puppet stance into a gun stance, you can transform into the murderous Shorthand, firing bullets by pulling your middle finger. Changing your hand to a fist will introduces the super-strong Fistfist, who can punch enemies and objects into oblivion, but is vulnerable on its back end.  

The character art style will be photos of hands, while the background art style will be photos of various areas on the campus backdrop, with paper assets on sticks bouncing around. Alternatively, the background art may be parallax-layered photos of the campus. The camera will zoom in and out where appropriate, giving a feeling of scale. You're a small hand in a big, big world, and you must journey far and wide in order to achieve your goal of making the game.  

### Controller overview
The controller will require the following components:  

**Flex sensor:**: To detect whether your mouth is open, or your trigger finger is being pulled. This must be connected between the player's thumb and middle finger somehow.  
**Accelerometer:**: To detect whether you're bouncing up and down to move along, as well as the angle you're aiming at. Depending on the orientation of the sensor,  it _may_ be possible to use this to detect whether you're turning around, by testing centrifugal force. This would be challenging though, and from a programming and accuracy standpoint a compass would be preferable.
**Compass (optional):**: To detect which way your hand is pointing and therefore the direction of the player character.  
**Vibrating motor:**

Based on the prerequisites above, the controller would work best as either a glove or a more bareboned set of components that can very easily be attached to the hand. For the latter, which would most likely feel more immersive for the player (as opposed to wearing a hand puppet of a hand), perhaps the ideal way to make attach them would be to fix a finger and thumb ring around the bend sensor, while fixing the compass and accelerometer to a wide rubber band which will go around the hand.

Alternatively, it may be novel to make a hand puppet that is, indeed, just a rubber hand. 

# Extra to the Page (no need to read this)
We were asked to write a page for the proposals, and indeed, all of the text below is part of the page. I have cut it out so that this page does not exceed a page, however, either way it is unlikely to exceed a page as it is, indeed, a page. Further to this though, one could observe that this page does not fit within one monitor screen. This is true, however it could be strongly argued that a monitor is not a page. To exceed a page would require that more than one page be stuck to the screen, perhaps with some sticky tape.  

### Quirks
* When you defeat enemies, they crumble into pieces.  
* The entire art style could be based on photos of props and puppets.  
* The more you open the mouth, the wider and more destructive your lazer. However, this expends more at a time.  
* **Mirror enemy.** This enemy is really dumb and tends to hold mirrors in random directions. If you shoot him at the right time your shot could bounce of multiple enemies, destroying them all.  
* Talk to a character. **Nod for yes and shake head for no.**  
* **Left-handed mode:** Entire game is flipped around to make it easier to navigate the level. (Hands have a bias for going inwards more than outwards)  
* **Sock puppet AI:** Meet Monday, Tuesday, Wednesday, Thursday and Friday as they try to find their missing partners.  
* **Classmate actors:** Ask around to see who wants to voice act their own hands as NPCs.  
* **Story: Game could use a short story**... try to finish the concept and action sequences by **next Fri 16th**.  
* **Fully awkwardly 3D hand rendering:** The direction of your hand is displayed on the screen in 8 intervals.  

### Characters
* **Sales hand:** Please, feel free to browse our collection anytime, because we've got lots of great products just waiting for you to not care about... (note: only says this if you're walking away from him while he's talking).  


### Potential music element
The game could be an infinite scroller with a background tune where cats fly in at different heights from the right-hand side. You need to open wide and unleash your lazer on them as they cross a certain point on your screen. Some of the cats are really long and you'll need to hold your lazer long enough. The higher the combo, the more apocalyptically powerful your lazer is on-screen and the stronger the vibration.  

The vibration should give a satisfying feel as you obliterate cats. Perhaps they could come from the left side as well?  

### Mechanics
**Bounce up and down:** Move foward. If possible, make game as responsive as possible. Track the motion of the accelerometer along a sine wave and the character on-screen will bounce along with it and forward.  
**Small crouch, fast motion up:** Jump, spring-style. The motion is like pushing down on a spring and then bouncing back up.
**Open mouth:** Fire super poweredlazer  
**Collect blitties:** Blitties are pretty, collect more to charge ur lazer for a more powerful attack.  
**Vibrate**--when you open your mouth?  
