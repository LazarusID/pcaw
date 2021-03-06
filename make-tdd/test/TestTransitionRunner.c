#include "unity.h"
#include "unity_fixture.h"

TEST_GROUP_RUNNER(Transition) {
  // state_bottom
  RUN_TEST_CASE(Transition,
                stateBottom_byDefault_setsDirectionUpAndTurnsMotorsUp);
  RUN_TEST_CASE(Transition,
                stateBottom_byDefault_turnsOffDownMotorWaitsTurnsOnUpMotor);
  RUN_TEST_CASE(Transition,
                stateBottom_byDefault_setsLastCheckedAfterTimerWait);

  // state_switch_on
  RUN_TEST_CASE(
      Transition,
      stateSwitchOn_whenDurationSet_turnsUpOffDownOnSetsDirectionDown);
  RUN_TEST_CASE(
      Transition,
      stateSwitchOn_whenDurationIsUnset_setsDurationToTimerValueAndLastCheckedToCurrentTimerValue);
  RUN_TEST_CASE(Transition,
                stateSwitchOn_byDefault_turnsUpMotorOffWaitsTurnsDownMotorOn);
  RUN_TEST_CASE(Transition,
                stateSwitchOn_whenDurationSet_callsWaitBeforeGettingTime);
}
