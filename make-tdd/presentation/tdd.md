name: title
# Test Driven Development

<img src="TheaTestingCircuits.jpg" width="90%" />
---
name: whatistdd
class: center middle
# What Is Test Driven Development?

Code that runs quickly on your development workstation.

The fastest route to a shippable product.

How Nate and Clay make their daily bread.
---
title: redtest
class: center middle
## Write A Failing Test

It should be something you want to be true about your code.

If it doesn't fail, you did something wrong.

This state is called .red[Red]

---
title: greentest
class: center middle
## Make It Pass

Do the simplest thing possible.

Don't try to anticipate what you'll need later.  You'll miss important test cases if you do.

This state is called .green[Green]

---
title: refactor
class: center middle
## Refactor

Look for opportunities to make the code cleaner.

Only do this if all of your test are .green[green].

---
# What Does A Test Look Like?

```c
TEST(Controller, setup_byDefault_setsLastCheckedToCurrentTimer) {
  
  // Arranging Pre-Conditions
  timer_value_will_return(1, 75);

  // Execute the function we care about
  setup();

  // Test the results of the execution
  TEST_ASSERT_EQUAL(75, MOTOR_STATE.last_check);
}
```
???
This is a good example of the Arrange, Execute, Assert pattern for tests
---
name: abstractionftw
class: middle
# Abstract Away Your Actions to Hide System Calls

* Separate your program logic from the hardware control.

* Write tests of your program logic first, to capture your intent.

* Testing of implementation can be skipped if the hardware control functions are thin wrappers around system calls.
???
Good example of the clean interface this provides in `src/state_transition.c`
---
name: systemcallsarebad
class: center middle
# Wait, My System Doesn't Have a millis() Function!

Sometimes we need a *test double*.

It's like a stunt double, but for your tests.

Link them in before system libraries, your test doubles are called first.

???
Look at a simple mock, such as in `mock/mock_motor.c`
---
name: testdoubleflavors
class: right
# Test Doubles In A Rainbow of Fruit Flavors!

--
count: false
## Stubs
A simple function that can be linked in, but does nothing.

--
count: false
## Mocks
An object which can respond to actions from the system under test.

--
count: false
## Fake
An object which has the same interface as the real object, but a simpler implementation, such as an in memory database for a remote one.

---
name: usingtestdoubles
# When Do I Use a Test Double?

* When I am calling a system function I don't have on my build system.

* When I am calling a system function that I need to control the return value.

* When calling a function would introduce a dependency in my test unrelated to what I am testing.

* When I need to know the function I'm testing called another function.

---
name: creating
# How Do I Write a Mock

Mocks have a few properties:

* An object with the same interface as the object I am mocking.

* Setup functions or methods to control the behavior of the mock when it is called.

* Inspection functions or methods to examine our interactions with the mock.