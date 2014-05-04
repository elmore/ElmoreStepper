ElmoreStepper
=============

Arduino stepper motor library for 28BYJ-48 motors available on ebay etc

Based on http://arduino.cc/en/reference/stepper which only works with 4 code steppers. I also wasnt enamoured with the code so I messed around with it (Im not a very competent c++ programmer so its probably not great even now but I think its structed a little nicer). 

The 28BYJ-48 I have uses 8 codes. It will work with the Arduino lib but is easy to stall and isnt very fast. With the 8 codes implemented its much more torquey and quite a bit faster.

Its currently only able to do the 8 codes but I will put the 4 code and 2/4 wire input complexity back in later :)
