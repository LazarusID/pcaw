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
---
name: systemcallsarebad
class: center middle
# Wait, My System Doesn't Have a millis() Function!

Sometimes we need a *test double*.

It's like a stunt double, but for your tests.

Link them in before system libraries, your test doubles are called first.
---
name: testdoubleflavors
class: right
# Test Doubles In A Rainbow of Fruit Flavors!

--
## Stubs
A simple function that can be linked in, but does nothing.

--
## Mocks
An object which can respond to actions from the system under test.

--
## Fake
An object which has the same interface as the real object, but a simpler implementation, such as an in memory database for a remote one.