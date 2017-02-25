//www.elegoo.com
//2016.12.8

// Define Pins - adjust values to suit your setup
#define BLUE 3
#define GREEN 5
#define RED 6

// Define maximum and minimum values
#define MAX 50
#define MIN 0

// Define colors (Pin# and current value)
struct color {
  int id, value;
  color(int i, int v){ id = i; value = v; };
} red(RED, MIN), blue(BLUE, MIN), green(GREEN, MIN);

// Declare additional variables and functions
int count = 6; // transition requires 1-3 iterations to complete any cycle
void transition(color a, color b, color c); // recursive transition between primary colors
void increase(color& c, int i); // raises pointed color output by specified integer
void decrease(color& c, int i); // lowers pointed color output by specified integer

// main setup
void setup()
{
  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(BLUE, OUTPUT);
  digitalWrite(RED, HIGH);  // default: cycle starts at red
  digitalWrite(GREEN, LOW);
  digitalWrite(BLUE, LOW);
}
// main loop
void loop()
{
  transition(red, green, blue);  // defines initial transition
}

// increase value of pointed color
void increase(color& c, int i)
{
  c.value += i;
  analogWrite(c.id, c.value);
}
//decrease value of pointed color
void decrease(color& c, int i)
{
  c.value -= i;
  analogWrite(c.id, c.value);
}

// describes transition from one primary color to the next
   // (default: starts with color a at max value, transitions to color b at max value) 
void transition(color a, color b, color c)
{
  // set initial values
  a.value = MAX;
  b.value = MIN;
  c.value = MIN;
  
  // define delay between forloop iterations
  #define delayTime 30

  // incremental transition
     // increase raises, decrease lowers light level of color by integer per iteration
  for(int i = MIN; i < (MAX); i += 1)
  {
    decrease(a,1);
    increase(b,1);
    delay(delayTime);
  }

  // recursion - after 6 iterations, returns to loop() to avoid infinite recursion
     // default: b becomes a, c becomes b, a becomes c
  if (--count > 0){
    transition(b,c,a);
  } else {
    count = 6;
  }
}

