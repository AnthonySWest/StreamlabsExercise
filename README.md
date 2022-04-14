Streamlabs Exercise

Please don't judge too harshly!

This electron/node stuff is completely foreign to me.

cmake is also new to me, so don't expect everything to be correct there, but it works.

I spent 20+ hours on this, so if its not to your liking, then it is what it is :)

The assignment didn't address how to package this for deployment, so, I'm stopping here due to the time already invested in this assignment.

Normally I don't store dlls and stuff in github, but, I don't know what you are expecting, or how you are expecting to easily test this, so included everything, except for the OBS source, but did include the OBS output (in same folder as "addonasw" in the electron folder).

This test app addressed all of the assignment items (except for bonus):

- Create an electron app (this thingy here).
- Make electron app interact with a native module (it may not do it correctly, but it works - manual addon install was done - in a real world scenario, there would need to be some deployment method, using npm, or something?).
- Make the native module interact with the obs library that I built (used cmake) (Are you aware that the OBS instructions for OBS on github don't work? That was fun lol).
- Expose an API in the C++ side that can be accessed by the electron app. I have no idea what the right way is to do this, but it appears to work.

Additional thoughts and items completed (due to my desire to learn more about this node stuff):

- In addition to exposing an object, also exposed a static function for additional learning.
- The assignment says it doesn't require node/electron experience. I beg to differ lol. Spent a lot of time reading docs before even starting. Have any of you tried this assignment lately? OBS doesn't build (without problem solving skills). Many node api examples don't work anymore, etc.
- The bonus steps seemed interesting, but, I spent way too much time on this already, and my kids miss me.
- I had fun working on this, but, it was certainly a challenge for all but the C++ files themselves lol.

Enjoy :)

Anthony S. West - 2022/04/13